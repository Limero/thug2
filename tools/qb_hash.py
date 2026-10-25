#!/usr/bin/env python3
"""Neversoft QB script hash, reverse-engineered from fn_8000A778 in the DOL.

Disassembly:
    8000A788: lbz r0, 0(r3)        # c = *str
    8000A78C: li r10, -1           # hash = 0xFFFFFFFF
    8000A790: addi r3, r3, 1       # str++
    8000A794: extsb r8, r0
    8000A798: cmpwi r8, 0          # if c == 0 -> done
    8000A7A0: lis r9, -0x7fd0      # r9 = 0x80300000
    8000A7A4: addi r7, r9, -0x5c4  # table = 0x802FFA3C (256 x u32)
    8000A7A8: addi r0, r8, -0x41   # tolower if in [A-Z]
    8000A7AC: cmplwi r0, 0x19
    8000A7B4: addi r0, r8, 0x20
    8000A7BC: cmpwi r8, 0x2f       # '/' -> '\\'
    8000A7C4: li r8, 0x5c
    8000A7C8: xor r0, r10, r8      # idx = (hash ^ c) & 0xFF
    8000A7D0: rlwinm r0, r0, 2, 0x16, 0x1d
    8000A7D4: srwi r10, r10, 8     # hash >>= 8
    8000A7D8: lwzx r11, r7, r0     # t = table[idx]
    8000A7E8: xor r10, r11, r10    # hash = t ^ (hash >> 8)

Verified against .prg embedded pairs:
    qb_hash('anims\\Ped_M\\Ped_M_CheerIdle6.ska.ngc') == 0x7E62B845
    qb_hash('LoadScene') == 0x3D559E7D
"""
import struct
import sys
import os
import re

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

TABLE_ADDR = 0x802FFA3C
TABLE_WORDS = 256


def load_table(dol_bytes):
    """Extract the 256-entry u32 hash table from raw DOL bytes."""
    # locate the section containing TABLE_ADDR
    offs = struct.unpack_from('>18I', dol_bytes, 0)
    addrs = struct.unpack_from('>18I', dol_bytes, 0x48)
    sizes = struct.unpack_from('>18I', dol_bytes, 0x90)
    for i in range(18):
        if addrs[i] <= TABLE_ADDR < addrs[i] + sizes[i]:
            fo = offs[i] + (TABLE_ADDR - addrs[i])
            data = dol_bytes[fo:fo + TABLE_WORDS * 4]
            if len(data) < TABLE_WORDS * 4:
                raise ValueError('table truncated')
            return list(struct.unpack('>%dI' % TABLE_WORDS, data))
    raise ValueError('table address 0x%X not in any DOL section' % TABLE_ADDR)


def qb_hash(name, table):
    h = 0xFFFFFFFF
    for b in name.encode('latin1'):
        # lowercase A-Z
        if 0x41 <= b <= 0x5A:
            b += 0x20
        # '/' -> '\\'
        if b == 0x2F:
            b = 0x5C
        h = table[(h ^ b) & 0xFF] ^ (h >> 8)
        h &= 0xFFFFFFFF
    return h


def main():
    dol = open('orig/G2TE52/sys/main.dol', 'rb').read()
    table = load_table(dol)
    print('table loaded: %d words from 0x%X' % (len(table), TABLE_ADDR))

    # Verified pairs: [hash][string] entries byte-extracted from pre/anims.prg.
    # (The LoadScene constant 0x3D559E7D is NOT the hash of 'LoadScene' — it is
    # an internal symbol hash loaded by that function; don't use it as a check.)
    checks = [
        (r'anims\Ped_M\Ped_M_CheerIdle6.ska.ngc', 0x7E62B845),
        (r'anims\Ped_M\Ped_M_CheerIdle5.ska.ngc', 0x47EF8480),
        (r'anims\Ped_M\Ped_M_CheerIdle2.ska.ngc', 0x238EE949),
        (r'anims\Ped_M\Ped_M_CheerIdle3.ska.ngc', 0x34F5FD0A),
        (r'anims\Ped_M\Ped_M_CheerIdle4.ska.ngc', 0x509490C3),
    ]
    ok = 0
    for name, want in checks:
        got = qb_hash(name, table)
        status = 'OK' if got == want else 'FAIL'
        if got == want:
            ok += 1
        print('%s qb_hash(%r) = 0x%08X (want 0x%08X)' % (status, name, got, want))
    print('%d/%d verified' % (ok, len(checks)))
    return 0 if ok == len(checks) else 1


# ---- shared QB-constants helpers (gen/apply tools + fill_wip_drafts) ----

CONSTANTS_H = os.path.join(os.path.dirname(__file__), '..', 'include',
                           'dolphin', 'qb_constants.h')

_const_map = None


def constants_map():
    """Parse include/qb_constants.h -> {int value: macro name}."""
    global _const_map
    if _const_map is None:
        _const_map = {}
        try:
            for line in open(CONSTANTS_H):
                m = re.match(r"#define\s+(QB_[A-Za-z0-9_]+)\s+0x([0-9A-Fa-f]{8})\b", line)
                if m:
                    _const_map[int(m.group(2), 16)] = m.group(1)
        except FileNotFoundError:
            pass
    return _const_map


_LIT_RE = re.compile(r"\b0x([0-9A-Fa-f]{8})U?\b")


def subst_qb_constants(text):
    """Rewrite magic 0xXXXXXXXX literals -> QB_<NAME> constants.

    Only non-comment lines; literals inside string literals are left alone.
    Returns (new_text, n_rewritten). Byte-safe: constants are #defines that
    expand to the identical literal, so code bytes never change.
    """
    cmap = constants_map()
    if not cmap:
        return text, 0
    out = []
    n = 0
    for ln in text.splitlines(keepends=True):
        if ln.lstrip().startswith('//'):
            out.append(ln)
            continue
        # block-comment state: rewrite only the parts of the line NOT inside
        # a /* ... */ comment (m2c strips these early, but hand-edited drafts
        # may carry a mid-line comment containing a literal).
        res = []
        i = 0
        in_str = False
        in_blk = False
        for m in _LIT_RE.finditer(ln):
            seg = ln[i:m.start()]
            res.append(seg)
            for ch in seg:
                if ch == '"':
                    in_str = not in_str
            # toggle block-comment state over the segment (cheap, single char
            # passes are fine for draft-sized lines)
            k = 0
            while k < len(seg):
                if not in_blk and seg.startswith('/*', k):
                    in_blk = True
                    k += 2
                elif in_blk and seg.startswith('*/', k):
                    in_blk = False
                    k += 2
                else:
                    k += 1
            v = int(m.group(1), 16)
            name = cmap.get(v)
            if name is not None and not in_str and not in_blk:
                res.append(name)
                n += 1
            else:
                res.append(m.group(0))
            i = m.end()
        res.append(ln[i:])
        out.append(''.join(res))
    return ''.join(out), n


_PLACEHOLDER_RE = re.compile(r"\bQB_UNKNOWN_0x([0-9A-Fa-f]{8})\b")


def subst_qb_placeholders(text):
    """Rename QB_UNKNOWN_0x<VAL> placeholder macros to the real QB_<NAME>
    once the header names that value (an identification happened).

    Same comment/string discipline as subst_qb_constants (code-only, string
    literals and comments untouched). Idempotent: after a rename the token is
    gone, and an already-named value has no placeholder left to match.
    Returns (new_text, n_renamed)."""
    cmap = constants_map()
    if not cmap:
        return text, 0
    out = []
    n = 0
    for ln in text.splitlines(keepends=True):
        if ln.lstrip().startswith('//'):
            out.append(ln)
            continue
        res = []
        i = 0
        in_str = False
        in_blk = False
        for m in _PLACEHOLDER_RE.finditer(ln):
            seg = ln[i:m.start()]
            res.append(seg)
            for ch in seg:
                if ch == '"':
                    in_str = not in_str
            k = 0
            while k < len(seg):
                if not in_blk and seg.startswith('/*', k):
                    in_blk = True
                    k += 2
                elif in_blk and seg.startswith('*/', k):
                    in_blk = False
                    k += 2
                else:
                    k += 1
            v = int(m.group(1), 16)
            name = cmap.get(v)
            if (name is not None and not name.startswith('QB_UNKNOWN_0x')
                    and not in_str and not in_blk):
                res.append(name)
                n += 1
            else:
                res.append(m.group(0))
            i = m.end()
        res.append(ln[i:])
        out.append(''.join(res))
    return ''.join(out), n


if __name__ == '__main__':
    sys.exit(main())
