#!/usr/bin/env python
"""Classify the THUG2 GC DOL's data sections into readable structures.

Covers three in-file data sections (each one dtk split asm unit):

  .data   sec 9,  0x802B23A0, 386,880 B  (auto_04_802B23A0_data.s)
  .sdata  sec 10, 0x803CA280,   2,016 B  (auto_06_803CA280_sdata.s)
  .sdata2 sec 11, 0x803CAF80,   4,736 B  (auto_08_803CAF80_sdata2.s)

The tool scans every aligned word and groups consecutive pointer-like words
into runs, then classifies each run:

  - VTABLE      most words point to DISTINCT .text function starts
                -> class vtables (methods nameable as <vtable>_mN)
  - JUMPTABLE   most words point into a SINGLE .text function (switch tables;
                dtk names these jumptable_*, cross-checked)
  - STRINGTAB   most words point into rodata/rodata2 at printable strings
  - REGISTRY    alternating {rodata2 string ptr, .text fn ptr} -> e.g. the
                script-command registry T3 (1327 name, func pairs)
  - DATAPTAB    most words point at other data-section addresses (object
                refs / interface maps / pointer tables)
  - FLOATRUN    most words are "clean" f32 values
  - MIXED       everything else (object instances, raw tables, bitfields)

dtk's chunk segmentation (from the split asm) is used only for labels; run
detection is independent so vtables/registries embedded in big chunks are
found.

For .sdata/.sdata2 every non-gap chunk is additionally decoded as a small
global: pointer-to-section, float/double constant (using dtk's `data:` type
hints from symbols.txt), short string, or raw int.

For every vtable, find its constructor: scan .text once for the lis/addi
materialization + stw store pattern whose target is a detected vtable.

Outputs:
  docs/data-structures.md      readable reference (data + sdata + sdata2)
  docs/data-vtables.tsv        machine-readable vtable registry
  docs/data-sdata-globals.tsv  decoded sdata/sdata2 small globals
  stdout summary

Usage:  tools/venv/bin/python tools/analyze_data_structures.py
"""
import bisect
import math
import os
import re
import struct

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DOL = os.path.join(ROOT, 'orig/G2TE52/sys/main.dol')
SYMS = os.path.join(ROOT, 'config/G2TE52/symbols.txt')
OUT_MD = os.path.join(ROOT, 'docs/data-structures.md')
OUT_TSV = os.path.join(ROOT, 'docs/data-vtables.tsv')
OUT_SDATA = os.path.join(ROOT, 'docs/data-sdata-globals.tsv')

D = open(DOL, 'rb').read()
offs = struct.unpack_from('>18I', D, 0)
addrs = struct.unpack_from('>18I', D, 0x48)
sizes = struct.unpack_from('>18I', D, 0x90)

T_S, T_E = addrs[1], addrs[1] + sizes[1]        # .text
RO_S, RO_E = addrs[7], addrs[7] + sizes[7]      # .rodata
RO2_S, RO2_E = addrs[8], addrs[8] + sizes[8]    # .rodata2

SECS = {
    'data':   dict(slot=9,  start=addrs[9],  size=sizes[9],
                   asm='auto_04_802B23A0_data.s', writable=True),
    'sdata':  dict(slot=10, start=addrs[10], size=sizes[10],
                   asm='auto_06_803CA280_sdata.s', writable=True),
    'sdata2': dict(slot=11, start=addrs[11], size=sizes[11],
                   asm='auto_08_803CAF80_sdata2.s', writable=False),
}
SLOT = {RO_S: 7, RO2_S: 8}
SLOT.update({info['start']: info['slot'] for info in SECS.values()})

ALL_SEC_RANGES = [(info['start'], info['start'] + info['size']) for info in SECS.values()]


def rd_u32(addr):
    """Read a big-endian u32 from any in-file data section."""
    for info in SECS.values():
        base = info['start']
        if base and base <= addr < base + info['size'] - 3:
            return struct.unpack_from('>I', D, offs[info['slot']] + (addr - base))[0]
    return None


def rd_bytes(addr, n):
    for name, info in SECS.items():
        base = info['start']
        if base and base <= addr < base + info['size'] and addr + n <= base + info['size']:
            return D[offs[info['slot']] + (addr - base):offs[info['slot']] + (addr - base) + n]
    return None


def in_data_sec(addr):
    return any(base <= addr < base + size for base, size in ALL_SEC_RANGES)

DA_S, DA_E = addrs[9], addrs[9] + sizes[9]


def in_dotdata(addr):
    """.data proper only (pointer-table targets; sdata/sdata2 are small globals)."""
    return DA_S <= addr < DA_E


def insn(addr):
    if not (T_S <= addr < T_E - 3):
        return None
    return struct.unpack_from('>I', D, offs[1] + (addr - T_S))[0]


def rodata_str(addr):
    base = None
    if RO_S <= addr < RO_E:
        base, size = RO_S, sizes[7]
    elif RO2_S <= addr < RO2_E:
        base, size = RO2_S, sizes[8]
    else:
        return None
    slot = SLOT[base]
    off = offs[slot] + (addr - base)
    j = off
    while j < offs[slot] + size and 32 <= D[j] < 127:
        j += 1
    return D[off:j].decode('latin1') if j - off >= 3 else None


# ---- symbols ----
fn_starts = set()
fn_by_start = {}       # start -> name
fn_ranges = []         # (start, end, name)
obj_hints = {}         # addr -> 'float'/'double'/'string'/'4byte'/...

for line in open(SYMS):
    m = re.match(r'^([A-Za-z_][A-Za-z0-9_]*) = \.text:0x([0-9A-F]+); // type:function size:0x([0-9A-Fa-f]+)', line)
    if m:
        s = int(m.group(2), 16)
        fn_starts.add(s)
        fn_by_start[s] = m.group(1)
        fn_ranges.append((s, s + int(m.group(3), 16), m.group(1)))
        continue
    m = re.match(r'^lbl_([0-9A-F]{8}) = \.([a-z0-9]+):0x[0-9A-F]+; // type:object(?: size:0x[0-9A-F]+)?(?: data:([a-z0-9]+))?', line)
    if m and m.group(2) in ('sdata', 'sdata2'):
        # sdata defaults to raw 4byte (pointer/global area); sdata2 without a
        # hint is the float/double constant pool (decode by value, not hint).
        obj_hints[int(m.group(1), 16)] = m.group(3) or ('4byte' if m.group(2) == 'sdata' else None)

fn_ranges.sort()
fn_starts_sorted = [f[0] for f in fn_ranges]


def covering_fn(addr):
    i = bisect.bisect_right(fn_starts_sorted, addr) - 1
    if i >= 0 and fn_ranges[i][0] <= addr < fn_ranges[i][1]:
        return fn_ranges[i]
    return None


def fn_at_start(addr):
    return fn_by_start.get(addr)


def method_name(w):
    n = fn_at_start(w)
    if n:
        return n
    f = covering_fn(w)
    if f:
        return '%s+0x%X' % (f[2], w - f[0])
    return '0x%08X' % w


# ---- dtk chunk labels per section ----
def parse_chunks(sec_name, asm_path):
    """Parse (name, addr, size) chunks from a dtk split asm file."""
    out = []
    cur_name, cur_addr, cur_size = None, 0, 0
    hdr = re.compile(r'^# \.%s:0x([0-9A-F]+) \| 0x([0-9A-F]+) \| size: 0x([0-9A-F]+)$' % sec_name)
    for line in open(asm_path):
        m = hdr.match(line.strip())
        if m:
            cur_addr, cur_size = int(m.group(2), 16), int(m.group(3), 16)
            cur_name = None
            continue
        m = re.match(r'^\.obj ([A-Za-z_][A-Za-z0-9_]*)', line.strip())
        if m:
            cur_name = m.group(1)
            continue
        m = re.match(r'^\.endobj', line.strip())
        if m and cur_name:
            out.append((cur_name, cur_addr, cur_size))
    return out


all_chunks = {}        # sec_name -> [(name, addr, size)]
for sec_name, info in SECS.items():
    all_chunks[sec_name] = parse_chunks(sec_name, os.path.join(ROOT, 'build/G2TE52/asm', info['asm']))


def chunk_label(addr):
    for sec_name, chunks in all_chunks.items():
        for name, a, size in chunks:
            if a <= addr < a + size:
                return name
    return 'lbl_%08X' % addr


# ---- per-section word scans ----
def build_words(sec_name):
    info = SECS[sec_name]
    words = []
    for a in range(info['start'], info['start'] + info['size'], 4):
        w = rd_u32(a)
        if w is None:
            break
        words.append((a, w))
    return words


VTABLE, JUMPTABLE, STRINGTAB, REGISTRY, DATAPTAB, FLOATRUN, MIXED = range(7)


def is_str(w):
    return rodata_str(w) is not None


def is_code(w):
    return T_S <= w < T_E


def scan_registries(words):
    out = []
    i = 0
    n = len(words)
    while i < n:
        _, w = words[i]
        if not is_str(w):
            i += 1
            continue
        pairs = []
        j = i
        while j + 1 < n:
            _, ws = words[j]
            _, wf = words[j + 1]
            if is_str(ws) and is_code(wf):
                pairs.append((rodata_str(ws), wf))
                j += 2
            else:
                break
        if len(pairs) >= 3:
            out.append((words[i][0], pairs))
            i = j
        else:
            i += 1
    return out


def is_dtk_jumptable(addr):
    return any(a <= addr < a + sz
               for chunks in all_chunks.values()
               for n, a, sz in chunks if n.startswith('jumptable_'))


def scan_code_runs(words):
    out = []
    i = 0
    n = len(words)
    while i < n:
        _, w = words[i]
        if not is_code(w):
            i += 1
            continue
        j = i
        while j < n and is_code(words[j][1]):
            j += 1
        ptrs = [words[k][1] for k in range(i, j)]
        if len(ptrs) >= 3:
            start_addr = words[i][0]
            starts = sum(1 for w in ptrs if w in fn_starts)
            cfs = set(covering_fn(w)[2] for w in ptrs if covering_fn(w))
            if is_dtk_jumptable(start_addr):
                out.append((start_addr, JUMPTABLE, {'target': 'dtk-named switch table'}))
            elif starts >= len(ptrs) * 0.5 and len(cfs) >= 3:
                out.append((start_addr, VTABLE, {'methods': [method_name(w) for w in ptrs]}))
            else:
                out.append((start_addr, MIXED,
                            {'code': len(ptrs), 'starts': starts, 'fns': len(cfs)}))
        i = j
    return out


def scan_stringtabs(words):
    out = []
    i = 0
    n = len(words)
    while i < n:
        _, w = words[i]
        if not is_str(w):
            i += 1
            continue
        j = i
        while j < n and is_str(words[j][1]):
            j += 1
        if j - i >= 3:
            out.append((words[i][0], [rodata_str(words[k][1]) for k in range(i, j)]))
        i = j
    return out


def scan_datatabs(words):
    out = []
    i = 0
    n = len(words)
    while i < n:
        _, w = words[i]
        if not in_dotdata(w):
            i += 1
            continue
        j = i
        while j < n and in_dotdata(words[j][1]):
            j += 1
        if j - i >= 3:
            out.append((words[i][0], [method_name(words[k][1]) for k in range(i, j)]))
        i = j
    return out


def is_float_word(w):
    if T_S <= w < T_E or RO_S <= w < RO_E or RO2_S <= w < RO2_E or in_data_sec(w):
        return False
    f = struct.unpack('>f', struct.pack('>I', w))[0]
    return math.isfinite(f) and f != 0.0 and 1e-6 <= abs(f) < 1e9


def scan_floats(words):
    out = []
    i = 0
    n = len(words)
    while i < n:
        if not is_float_word(words[i][1]):
            i += 1
            continue
        j = i
        while j < n and is_float_word(words[j][1]):
            j += 1
        if j - i >= 4:
            out.append((words[i][0],
                        [struct.unpack('>f', struct.pack('>I', words[k][1]))[0]
                         for k in range(i, j)]))
        i = j
    return out


# ---- run the structural scans on .data only ----
# (.sdata/.sdata2 are decoded chunk-by-chunk as small globals below; running
# the pointer-run scans there fabricates fake tables out of adjacent globals.)
structures = []        # (kind, sec_name, addr, nwords, detail)
sec_name = 'data'
words = build_words(sec_name)
for name, a, sz in all_chunks[sec_name]:
    if name.startswith('jumptable_'):
        structures.append((JUMPTABLE, sec_name, a, sz // 4, {'target': 'dtk-named switch table'}))
for start, pairs in scan_registries(words):
    structures.append((REGISTRY, sec_name, start, len(pairs) * 2, {'pairs': pairs}))
for start, kind, detail in scan_code_runs(words):
    if kind == VTABLE or kind == MIXED:
        nw = len(detail['methods']) if 'methods' in detail else detail.get('code', 0)
        structures.append((kind, sec_name, start, nw, detail))
for start, ss in scan_stringtabs(words):
    structures.append((STRINGTAB, sec_name, start, len(ss), {'strings': ss}))
for start, ps in scan_datatabs(words):
    structures.append((DATAPTAB, sec_name, start, len(ps), {'ptrs': ps}))
for start, fv in scan_floats(words):
    structures.append((FLOATRUN, sec_name, start, len(fv), {'floats': fv}))

# ---- constructor map: single pass over .text ----
# lis rD,hi ; addi rD,rD,lo  ->  target = (hi<<16)|sign(lo); if target in a
# data section and followed by stw rD -> store site (candidate constructor).
ctor_targets = {}      # target_addr -> (text_addr, fn_name)
for addr in range(T_S, T_E - 8, 4):
    i1 = insn(addr)
    if i1 is None or (i1 >> 26) != 15:
        continue
    rd = (i1 >> 21) & 0x1F
    hi = i1 & 0xFFFF
    for off in range(4, 52, 4):
        i2 = insn(addr + off)
        if i2 is None:
            break
        if (i2 >> 26) == 14 and ((i2 >> 21) & 0x1F) == rd and ((i2 >> 16) & 0x1F) == rd:
            lo = i2 & 0xFFFF
            if lo >= 0x8000:
                lo -= 0x10000
            target = ((hi << 16) + lo) & 0xFFFFFFFF
            if not in_data_sec(target):
                continue
            for off2 in range(4, 20, 4):
                i3 = insn(addr + off + off2)
                if i3 is None:
                    break
                if (i3 >> 26) == 36 and ((i3 >> 21) & 0x1F) == rd:
                    f = covering_fn(addr)
                    ctor_targets.setdefault(target, (addr, f[2] if f else 'fn_%08X' % addr))
                    break
            break

# ---- aggregate ----
by_kind = {}
for k, sec_name, start, nw, detail in structures:
    by_kind.setdefault(k, []).append((sec_name, start, nw, detail))

vtables = by_kind.get(VTABLE, [])
jumptables = by_kind.get(JUMPTABLE, [])
stringtabs = by_kind.get(STRINGTAB, [])
registries = by_kind.get(REGISTRY, [])
datatabs = by_kind.get(DATAPTAB, [])
floatruns = by_kind.get(FLOATRUN, [])
mixed = by_kind.get(MIXED, [])

vt_ctors = {}
for sec_name, start, nw, detail in vtables:
    if start in ctor_targets:
        vt_ctors[start] = ctor_targets[start][1]

# ---- decode sdata/sdata2 small globals ----
# Smallest normal (non-denormal) values; anything below is denormal noise.
F64_MIN_NORMAL = struct.unpack('>d', struct.pack('>Q', 0x0010000000000000))[0]  # ~2.2e-308
F32_MIN_NORMAL = struct.unpack('>f', struct.pack('>I', 0x00800000))[0]  # ~1.2e-38


def _fmt_vals(kind, vals):
    """Join a value list; full precision kept for the TSV, doc truncates."""
    fmt = '%.10g' if kind == 'f64' else '%.8g'
    return ', '.join(fmt % f for f in vals)


def _disp(text):
    """Truncate long values for the readable doc (TSV keeps full text)."""
    return text if len(text) <= 100 else text[:97] + '...'


def decode_global(sec_name, addr, size):
    """Decode one dtk chunk as a small global. Returns (kind, text)."""
    hint = obj_hints.get(addr)
    b = rd_bytes(addr, size)
    if sec_name == 'sdata2':
        # r2 constant pool: 4byte-hinted chunks are raw ints, not floats
        if hint == '4byte':
            if b is not None and size % 4 == 0:
                ws = [struct.unpack_from('>I', b, k)[0] for k in range(0, size, 4)]
                return 'int[]', ', '.join('0x%08X' % w for w in ws)
            return 'raw', '?'
        # f64 run: all finite, nonzero values must not be denormal
        if b is not None and size % 8 == 0:
            vals = []
            ok = True
            for k in range(0, size, 8):
                f = struct.unpack_from('>d', b, k)[0]
                if not math.isfinite(f) or (f != 0.0 and abs(f) < F64_MIN_NORMAL):
                    ok = False
                    break
                vals.append(f)
            if ok:
                return 'f64', _fmt_vals('f64', vals)
        # f32 run fallback (pairs of floats)
        if b is not None and size % 4 == 0:
            vals = []
            ok = True
            for k in range(0, size, 4):
                f = struct.unpack_from('>f', b, k)[0]
                if not math.isfinite(f) or (f != 0.0 and abs(f) < F32_MIN_NORMAL):
                    ok = False
                    break
                vals.append(f)
            if ok:
                return 'f32', _fmt_vals('f32', vals)
        if b is not None and size % 4 == 0:
            ws = [struct.unpack_from('>I', b, k)[0] for k in range(0, size, 4)]
            return 'int[]', ', '.join('0x%08X' % w for w in ws)
        return 'raw', '?'
    if size == 4:
        w = rd_u32(addr)
        if w is None:
            return 'raw', '?'
        # string?
        if hint == 'string':
            s = ''
            for k in range(4):
                c = (w >> (24 - 8 * k)) & 0xFF
                if 32 <= c < 127:
                    s += chr(c)
            if s:
                return 'str', repr(s)
        if hint == 'float':
            f = struct.unpack('>f', struct.pack('>I', w))[0]
            if math.isfinite(f):
                return 'f32', '%.8g' % f
        if in_data_sec(w):
            return 'ptr', '-> %s' % chunk_label(w)
        if T_S <= w < T_E:
            return 'ptr', '-> %s' % method_name(w)
        if is_str(w):
            return 'ptr', '-> `%s`' % rodata_str(w)
        if hint == 'float' or (math.isfinite(struct.unpack('>f', struct.pack('>I', w))[0])
                               and 1e-6 <= abs(struct.unpack('>f', struct.pack('>I', w))[0]) < 1e9):
            f = struct.unpack('>f', struct.pack('>I', w))[0]
            return 'f32', '%.8g' % f
        return 'int', '0x%08X (%d)' % (w, w if w < 0x80000000 else w - 0x100000000)
    b = rd_bytes(addr, min(size, 16))
    if b is None:
        return 'raw', '?'
    # short printable string?
    s = b.decode('latin1', 'replace')
    if all(32 <= ord(c) < 127 for c in s.rstrip('\x00')) and s.rstrip('\x00'):
        return 'str', repr(s.rstrip('\x00'))
    if size == 2:
        v = struct.unpack_from('>H', b, 0)[0]
        return 'int', '0x%04X (%d)' % (v, v)
    if size == 1:
        return 'int', '0x%02X (%d)' % (b[0], b[0])
    words = []
    for k in range(0, len(b) - 3, 4):
        words.append(struct.unpack_from('>I', b, k)[0])
    return 'int[]', ', '.join('0x%08X' % w for w in words)


sdata_rows = []   # (addr, sec, name, kind, text)
for sec_name in ('sdata', 'sdata2'):
    for name, addr, size in all_chunks[sec_name]:
        if name.startswith('gap_'):
            continue
        kind, text = decode_global(sec_name, addr, size)
        sdata_rows.append((addr, sec_name, name, kind, text))
sdata_rows.sort()

# ================= output =================
total_chunks = sum(len(c) for c in all_chunks.values())
lines = []
lines.append('# THUG2 G2TE52 data structure map (.data / .sdata / .sdata2)')
lines.append('')
lines.append('_Auto-generated by `tools/analyze_data_structures.py` — do not edit by hand._')
lines.append('')
lines.append('## TL;DR')
lines.append('')
lines.append('Three in-file data sections, each one dtk split asm unit:')
lines.append('')
lines.append('| section | range | size | dtk chunks | notes |')
lines.append('|---|---|---|---|---|')
for sec_name in ('data', 'sdata', 'sdata2'):
    info = SECS[sec_name]
    nch = len(all_chunks[sec_name])
    note = {'data': 'objects, vtables, tables', 'sdata': 'small globals (r13)',
            'sdata2': 'float/double constants (r2)'}[sec_name]
    lines.append('| `.%s` | 0x%08X..0x%08X | %d B | %d | %s |' % (
        sec_name, info['start'], info['start'] + info['size'], info['size'], nch, note))
lines.append('')
lines.append('This map groups every aligned run of pointer-like words and classifies it:')
lines.append('')
lines.append('- **%d vtables** (%d method slots) — class vtables; methods nameable' % (
    len(vtables), sum(len(d['methods']) for _, _, _, d in vtables)))
lines.append('- **%d jump tables** (dtk also names %d `jumptable_*`)' % (
    len(jumptables), sum(1 for chunks in all_chunks.values() for n, _, _ in chunks
                         if n.startswith('jumptable_'))))
lines.append('- **%d string-pointer tables**' % len(stringtabs))
lines.append('- **%d {name,func} registries** (incl. T3 script commands)' % len(registries))
lines.append('- **%d data-pointer tables** (object refs / interface maps)' % len(datatabs))
lines.append('- **%d float runs**' % len(floatruns))
lines.append('- **%d mixed/opaque runs** (object instances, raw tables)' % len(mixed))
lines.append('- **%d decoded sdata/sdata2 small globals** (see §8–9, `data-sdata-globals.tsv`)'
             % len(sdata_rows))
lines.append('')
lines.append('## 1. Vtables')
lines.append('')
lines.append('`ctor` = the function that materializes the table address with lis/addi and')
lines.append('stores it with stw (single-pass scan). `?` here does **not** mean the')
lines.append('lookup failed: these method tables are registered through the data-pointer')
lines.append('table at 0x80308040 (interface map) rather than stored by per-class')
lines.append('constructors, so no ctor-store exists. Methods are named from symbols.txt;')
lines.append('unmatched ones stay fn_XXXX.')
lines.append('')
lines.append('**Rename status (M6.83, via `tools/rename_vtable_methods.py`):** the slots')
lines.append('span fewer unique functions (shared default handlers occupy many slots,')
lines.append('e.g. `fn_8025A724` x19). Only **matched** functions (those with a')
lines.append('`src/fn_XXXX.c`) are renamed to `Vtable0x<addr>_m<slot>` (symbols.txt +')
lines.append('src + callers, M6.76 pipeline, DOL byte-clean); unmatched fns keep `fn_`')
lines.append('until matched — per M6.76 policy a rename needs a defining source file to')
lines.append('anchor to. The machine-readable manifest (vtable, slot, fn, suggested')
lines.append('name) is `data-vtables.tsv`; rerunning the rename tool is a no-op.')
lines.append('')
lines.append('| vtable | slots | ctor | first methods |')
lines.append('|---|---|---|---|')
for sec_name, start, nw, detail in sorted(vtables):
    ms = detail['methods']
    lines.append('| `%s` | %d | `%s` | %s |' % (
        chunk_label(start), len(ms), vt_ctors.get(start, '?') or 'via-data-table',
        ', '.join('`%s`' % m for m in ms[:6])))
lines.append('')

lines.append('## 2. Jump tables')
lines.append('')
lines.append('Switch tables, named by dtk from their `lwzx/mtctr/bctr` dispatch sites.')
lines.append('')
lines.append('| jumptable | entries |')
lines.append('|---|---|')
for sec_name, start, nw, detail in sorted(jumptables):
    lines.append('| `%s` | %d |' % (chunk_label(start), nw))
lines.append('')

lines.append('## 3. String-pointer tables')
lines.append('')
lines.append('| table | entries | first strings |')
lines.append('|---|---|---|')
for sec_name, start, nw, detail in sorted(stringtabs, key=lambda t: -t[2])[:20]:
    ss = detail['strings']
    lines.append('| `%s` | %d | %s |' % (chunk_label(start), len(ss),
                 ', '.join('`%s`' % s for s in ss[:6])))
lines.append('')

lines.append('## 4. {name, func} registries')
lines.append('')
lines.append('Alternating rodata2-string / .text-fn pointer pairs. T3 (0x80303464)')
lines.append('is the script-command registry. The strict alternating scan splits it at')
lines.append('entries whose name is <3 chars or whose handler falls outside .text, so')
lines.append('the pair counts here (381 + 820 = 1201) are a lower bound — the')
lines.append('authoritative full list is `rodata2-script-command-registry.tsv` (1327')
lines.append('rows).')
lines.append('')
lines.append('| registry | pairs | first pairs |')
lines.append('|---|---|---|')
for sec_name, start, nw, detail in sorted(registries, key=lambda t: -t[2])[:15]:
    ps = detail['pairs']
    lines.append('| `lbl_%08X` | %d | %s |' % (start, len(ps),
                 ', '.join('`%s`→`%s`' % (p[0], method_name(p[1])) for p in ps[:5])))
lines.append('')

lines.append('## 5. Data-pointer tables')
lines.append('')
lines.append('Tables whose words point at other data-section addresses (manager object')
lines.append('registries, interface maps, linked lists).')
lines.append('')
lines.append('| table | entries | first pointers |')
lines.append('|---|---|---|')
for sec_name, start, nw, detail in sorted(datatabs, key=lambda t: -t[2])[:15]:
    lines.append('| `%s` | %d | %s |' % (chunk_label(start), nw,
                 ', '.join('`%s`' % p for p in detail['ptrs'][:6])))
lines.append('')

lines.append('## 6. Float runs')
lines.append('')
lines.append('| run | values | first floats |')
lines.append('|---|---|---|')
for sec_name, start, nw, detail in sorted(floatruns, key=lambda t: -t[2])[:12]:
    fv = detail['floats']
    lines.append('| `%s` | %d | %s |' % (chunk_label(start), len(fv),
                 ', '.join('%.4g' % f for f in fv[:6])))
lines.append('')

lines.append('## 7. Mixed/opaque runs (manual review)')
lines.append('')
for sec_name, start, nw, detail in sorted(mixed, key=lambda t: -t[2])[:25]:
    desc = detail if detail else ''
    lines.append('- `%s` (%d words) %s' % (chunk_label(start), nw, desc))
lines.append('')

lines.append('## 8. `.sdata` small globals (r13, `-msdata=eabi -G4`)')
lines.append('')
lines.append('Every non-gap chunk decoded: pointer into a section, f32/f64 constant')
lines.append('(dtk `data:` hint), short string, or raw int. Full list in')
lines.append('`data-sdata-globals.tsv`.')
lines.append('')
lines.append('| object | size | kind | value |')
lines.append('|---|---|---|---|')
for addr, sec_name, name, kind, text in sdata_rows:
    if sec_name != 'sdata':
        continue
    sz = sum(sz for n, a, sz in all_chunks['sdata'] if a == addr) or 4
    lines.append('| `%s` | %d | %s | %s |' % (name, sz, kind, _disp(text)))
lines.append('')

lines.append('## 9. `.sdata2` constants (r2, float/double literals)')
lines.append('')
lines.append('The compiler pool of deduplicated float/double constants (loaded with')
lines.append('`lfs`/`lfd` via r2).')
lines.append('')
lines.append('| object | size | kind | value |')
lines.append('|---|---|---|---|')
for addr, sec_name, name, kind, text in sdata_rows:
    if sec_name != 'sdata2':
        continue
    sz = sum(sz for n, a, sz in all_chunks['sdata2'] if a == addr) or 4
    lines.append('| `%s` | %d | %s | %s |' % (name, sz, kind, _disp(text)))
lines.append('')

open(OUT_MD, 'w').write('\n'.join(lines) + '\n')

# ---- TSV: vtables (one row per method slot = rename manifest) ----
# columns: vtable_addr, slot, fn_or_raw, suggested_name
with open(OUT_TSV, 'w') as f:
    f.write('# vtable_addr\tslot\tfn_or_raw\tsuggested_name\n')
    for sec_name, start, nw, detail in sorted(vtables):
        for i, m in enumerate(detail['methods']):
            f.write('lbl_%08X\t%d\t%s\tVtable0x%08X_m%d\n' % (
                start, i, m, start, i))

# ---- TSV: sdata/sdata2 globals ----
with open(OUT_SDATA, 'w') as f:
    f.write('# addr\tsection\tobject\tsize\tkind\tvalue\n')
    for addr, sec_name, name, kind, text in sdata_rows:
        sz = sum(sz for n, a, sz in all_chunks[sec_name] if a == addr) or 4
        f.write('lbl_%08X\t%s\t%s\t%d\t%s\t%s\n' % (addr, sec_name, name, sz, kind, text))

# ---- stdout summary ----
print('=== data structure summary ===')
for sec_name in ('data', 'sdata', 'sdata2'):
    print('  %-7s %d chunks' % (sec_name, len(all_chunks[sec_name])))
print('vtables:      %d (%d method slots)' % (
    len(vtables), sum(len(d['methods']) for _, _, _, d in vtables)))
print('jumptables:   %d' % len(jumptables))
print('string-tabs:  %d' % len(stringtabs))
print('registries:   %d (%d pairs)' % (len(registries),
      sum(len(d['pairs']) for _, _, _, d in registries)))
print('data-ptr-tabs:%d' % len(datatabs))
print('float-runs:   %d' % len(floatruns))
print('mixed:        %d' % len(mixed))
print('sdata globals:%d' % sum(1 for r in sdata_rows if r[1] == 'sdata'))
print('sdata2 consts:%d' % sum(1 for r in sdata_rows if r[1] == 'sdata2'))
print('--- vtables ---')
for sec_name, start, nw, detail in sorted(vtables):
    print('  %-20s %4d slots  ctor=%s' % (chunk_label(start), nw, vt_ctors.get(start, '?')))
print('--- sdata sample ---')
for addr, sec_name, name, kind, text in sdata_rows[:10]:
    print('  %-20s %-8s %s' % (name, kind, text))
print('--- sdata2 sample ---')
n = 0
for addr, sec_name, name, kind, text in sdata_rows:
    if sec_name == 'sdata2':
        print('  %-20s %-8s %s' % (name, kind, text))
        n += 1
        if n >= 12:
            break
