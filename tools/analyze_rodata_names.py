#!/usr/bin/env python
"""Extract the rodata2 string name tables from the THUG2 GC DOL.

The DOL's .rodata2 section (sec 8, 0x8028FB60) holds read-only string data
and float constants.  Three pointer tables in .data reference the strings:

  T1 0x80301B50  file-type extension names (BIN/COL/SCN/GEOM/MDL/SKA/...)
  T2 0x80303030  level-event names (LevelEvents/... + Story/...)
  T3 0x80303464  SCRIPT COMMAND REGISTRY: 1327 x {const char *name, void (*func)()}

T3 is the goldmine: each 8-byte entry pairs a command name with the address
of its implementation function, so it provides original C function names
for the fn_XXXXXXXX symbols (e.g. "LoadScene" -> fn_80118DF8).

Output:
  docs/rodata2-script-command-registry.tsv   (name, func_addr, fn_sym, size, decompiled)
  stdout summary with per-table consumer counts

Usage:  tools/venv/bin/python tools/analyze_rodata_names.py
"""
import bisect
import os
import re
import struct

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DOL = os.path.join(ROOT, 'orig/G2TE52/sys/main.dol')
SYMS = os.path.join(ROOT, 'config/G2TE52/symbols.txt')
OUT_TSV = os.path.join(ROOT, 'docs/rodata2-script-command-registry.tsv')
SRCDIR = os.path.join(ROOT, 'src')

D = open(DOL, 'rb').read()
offs = struct.unpack_from('>18I', D, 0)
addrs = struct.unpack_from('>18I', D, 0x48)
sizes = struct.unpack_from('>18I', D, 0x90)

T_S, T_E = addrs[1], addrs[1] + sizes[1]        # .text
RO_S, RO_E = addrs[8], addrs[8] + sizes[8]      # .rodata2
DA_S, DA_E = addrs[9], addrs[9] + sizes[9]      # .data

# ---- fn symbols ----
fns = []  # (start, end, name)
for line in open(SYMS):
    m = re.match(r'^(fn_[0-9A-F]{8}) = \.text:0x([0-9A-F]+); // type:function size:0x([0-9A-Fa-f]+)', line)
    if m:
        s = int(m.group(2), 16)
        fns.append((s, s + int(m.group(3), 16), m.group(1)))
fns.sort()
starts = [f[0] for f in fns]


def covering(addr):
    i = bisect.bisect_right(starts, addr) - 1
    if i >= 0 and fns[i][0] <= addr < fns[i][1]:
        return fns[i][2]
    return None


def read_str(addr):
    if not (RO_S <= addr < RO_E):
        return None
    off = offs[8] + (addr - RO_S)
    j = off
    while j < offs[8] + sizes[8] and 32 <= D[j] < 127:
        j += 1
    s = D[off:j].decode('latin1')
    return s if len(s) >= 2 else None


def w32(da):
    if not (DA_S <= da < DA_E - 3):
        return None
    return struct.unpack_from('>I', D, offs[9] + (da - DA_S))[0]


def func_bytes(addr, size):
    """Raw bytes of a .text function from the DOL."""
    if not (T_S <= addr < T_E) or size <= 0:
        return b''
    off = offs[1] + (addr - T_S)
    end = min(off + size, offs[1] + sizes[1])
    return D[off:end]


def is_stub(addr, size):
    """True if the function is an 8-byte placeholder: `li rD, imm; blr`.

    THUG2's GC build ships auto-generated stubs for script commands whose
    real implementation is stripped from this platform (returns a hardcoded
    1/0). 72 of 1185 registry funcs match this exactly.
    """
    if size != 8:
        return False
    b = func_bytes(addr, size)
    if len(b) != 8:
        return False
    w0, w1 = struct.unpack_from('>II', b, 0)
    # addi rD, r0, imm  (li form)  +  blr
    return (w0 >> 26) == 14 and ((w0 >> 16) & 0x1F) == 0 and w1 == 0x4E800020


def extract_registry(lo, hi):
    """Walk the 8-byte {name, func} table; return [(name, func_addr, fn_sym)].

    The table is exactly 1327 x 8-byte entries from 0x80303464 to 0x80305DDC.
    Entries whose func slot is 0/NULL (command aliases, registration-only
    names) still emit a row with func_addr=None.
    """
    entries = []
    da = lo
    while da < hi:
        v = w32(da)
        if v is not None and RO_S <= v < RO_E and (s := read_str(v)):
            w = w32(da + 4)
            if w is not None and T_S <= w < T_E:
                entries.append((s, w, covering(w)))
            else:
                entries.append((s, None, None))
        da += 8
    return entries


def extract_names(lo, hi):
    """Walk a plain string-pointer table (no func pairs); return [name]."""
    names = []
    da = lo
    while da < hi:
        v = w32(da)
        if v is None:
            break
        if RO_S <= v < RO_E and (s := read_str(v)):
            names.append(s)
        da += 4
    return names


def main():
    ext = extract_names(0x80301B50, 0x80301BAC)
    events = extract_names(0x80303030, 0x8030313C)
    cmds = extract_registry(0x80303464, 0x80305DDC)

    os.makedirs(os.path.dirname(OUT_TSV), exist_ok=True)
    with open(OUT_TSV, 'w') as f:
        f.write('# THUG2 GC script-command registry (from DOL .data 0x80303464, 1327 x {name, func})\n')
        f.write('# name<TAB>func_addr<TAB>fn_symbol<TAB>size<TAB>decompiled<TAB>stub\n')
        f.write('# stub=Y: 8-byte `li rD,imm; blr` placeholder (command stripped on GC)\n')
        for s, fa, fn in cmds:
            decomp = 'Y' if fn and os.path.exists(os.path.join(SRCDIR, fn + '.c')) else 'N'
            size = ''
            stub = '-' if fa is None else 'N'
            if fn:
                i = bisect.bisect_right(starts, fa) - 1
                size = '0x%X' % (fns[i][1] - fns[i][0]) if i >= 0 else ''
                if is_stub(fa, fns[i][1] - fns[i][0]):
                    stub = 'Y'
            f.write('%s\t%s\t%s\t%s\t%s\t%s\n' % (
                s, '0x%08X' % fa if fa else '-', fn or '-', size, decomp, stub))

    distinct = {}
    no_func = 0
    stubs = 0
    for s, fa, fn in cmds:
        if fn:
            distinct.setdefault(fn, []).append(s)
            i = bisect.bisect_right(starts, fa) - 1
            if i >= 0 and is_stub(fa, fns[i][1] - fns[i][0]):
                stubs += 1
        else:
            no_func += 1
    decompiled = [fn for fn in distinct if os.path.exists(os.path.join(SRCDIR, fn + '.c'))]

    print('file-type names (T1): %d   level-event names (T2): %d' % (len(ext), len(events)))
    print('script-command registry (T3): %d entries (%d without func ptr) -> %d distinct funcs' % (
        len(cmds), no_func, len(distinct)))
    print('  funcs already decompiled (have real names now): %d' % len(decompiled))
    print('  funcs still unmatched (naming targets): %d' % (len(distinct) - len(decompiled)))
    print('  8-byte `li;blr` STUBS (command stripped on GC): %d' % stubs)
    print('wrote %s' % OUT_TSV)


if __name__ == '__main__':
    main()
