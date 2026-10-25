#!/usr/bin/env python3
"""Post-link patch for THUG2 (G2TE52) matching decomp build.

The original game was compiled with -sdata2 0, so ALL small data (including
the constants in DOL section 11 @ 0x803CAF80) is addressed via r13 (SDA base
0x803D2280). dtk's read-only heuristic names that region `.sdata2`, so mwld
emits r2-based accesses against _SDA2_BASE_ = 0x803D2F80 instead.

Since the built SDA2 base (0x803D2F80) and the original SDA base (0x803D2280)
differ by exactly +0xD00, the patch:

  1. rewrites every r2-based small-data access to r13, adding 0xD00 to the
     displacement (target address unchanged -> bytes match the original), and
  2. rewrites the init's r2 setup from 0x803D2F80 to the original 0x803E2280.

Only instructions whose resolved target lies inside the second small-data
section (0x803CAF80..0x803CC200) are touched, so embedded data inside .text
can never be corrupted.

Usage: patch_dol.py <main.dol>   (patches in place)
"""
import struct
import sys

R13_BASE = 0x803D2280  # SDA base (identical in both builds)
BUILT_R2 = 0x803D2F80  # mwld default _SDA2_BASE_: _f_sdata2 (0x803CAF80) + 0x8000
ORIG_R2 = 0x803E2280   # original r2 init value
DELTA = BUILT_R2 - R13_BASE  # 0xD00

# Second small-data region (dtk's .sdata2 == original .sdata constant pool)
SDATA2_START = 0x803CAF80
SDATA2_END = 0x803CC200

# D-form opcodes where RA is a base register and the low 16 bits are a disp.
# For int loads/stores RD is a GPR; for FP loads/stores RD is an FPR.
MEM_OPS = {
    32: "lwz", 33: "lwzu",
    34: "lbz", 35: "lbzu",
    36: "stw", 37: "stwu",
    38: "stb", 39: "stbu",
    40: "lhz", 41: "lhzu",
    42: "lha", 43: "lhau",
    44: "sth", 45: "sthu",
    46: "lmw", 47: "stmw",
    48: "lfs", 49: "lfsu",
    50: "lfd", 51: "lfdu",
    52: "stfs", 53: "stfsu",
    54: "stfd", 55: "stfdu",
}
# Integer MEM_OPS (RD is a GPR; loading into r2 itself would be unusual)
INT_MEM_OPS = set(range(32, 48))
ADDI_OPS = {14: "addi", 12: "addic", 13: "addic."}
LIS = 15   # lis rD, imm (addis rD, 0, imm)
ORI = 24   # ori rA, rS, imm


def sign16(v: int) -> int:
    return v - 0x10000 if v >= 0x8000 else v


def find_init_r2_setup(data: bytearray, off: int, addr: int, size: int) -> int:
    """Return the r2 value the init setup computes, or None if not found."""
    pos = 0
    while pos + 4 <= size:
        word = struct.unpack_from(">I", data, off + pos)[0]
        op = word >> 26
        rd = (word >> 21) & 0x1F
        ra = (word >> 16) & 0x1F
        disp = word & 0xFFFF
        if ra == 2 and rd == 2 and op == ORI:
            for back in range(1, 5):
                bp = pos - back * 4
                if bp < 0:
                    break
                w = struct.unpack_from(">I", data, off + bp)[0]
                if (w >> 26) == LIS and ((w >> 21) & 0x1F) == 2:
                    return ((w & 0xFFFF) << 16) | disp
        pos += 4
    return None


def main() -> None:
    if len(sys.argv) != 2:
        print(__doc__)
        sys.exit(1)
    path = sys.argv[1]
    data = bytearray(open(path, "rb").read())

    offs = struct.unpack_from(">18I", data, 0)
    addrs = struct.unpack_from(">18I", data, 0x48)
    sizes = struct.unpack_from(">18I", data, 0x90)

    # Sanity: section 0 must be the entry section (.init)
    entry = struct.unpack_from(">I", data, 0xE0)[0]
    assert addrs[0] <= entry < addrs[0] + sizes[0], (
        f"Entry point 0x{entry:X} not in section 0; DOL layout unexpected"
    )

    # Sanity: the init's r2 setup must compute BUILT_R2, otherwise the +0xD00
    # displacement math below would be wrong. Fail fast instead of letting the
    # final hash check catch it.
    actual_r2 = find_init_r2_setup(data, offs[0], addrs[0], sizes[0])
    assert actual_r2 == BUILT_R2, (
        f"Init r2 setup computes 0x{actual_r2:X}, expected 0x{BUILT_R2:X}; "
        f"refusing to patch with stale constants"
    )

    patched_accesses = 0
    skipped_data = 0
    patched_init = 0

    # Sections 0 (.init) and 1 (.text) are the only code sections
    for sec_idx in (0, 1):
        off, addr, size = offs[sec_idx], addrs[sec_idx], sizes[sec_idx]
        pos = 0
        while pos + 4 <= size:
            word = struct.unpack_from(">I", data, off + pos)[0]
            op = word >> 26
            rd = (word >> 21) & 0x1F
            ra = (word >> 16) & 0x1F
            disp = sign16(word & 0xFFFF)

            if ra == 2 and op in MEM_OPS and not (op in INT_MEM_OPS and rd == 2):
                # Memory access via r2. Only patch if the target lies inside
                # the sdata2 region (this rejects embedded data in .text).
                target = BUILT_R2 + disp
                if SDATA2_START <= target < SDATA2_END:
                    new_word = (word & ~(0x1F << 16)) | (13 << 16)
                    new_disp = disp + DELTA
                    assert -0x8000 <= new_disp <= 0x7FFF, (
                        f"disp out of range @ {addr + pos:#010x}: {new_disp:#x}"
                    )
                    new_word = (new_word & 0xFFFF0000) | (new_disp & 0xFFFF)
                    struct.pack_into(">I", data, off + pos, new_word)
                    patched_accesses += 1
                else:
                    skipped_data += 1
            elif ra == 2 and rd != 2 and op in ADDI_OPS:
                target = BUILT_R2 + disp
                if SDATA2_START <= target < SDATA2_END:
                    new_word = (word & ~(0x1F << 16)) | (13 << 16)
                    new_disp = disp + DELTA
                    assert -0x8000 <= new_disp <= 0x7FFF, (
                        f"disp out of range @ {addr + pos:#010x}: {new_disp:#x}"
                    )
                    new_word = (new_word & 0xFFFF0000) | (new_disp & 0xFFFF)
                    struct.pack_into(">I", data, off + pos, new_word)
                    patched_accesses += 1
                else:
                    skipped_data += 1
            elif ra == 2 and rd == 2 and op == ORI:
                # ori r2, r2, imm: look back for the matching "lis r2, hi"
                for back in range(1, 5):
                    bp = pos - back * 4
                    if bp < 0:
                        break
                    w = struct.unpack_from(">I", data, off + bp)[0]
                    if (w >> 26) == LIS and ((w >> 21) & 0x1F) == 2:
                        hi = w & 0xFFFF
                        value = (hi << 16) | (disp & 0xFFFF)
                        if value == BUILT_R2:
                            new_hi = (ORIG_R2 >> 16) & 0xFFFF
                            new_lo = ORIG_R2 & 0xFFFF
                            struct.pack_into(
                                ">I", data, off + bp, (LIS << 26) | (2 << 21) | new_hi
                            )
                            struct.pack_into(
                                ">I", data, off + pos,
                                (ORI << 26) | (2 << 21) | (2 << 16) | new_lo,
                            )
                            patched_init += 1
                        break
            pos += 4

    print(
        f"{path}: patched {patched_init} init r2 setup(s), "
        f"{patched_accesses} r2->r13 access(es), skipped {skipped_data} non-sdata r2 match(es)"
    )
    open(path, "wb").write(data)


if __name__ == "__main__":
    main()
