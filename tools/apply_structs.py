#!/usr/bin/env python3
"""Rewrite byte-offset derefs to struct member access using the struct types
detected by tools/detect_structs.py.

Three site families are rewritten to struct member access:
  * pointer form `*(T *)((char *)BASE + 0xNN)` (+ the one-level nested
    form)  ->  `((Unk_XXXX *)BASE)->unkNN`
  * address form `*(T *)((char *)&BASE + 0xNN)` (stack locals / statics /
    globals, base key ('a', ident))  ->  `((Unk_XXXX *)&BASE)->unkNN`
  * direct form `*(T *)(BASE + 0xNN)` (no cast, base key ('i', ident)) — the
    byte offset is LIT * element size from the base's declaration, computed
    with the same `base_add_mult` lookup (and exclusion for unknown pointee
    sizes) as the detection side  ->  `((Unk_XXXX *)BASE)->unk(BASE+LIT*mult)`
  * stride form `*(T *)((char *)BASE + ID * W)` with W == sizeof(T)  ->
    `((T *)BASE)[ID]` — an array element access, byte-safe with no struct
A site is replaced **only** when the detected struct for (file, base) has a
field at exactly the byte offset whose type string equals the site's cast
type — that makes the rewrite codegen-identical by construction (same
load/store width, same offset).

Matched src/fn_*.c files are additionally verified per-file: the rewritten
body is compiled with the real ngccc flags (plus the file's `extra_cflags`
marker) via gen_leaves.compile_fn and compared masked against the retail
bytes; any file that does not come back 100% byte-identical is reverted, so
the DOL can never drift. src/wip/ drafts are inert (never compiled) and are
rewritten without verification.

The struct header is the FIXED type reference: run
`tools/detect_structs.py` FIRST (it writes include/structs.h
from the pristine corpus) and never regenerate it during apply — otherwise
field types flip as raw sites vanish and previously-verified files can
un-verify. On an already-applied corpus (pointer family rewritten), run
`tools/detect_structs.py --extend` to add the address-form classes to the
frozen header/cache without touching the pointer section.

Usage:
    tools/venv/bin/python tools/detect_structs.py [--extend]   # generate header
    tools/venv/bin/python tools/apply_structs.py --dry-run
    tools/venv/bin/python tools/apply_structs.py --apply [--jobs 8]
"""
import collections
import glob
import multiprocessing as mp
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)
sys.path.insert(0, os.path.join(ROOT, 'tools'))

import detect_structs as ds
import gen_leaves as gl

APPLY = '--apply' in sys.argv
JOBS = 8
if '--jobs' in sys.argv:
    JOBS = int(sys.argv[sys.argv.index('--jobs') + 1])
LIMIT = None
if '--limit' in sys.argv:
    LIMIT = int(sys.argv[sys.argv.index('--limit') + 1])

FN_RE = re.compile(r'fn_([0-9A-F]{8})\.c$')
EXTCFLAGS_RE = re.compile(r'//\s*extra_cflags:\s*(.*)')

# Struct-class token: canonical Unk_* names plus human-readable aliases from
# ds.ALIASES (CStruct, CScript, ...). Site/decl/pun patterns use CLASS so
# renamed corpus sites keep matching; canonical() maps back to the Unk_ key
# for every cache/header lookup; display() is the emission spelling.
CLASS_INNER = r'Unk_[0-9A-F]+|%s' % '|'.join(ds.ALIASES.values())
CLASS = r'(?:%s)' % CLASS_INNER
# Case-tolerant twin for type_params.py, which historically accepts lowercase
# hex in Unk_ names (behavior-preserving: same matches as before + aliases).
CLASS_INNER_CI = r'Unk_[0-9A-Fa-f]+|%s' % '|'.join(ds.ALIASES.values())
CLASS_CI = r'(?:%s)' % CLASS_INNER_CI
_REV_ALIASES = {v: k for k, v in ds.ALIASES.items()}


def canonical(cls):
    """Corpus spelling -> canonical Unk_ cache key."""
    return _REV_ALIASES.get(cls, cls)


def display(cls):
    """Canonical Unk_ key (or alias) -> corpus emission spelling."""
    return ds.ALIASES.get(cls, cls)


def class_alt(key):
    """Regex alternation matching every spelling of one canonical class."""
    disp = ds.ALIASES.get(key, key)
    if disp == key:
        return re.escape(key)
    return r'(?:%s|%s)' % (re.escape(key), re.escape(disp))


def canonical_type(typ):
    """Map aliased class tokens inside a type string back to canonical keys
    ('CStruct *' -> 'Unk_2EF06E12 *'). Used for cache/header comparisons so
    mixed spellings still match; emission always goes through display()."""
    for k, v in ds.ALIASES.items():
        typ = re.sub(r'\b%s\b' % re.escape(v), k, typ)
    return typ

# symbols.txt: function address -> size (any symbol name — renamed fns too)
SYM_SIZE = {}
for line in open(os.path.join(ROOT, 'config', 'G2TE52', 'symbols.txt')):
    m = re.match(r'^([A-Za-z_][A-Za-z0-9_]*) = \.text:0x([0-9A-F]+); // type:function size:0x([0-9A-Fa-f]+)', line)
    if m:
        SYM_SIZE[int(m.group(2), 16)] = int(m.group(3), 16)


def masked_pct(orig, got, masks):
    n = min(len(orig), len(got)) // 4
    if n == 0:
        return 0.0
    hit = sum(1 for i in range(n)
              if (int.from_bytes(orig[i * 4:(i + 1) * 4], 'big') & masks.get(i * 4, 0xFFFFFFFF)) ==
                 (int.from_bytes(got[i * 4:(i + 1) * 4], 'big') & masks.get(i * 4, 0xFFFFFFFF)))
    return 100.0 * hit / n


def extra_flags(text):
    m = EXTCFLAGS_RE.search(text)
    return m.group(1).split() if m else []


def verify_src(addr, sym_size, new_text):
    """Compile rewritten body and require a byte-identical masked match."""
    got, masks = gl.compile_fn(addr, body_of(new_text), extra_flags(new_text))
    if not got:
        return False
    if len(got) != sym_size:
        return False
    orig = gl.d[gl.t_off + (addr - gl.t_addr): gl.t_off + (addr - gl.t_addr) + len(got)]
    return masked_pct(orig, got, masks) == 100.0


def ensure_include(text):
    """Add the structs include when the text uses Unk_ types and lacks it.
    Pure stride-array rewrites (no Unk_ class) don't need the header.

    Inserted at the END of the file's TOP include block (after the last
    #include that precedes the first code line) — extern declarations that
    now name Unk_ classes sit right below the includes. A stray #include
    mid-file (a duplicated draft line) does not extend the block."""
    if 'Unk_' not in text and not any(a in text for a in ds.ALIASES.values()) \
            or '#include "structs.h"' in text:
        return text
    lines = text.split('\n')
    last_top_inc = -1
    for i, l in enumerate(lines):
        if l.startswith('#include'):
            last_top_inc = i
        elif l.strip() and not l.startswith('//'):
            break  # first code line ends the top include block
    if last_top_inc < 0:
        return text
    lines.insert(last_top_inc + 1,
                 '#include "structs.h"')
    return '\n'.join(lines)


def plan_rewrites(file, text, class_of, names, offs_types):
    """Return list of (start, end, replacement) applied right-to-left.

    A site at an offset whose class field has the EXACT cast type becomes the
    member access `((Unk *)BASE)->unkNN`. When the class field type differs
    (same-width type punning, e.g. f32 site over an s32-majority field, or a
    narrower access over a wider field) the site becomes the member-address
    cast form `*((T *)&((Unk *)BASE)->unkNN)` — same address, same load, so
    still byte-identical. No field at the offset (odd-align/overlap drops)
    leaves the site raw.
    """
    # cache keys are repo-relative (see detect_structs.canon); normalize the
    # on-disk path before lookup so absolute caller paths still resolve
    file = ds.canon(file)

    def exact_ci(base, off):
        """Class index if (file, base) maps to one with a field at off."""
        ci = class_of.get((file, base))
        if ci is None or off not in offs_types[ci]:
            return None
        return ci

    def member_ref(ci, base_expr, off):
        return '((%s *)%s)->unk0x%X' % (display(names[ci]), base_expr, off)

    def rewrite(base, base_expr, off, typ):
        """Replacement text, or None when the offset has no emitted field."""
        ci = exact_ci(base, off)
        if ci is None:
            return None
        ref = member_ref(ci, base_expr, off)
        if canonical_type(offs_types[ci][off]) == canonical_type(typ):
            return ref
        return '*((%s *)&%s)' % (typ, ref)

    masked = ds.mask_comments_strings(text)
    repls = []
    consumed = []
    for n in ds.NEST1_RE.finditer(masked):
        t2, t1, ident, o1, o2 = n.groups()
        o1, o2 = int(o1, 0), int(o2, 0)
        t1s, t2s = t1.strip(), t2.strip()
        c1 = exact_ci(ident, o1)
        c2 = exact_ci(('d', ident, o1), o2)
        if c1 is not None and c2 is not None:
            if canonical_type(offs_types[c1][o1]) == canonical_type(t1s) and \
                    canonical_type(offs_types[c2][o2]) == canonical_type(t2s):
                repls.append((n.start(), n.end(),
                              '((%s *)((%s *)%s)->unk0x%X)->unk0x%X' % (
                                  display(names[c2]), display(names[c1]),
                                  ident, o1, o2)))
                consumed.append(n.span())
    for m in ds.SITE_RE.finditer(masked):
        if any(a <= m.start() < b for a, b in consumed):
            continue
        t, ident, off = m.groups()
        off = int(off, 0)
        new = rewrite(ident, ident, off, t.strip())
        if new:
            repls.append((m.start(), m.end(), new))
    for m in ds.AMP_RE.finditer(masked):
        t, ident, off = m.groups()
        off = int(off, 0)
        new = rewrite(('a', ident), '&%s' % ident, off, t.strip())
        if new:
            repls.append((m.start(), m.end(), new))
    for m in ds.DIR_RE.finditer(masked):
        t, ident, off = m.groups()
        # addend is in units of the base's declared type — same decl lookup
        # (and same exclusion for unknown pointee sizes) as the detection side
        mult = ds.base_add_mult(masked, ident)
        if mult == 0:
            continue
        off = int(off, 0) * mult
        new = rewrite(('i', ident), ident, off, t.strip())
        if new:
            repls.append((m.start(), m.end(), new))
    for m in ds.STRIDE_RE.finditer(masked):
        t, base, idx, scale = m.groups()
        # element access: `(char *)BASE + ID * W` with W == sizeof(T) is
        # `((T *)BASE)[ID]` — byte-safe by construction, no struct class
        if ds.type_width(t.strip()) == int(scale, 0):
            repls.append((m.start(), m.end(),
                          '((%s *)%s)[%s]' % (t.strip(), base, idx)))
    return repls


def apply_repls(text, repls):
    out = text
    for start, end, new in sorted(repls, key=lambda r: -r[0]):
        out = out[:start] + new + out[end:]
    return out


def body_of(text):
    return '\n'.join(l for l in text.splitlines()
                     if not l.startswith('//') and 'types.h' not in l)


def verify_compiles(addr, text):
    got, _masks = gl.compile_fn(addr, body_of(text), extra_flags(text))
    return got is not None


# ---------------------------------------------------------------------------
# --retarget-types: fix member types that every textual use shows are wrong.
# A pun form `*((T *)&((Unk_X *)B)->unkNN)` — or the typed-base variant
# `*((T *)&name->unkNN)` with `name` declared `Unk_X *` — exists (from
# earlier applies) when the site's original cast type T differed from the
# class field type. When EVERY use of the member in the corpus is such a pun
# of one type T and there are no plain / address-of uses, the field is
# retyped to T and the puns become plain member accesses — same-width access
# at the same offset, so codegen is unchanged for the access (verified
# per-file like all applies).
# ---------------------------------------------------------------------------
RETARGET = '--retarget-types' in sys.argv

RT_W = {'s8': 1, 'u8': 1, 's16': 2, 'u16': 2, 's32': 4, 'u32': 4, 'f32': 4,
        's64': 8, 'u64': 8, 'f64': 8, '__ps_t': 8, 'char': 1, 'int': 4,
        'short': 2, 'long': 4, 'float': 4, 'double': 8, 'bool': 1}
RT_W.update({'void *': 4, 'char *': 4, 's8 *': 4, 'u8 *': 4, 's16 *': 4,
             'u16 *': 4, 's32 *': 4, 'u32 *': 4, 'f32 *': 4, 'f64 *': 4,
             '__ps_t *': 4, 'void **': 4})
# pun form `*((T *)&((Unk_X *)B)->unkNN)`: capture the cast's parenthesized
# content, then T = content minus its final `*` (the cast star).
RT_PUN = re.compile(
    r'\*\(\s*\(\s*([^()]*?)\s*\)\s*&\s*\(\s*\(\s*'
    r'(' + CLASS + r')\s*\*\)([A-Za-z_]\w*)\s*\)\s*->\s*'
    r'unk0x([0-9A-Fa-f]+)\s*\)')
# typed-base pun `*((T *)&name->unkNN)` — the class comes from the base
# name's declaration, resolved through rt_decl_map (per file).
TB_PUN = re.compile(
    r'\*\(\s*\(\s*([^()]*?)\s*\)\s*&\s*([A-Za-z_]\w*)\s*->\s*'
    r'unk0x([0-9A-Fa-f]+)\s*\)')
RT_CAST = re.compile(
    r'\(\s*\(\s*(' + CLASS + r')\s*\*\)[\w.]+\s*\)\s*->\s*'
    r'unk0x([0-9A-Fa-f]+)\b')
RT_BARE = re.compile(r'\b([A-Za-z_]\w*)\s*->\s*unk0x([0-9A-Fa-f]+)\b')
RT_DECL = re.compile(r'\((' + CLASS + r')\s*\*+\s*([A-Za-z_]\w*)\)')
RT_ADDR = re.compile(
    r'&\s*\(?\s*\(\s*(' + CLASS + r')\s*\*\)[\w.]+\s*\)?\s*->\s*'
    r'unk0x([0-9A-Fa-f]+)\b')


def header_field_types():
    """class -> {offset: type} parsed from the current structs.h."""
    txt = open(ds.OUT_H, encoding='utf-8').read()
    out = {}
    for m in re.finditer(r'typedef struct (' + CLASS + r') \{(.*?)\} \1;',
                         txt, re.S):
        fields = {}
        for fm in re.finditer(
                r'([A-Za-z_][\w \*]*?)\s+(unk0x([0-9A-Fa-f]+)|pad0x[0-9A-Fa-f]+\[[0-9A-Fa-f]+\])\s*;',
                m.group(2)):
            if fm.group(3):
                fields[int(fm.group(3), 16)] = fm.group(1).strip()
        out[canonical(m.group(1))] = fields
    return out


def blank_pun_text(txt):
    """Blank both pun families so their member text never counts as a plain
    read / address-of use in the disqualification scans."""
    out = list(txt)
    for rx in (RT_PUN, TB_PUN):
        for m in rx.finditer(txt):
            for i in range(m.start(), m.end()):
                out[i] = ' '
    return ''.join(out)


def rt_decl_map(txt):
    """name -> classes it is declared as in params/locals/externs."""
    out = collections.defaultdict(set)
    for m in RT_DECL.finditer(txt):
        out[m.group(2)].add(canonical(m.group(1)))
    # locals: `Unk_X *p;` / `CStruct *p;` / ... outside parens
    for m in re.finditer(r'\b(' + CLASS + r')\s*\*+\s*([A-Za-z_]\w*)\s*(?:;|=|,|\))', txt):
        out[m.group(2)].add(canonical(m.group(1)))
    return out


def find_retarget_candidates(files):
    """Return {cls: {off: new_type}} to retype, with full-use analysis."""
    puns = collections.Counter()
    plain = set()
    addrt = set()
    for f in files:
        txt = open(f, encoding='utf-8', errors='replace').read()
        masked = blank_pun_text(txt)
        for m in RT_PUN.finditer(txt):
            puns[(canonical(m.group(2)), int(m.group(4), 16),
                  m.group(1).strip())] += 1
        dm = rt_decl_map(masked)
        for m in TB_PUN.finditer(txt):
            for cls in dm.get(m.group(2), ()):
                puns[(cls, int(m.group(3), 16),
                      m.group(1).strip())] += 1
        for m in RT_CAST.finditer(masked):
            plain.add((canonical(m.group(1)), int(m.group(2), 16)))
        for m in RT_BARE.finditer(masked):
            for cls in dm.get(m.group(1), ()):
                plain.add((cls, int(m.group(2), 16)))
        for m in RT_ADDR.finditer(masked):
            addrt.add((canonical(m.group(1)), int(m.group(2), 16)))
        # bare `&p->unkNN` on a typed local — genuine address-of use
        for m in re.finditer(r'&\s*([A-Za-z_]\w*)\s*->\s*unk0x([0-9A-Fa-f]+)\b', masked):
            for cls in dm.get(m.group(1), ()):
                addrt.add((cls, int(m.group(2), 16)))
    hdr = header_field_types()
    cand = {}
    bymember = collections.defaultdict(list)
    for (cls, off, T), n in puns.items():
        bymember[(cls, off)].append((T, n))
    for (cls, off), uses in bymember.items():
        decl = hdr.get(cls, {}).get(off)
        if decl is None or 'volatile' in decl:
            continue
        ts = set(t for t, _ in uses)
        if len(ts) != 1:
            continue
        T = next(iter(ts))
        # T came from `(content *)`: content minus its final star
        T = T.rstrip().rstrip('*').rstrip() or T
        if 'volatile' in T or ' ' in T:
            continue  # qualified / multi-word pun types stay raw
        if RT_W.get(decl) != RT_W.get(T) or RT_W.get(T) is None:
            continue  # width-changing or unknown pun types stay raw
        if (cls, off) in plain or (cls, off) in addrt:
            continue  # other code reads the member as declared — shared field
        cand[(cls, off)] = T
    return cand, puns, hdr


def retarget_apply(cand, files):
    """Flip header + cache field types, rewrite pun sites, verify per file.
    Returns (written, reverted, sites)."""
    # 1. header: retype the field line inside the class's own typedef block
    htxt = open(ds.OUT_H, encoding='utf-8').read()
    for (cls, off), T in cand.items():
        decl = header_field_types()[cls][off]
        def repl(m):
            return m.group(1) + ' %s %s;' % (T, m.group(2))
        pat = re.compile(r'(typedef struct ' + class_alt(cls) + r' \{(.*?)\} ' + class_alt(cls) + r';)', re.S)
        bm = pat.search(htxt)
        assert bm, cls
        body = bm.group(1)
        lm = re.search(r'^([ ]+)%s (unk0x%X);$' % (re.escape(decl), off),
                       body, re.M)
        assert lm, (cls, hex(off), decl)
        newbody = body[:lm.start()] + lm.group(1) + T + \
            ' unk0x%X;' % off + body[lm.end():]
        htxt = htxt.replace(body, newbody)
    open(ds.OUT_H, 'w').write(htxt)
    # 2. cache: retype the field in the frozen reference
    import json
    cache = json.load(open(ds.CACHE))
    names = cache['names']
    ci_by_name = {v: int(k) for k, v in names.items()}
    for (cls, off), T in cand.items():
        ci = ci_by_name[cls]
        cache['offs'][str(ci)][str(off)] = T
    json.dump(cache, open(ds.CACHE, 'w'), sort_keys=True)
    # 3. rewrite files
    written = reverted = sites = 0
    for f in files:
        txt = open(f, encoding='utf-8', errors='replace').read()
        repls = []
        for m in RT_PUN.finditer(txt):
            cls, off = canonical(m.group(2)), int(m.group(4), 16)
            if (cls, off) in cand:
                repls.append((m.start(), m.end(),
                              '((%s *)%s)->unk0x%X' % (display(cls), m.group(3), off)))
        dm = rt_decl_map(blank_pun_text(txt))
        for m in TB_PUN.finditer(txt):
            off = int(m.group(3), 16)
            scls = sorted(dm.get(m.group(2), ()))
            # rewrite only when the base name's class is unambiguous here and
            # that exact (class, offset) flipped — `name` then reads the
            # retyped member directly, no cast needed.
            if len(scls) == 1 and (scls[0], off) in cand:
                repls.append((m.start(), m.end(),
                              '%s->unk0x%X' % (m.group(2), off)))
        if not repls:
            continue
        new_txt = txt
        for a, b, rep in sorted(repls, key=lambda r: -r[0]):
            new_txt = new_txt[:a] + rep + new_txt[b:]
        mn = FN_RE.match(os.path.basename(f))
        addr = int(mn.group(1), 16) if mn else None
        is_src = f.startswith(os.path.join(ROOT, 'src', '')) and not f.startswith(
            os.path.join(ROOT, 'src', 'wip', ''))
        if is_src and addr is not None:
            sym_size = SYM_SIZE.get(addr)
            if sym_size is not None and verify_src(addr, sym_size, new_txt):
                open(f, 'w').write(new_txt)
                written += 1
                sites += len(repls)
            else:
                reverted += 1
        else:
            if addr is not None and verify_compiles(addr, txt) and \
                    not verify_compiles(addr, new_txt):
                reverted += 1
            else:
                open(f, 'w').write(new_txt)
                written += 1
                sites += len(repls)
    return written, reverted, sites


# ---------------------------------------------------------------------------
# --fnptr-fields: retype call-only 4-byte struct slots to fn-pointer members.
#
# A slot detected as `s32` (every load is 4 bytes) but whose corpus-wide uses
# are exclusively cast-call targets — `((RET (*)(ARGS))SLOT)(...)` — is really
# a function-pointer field (vtbl / handler slot). When the slot has no data
# uses (stores, comparisons, address-of, passing-by-value) the field is
# retyped in the header + cache to its strict-majority call signature
# `RET (*)(ARGS)`. Majority call sites then drop the cast; deviant-signature
# sites keep an explicit fn->fn cast (legal, codegen-neutral — the original
# cast of an s32 was already there). Sites that load the slot into a local
# (`s32 L; ... L = SLOT;`) retype the local; m2c single-use temps are inlined.
# src files are byte-verified per-file like every rewrite.
# Idempotent: on re-run the flipped field's header decl already contains '(',
# so it is skipped, and majority sites are already cast-free.
# ---------------------------------------------------------------------------
FNP = '--fnptr-fields' in sys.argv

FP_CAST = re.compile(
    r'\(\s*\(\s*([A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)?\s*\*?)\s*\(\s*\*\s*\)')
FP_MEM_I = re.compile(
    r'\(\s*\(\s*(' + CLASS + r')\s*\*\)\s*'
    r'([A-Za-z_]\w*(?:\s*->\s*[A-Za-z_]\w*)*)\s*\)\s*->\s*'
    r'unk0x([0-9A-Fa-f]+)\b')
FP_MEM_B = re.compile(r'\b([A-Za-z_]\w*)\s*->\s*unk0x([0-9A-Fa-f]+)\b')


def _fp_balanced(txt, i):
    d = 0
    while i < len(txt):
        c = txt[i]
        if c == '(':
            d += 1
        elif c == ')':
            d -= 1
            if d == 0:
                return i
        i += 1
    return -1


def _fp_windows(masked):
    """Yield (s, oc, aa, ac, k, ret, argtxt) for every `((RET (*)(ARGS))C)(A)`
    cast-call. s = cast start, oc = the `)` closing the callee expression
    (callee text is masked[k:oc], where k sits right after the cast's own
    closing paren; bridge casts like `(void *)M` live inside that zone), and
    [aa, ac] is the call's argument span."""
    for m in FP_CAST.finditer(masked):
        i = m.end()
        if i >= len(masked) or masked[i] != '(':
            continue
        c1 = _fp_balanced(masked, i)
        if c1 < 0 or c1 + 1 >= len(masked) or masked[c1 + 1] != ')':
            continue
        k = c1 + 2
        d, oc = 1, k
        while oc < len(masked):
            c = masked[oc]
            if c == '(':
                d += 1
            elif c == ')':
                d -= 1
                if d == 0:
                    break
            oc += 1
        if oc >= len(masked) or d != 0:
            continue
        aa = oc + 1
        if aa >= len(masked) or masked[aa] != '(':
            continue
        ac = _fp_balanced(masked, aa)
        if ac < 0:
            continue
        yield (m.start(), oc, aa, ac, k, m.group(1).strip(),
               masked[i + 1:c1].strip())


def _fp_members(masked, declmap):
    """Yield (st, en, cls, off) member occurrences. Inline casts know their
    class; bare accesses resolve the base name through declmap. Classes are
    canonical Unk_ keys (display spellings mapped back)."""
    for m in FP_MEM_I.finditer(masked):
        yield (m.start(), m.end(), canonical(m.group(1)), int(m.group(3), 16))
    for m in FP_MEM_B.finditer(masked):
        for cls in declmap.get(m.group(1), ()):
            yield (m.start(), m.end(), cls, int(m.group(2), 16))


def _fp_mem_in_window(win, occ):
    """True when occ sits in the callee zone of win (not its arguments)."""
    s, oc, _aa, _ac, _k, _ret, _at = win
    return s <= occ[0] and occ[1] <= oc


def _fp_load_target(masked, st, en):
    """When masked[st:en] is the whole RHS of `L = (M);` return L else None."""
    i = en
    while i < len(masked) and masked[i] in ' \t':
        i += 1
    if i >= len(masked) or masked[i] != ';':
        return None
    p = st - 1
    while p >= 0 and masked[p] in ' \t':
        p -= 1
    if p >= 0 and masked[p] == ')':
        d = 1
        q = p - 1
        while q >= 0 and d:
            if masked[q] == ')':
                d += 1
            elif masked[q] == '(':
                d -= 1
            q -= 1
        if q < 0:
            return None
        p = q - 1
        while p >= 0 and masked[p] in ' \t':
            p -= 1
    if p < 0 or masked[p] != '=':
        return None
    p -= 1
    while p >= 0 and masked[p] in ' \t':
        p -= 1
    q = p
    while q >= 0 and (masked[q].isalnum() or masked[q] == '_'):
        q -= 1
    L = masked[q + 1:p + 1]
    r = q
    while r >= 0 and masked[r] in ' \t':
        r -= 1
    if not L or not L[0].isalpha() or (r >= 0 and masked[r] not in ';{\n'):
        return None
    return L


def _fp_decl(masked, L):
    """Return the type string of L's scalar declaration, or None. Only a
    unique `TYPE L;` decl with a 4-byte scalar type qualifies for retyping."""
    hits = []
    for m in re.finditer(
            r'^[ \t]*([A-Za-z_][\w ]*?\*?)[ \t]+' + re.escape(L) +
            r'[ \t]*;', masked, re.M):
        t = ' '.join(m.group(1).split())
        if RT_W.get(t) == 4:
            hits.append(t)
    return hits[0] if len(hits) == 1 else None


def _fp_line_of(txt, pos):
    return txt.count('\n', 0, pos) + 1


def _fp_callee_name(masked, win):
    """The identifier a cast-call ultimately invokes, or None when the callee
    is not a plain (possibly cast-wrapped) identifier."""
    _s, _oc, _aa, _ac, k, _r, _a = win
    ct = masked[k:win[1]].rstrip()
    m = re.match(r'^(?:\([^()]*\)\s*)*([A-Za-z_]\w*)$', ct)
    if m and m.end() == len(ct):
        return m.group(1)
    return None


def _fp_callee_idx(wins, occs):
    """Parallel to occs: for each occurrence the window index for which it is
    the EFFECTIVE callee — the last member access in that window's callee
    zone — else None. Earlier accesses in the same zone (chained bases like
    `((Unk_X *)a->unkN)->unkM` or `(void *)(x->unkM)`) are base reads, not
    calls, and fall through to data-use handling. The innermost window wins
    when occurrences nest."""
    n = len(occs)
    inn = [None] * n
    for oi, occ in enumerate(occs):
        cw = [i for i, w in enumerate(wins) if _fp_mem_in_window(w, occ)]
        if cw:
            inn[oi] = min(cw, key=lambda i: (wins[i][1] - wins[i][0],
                                             wins[i][0]))
    zone_max = {}
    for oi in range(n):
        wi = inn[oi]
        if wi is not None and (wi not in zone_max or
                               occs[oi][1] > occs[zone_max[wi]][1]):
            zone_max[wi] = oi
    out = [None] * n
    for wi, oi in zone_max.items():
        out[oi] = wi
    return out


def find_fnptr_candidates(files):
    """Return (cand, report). cand[(cls, off)] = (ret, argtxt). A member
    qualifies when (a) the header field is a 4-byte scalar, (b) every corpus
    use is a cast-call callee or a load into a retypeable local / inlinable
    single-use temp, and (c) call signatures have a strict majority."""
    hdr = header_field_types()
    calls = collections.defaultdict(list)    # (cls, off) -> [(ret, args)]
    loads = collections.defaultdict(dict)    # (cls, off) -> {file: {L: stats}}
    baduse = collections.defaultdict(list)   # (cls, off) -> [(file, line)]
    for f in files:
        txt = open(f, encoding='utf-8', errors='replace').read()
        masked = ds.mask_comments_strings(txt)
        dm = rt_decl_map(masked)
        wins = list(_fp_windows(masked))
        occs = list(_fp_members(masked, dm))
        cal = _fp_callee_idx(wins, occs)
        for oi, occ in enumerate(occs):
            st, en, cls, off = occ
            key = (cls, off)
            wi = cal[oi]
            if wi is not None:
                w = wins[wi]
                calls[key].append((w[5], w[6]))
            else:
                L = _fp_load_target(masked, st, en)
                if L is not None:
                    stat = loads[key].setdefault(
                        f, {}).setdefault(L, {'decl': None, 'loads': 0,
                                              'calls': 0, 'bad': 0})
                    stat['loads'] += 1
                else:
                    baduse[key].append((f, _fp_line_of(txt, st)))
    cand = {}
    report = []
    for (cls, off), sigs in calls.items():
        decl = hdr.get(cls, {}).get(off)
        if decl is None or '(' in decl or 'volatile' in decl:
            continue
        if RT_W.get(decl) != 4:
            continue
        if baduse.get((cls, off)):
            continue
        cnt = collections.Counter(sigs)
        (ret, args), topn = cnt.most_common(1)[0]
        if topn * 2 <= len(sigs):
            continue  # no strict majority — shared heterogeneous slot
        perfile = loads.get((cls, off), {})
        ok = True
        for path, lstats in perfile.items():
            ptext = open(path, encoding='utf-8', errors='replace').read()
            pmask = ds.mask_comments_strings(ptext)
            pwin = list(_fp_windows(pmask))
            for L, st_ in lstats.items():
                declT = _fp_decl(pmask, L)
                st_['decl'] = declT
                dlre = re.compile(r'^[ \t]*[A-Za-z_][\w ]*?\*?[ \t]+'
                                  + re.escape(L) + r'[ \t]*;', re.M)
                for m in re.finditer(r'\b' + re.escape(L) + r'\b', pmask):
                    pos = m.start()
                    line_st = pmask.rfind('\n', 0, pos) + 1
                    if dlre.match(pmask, line_st):
                        continue  # the declaration itself
                    cal = False
                    for w in pwin:
                        s, oc, _aa, _ac, _k, _r, _a = w
                        if s <= pos and pos + len(L) <= oc and \
                                _fp_callee_name(pmask, w) == L:
                            cal = True
                            break
                    if cal:
                        st_['calls'] += 1
                        continue
                    i = pos + len(L)
                    while i < len(pmask) and pmask[i] in ' \t':
                        i += 1
                    if i < len(pmask) and pmask[i] == '=':
                        continue  # assignment LHS (the load)
                    st_['bad'] += 1
                if declT is not None:
                    # declared local: mode 1 (call-only, retype decl) or
                    # mode 3 (dual-use s32, cast (s32) at each load)
                    st_['mode'] = 1 if st_['bad'] == 0 else 3
                else:
                    # m2c temp: exactly one load and one call use required
                    if st_['loads'] == 1 and st_['calls'] == 1 \
                            and st_['bad'] == 0:
                        st_['mode'] = 2
                    else:
                        ok = False
        if not ok:
            report.append('%s.unk0x%X: SKIP bad loads %s' % (
                cls, off, {os.path.basename(p): v
                           for p, v in perfile.items()}))
            continue
        cand[(cls, off)] = (ret, args)
        report.append('%s.unk0x%X: %s -> %s (*)(%s)   %d calls %s' % (
            cls, off, decl, ret, args, len(sigs),
            {('%s(%s)' % k): v for k, v in cnt.items()}))
        for path, lstats in perfile.items():
            for L, st_ in lstats.items():
                report.append('    load %-16s %-22s x%d (decl %s, calls %d, '
                              'bad %d, mode %d)' % (L, os.path.basename(path),
                                                     st_['loads'], st_['decl'],
                                                     st_['calls'], st_['bad'],
                                                     st_.get('mode', 0)))
    return cand, report


def fnptr_apply(cand, files):
    """Flip header + cache field types, rewrite call sites, verify per file.
    Returns (written, reverted, sites)."""
    # 1. header + cache flip
    htxt = open(ds.OUT_H, encoding='utf-8').read()
    for (cls, off), (ret, args) in cand.items():
        decl = header_field_types()[cls][off]
        pat = re.compile(r'(typedef struct ' + class_alt(cls) + r' \{(.*?)\} ' + class_alt(cls) + r';)', re.S)
        bm = pat.search(htxt)
        assert bm, cls
        body = bm.group(1)
        lm = re.search(r'^([ ]+)%s (unk0x%X);$' % (re.escape(decl), off),
                       body, re.M)
        assert lm, (cls, hex(off), decl)
        newbody = body[:lm.start()] + lm.group(1) + \
            '%s (*%s)(%s);' % (ret, 'unk0x%X' % off, args) + body[lm.end():]
        htxt = htxt.replace(body, newbody)
    open(ds.OUT_H, 'w').write(htxt)
    import json
    cache = json.load(open(ds.CACHE))
    names = cache['names']
    ci_by_name = {v: int(k) for k, v in names.items()}
    for (cls, off), (ret, args) in cand.items():
        ci = ci_by_name[cls]
        cache['offs'][str(ci)][str(off)] = '%s (*)(%s)' % (ret, args)
    json.dump(cache, open(ds.CACHE, 'w'), sort_keys=True)

    # 2. per-file rewrites
    written = reverted = sites = 0
    for f in files:
        txt = open(f, encoding='utf-8', errors='replace').read()
        masked = ds.mask_comments_strings(txt)
        dm = rt_decl_map(masked)
        wins = list(_fp_windows(masked))
        occs = list(_fp_members(masked, dm))
        repls = []
        # 2a. windows whose callee zone's effective callee is a flipped
        # member (the last member access in the zone). Callee zones that pun
        # the slot (`*((void * *)&M)`, any `&`) keep their text: dropping the
        # pun around a member changes codegen.
        cal = _fp_callee_idx(wins, occs)
        for wi, w in enumerate(wins):
            s, oc, _aa, _ac, k, ret, argtxt = w
            if '&' in masked[k:oc]:
                continue
            inside = [oi for oi, o in enumerate(occs)
                      if _fp_mem_in_window(w, o)]
            if not inside:
                continue
            maxoi = max(inside, key=lambda oi: occs[oi][1])
            if cal[maxoi] != wi:
                continue  # not the effective callee of this window
            st, en, cls, off = occs[maxoi]
            if (cls, off) not in cand:
                continue
            cret, cargs = cand[(cls, off)]
            mtext = txt[st:en]
            rep = mtext if (ret, argtxt) == (cret, cargs) else \
                '((%s (*)(%s))%s)' % (ret, argtxt, mtext)
            repls.append((s, oc + 1, rep))
            sites += 1
        # 2b. load locals / m2c temps feeding calls of flipped members
        for (cls, off), (cret, cargs) in cand.items():
            lmap = collections.defaultdict(list)  # L -> [load occ spans]
            for o in occs:
                if (o[2], o[3]) != (cls, off):
                    continue
                L = _fp_load_target(masked, o[0], o[1])
                if L is not None:
                    lmap[L].append((o[0], o[1]))
            for L, spans in lmap.items():
                # re-derive the local's use mode exactly as the candidate
                # scan did (cheap: only files with loads reach this point)
                pwin = wins
                dlre = re.compile(r'^[ \t]*[A-Za-z_][\w ]*?\*?[ \t]+'
                                  + re.escape(L) + r'[ \t]*;', re.M)
                ncall = nbad = 0
                for m in re.finditer(r'\b' + re.escape(L) + r'\b', masked):
                    pos = m.start()
                    line_st = masked.rfind('\n', 0, pos) + 1
                    if dlre.match(masked, line_st):
                        continue
                    if any(s <= pos and pos + len(L) <= oc and
                           _fp_callee_name(masked, w) == L
                           for w in pwin for (s, oc, _a, _b, _c, _d, _e) in [w]):
                        ncall += 1
                        continue
                    i = pos + len(L)
                    while i < len(masked) and masked[i] in ' \t':
                        i += 1
                    if i < len(masked) and masked[i] == '=':
                        continue
                    nbad += 1
                decl = _fp_decl(masked, L)
                if decl is not None and nbad == 0:
                    # mode 1: retype `TYPE L;` -> `RET (*L)(ARGS);`
                    dpat = (r'^([ \t]*)' + re.escape(decl) + r'[ \t]+' +
                            re.escape(L) + r'[ \t]*;')
                    m0 = re.search(dpat, masked, re.M)
                    assert m0, (f, L, decl)
                    m1 = re.search(dpat, txt[m0.start():])
                    assert m1, (f, L, decl)
                    a = m0.start() + m1.start()
                    b = m0.start() + m1.end()
                    repls.append((a, b, m1.group(1) +
                                  '%s (*%s)(%s);' % (cret, L, cargs)))
                    sites += 1
                    # rewrite each cast-call window that calls L directly
                    for w in wins:
                        s, oc, _aa, _ac, _k, ret, argtxt = w
                        if _fp_callee_name(masked, w) != L:
                            continue
                        rep = L if (ret, argtxt) == (cret, cargs) else \
                            '((%s (*)(%s))%s)' % (ret, argtxt, L)
                        repls.append((s, oc + 1, rep))
                        sites += 1
                elif decl is not None and nbad > 0:
                    # mode 3: dual-use s32 local — cast at each load
                    for (o0, o1) in spans:
                        repls.append((o0, o1, '(s32)%s' % txt[o0:o1]))
                        sites += 1
                else:
                    # mode 2 (m2c temp): single load line + single call use
                    # (validated in find_fnptr_candidates). Delete the load
                    # line; rewrite the use window with the member expression.
                    for (o0, o1) in spans:
                        ls = txt.rfind('\n', 0, o0) + 1
                        le = txt.find('\n', o1)
                        if le < 0:
                            le = len(txt)
                        else:
                            le += 1
                        line = txt[ls:le]
                        if re.match(r'^\s*' + re.escape(L) +
                                    r'\s*=\s*[^;]*;\s*$', line):
                            repls.append((ls, le, ''))
                            mtext = txt[o0:o1]
                            for w in wins:
                                s, oc, _aa, _ac, _k, ret, argtxt = w
                                if _fp_callee_name(masked, w) != L:
                                    continue
                                rep = mtext if (ret, argtxt) == (cret, cargs) \
                                    else '((%s (*)(%s))%s)' % (
                                        ret, argtxt, mtext)
                                repls.append((s, oc + 1, rep))
                                sites += 1
        if not repls:
            continue
        new_txt = apply_repls(txt, repls)
        mn = FN_RE.match(os.path.basename(f))
        addr = int(mn.group(1), 16) if mn else None
        is_src = f.startswith(os.path.join(ROOT, 'src', '')) and not \
            f.startswith(os.path.join(ROOT, 'src', 'wip', ''))
        if is_src and addr is not None:
            sym_size = SYM_SIZE.get(addr)
            if sym_size is not None and verify_src(addr, sym_size, new_txt):
                open(f, 'w').write(new_txt)
                written += 1
            else:
                reverted += 1
        else:
            if addr is not None and verify_compiles(addr, txt) and \
                    not verify_compiles(addr, new_txt):
                reverted += 1
            else:
                open(f, 'w').write(new_txt)
                written += 1
    return written, reverted, sites
# ---------------------------------------------------------------------------
# --local-fnptrs: drop cast-calls whose callee is not a struct member.
#
# Three remaining families after --fnptr-fields:
#
#   A. A local is ALREADY declared `RET (*NAME)(D1, ...)` (m2c typed it from
#      a load cast), but the call site hides the prototype with a cast:
#        s32 (*var_r9)(s32, s32, s32);
#        var_r9 = (s32 (*)(s32, s32, s32))temp_entry.unk4;
#        ...
#        ((s32 (*)(void *, void *, void *))var_r9)((char *)arg0 + r, a, b);
#      The decl arg types are retyped to the call's actual argument shapes
#      (pointer-typed expressions -> the pointee/void type, f32 stays f32,
#      integers stay s32/u32), every fn-ptr cast that feeds NAME (the decl
#      and load-cast lines) is retyped to match, and each cast-call becomes
#      a plain `var_r9(...)`.  Sites whose call-arg COUNT differs from the
#      decl (m2c register-reuse temps, `()` old-style decls) are skipped.
#
#   B. An int-typed local holds a fn pointer loaded from a member
#      (`s32 fp; fp = vt->unk0xC; ... ((void (*)(...))fp)(...)`).  When the
#      local's only other uses are comparisons and member loads (no
#      arithmetic), its decl is retyped to the call signature, the loads get
#      an explicit fn-ptr cast, and the call drops its cast.
#
#   C. The callee zone bridges a 4-byte member read through `(s32)` /
#      `(void *)`: `((s32 (*)(void *))(s32)(p->unkN))(...)`.  For a raw
#      (shared) scalar field the bridge cast is redundant — the member keeps
#      a single direct fn-ptr cast, exactly like the 815 member-direct raw
#      sites that already read `((s32 (*)(void *))p->unkN)`.
#
# src files are byte-verified per file like every rewrite; wip drafts are
# compile-checked (reverted only when the rewrite breaks a compiling body).
# Idempotent: family A disappears once decls match; B once the int local is
# retyped; C once the redundant bridge is gone.
# ---------------------------------------------------------------------------
LNP = '--local-fnptrs' in sys.argv

# fn-ptr local decl:  `RET (*NAME)(ARGS);`
LNP_DECL = re.compile(
    r'^[ \t]*(?:register\s+)?(?:const\s+)?'
    r'((?:s8|u8|s16|u16|s32|u32|s64|u64|f32|f64|void|char)\s*\**\s*'
    r'\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*(?:\(\s*\"[^\"]*\"\s*\)\s*)?'
    r'\(([^)]*)\))\s*;', re.M)
# scalar local decl:  `s32 NAME;`
LNP_INTDECL = re.compile(
    r'^[ \t]*(?:register\s+)?(?:const\s+)?'
    r'(s32|u32|int|long)\s+([A-Za-z_]\w*)\s*;', re.M)
# fn-ptr cast feeding NAME (assignment load): `NAME = (RET (*)(ARGS))SRC;`
LNP_LOADCAST = re.compile(
    r'^[ \t]*([A-Za-z_]\w*)\s*=\s*\(\s*'
    r'((?:s8|u8|s16|u16|s32|u32|s64|u64|f32|f64|void|char)\s*\**\s*'
    r'\(\s*\*\s*\)\s*\([^)]*\))\s*\)\s*', re.M)


def _lnp_arg_shape(a):
    """Register class of a call-argument expression: 'f' for float, 'p' for
    a pointer-shaped value, 'i' for integers, None when unknown.  Only the
    GPR-vs-FPR split changes caller codegen, so retyping between 'p' and
    'i' spellings is byte-neutral — both pass a 32-bit GPR."""
    a = a.strip()
    if not a:
        return None
    if re.match(r'^(?:temp_f|var_f|farg|_f|f_)\w*$', a) or \
            re.match(r'^\(f32\)|^\(double\)|^\(f64\)', a):
        return 'f'
    if a.startswith('&') or re.match(r'^\([^()]*\*\)', a) or \
            re.search(r'->\s*unk0x[0-9A-Fa-f]+', a) or \
            re.match(r'^\b(?:fn_|lbl_)[0-9A-Fa-f]+\b', a):
        return 'p'
    if re.match(r'^[0-9]|^-?0x', a):
        return 'i'
    return None


def _lnp_pointer_type(a, dtypes):
    """A clean pointer type for a pointer-shaped call argument: the declared
    pointer type of a bare identifier, else 'void *'."""
    m = re.match(r'^([A-Za-z_]\w*)$', a)
    if m:
        t = dtypes.get(m.group(1))
        if t and t.endswith('*'):
            return t
    if a.startswith('&'):
        return 'void *'
    mm = re.search(r'\(\s*((?:%s|char|void|s8|u8|s16|u16|s32|u32)'
                   r'\s*\*)\s*\)' % CLASS_INNER, a)
    if mm:
        return mm.group(1).strip()
    return 'void *'


def _lnp_decl_types(txt):
    """name -> declared type for pointer/float params + locals."""
    out = {}
    for m in re.finditer(
            r'^[ \t]*(?:register\s+)?(?:const\s+)?'
            r'((?:%s|s8|u8|s16|u16|s32|u32|s64|u64|f32|f64|void|char)'
            r'\s*\**)\s+([A-Za-z_]\w*)\s*[;=]' % CLASS_INNER, txt, re.M):
        t = m.group(1).strip()
        if t.endswith('*') or t in ('f32', 'f64', 'double'):
            out.setdefault(m.group(2), t)
    return out


def _lnp_call_args(masked, w):
    return masked[w[2] + 1:w[3]]


def find_local_candidates(files):
    """Return (cand, report).  cand[file] = list of rewrite tuples; only
    family-A locals, family-B int locals and family-C bridge sites that
    survive eligibility."""
    cand = {}
    report = []
    hdr = header_field_types()
    for f in files:
        txt = open(f, encoding='utf-8', errors='replace').read()
        masked = ds.mask_comments_strings(txt)
        dtypes = _lnp_decl_types(txt)
        wins = list(_fp_windows(masked))
        fnptr_of = {}
        for m in LNP_DECL.finditer(txt):
            fnptr_of[m.group(2)] = (m.group(1), m.group(3), m.start(), m.end())
        # ---------------- family A ----------------
        for name, (decl, dargs, ds0, de0) in fnptr_of.items():
            calls = []            # (win, callee-text, arg-text)
            for w in wins:
                if ap_callee_name_is(masked, w, name):
                    calls.append((w, masked[w[4]:w[1]].strip(),
                                  _lnp_call_args(masked, w)))
            if not calls:
                continue
            dlist = [x.strip() for x in dargs.split(',') if x.strip()]
            if len(dlist) == 0:
                continue  # `()` old-style decl — retyping is a guess
            rows = []
            ok = True
            for w, ct, cargs in calls:
                clist = [x.strip() for x in cargs.split(',') if x.strip()]
                if len(clist) != len(dlist):
                    ok = False
                    break
                rows.append(clist)
            if not ok:
                continue
            # per-position: adopt pointer/f32 types that every call agrees
            # on.  The decl arg count must equal the call count (checked
            # above), so the final text drops the cast entirely; args that
            # are ints keep the existing spelling (byte-neutral GPR pass).
            newargs = list(dlist)
            for i in range(len(dlist)):
                shapes = [_lnp_arg_shape(r[i]) for r in rows]
                if 'f' in shapes and all(s in ('f', None) for s in shapes):
                    if dlist[i] != 'f32':
                        newargs[i] = 'f32'
                elif 'p' in shapes and all(s in ('p', None) for s in shapes):
                    t = _lnp_pointer_type(rows[0][i], dtypes)
                    if dlist[i] != t:
                        newargs[i] = t
            # every fn-ptr cast feeding NAME must have the same arg count so
            # it can be retyped along with the decl
            n_extra = 0
            for lm in LNP_LOADCAST.finditer(txt):
                if lm.group(1) != name:
                    continue
                la = lm.group(2)
                mm = re.search(r'\(\s*\*\s*\)\s*\(([^)]*)\)', la)
                if mm and len([x for x in mm.group(1).split(',')
                               if x.strip()]) != len(dlist):
                    ok = False
                    break
                n_extra += 1
            if not ok:
                continue
            cand.setdefault(f, []).append(
                (name, decl, ds0, de0, dargs, ', '.join(newargs), calls,
                 n_extra, 'A', '', '', len(calls)))
            report.append('%s:%d %-12s %s(%s) -> (%s)  %d calls, %d load-cast'
                          % (os.path.basename(f), _ln(txt, ds0), name,
                             decl.split('(')[0].strip(), dargs,
                             ', '.join(newargs), len(calls), n_extra))
        # ---------------- family B ----------------
        for m in LNP_INTDECL.finditer(txt):
            name = m.group(2)
            if name in fnptr_of or name.startswith(('arg', 'temp_')):
                continue
            if any(re.search(r'__asm__', l) and re.search(
                    r'\b' + name + r'\b', l)
                   for l in txt.split('\n')):
                continue  # register-asm dual-use
            winsig = None
            for w in wins:
                if ap_callee_name_is(masked, w, name):
                    winsig = (w[5], w[6])
                    break
            if winsig is None:
                continue
            # eligibility: EVERY other occurrence of NAME (outside its decl,
            # in masked text so comments don't count) must be either the
            # callee of one of these windows or the LHS of an assignment
            # `NAME = ...;`.  RHS content is irrelevant — apply wraps each
            # load in an explicit (RET (*)(ARGS)) cast.  Any genuine data
            # use (arithmetic operand, arg pass, compare, member store)
            # disqualifies the retype.
            bad = False
            for um in re.finditer(r'\b' + name + r'\b', masked):
                pos = um.start()
                if m.start() <= pos < m.end():
                    continue
                if any(s <= pos <= oc and ap_callee_name_is(masked, w, name)
                       for w in wins for (s, oc) in [(w[0], w[1])]):
                    continue
                i = pos + len(name)
                while i < len(masked) and masked[i] in ' \t':
                    i += 1
                if i < len(masked) and masked[i] == '=' and not (
                        i + 1 < len(masked) and masked[i + 1] == '='):
                    continue  # load LHS
                bad = True
                break
            if bad:
                continue
            # all call windows must agree on the cast signature so the decl
            # retype keeps every dropped cast honest
            sigs = set()
            ncall = 0
            for w in wins:
                if ap_callee_name_is(masked, w, name):
                    sigs.add((w[5], w[6]))
                    ncall += 1
            if len(sigs) != 1:
                continue
            (ret, args) = next(iter(sigs))
            cand.setdefault(f, []).append(
                (name, '', m.start(), m.end(), m.group(1), '', [], 0, 'B',
                 ret, args, ncall))
            report.append('%s:%d %-12s int local cast-called (%s) — retype'
                          '  %d call' % (
                              os.path.basename(f), _ln(txt, m.start()), name,
                              '%s (*)(%s)' % (ret, args), ncall))
        # ---------------- family C ----------------
        # callee zone bridges a scalar member through a redundant cast:
        #   ((s32 (*)(void *))(s32)(p->unkN))(args)
        # The member's header type is already the 4-byte scalar the fn-ptr
        # cast loads, so the (s32) bridge is a no-op.  Dropping it yields
        # the member-direct spelling used by every other raw member site:
        #   ((s32 (*)(void *))p->unkN)(args)
        for w in wins:
            s, oc, _aa, _ac, k, _ret, _at = w
            zone = masked[k:oc].strip()
            bm = re.match(r'^\(\s*s32\s*\)\s*\(\s*'
                          r'((?:\([^()]*\)\s*)*[A-Za-z_]\w*'
                          r'(?:\s*->\s*unk0x[0-9A-Fa-f]+)?)\s*\)$', zone)
            if not bm:
                continue
            base = bm.group(1)
            mm = re.match(r'^(?:\([^()]*\)\s*)*([A-Za-z_]\w*)'
                          r'->\s*unk0x([0-9A-Fa-f]+)$', base)
            if not mm:
                continue
            hdr_t = None
            for cl in rt_decl_map(txt).get(mm.group(1), ()):
                hdr_t = hdr.get(cl, {}).get(int(mm.group(2), 16))
                if hdr_t:
                    break
            if hdr_t != 's32':
                continue  # bridge may be a real widen/narrow — leave it
            cand.setdefault(f, []).append(
                ('', '', 0, 0, '', base, [w], 0, 'C', '', '', 1))
            report.append('%s:%d (s32)-bridge over %s -> direct member' % (
                os.path.basename(f), _ln(txt, s), base))
    return cand, report


def _ln(txt, pos):
    return txt.count('\n', 0, pos) + 1


def ap_callee_name_is(masked, w, name):
    return _fp_callee_name(masked, w) == name


def local_apply(cand, files):
    """Apply family A/B/C rewrites with per-file verification."""
    written = reverted = sites = 0
    for f in files:
        if f not in cand:
            continue
        txt = open(f, encoding='utf-8', errors='replace').read()
        masked = ds.mask_comments_strings(txt)
        wins = list(_fp_windows(masked))
        repls = []
        for (name, decl, ds0, de0, dargs, newargs, calls, n_extra, kind,
             sret, sargs, _ncall) in cand[f]:
            if kind == 'A':
                # 1. decl line args
                a = txt.find(decl, ds0)
                b = a + len(decl)
                mm = re.match(r'^(.*\(\s*\*\s*' + re.escape(name) +
                              r'\s*\)\s*(?:\(\s*\"[^\"]*\"\s*\)\s*)?)'
                              r'\([^)]*\)(.*)$', decl, re.S)
                assert mm, (f, decl)
                repls.append((a, b, mm.group(1) + '(' + newargs + ')' +
                              mm.group(2)))
                sites += 1
                # 2. load-cast lines
                for lm in LNP_LOADCAST.finditer(txt):
                    if lm.group(1) != name:
                        continue
                    oldcast = lm.group(2)
                    m2 = re.match(r'^((?:s8|u8|s16|u16|s32|u32|s64|u64|f32|'
                                  r'f64|void|char)\s*\**\s*\(\s*\*\s*\)'
                                  r'\s*\()(?:[^)]*)(\))$', oldcast, re.S)
                    if m2:
                        repls.append((lm.start(2), lm.end(2),
                                      m2.group(1) + newargs + m2.group(2)))
                        sites += 1
                # 3. each call -> NAME(ARGS)
                for w, ct, cargs in calls:
                    repls.append((w[0], w[1] + 1, name))
                    sites += 1
            elif kind == 'B':  # int local
                # decl: TYPE NAME; -> RET (*NAME)(ARGS);
                dm = re.match(r'^(\s*)(?:register\s+)?(?:const\s+)?'
                              r'(?:s32|u32|int|long)\s+', txt[ds0:de0])
                repls.append((ds0, de0, dm.group(1) + '%s (*%s)(%s);'
                              % (sret, name, sargs)))
                sites += 1
                # loads: NAME = SRC; -> NAME = (RET (*)(ARGS))SRC;
                for um in re.finditer(r'\b' + name + r'\b', masked):
                    pos = um.start()
                    if ds0 <= pos < de0:
                        continue
                    if any(w[0] <= pos <= w[1] and
                           ap_callee_name_is(masked, w, name) for w in wins):
                        continue  # the call's own callee slot
                    i = pos + len(name)
                    while i < len(masked) and masked[i] in ' \t':
                        i += 1
                    if i >= len(masked) or masked[i] != '=':
                        continue
                    j = masked.find(';', i)
                    if j < 0:
                        continue
                    rhs = masked[i + 1:j]
                    cm = re.match(
                        r'^\s*\(\s*((?:s8|u8|s16|u16|s32|u32|s64|u64|f32|'
                        r'f64|void|char)\s*\**\s*\(\s*\*\s*\)\s*\()'
                        r'([^)]*)(\)\s*\))(.*)$', rhs, re.S)
                    if cm:
                        # already a fn-ptr cast — retype its arg list
                        repls.append((i, j, '= (%s (*)(%s))%s'
                                      % (sret, sargs,
                                         cm.group(4).lstrip())))
                    else:
                        repls.append((i, j, '= (%s (*)(%s))%s'
                                      % (sret, sargs, rhs.lstrip())))
                    sites += 1
                # calls -> NAME(ARGS)
                for w in wins:
                    if ap_callee_name_is(masked, w, name):
                        repls.append((w[0], w[1] + 1, name))
                        sites += 1
            else:  # C: drop redundant (s32) bridge in the callee zone
                w = calls[0]
                s, oc, _aa, _ac, _k, ret, atxt = w
                zone = masked[s:oc + 1]
                repls.append((s, oc + 1, '((%s (*)(%s))%s)'
                              % (ret, atxt, newargs)))
                sites += 1
        if not repls:
            continue
        new_txt = apply_repls(txt, repls)
        mn = FN_RE.match(os.path.basename(f))
        addr = int(mn.group(1), 16) if mn else None
        is_src = f.startswith(os.path.join(ROOT, 'src', '')) and not \
            f.startswith(os.path.join(ROOT, 'src', 'wip', ''))
        if is_src and addr is not None:
            sym_size = SYM_SIZE.get(addr)
            if sym_size is not None and verify_src(addr, sym_size, new_txt):
                open(f, 'w').write(new_txt)
                written += 1
            else:
                reverted += 1
        else:
            if addr is not None and verify_compiles(addr, txt) and \
                    not verify_compiles(addr, new_txt):
                reverted += 1
            else:
                open(f, 'w').write(new_txt)
                written += 1
    return written, reverted, sites

# ---------------------------------------------------------------------------
# --nested-ptrs: retype scalar struct slots whose reads are exclusively
# `Unk_X *` pointer uses into typed nested-struct pointers.
#
# A slot detected as s32/u32/int/long/void * but whose every corpus read is a
# direct `((Unk_X *)SLOT)` cast or a load into an Unk_X *-typed local is
# really a pointer to that nested struct — callers hand out the address of a
# Unk_X object through that slot. Stores must be pointer/null too. When the
# reads agree on a single Unk_X and nothing reads the slot as a scalar, the
# header + cache field is retyped to `Unk_X *` and the now-redundant
# `((Unk_X *)SLOT)` wrapping casts are dropped at their sites (codegen-
# neutral: the slot was always loaded as a 4-byte pointer).
#
# structs.h typedefs are positional: a member typed `Unk_X *` needs
# Unk_X's typedef to precede the host class. Forward references use the
# struct-tag form `struct Unk_X *` — legal C89, the tag is declared
# incomplete by the reference and completed by the later typedef. Self-
# referential slots also use the tag form (a typedef name is not in scope
# inside its own declaration).
# ---------------------------------------------------------------------------
NEST = '--nested-ptrs' in sys.argv

NEST_CAST_OPEN = re.compile(r'\(\s*(' + CLASS + r')\s*\*\s*$')
NEST_LOCAL = re.compile(r'\b(' + CLASS + r')\s*\*+\s*([A-Za-z_]\w*)\b')


def _n_scalar(hd):
    return hd is not None and (re.match(r'^(s32|u32|int|long)$', hd)
                               or hd == 'void *')


def _n_stmt_bounds(masked, pos):
    """(start, end) of the statement containing pos. Boundaries are depth-0
    `;`, `{`, or `}` scanned in both directions."""
    n = len(masked)
    s = pos
    d = 0
    while s >= 0:
        c = masked[s]
        if c == '}':
            if d == 0:
                break
            d -= 1
        elif c == '{':
            if d == 0:
                break
            d += 1
        elif c == ';' and d == 0:
            break
        s -= 1
    e = pos
    d = 0
    while e < n:
        c = masked[e]
        if c == '{':
            d += 1
        elif c == '}':
            if d == 0:
                break
            d -= 1
        elif c == ';' and d == 0:
            e += 1
            break
        e += 1
    return s + 1, e


def _n_classify(txt, masked, occ, dm, local_t):
    """Role of one member-read occurrence.

    Returns (kind, drop, tgt):
      kind 'cast:Unk_T' — read is the operand of a wrapping `(Unk_T *)` cast;
        drop = (start, end) of that whole cast expression to delete
      kind 'load:Unk_T' — `L = READ;` with L declared Unk_T *
      kind 'store-null' / 'store-ptr' / 'store-other:<rhs>'
      kind 'other'      — disqualifying scalar use
    """
    st, en, cls, off = occ
    drop = None
    left = masked[max(0, st - 200):st]
    cm = NEST_CAST_OPEN.search(left)
    if cm:
        j = en
        while j < len(masked) and masked[j] in ' \t':
            j += 1
        if j < len(masked) and masked[j] == ')':
            p = st - len(left) + cm.start()
            tgt = canonical(cm.group(1))
            return 'cast:' + tgt, (p, j + 1), tgt
    s0, e0 = _n_stmt_bounds(masked, st)
    stmt = masked[s0:e0]
    base_txt = masked[st:en]
    after = masked[en:en + 60]
    am = re.match(r'\s*=', after)
    if am:
        rest = after[am.end():]
        if re.match(r'^(NULL|0)\b', rest):
            return 'store-null', None, None
        if (re.match(r'^&?\s*[A-Za-z_]', rest)
                or re.match(r'^\s*\(\s*(?:%s|void|char|s8|u8|s16'
                            r'|u16|s32|u32|int)\s*\*+\s*\)' % CLASS_INNER, rest)
                or re.match(r'^[A-Za-z_]\w*\s*->', rest)):
            return 'store-ptr', None, None
        lm2 = re.match(r'^([A-Za-z_]\w*)\b', rest)
        if lm2 and lm2.group(1) in local_t:
            return 'store-ptr', None, None
        return 'store-other:' + rest.strip()[:16], None, None
    mm = re.match(r'^\s*([A-Za-z_]\w*)\s*=\s*(.*?)\s*;?\s*$', stmt, re.S)
    if mm:
        lhs, rhs = mm.group(1), mm.group(2)
        if rhs.strip() == base_txt:
            if lhs in local_t:
                return 'load:' + local_t[lhs], None, local_t[lhs]
            return 'other', None, None
    if re.match(r'\s*->', after):
        return 'deref-chain', None, None
    return 'other', None, None


def _n_local_types(txt):
    out = {}
    for m in NEST_LOCAL.finditer(txt):
        out.setdefault(m.group(2), canonical(m.group(1)))
    return out


def find_nested_candidates(files):
    """Return (cand {cls: {off: Unk_T}}, report) for scalar slots whose every
    use is pointer-to-one-Unk_X. Unk_T must be an existing header class."""
    hdr = header_field_types()
    agg = collections.defaultdict(collections.Counter)
    by_slot = collections.defaultdict(list)
    for f in files:
        txt = open(f, encoding='utf-8', errors='replace').read()
        masked = ds.mask_comments_strings(txt)
        dm = rt_decl_map(txt)
        local_t = _n_local_types(txt)
        for occ in _fp_members(masked, dm):
            cl, off = occ[2], occ[3]
            hd = hdr.get(cl, {}).get(off)
            if not _n_scalar(hd):
                continue
            k, _drop, _t = _n_classify(txt, masked, occ, dm, local_t)
            agg[(cl, off)][k] += 1
            by_slot[(cl, off)].append((os.path.basename(f), k))
    cand = {}
    report = []
    for (cl, off), cnt in sorted(agg.items()):
        reads = {k.split(':', 1)[1]: n for k, n in cnt.items()
                 if k.startswith('cast:') or k.startswith('load:')}
        if len(reads) != 1:
            continue
        if any(not k.startswith(('cast:', 'load:', 'store-null', 'store-ptr'))
               for k in cnt):
            continue
        tgt, nread = next(iter(reads.items()))
        nstore = sum(n for k, n in cnt.items() if k.startswith('store'))
        nall = sum(cnt.values())
        cand.setdefault(cl, {})[off] = tgt
        report.append('%s.unk0x%X: %s -> %s *  (%d use(s), %d read, %d store)'
                      % (cl, off, hdr[cl][off], tgt, nall, nread, nstore))
    return cand, report


def _n_member_type(host, tgt, htxt):
    """Header type text for a tgt-pointer member of host: plain typedef name
    when Unk_tgt already precedes Unk_host, else the struct-tag form.
    host/tgt are canonical keys; the header is matched on either spelling
    and the emission uses the display name."""
    def idx(key):
        m = re.search(r'\btypedef struct %s \{' % class_alt(key), htxt)
        return m.start() if m else None
    hi, ti = idx(host), idx(tgt)
    disp = display(tgt)
    if tgt == host or (hi is not None and ti is not None and ti > hi):
        return 'struct %s *' % disp
    return '%s *' % disp


def nested_apply(cand, files):
    """Flip header + cache field types, drop redundant wrapping casts,
    verify per file. Returns (written, reverted, sites)."""
    # 1. header flip
    htxt = open(ds.OUT_H, encoding='utf-8').read()
    for cls, offs in sorted(cand.items()):
        for off, tgt in sorted(offs.items()):
            decl = header_field_types()[cls][off]
            pat = re.compile(r'(typedef struct ' + class_alt(cls) + r' \{(.*?)\} ' + class_alt(cls) + r';)',
                             re.S)
            bm = pat.search(htxt)
            assert bm, cls
            body = bm.group(1)
            lm = re.search(r'^([ ]+)%s (unk0x%X);$' % (re.escape(decl), off),
                           body, re.M)
            assert lm, (cls, hex(off), decl)
            newbody = body[:lm.start()] + lm.group(1) + \
                _n_member_type(cls, tgt, htxt) + \
                ' unk0x%X;' % off + body[lm.end():]
            htxt = htxt.replace(body, newbody)
    open(ds.OUT_H, 'w').write(htxt)
    # 2. cache flip
    import json
    cache = json.load(open(ds.CACHE))
    names = cache['names']
    ci_by_name = {v: int(k) for k, v in names.items()}
    for cls, offs in cand.items():
        ci = ci_by_name[cls]
        for off, tgt in offs.items():
            cache['offs'][str(ci)][str(off)] = _n_member_type(cls, tgt, htxt)
    json.dump(cache, open(ds.CACHE, 'w'), sort_keys=True)
    # 3. per-file rewrites: drop `((Unk_T *)SLOT)` wraps for flipped slots
    hdr = header_field_types()
    written = reverted = sites = 0
    for f in files:
        txt = open(f, encoding='utf-8', errors='replace').read()
        masked = ds.mask_comments_strings(txt)
        dm = rt_decl_map(txt)
        local_t = _n_local_types(txt)
        repls = []
        for occ in _fp_members(masked, dm):
            cl, off = occ[2], occ[3]
            if cl not in cand or off not in cand[cl]:
                continue
            k, drop, tgt = _n_classify(txt, masked, occ, dm, local_t)
            if k == 'cast:' + cand[cl][off] and drop is not None:
                st, en, _a, _b = occ
                repls.append((drop[0], drop[1], txt[st:en]))
                sites += 1
        if not repls:
            continue
        new_txt = txt
        for a, b, rep in sorted(repls, key=lambda r: -r[0]):
            new_txt = new_txt[:a] + rep + new_txt[b:]
        mn = FN_RE.match(os.path.basename(f))
        addr = int(mn.group(1), 16) if mn else None
        is_src = f.startswith(os.path.join(ROOT, 'src', '')) and not \
            f.startswith(os.path.join(ROOT, 'src', 'wip', ''))
        if is_src and addr is not None:
            sym_size = SYM_SIZE.get(addr)
            if sym_size is not None and verify_src(addr, sym_size, new_txt):
                open(f, 'w').write(new_txt)
                written += 1
            else:
                reverted += 1
        else:
            if addr is not None and verify_compiles(addr, txt) and \
                    not verify_compiles(addr, new_txt):
                reverted += 1
            else:
                open(f, 'w').write(new_txt)
                written += 1
    return written, reverted, sites


# ---------------------------------------------------------------------------
# --lbl-types: retype `extern lbl_XXXX` globals and drop `*(T *)&lbl` casts.
#
# m2c emits `extern char lbl_802FFE54[];` plus `*(s32 *)&lbl_802FFE54 = 0;`
# for absolute-address DOL globals. When EVERY use of a lbl in the corpus is
# a cast-deref `*(T *)&lbl` of one scalar type T (load or store) and nothing
# indexes / address-arithmetics the lbl, the decl is retyped to
# `extern T lbl_X;` and each site becomes a plain `lbl_X` — the address is
# the same, the load/store width is the same, so codegen is unchanged
# (verified per-file like all applies). Bare value uses are allowed only in
# files whose decl is ALREADY the scalar T (array-decay / pointer uses in
# char[]-decl files disqualify the lbl). Struct-y casts (S4, sn_ps, const
# u8 tables) and `&lbl + off` address arithmetic are excluded — those stay
# raw arrays.
# ---------------------------------------------------------------------------
LBLT = '--lbl-types' in sys.argv

LBL_DECL = re.compile(r'^(\s*extern\s+)([^;\n]*?\b)(lbl_[0-9A-Fa-f]+)(\s*\[[^\]]*\]\s*)?(;)', re.M)
LBL_SITE = re.compile(r'\*\(\s*\(?\s*([^)]*?)\s*\)\s*&\s*(lbl_[0-9A-Fa-f]+)(\[0\])?')
# redundant identity value-cast `(s32)lbl_X` on an already-s32 extern
LBL_VC = re.compile(r'\(\s*(s8|u8|s16|u16|s32|u32|f32|f64|int|float|double)'
                    r'\s*\)\s*(lbl_[0-9A-Fa-f]+)(?!\[)')
LBL_IDX = re.compile(r'\b(lbl_[0-9A-Fa-f]+)\s*\[')
LBL_BARE = re.compile(r'\b(lbl_[0-9A-Fa-f]+)\b')

# scalar type a `*(T *)&lbl` site needs the decl to become
def _lbl_scalar(casttype):
    t = casttype.strip()
    m = re.match(r'^(.+?)\s*\*\s*$', t)
    if not m:
        return None
    s = m.group(1).strip()
    if s == 'void':
        return 'void *'
    qs = [q for q in ('volatile', 'const') if q in s.split()]
    base = s.replace('volatile', '').replace('const', '').strip()
    return ' '.join(qs + [base]).strip()

# builtin scalar decls a retyped extern can be (no file-local typedefs)
LBL_SCALAR_OK = ('s8', 'u8', 's16', 'u16', 's32', 'u32', 'f32', 'f64',
                 'char', 'int', 'short', 'long', 'float', 'double',
                 'void *', '__ps_t')


def _lbl_decls(txt):
    """{lbl: (decl_type, has_brackets, span, line_has_multi)} from extern lines."""
    out = {}
    for m in LBL_DECL.finditer(txt):
        prefix = m.group(1)
        typ = re.sub(r'\b(lbl_[0-9A-Fa-f]+)\s*(\[[^\]]*\])?', '', m.group(2)).strip()
        line_start = txt.rfind('\n', 0, m.start()) + 1
        line_end = txt.find('\n', m.end())
        if line_end < 0:
            line_end = len(txt)
        line = txt[line_start:line_end]
        multi = len(re.findall(r'\b(lbl_[0-9A-Fa-f]+)\b', line)) > 1
        out[m.group(3)] = (typ, bool(m.group(4)), (m.start(), m.end()), multi)
    return out


def _lbl_sites(masked):
    """Yield (lbl, scalar, span, unsafe) for each matched cast-deref site."""
    for m in LBL_SITE.finditer(masked):
        mt = m.group(0)
        bal = mt.count('(') - mt.count(')')
        nxt = ''
        j = m.end()
        while j < len(masked) and masked[j] in ' \t':
            j += 1
        if j < len(masked):
            nxt = masked[j]
        unsafe = False
        span = (m.start(), m.end())
        if bal > 0:
            if nxt == ')':
                span = (m.start(), j + 1)  # double-paren close `*((T *)&lbl)`
            else:
                unsafe = True  # address arithmetic inside open parens
        if bal == 0 and nxt == '[':
            unsafe = True  # `*(T *)&lbl[i]` with i != 0 — element indexing
        yield m.group(2), _lbl_scalar(m.group(1)), span, unsafe


_VC_NORM = {'int': 's32', 'float': 'f32', 'double': 'f64'}


def _lbl_vc_sites(masked, file_decl, f):
    """Yield (span, lbl) for redundant `(T)lbl_X` identity casts: the file's
    decl for that lbl is exactly the scalar T (no brackets), so the cast is a
    no-op. Real conversions (decl is char[] / different width / bracketed)
    are not matched here."""
    for m in LBL_VC.finditer(masked):
        cast = _VC_NORM.get(m.group(1).strip(), m.group(1).strip())
        lbl = m.group(2)
        d = file_decl.get((f, lbl))
        if d is not None and not d[1] and d[0] == cast:
            yield m.span(), lbl


def find_lbl_candidates(files):
    """Return (cand {lbl: scalar}, report) for lbls whose every use is a
    single-scalar cast-deref. Excludes indexed / address-arith / struct-y
    uses; bare value uses allowed only with an already-scalar decl."""
    lbl_cast = collections.defaultdict(collections.Counter)
    lbl_unsafe = collections.Counter()
    lbl_idx = collections.Counter()
    lbl_bare = collections.defaultdict(collections.Counter)  # lbl -> file -> n
    lbl_decl = {}      # lbl -> set of (decl_type, has_brackets)
    file_decl = {}     # (file, lbl) -> (decl_type, has_brackets)
    lbl_src = collections.Counter()   # lbl -> n sites in byte-verified src
    vc_sites = collections.Counter()   # (file, span) -> lbl (redundant value casts)
    for f in files:
        txt = open(f, encoding='utf-8', errors='replace').read()
        masked = ds.mask_comments_strings(txt)
        decls = _lbl_decls(txt)
        # mask decl lines
        dm = list(decls.values())
        for _t, _b, sp, _m in dm:
            masked = masked[:sp[0]] + ' ' * (sp[1] - sp[0]) + masked[sp[1]:]
        for lbl, scalar, _sp, unsafe in _lbl_sites(masked):
            if scalar is None:
                lbl_unsafe[lbl] += 1
                continue
            lbl_cast[lbl][scalar] += 1
            if unsafe:
                lbl_unsafe[lbl] += 1
            mn = FN_RE.match(os.path.basename(f))
            if mn and not f.startswith(os.path.join(ROOT, 'src', 'wip', '')):
                lbl_src[lbl] += 1
        # mask cast-deref sites so idx/bare counters don't double count
        m2 = LBL_SITE.sub(lambda m: ' ' * (m.end() - m.start()), masked)
        for m in LBL_IDX.finditer(m2):
            lbl_idx[m.group(1)] += 1
        for m in LBL_BARE.finditer(m2):
            lbl_bare[m.group(1)][f] += 1
        for lbl, (typ, br, _sp, _m) in decls.items():
            lbl_decl.setdefault(lbl, set()).add((typ, br))
            file_decl[(f, lbl)] = (typ, br)
        # redundant identity value-casts need the file's decl — collected above
        for sp, lbl in _lbl_vc_sites(masked, file_decl, f):
            vc_sites[(f, sp[0], sp[1])] = lbl
    cand = {}
    report = []
    for lbl, cnt in sorted(lbl_cast.items()):
        if len(cnt) != 1:
            continue
        if lbl_unsafe.get(lbl, 0) or lbl_idx.get(lbl, 0):
            continue
        scalar, n = next(iter(cnt.items()))
        if scalar not in LBL_SCALAR_OK:
            continue
        if lbl not in lbl_decl:
            continue
        # bare uses: only in files whose decl is already scalar == scalar.
        # A file that mentions `lbl` bare (no `*(T *)&` cast) must already
        # declare it as the plain scalar — retyping char[]-decl files there
        # would turn array decays into value reads. (That file keeps its decl;
        # only the cast-deref files get the decl retype.)
        bad = False
        for f, nb in lbl_bare.get(lbl, {}).items():
            fd = file_decl.get((f, lbl))
            if fd is None or fd[1] or fd[0] != scalar:
                bad = True
                break
        if bad:
            continue
        cand[lbl] = scalar
        decls = sorted(set('%s%s' % (t, '[]' if b else '') for t, b in lbl_decl[lbl]))
        report.append('%s: %s  (%d cast-deref site(s), %s src) decls=%s'
                      % (lbl, scalar, n, 'src' if lbl_src[lbl] else 'wip',
                         ','.join(decls)))
    return cand, report, vc_sites


def lbl_apply(cand, vc_sites, files):
    """Retype decls to the scalar, drop `*(T *)&lbl` casts, and drop
    redundant identity `(T)lbl_X` value casts. Per-file src byte-verify /
    wip compile gates, auto-revert on failure."""
    written = reverted = sites = 0
    vc_n = 0
    for f in files:
        txt = open(f, encoding='utf-8', errors='replace').read()
        masked = ds.mask_comments_strings(txt)
        decls = _lbl_decls(txt)
        dm = list(decls.values())
        for _t, _b, sp, _m in dm:
            masked = masked[:sp[0]] + ' ' * (sp[1] - sp[0]) + masked[sp[1]:]
        repls = []
        # decl retypes (single-declarator extern lines only)
        for lbl, (typ, br, sp, multi) in sorted(decls.items()):
            if multi:
                continue  # shared type line — leave untouched
            if lbl not in cand:
                continue
            scalar = cand[lbl]
            if typ == scalar and not br:
                continue
            indent = txt[:sp[0]][txt[:sp[0]].rfind('\n') + 1:]
            repls.append((sp[0], sp[1], '%sextern %s %s;' % (indent, scalar, lbl)))
        # site rewrites
        for lbl, scalar, sp, unsafe in _lbl_sites(masked):
            if unsafe or lbl not in cand:
                continue
            if cand[lbl] != scalar:
                continue
            repls.append((sp[0], sp[1], lbl))
        # redundant identity value-casts `(T)lbl_X` on already-scalar decls
        for (ff, a, b), lbl in sorted(vc_sites.items()):
            if ff != f:
                continue
            repls.append((a, b, lbl))
            vc_n += 1
        if not repls:
            continue
        new_txt = txt
        for a, b, rep in sorted(repls, key=lambda r: -r[0]):
            new_txt = new_txt[:a] + rep + new_txt[b:]
        sites += len([r for r in repls if not r[2].startswith('extern')])
        mn = FN_RE.match(os.path.basename(f))
        addr = int(mn.group(1), 16) if mn else None
        is_src = f.startswith(os.path.join(ROOT, 'src', '')) and not \
            f.startswith(os.path.join(ROOT, 'src', 'wip', ''))
        if is_src and addr is not None:
            sym_size = SYM_SIZE.get(addr)
            if sym_size is not None and verify_src(addr, sym_size, new_txt):
                open(f, 'w').write(new_txt)
                written += 1
            else:
                reverted += 1
        else:
            if addr is not None and verify_compiles(addr, txt) and \
                    not verify_compiles(addr, new_txt):
                reverted += 1
            else:
                open(f, 'w').write(new_txt)
                written += 1
    return written, reverted, sites


def process_file(args):
    fp, class_of, names, offs_types = args
    m = FN_RE.match(os.path.basename(fp))
    is_src = fp.startswith(os.path.join(ROOT, 'src', '')) and not fp.startswith(os.path.join(ROOT, 'src', 'wip', ''))
    text = open(fp, encoding='utf-8', errors='replace').read()
    repls = plan_rewrites(fp, text, class_of, names, offs_types)
    if not repls:
        return None
    new_text = ensure_include(apply_repls(text, repls))
    addr = int(m.group(1), 16) if m else None
    if is_src and m:
        if APPLY:
            sym_size = SYM_SIZE.get(addr)
            if sym_size is None:
                status = 'reverted-no-size'
            elif verify_src(addr, sym_size, new_text):
                status = 'src-verified'
            else:
                status = 'reverted-mismatch'
        else:
            status = 'src'
    else:
        if APPLY and addr is not None:
            # inert drafts: only revert when the rewrite breaks a previously
            # compiling body (drafts that already fail are kept as-is)
            if verify_compiles(addr, text) and not verify_compiles(addr, new_text):
                status = 'reverted-breaks-compile'
            else:
                status = 'wip'
        else:
            status = 'wip'
    if status.startswith('reverted'):
        return (fp, status, len(repls), text)
    return (fp, status, len(repls), new_text)


def main():
    # NOTE: the struct header + detection cache are the FIXED type reference —
    # generate them together with tools/detect_structs.py (from the pristine
    # corpus) and never regenerate them here. Re-deriving mid-apply flips field
    # types as sites vanish from the raw-pattern scan, which can un-verify
    # files that were byte-checked against the previous header (and breaks
    # idempotency).
    if not os.path.exists(ds.CACHE):
        sys.exit('missing %s — run tools/detect_structs.py first'
                 % ds.CACHE)
    class_of, names, offs_types, site_count = ds.load_cache()

    files = sorted(glob.glob(os.path.join(ROOT, 'src', '*.c')) +
                   glob.glob(os.path.join(ROOT, 'src', 'wip', '*.c')))
    # only single-function fn_*.c files carry the raw pattern family
    files = [f for f in files if FN_RE.match(os.path.basename(f))]
    if LIMIT is not None:
        files = files[:LIMIT]

    if RETARGET:
        cand, puns, hdr = find_retarget_candidates(files)
        print('member-type retarget candidates (apply=%s):' % APPLY)
        total_sites = 0
        for (cls, off), T in sorted(cand.items()):
            decl = hdr.get(cls, {}).get(off, '?')
            n = sum(n for (c, o, t), n in puns.items()
                    if (c, o) == (cls, off))
            total_sites += n
            print('  %s.unk0x%X: %s -> %s  (%d pun sites)' % (cls, off, decl, T, n))
        if not cand:
            print('  (none — every punned member also has plain uses of its '
                  'declared type, so the class field type is the shared truth)')
            return 0
        if not APPLY:
            print('  %d site(s) — pass --apply to retype' % total_sites)
            return 0
        written, reverted, sites = retarget_apply(cand, files)
        print('retargeted: %d files / %d sites written, %d reverted'
              % (written, sites, reverted))
        return 0

    if FNP:
        cand, report = find_fnptr_candidates(files)
        print('fn-ptr field candidates (apply=%s):' % APPLY)
        for line in report:
            print('  ' + line)
        if not cand:
            print('  (none — every called slot also has data uses or its '
                  'call signatures tie, so the class field stays scalar)')
            return 0
        if not APPLY:
            print('  %d member(s) — pass --apply to retype' % len(cand))
            return 0
        written, reverted, sites = fnptr_apply(cand, files)
        print('fnptr-fields: %d files / %d sites written, %d reverted'
              % (written, sites, reverted))
        return 0

    if LNP:
        cand, report = find_local_candidates(files)
        print('local fn-ptr candidates (apply=%s):' % APPLY)
        for line in report:
            print('  ' + line)
        if not cand:
            print('  (none)')
            return 0
        n = sum(len(v) for v in cand.values())
        if not APPLY:
            print('  %d local(s) in %d file(s) — pass --apply to rewrite'
                  % (n, len(cand)))
            return 0
        written, reverted, sites = local_apply(cand, files)
        print('local-fnptrs: %d files / %d sites written, %d reverted'
              % (written, sites, reverted))
        return 0

    if NEST:
        cand, report = find_nested_candidates(files)
        print('nested-struct pointer candidates (apply=%s):' % APPLY)
        for line in report:
            print('  ' + line)
        if not cand:
            print('  (none — every scalar slot with pointer reads also has '
                  'plain scalar uses or disagrees on the target struct)')
            return 0
        n = sum(len(v) for v in cand.values())
        if not APPLY:
            print('  %d member(s) — pass --apply to retype' % n)
            return 0
        written, reverted, sites = nested_apply(cand, files)
        print('nested-ptrs: %d files / %d sites written, %d reverted'
              % (written, sites, reverted))
        return 0

    if LBLT:
        cand, report, vc_sites = find_lbl_candidates(files)
        print('lbl-type candidates (apply=%s):' % APPLY)
        for line in report:
            print('  ' + line)
        print('  redundant identity value-casts: %d site(s)' % len(vc_sites))
        if not cand and not vc_sites:
            print('  (none — every cast-deref lbl also has array/pointer uses '
                  'or disagrees on the scalar type)')
            return 0
        if not APPLY:
            print('  %d lbl(s) + %d value-cast(s) — pass --apply to rewrite'
                  % (len(cand), len(vc_sites)))
            return 0
        written, reverted, sites = lbl_apply(cand, vc_sites, files)
        print('lbl-types: %d files / %d sites written, %d reverted'
              % (written, sites, reverted))
        return 0

    print('scanning %d fn_*.c files (apply=%s jobs=%d)' % (len(files), APPLY, JOBS))
    args = [(fp, class_of, names, offs_types) for fp in files]
    if APPLY:
        ctx = mp.get_context('fork')
        with ctx.Pool(JOBS) as pool:
            results = [r for r in pool.imap_unordered(process_file, args) if r is not None]
    else:
        results = []
        for a in args:
            r = process_file(a)
            if r is not None:
                results.append(r)

    stats = collections.Counter()
    total_sites = 0
    for fp, status, n, _txt in results:
        stats[status] += 1
        total_sites += n
    print('files with rewrites: %d  sites rewritten: %d' % (len(results), total_sites))
    for k in sorted(stats):
        print('  %-18s %d' % (k, stats[k]))

    if APPLY:
        for fp, status, n, txt in results:
            if not status.startswith('reverted'):
                open(fp, 'w').write(txt)
    return 0


if __name__ == '__main__':
    sys.exit(main())