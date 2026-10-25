#!/usr/bin/env python3
"""Bulk-detect anonymous struct layouts from byte-offset derefs in src + src/wip.

Three literal-offset access families are detected independently and merged
into shared struct types in `include/structs.h`:

1. pointer form: `*(T *)((char *)BASE + 0xNN)` with BASE an identifier (plus
   one level of nesting where BASE is itself `*(T1 *)((char *)ID + O1)`).
2. address form (stack/static objects): `*(T *)((char *)&BASE + 0xNN)`.
3. direct form: `*(T *)(BASE + 0xNN)` with NO (char *) cast. The addend is
   in units of BASE's declared type: the byte offset is LIT * element size,
   resolved per (file, base) via `base_add_mult` from the file's declaration
   (1 for int/char/void bases, pointee size for typed pointers, 0 — site
   excluded — when the pointee size is unknowable).

Sites are grouped per (file, base) into per-layout clusters, merged into
shared struct classes, and emitted as typedefs. The families merge
independently (extra-family layouts never vote on a pointer-form class's
fields), but a family class whose final field map is *identical* to an
already-emitted class reuses that class instead of emitting a duplicate.
`apply_structs.py` also rewrites the stride form `*(T *)((char *)BASE + ID*W)`
(width == sizeof(T)) to `((T *)BASE)[ID]` — an array element access that
needs no struct class.

Merging rule (deterministic, no transitive glue):
  * An offset is "clean" in a layout when every site at it agrees on width
    (1/2/4/8); conflicting offsets are excluded (their sites stay raw pointer
    arithmetic in the apply step).
  * Layout signatures are (offset, width-class) sets. Distinct signatures are
    processed largest-first; a signature folds into the first class whose
    signature is a superset of it *with matching widths* (so small layouts join
    big ones, but two big overlapping layouts never merge, and disjoint layouts
    never merge).
  * If a class still ends up with conflicting widths at one offset (two member
    layouts disagreed there), that offset is dropped class-wide (sites stay
    raw).
  * A class's field type at an offset is the majority cast type among its
    member sites; `apply_structs.py` rewrites a site only when its cast type
    equals the class field type exactly — that keeps codegen byte-identical.

Fields are named `unk0xNN` by absolute byte offset; every gap (including the
leading gap) becomes `char pad0xNN`. A field whose natural alignment would
shift its offset is dropped from the struct (its sites stay raw), so every
emitted struct has byte-exact field offsets by construction.

Usage:
    tools/venv/bin/python tools/detect_structs.py            # write header
    tools/venv/bin/python tools/detect_structs.py --extend   # extra families
        # only, on an already-applied corpus: loads the frozen cache, detects
        # the `&base` + direct families (untouched by earlier rewrites),
        # folds/appends; repeat with apply until it reports `new: 0`
    tools/venv/bin/python tools/detect_structs.py --check    # exit 1 if stale
"""
import collections
import glob
import hashlib
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT_H = os.path.join(ROOT, 'include', 'dolphin', 'structs.h')
CACHE = os.path.join(ROOT, 'tools', 'unk_structs_cache.json')


def canon(fp):
    """Repo-relative path for cache keys.

    Cache keys used to be absolute (glob of ROOT), which embedded the
    check-out owner's home directory and broke the cache on any other
    machine. Keys are now relative to the repo root (e.g.
    `src/fn_80005BA4.c`); load_cache() normalizes legacy absolute keys
    so old caches still load.
    """
    ap = os.path.abspath(fp)
    try:
        return os.path.relpath(ap, ROOT)
    except ValueError:
        return ap

# ---------------------------------------------------------------------------
# access-site patterns
# ---------------------------------------------------------------------------
# `*(<cast> *)((char *)BASE + 0xNN)` with BASE an identifier. The captured
# group is the cast minus its final star == the deref result type (the struct
# field type), e.g. `*(s32 *)` -> "s32", `*(void **)` -> "void *",
# `*(__ps_t *)` -> "__ps_t".
OFF = r'(?:\(s32\)\s*)?((?:0x[0-9A-Fa-f]+)|\d+)'
SITE_RE = re.compile(
    r'\*\(\s*([A-Za-z_][A-Za-z0-9_ \*]*?)\s*\*\)\s*\(\s*\(char\s*\*\)\s*'
    r'([A-Za-z_][A-Za-z0-9_]*)\s*\+\s*' + OFF + r'\s*\)')
# one level of nesting: `*(T2 *)((char *)*(T1 *)((char *)ID + O1) + O2)`
NEST1_RE = re.compile(
    r'\*\(\s*([A-Za-z_][A-Za-z0-9_ \*]*?)\s*\*\)\s*\(\s*\(char\s*\*\)\s*'
    r'\*\(\s*([A-Za-z_][A-Za-z0-9_ \*]*?)\s*\*\)\s*\(\s*\(char\s*\*\)\s*'
    r'([A-Za-z_][A-Za-z0-9_]*)\s*\+\s*' + OFF + r'\s*\)\s*'
    r'\+\s*' + OFF + r'\s*\)')
# address form (stack/static/global objects): `*(T *)((char *)&BASE + 0xNN)`
AMP_RE = re.compile(
    r'\*\(\s*([A-Za-z_][A-Za-z0-9_ \*]*?)\s*\*\)\s*\(\s*\(char\s*\*\)\s*'
    r'&\s*([A-Za-z_][A-Za-z0-9_]*)\s*\+\s*' + OFF + r'\s*\)')
# direct form: `*(T *)(BASE + 0xNN)` with NO (char *) cast — the addend is in
# units of BASE's declared type, so the byte offset is LIT * element size
# (1 for int/char/void-ish bases, sizeof pointee for typed pointers).
DIR_RE = re.compile(
    r'\*\(\s*([A-Za-z_][A-Za-z0-9_ \*]*?)\s*\*\)\s*\(\s*'
    r'([A-Za-z_][A-Za-z0-9_]*)\s*\+\s*' + OFF + r'\s*\)')
# stride form: `*(T *)((char *)BASE + ID * 0xNN)` where the scale equals the
# deref width — an array element access `((T *)BASE)[ID]` (apply-side only).
STRIDE_RE = re.compile(
    r'\*\(\s*([A-Za-z_][A-Za-z0-9_ \*]*?)\s*\*\)\s*\(\s*\(char\s*\*\)\s*'
    r'([A-Za-z_][A-Za-z0-9_]*)\s*\+\s*([A-Za-z_][A-Za-z0-9_]*)\s*\*\s*'
    r'((?:0x[0-9A-Fa-f]+)|\d+)\s*\)')

# width / alignment of a deref-result type (captured group)
WIDTH = {'s8': 1, 'u8': 1, 'char': 1, 's16': 2, 'u16': 2,
         's32': 4, 'u32': 4, 'f32': 4, 'float': 4, 'int': 4,
         'signed': 4, 'unsigned': 4, 'void': 4,
         '__ps_t': 8, 'sn_ps': 8, 'f64': 8, 's64': 8, 'u64': 8, 'double': 8}
ALIGN = {'s8': 1, 'u8': 1, 'char': 1, 's16': 2, 'u16': 2,
         '__ps_t': 8, 'sn_ps': 8, 'f64': 8, 's64': 8, 'u64': 8, 'double': 8}

KNOWN_BASES = set(WIDTH) | {'signed', 'unsigned', 'int'}

# a declarator `[type...] [*...] NAME` — used to resolve whether a direct-form
# base is a typed pointer (element-scaled adds) or an int/byte object.
DECL_RE = re.compile(
    r'\b([A-Za-z_][A-Za-z0-9_]*(?:\s+[A-Za-z_][A-Za-z0-9_]*)*)\s+(\*+\s*)?'
    r'([A-Za-z_][A-Za-z0-9_]*)\s*(\[[^\]\n]*\])?\s*(?:=|,|;|\))')
STORAGE = {'register', 'static', 'extern', 'volatile', 'const'}


def decl_type(masked, name):
    """Type string ('s32', 'void *', 'f32 *', ...) of the first declarator of
    `name` in the (comment-masked) file text, or None if undeclared."""
    for m in DECL_RE.finditer(masked):
        if m.group(3) == name:
            t = m.group(1).strip()
            if t.split()[0] in STORAGE:
                t = ' '.join(t.split()[1:])
            if t in STORAGE or not t:
                continue
            return t + m.group(2).rstrip() if m.group(2) else t
    return None


def base_add_mult(masked, name):
    """Element-add multiplier for `NAME + LIT` without a (char *) cast.

    C semantics: scalar ints / char / void bases add in bytes (1); typed
    pointers scale by their pointee size (2/4/8); pointer-to-pointer is 4.
    Returns 0 when the pointee size is unknowable from the declaration — such
    sites are excluded (staying raw) because their byte offset is ambiguous.
    """
    d = decl_type(masked, name)
    if d is None:
        return 1
    s = d.strip()
    nstar = 0
    while s.endswith('*'):
        nstar += 1
        s = s[:-1].rstrip()
    if nstar == 0:
        return 1                       # scalar variable: integer byte add
    if nstar > 1:
        return 4                       # pointer-to-pointer
    core = s.split()[-1] if s.split() else ''
    if core in ('char', 'signed', 'unsigned', 'void'):
        return 1                       # byte-pointer / byte semantics
    return WIDTH.get(core, 0)          # typed pointee; 0 = unknown size


def canonical_type(g):
    """Map a deref-result type to a header-safe form.

    File-local typedefs (e.g. `MgrC_t` defined inside one .c) cannot be used
    in the shared header: unknown pointer types become `void *`, unknown
    scalars become `s32`. Rewriting still requires the site's RAW type to
    equal the field type exactly, so unknown-typed sites are never rewritten
    (they only contribute layout/merging width).
    """
    t = g.strip()
    vol = ''
    rest = t
    if rest.startswith('volatile '):
        vol = 'volatile '
        rest = rest[len('volatile '):].strip()
    if rest.endswith('*'):
        inner = rest[:-1].strip()
        if inner in KNOWN_BASES:
            return t
        return vol + 'void *'
    if rest in KNOWN_BASES:
        return t
    return vol + 's32'


def type_width(g):
    t = g.strip()
    if t.endswith('*'):
        return 4
    base = t.replace('volatile', '').strip()
    return WIDTH.get(base, 4)


def type_align(g):
    t = g.strip()
    if t.endswith('*'):
        return 4
    base = t.replace('volatile', '').strip()
    return ALIGN.get(base, 4)


def mask_comments_strings(text):
    """Return a same-length copy with comments and string literals blanked."""
    out = list(text)
    i, n = 0, len(text)
    in_str = in_ch = block = False
    while i < n:
        c = text[i]
        if block:
            out[i] = ' '
            if c == '*' and i + 1 < n and text[i + 1] == '/':
                out[i + 1] = ' '
                i += 2
                block = False
                continue
            i += 1
            continue
        if in_str:
            if c == '\\':
                out[i] = ' '
                if i + 1 < n:
                    out[i + 1] = ' '
                i += 2
                continue
            out[i] = ' '
            if c == '"':
                in_str = False
            i += 1
            continue
        if in_ch:
            out[i] = ' '
            if c == "'":
                in_ch = False
            i += 1
            continue
        if c == '/' and i + 1 < n and text[i + 1] == '/':
            while i < n and text[i] != '\n':
                out[i] = ' '
                i += 1
            continue
        if c == '/' and i + 1 < n and text[i + 1] == '*':
            out[i] = out[i + 1] = ' '
            i += 2
            block = True
            continue
        if c == '"':
            in_str = True
            out[i] = ' '
        elif c == "'":
            in_ch = True
            out[i] = ' '
        i += 1
    return ''.join(out)


def scan_sites(text):
    """Yield (base_key, offset, cast_type, span) for every deref site.

    base_key is either the identifier string or a tuple ('d', ident, off1)
    for a base that is itself `*(T1 *)((char *)ident + off1)`.
    """
    masked = mask_comments_strings(text)
    nest1 = list(NEST1_RE.finditer(masked))
    for m in SITE_RE.finditer(masked):
        t, ident, off = m.groups()
        off = int(off, 0)
        for n in nest1:
            if n.start() <= m.start() < n.end():
                t2, t1, nid, o1, o2 = n.groups()
                yield (('d', ident, off), int(o2, 0), t2.strip(), n.span())
                break
        yield (ident, off, t.strip(), m.span())


def collect_layouts(files):
    """Return (layouts, site_count) for the pointer-form family.

    layouts[(file, base)] -> {offset: collections.Counter(cast_type)}
    Only offsets whose sites all agree on width are kept.
    """
    layouts = {}
    site_count = 0
    for fp in files:
        text = open(fp, encoding='utf-8', errors='replace').read()
        base_sites = collections.defaultdict(lambda: collections.defaultdict(collections.Counter))
        for base, off, typ, _span in scan_sites(text):
            site_count += 1
            base_sites[base][off][canonical_type(typ)] += 1
        key = canon(fp)
        for base, offs in base_sites.items():
            lay = layouts.setdefault((key, base), {})
            for off, counter in offs.items():
                if off >= 0x80000000:
                    # absolute-address arithmetic, not a struct field offset
                    continue
                lay[off] = counter   # widths may conflict — resolved per class
    return layouts, site_count


def collect_amp_layouts(files):
    """Return (layouts, site_count) for the address-form (`&base`) family.

    Base keys are tuples ('a', ident) so they never collide with the plain
    identifier keys of the pointer family inside one file.
    """
    layouts = {}
    site_count = 0
    for fp in files:
        text = open(fp, encoding='utf-8', errors='replace').read()
        masked = mask_comments_strings(text)
        base_sites = collections.defaultdict(lambda: collections.defaultdict(collections.Counter))
        for m in AMP_RE.finditer(masked):
            t, ident, off = m.groups()
            off = int(off, 0)
            if off >= 0x80000000:
                continue
            site_count += 1
            base_sites[('a', ident)][off][canonical_type(t)] += 1
        key = canon(fp)
        for base, offs in base_sites.items():
            lay = layouts.setdefault((key, base), {})
            for off, counter in offs.items():
                lay[off] = counter   # widths may conflict — resolved per class
    return layouts, site_count


def collect_i_layouts(files):
    """Return (layouts, site_count) for the direct form `*(T *)(BASE + LIT)`.

    Base keys are ('i', ident). The addend is in units of BASE's declared type
    (see base_add_mult): byte offsets are LIT * element size, so layouts live
    in the same byte space as every other family. Sites on bases whose pointee
    size is unknowable (mult 0) are excluded — their byte offset is ambiguous
    and they must stay raw.
    """
    layouts = {}
    site_count = 0
    for fp in files:
        text = open(fp, encoding='utf-8', errors='replace').read()
        masked = mask_comments_strings(text)
        base_sites = collections.defaultdict(lambda: collections.defaultdict(collections.Counter))
        for m in DIR_RE.finditer(masked):
            t, ident, off = m.groups()
            mult = base_add_mult(masked, ident)
            if mult == 0:
                continue
            off = int(off, 0) * mult
            if off >= 0x80000000:
                continue
            site_count += 1
            base_sites[('i', ident)][off][canonical_type(t)] += 1
        key = canon(fp)
        for base, offs in base_sites.items():
            lay = layouts.setdefault((key, base), {})
            for off, counter in offs.items():
                lay[off] = counter   # widths may conflict — resolved per class
    return layouts, site_count


def _widths(counter):
    return {type_width(t) for t in counter}


def merge_classes(layouts):
    """Return (class_of, classes).

    class_of: {(file, base) -> class_index}
    classes:  [ {offset: collections.Counter(cast_type)} ] aggregated over the
               member layouts of each merged class.

    A layout signature carries EVERY (offset, width) pair seen at an offset
    (conflicting widths are kept, not filtered); a layout folds into a class
    only when the class already contains each (offset, width) pair.
    """
    sig_buckets = {}  # frozenset((off,width)) -> [keys]
    for key, lay in layouts.items():
        if not lay:
            continue
        sig = frozenset((off, w) for off, c in lay.items() for w in _widths(c))
        sig_buckets.setdefault(sig, []).append(key)

    classes = []       # each: {off: Counter}
    class_of = {}
    order = sorted(sig_buckets.keys(), key=lambda s: (-len(s), sorted(s)))
    for sig in order:
        keys = sig_buckets[sig]
        candidate = None
        for ci, cls in enumerate(classes):
            # superset containing every (offset, width) pair
            if all(off in cls and w in _widths(cls[off]) for off, w in sig):
                candidate = ci
                break
        if candidate is None:
            candidate = len(classes)
            classes.append({})
        cls = classes[candidate]
        for key in keys:
            class_of[key] = candidate
            for off, counter in layouts[key].items():
                cls.setdefault(off, collections.Counter()).update(counter)
    return class_of, classes


def class_field_types(cls):
    """{offset: cast_type} by majority vote (ties -> lexicographically first).

    Conflicting widths at one offset are NOT dropped: the most-used type wins
    and the offset is emitted as that field. Sites at the offset whose own
    cast type differs are still rewritten by `apply_structs.py` through the
    member-address cast form `*(T *)&member` — same address, same load, so
    byte-safe — provided the field itself is emittable there.
    """
    out = {}
    for off, counter in cls.items():
        # most-used type wins; if its alignment would shift the field (odd
        # offset), fall back to the most-used type that lands exactly there
        cand = sorted(counter, key=lambda t: (counter[t], t), reverse=True)
        pick = next((t for t in cand if off % type_align(t) == 0), cand[0])
        out[off] = pick
    return out


def emittable_offsets(offsets_types):
    """Subset of offsets whose fields land at their exact byte offset.

    Walks the offsets ascending, advancing a running offset past each kept
    field; a field is dropped when the running offset has already passed it
    (overlap) or when its natural alignment would shift it. Dropped fields
    never advance the running offset, so later fields stay aligned.
    """
    keep = []
    running = 0
    for off in sorted(offsets_types):
        typ = offsets_types[off]
        w = type_width(typ)
        a = type_align(typ)
        if running > off or off % a != 0:
            continue
        keep.append(off)
        running = off + w
    return keep


def emit_struct(name, offsets_types):
    """Return (lines, dropped_offsets) for one typedef with exact offsets."""
    lines = ['typedef struct %s {' % name]
    running = 0
    dropped = []
    for off in sorted(offsets_types):
        typ = offsets_types[off]
        w = type_width(typ)
        a = type_align(typ)
        if running > off or off % a != 0:
            dropped.append(off)
            continue
        if off > running:
            lines.append('    char pad0x%X[0x%X];' % (running, off - running))
        lines.append('    %s unk0x%X;' % (display_type(typ), off))
        running = off + w
    lines.append('} %s;' % name)
    return lines, dropped


def class_name(sig):
    h = hashlib.sha1(repr(sorted(sig)).encode()).hexdigest()[:8].upper()
    return 'Unk_%s' % h


# Canonical Unk_* class key -> human-readable display name. Evidence is
# external (never from layout hashes): CStruct/CScript are the Neversoft
# script-engine structs all 65 THPG Script* handlers take
# (`...FPQ26Script7CStructPQ26Script7CScript`), and Unk_2EF06E12 is the
# usage-proven QB command-parameter block. Detection keys, the frozen cache,
# and all merging stay on the Unk_ key; ONLY header emission (and the corpus
# tools that parse it) use the display name, via display_name() below.
ALIASES = {
    'Unk_2EF06E12': 'CStruct',   # QB command parameter block (Script::CStruct)
    'Unk_B6E8234C': 'CScript',   # calling script (Script::CScript)
}


def display_name(cls):
    """Header/corpus spelling of a canonical class key."""
    return ALIASES.get(cls, cls)


def display_type(typ):
    """Translate aliased class tokens inside a header member-type string
    ('Unk_2EF06E12 *' -> 'CStruct *', 'struct Unk_X *' -> 'struct CStruct *').
    Spacing is preserved byte-for-byte; non-aliased strings pass through."""
    for k, v in ALIASES.items():
        typ = typ.replace(k, v)
    return typ


def _final_fields(cls):
    """Field map {offset: cast_type} after dropping unrepresentable offsets."""
    ft = class_field_types(cls)
    for off in set(ft) - set(emittable_offsets(ft)):
        del ft[off]   # unrepresentable in C layout: leave sites raw
    return ft


def fold_append(fam_class_of, fam_classes, class_of, names, offs_types, used,
                aggregates=None):
    """Fold/append one independently-merged extra family into the class tables.

    A family class whose final field map equals an existing class's reuses
    that class (it never votes on another class's fields, so existing classes
    keep their types); the rest are appended. `aggregates` (the full-build
    per-class site counters) is updated for coverage stats when given.
    """
    fold = {}
    for aj, cls in enumerate(fam_classes):
        ft = _final_fields(cls)
        tgt = next((ci for ci, e in offs_types.items() if e == ft), None)
        if tgt is None:
            tgt = len(offs_types)
            sig = frozenset((off, type_width(ft[off])) for off in ft)
            nm = class_name(sig)
            k = 2
            while nm in used:
                nm = '%s_%d' % (class_name(sig), k)
                k += 1
            used.add(nm)
            names[tgt] = nm
            offs_types[tgt] = ft
            if aggregates is not None:
                aggregates.append(cls)
        elif aggregates is not None:
            aggregates[tgt].update(cls)   # fold stats only
        fold[aj] = tgt
    for key, aj in fam_class_of.items():
        class_of[key] = fold[aj]


def build():
    """Run detection over every family from a pristine corpus.

    Returns (class_of, classes, names, offs_types, site_count, amp_site_count,
    dir_site_count, ptr_n) where class_of keys are (file, base) with base a
    str (pointer family), ('a', ident) (address form), or ('i', ident)
    (direct int-ptr form). Extra-family classes fold into an existing class
    only when their final field map is identical to it; they never vote on
    another class's fields, so the pointer family's classes and field types
    are unchanged by their presence.
    """
    files = sorted(glob.glob(os.path.join(ROOT, 'src', '*.c')) +
                   glob.glob(os.path.join(ROOT, 'src', 'wip', '*.c')))
    layouts, site_count = collect_layouts(files)
    amp_layouts, amp_site_count = collect_amp_layouts(files)
    dir_layouts, dir_site_count = collect_i_layouts(files)
    class_of, classes = merge_classes(layouts)
    names = {}
    used = set()
    offs_types = {}
    for ci, cls in enumerate(classes):
        ft = _final_fields(cls)
        sig = frozenset((off, type_width(ft[off])) for off in ft)
        nm = class_name(sig)
        k = 2
        while nm in used:
            nm = '%s_%d' % (class_name(sig), k)
            k += 1
        used.add(nm)
        names[ci] = nm
        offs_types[ci] = ft
    # ---- extra families: merge independently, then fold/append ----
    ptr_n = len(classes)
    amp_class_of, amp_classes = merge_classes(amp_layouts)
    fold_append(amp_class_of, amp_classes, class_of, names, offs_types, used,
                aggregates=classes)
    dir_class_of, dir_classes = merge_classes(dir_layouts)
    fold_append(dir_class_of, dir_classes, class_of, names, offs_types, used,
                aggregates=classes)
    return class_of, classes, names, offs_types, site_count, amp_site_count, \
        dir_site_count, ptr_n


def gen_header(class_of, classes, names, offs_types, ptr_n=None, append=False):
    """Write structs.h.

    Class ordering: when ptr_n is given, indices < ptr_n (pointer family) are
    emitted first in geometry order, then the address-form classes (index
    order); with ptr_n=None every class is geometry-ordered. `classes`
    (aggregate site counters) is optional and only feeds the coverage tally.

    When append=True the pointer section already on disk is preserved
    byte-for-byte and only the address-form classes (index >= ptr_n) are
    spliced in before the final #endif — --extend uses this so incremental
    runs never rewrite the frozen pointer section.
    """
    def base_stats(which):
        bc = collections.defaultdict(collections.Counter)
        fc = collections.defaultdict(set)
        for (fp, base), ci in class_of.items():
            if not which(ci):
                continue
            if isinstance(base, str):
                b = base
            elif base[0] == 'a':
                b = '&%s' % base[1]
            elif base[0] == 'i':
                b = '%s+' % base[1]
            else:
                b = '*(%s@0x%X)' % (base[1], base[2])
            bc[ci][b] += 1
            fc[ci].add(os.path.basename(fp))
        return bc, fc

    n_fields = n_sites = n_emit = 0
    out = []

    def emit_block(ci, bc, fc):
        """Append one typedef block; return (sites_covered, fields_added)."""
        ft = offs_types[ci]
        lines, dropped = emit_struct(display_name(names[ci]), ft)
        for d in dropped:
            del ft[d]
        if not ft:
            return 0, 0
        ns = sum(sum(c.values()) for c in classes[ci].values()) \
            if classes is not None else 0
        bases = ', '.join('%s×%d' % (b, c) for b, c in bc[ci].most_common(4))
        hi = max(ft) + type_width(ft[max(ft)])
        out.append('')
        out.append('// %s — %d file(s), %d fields, offsets 0x%X..0x%X%s' % (
            display_name(names[ci]), len(fc[ci]), len(ft), min(ft), hi,
            '' if not bases else ' · bases %s' % bases))
        out.extend(lines)
        return ns, len(ft)

    geom = lambda ci: (min(offs_types[ci]) if offs_types[ci] else 0,
                       max(offs_types[ci]) if offs_types[ci] else 0,
                       len(offs_types[ci]))
    if append:
        amp = sorted([ci for ci in offs_types if ci >= ptr_n])
        if not amp:
            return 0, 0, 0
        bc, fc = base_stats(lambda ci: ci >= ptr_n)
        for ci in amp:
            ns, nf = emit_block(ci, bc, fc)
            n_sites += ns
            n_fields += nf
            n_emit += 1
        txt = open(OUT_H, encoding='utf-8').read()
        tail = txt.rstrip()
        assert tail.endswith('#endif'), 'header missing final #endif'
        body = tail[:-len('#endif')].rstrip() + '\n'
        open(OUT_H, 'w').write(body + '\n'.join(out) + '\n#endif\n')
        return n_emit, n_fields, n_sites

    if ptr_n is None:
        order = sorted(range(len(offs_types)), key=geom)
    else:
        ptr = sorted([ci for ci in offs_types if ci < ptr_n], key=geom)
        amp = sorted([ci for ci in offs_types if ci >= ptr_n])
        order = ptr + amp
    out.append('// Auto-generated by tools/detect_structs.py — do not edit by hand.')
    out.append('// Anonymous struct layouts inferred from the byte-offset deref')
    out.append('// patterns in src/ + src/wip/ (see the tool docstring for the')
    out.append('// merging and safety rules). Fields are named by absolute byte')
    out.append('// offset; pads fill the gaps. Rewriting is byte-safe: a site is')
    out.append('// only rewritten when its cast type matches the field type.')
    out.append('#ifndef _STRUCTS_H_')
    out.append('#define _STRUCTS_H_')
    out.append('')
    out.append('#include "types.h"')
    out.append('')
    # __ps_t is an SN/ProDG cc1 builtin (8-byte paired single) used for PS
    # fields. ngccc predefines __SN__, so it keeps the builtin; any other
    # compiler gets a plain 8-byte stand-in so this header still parses for
    # host-side tooling (clangd, m2c, permuter, syntax checks).
    out.append('// __ps_t is an SN/ProDG cc1 builtin (8-byte paired single); ngccc')
    out.append('// (which predefines __SN__) keeps the builtin. Other compilers get a')
    out.append('// plain 8-byte stand-in so this header parses for host-side tooling.')
    out.append('#ifndef __SN__')
    out.append('typedef double __ps_t;')
    out.append('#endif')
    bc, fc = base_stats(lambda ci: True)
    for ci in order:
        ns, nf = emit_block(ci, bc, fc)
        n_sites += ns
        n_fields += nf
    out.append('')
    out.append('#endif')
    open(OUT_H, 'w').write('\n'.join(out) + '\n')
    return len(order), n_fields, n_sites


def write_cache(class_of, names, offs_types, site_count):
    """Persist the detection so apply_structs.py resolves against the SAME
    frozen reference it was run with (header + cache are written together by
    this tool; apply_structs never regenerates either)."""
    import json
    def base_key(b):
        return list(b) if isinstance(b, tuple) else b
    payload = {
        'site_count': site_count,
        'names': {str(ci): nm for ci, nm in names.items()},
        'offs': {str(ci): {str(off): typ for off, typ in ft.items()}
                 for ci, ft in offs_types.items()},
        'class_of': {'%s|%s' % (fp, json.dumps(base_key(b))): ci
                     for (fp, b), ci in class_of.items()},
    }
    with open(CACHE, 'w') as f:
        json.dump(payload, f, sort_keys=True)
    return CACHE


def load_cache():
    """Load the frozen detection reference written by write_cache()."""
    import json
    with open(CACHE) as f:
        p = json.load(f)
    names = {int(ci): nm for ci, nm in p['names'].items()}
    offs_types = {int(ci): {int(off): typ for off, typ in ft.items()}
                  for ci, ft in p['offs'].items()}
    class_of = {}
    for key, ci in p['class_of'].items():
        fp, bjson = key.split('|', 1)
        # normalize legacy absolute keys (pre-relative-key caches) so an
        # old cache still resolves after a fresh detect run rewrites it
        if os.path.isabs(fp):
            try:
                fp = os.path.relpath(fp, ROOT)
            except ValueError:
                pass
        b = json.loads(bjson)
        b = tuple(b) if isinstance(b, list) else b
        class_of[(fp, b)] = int(ci)
    return class_of, names, offs_types, int(p['site_count'])


def extend_main():
    """Incremental extra-family detection on an already-applied corpus.

    Loads the frozen cache (pointer-family classes from the pristine corpus),
    detects the address-form (`&base`) and direct (`BASE + LIT`) families on
    the current corpus — their sites are untouched by the earlier rewrites, so
    results equal a pristine run — folds family classes into existing classes
    with an identical field map and appends the rest, then rewrites header +
    cache. Pointer classes are never recomputed or re-voted on.
    """
    class_of, names, offs_types, site_count = load_cache()
    files = sorted(glob.glob(os.path.join(ROOT, 'src', '*.c')) +
                   glob.glob(os.path.join(ROOT, 'src', 'wip', '*.c')))
    ptr_n = len(offs_types)
    used = set(names.values())
    fams = []
    for label, coll in (('ptr', collect_layouts(files)),
                        ('addr', collect_amp_layouts(files)),
                        ('direct', collect_i_layouts(files))):
        layouts, nsites = coll
        fco, fcls = merge_classes(layouts)
        covered = sum(sum(c.values()) for cls in fcls for c in cls.values())
        before = len(offs_types)
        fold_append(fco, fcls, class_of, names, offs_types, used)
        n_new = len(offs_types) - before
        fams.append((label, nsites, len(fco), len(fcls), covered, n_new))
    n_classes, n_fields, _n_sites = gen_header(
        class_of, None, names, offs_types, ptr_n, append=True)
    # keep the frozen site_count stat as-is — it counts the original corpus's
    # sites; re-adding per-run family tallies would inflate it non-idempotently
    write_cache(class_of, names, offs_types, site_count)
    for label, nsites, nlay, ncls, covered, n_new in fams:
        print('%-7s sites:      %d' % (label, nsites))
        print('  layouts: %d  classes: %d (new: %d)  covered: %d (%.1f%%)' % (
            nlay, ncls, n_new, covered, 100.0 * covered / nsites if nsites else 0))
    print('total classes:       %d (ptr %d)' % (len(offs_types), ptr_n))
    print('header:              %s (%d KB)' % (OUT_H, os.path.getsize(OUT_H) // 1024))
    return 0


def main():
    if '--extend' in sys.argv:
        return extend_main()
    class_of, classes, names, offs_types, site_count, amp_site_count, \
        dir_site_count, ptr_n = build()
    n_classes, n_fields, n_sites = gen_header(class_of, classes, names, offs_types, ptr_n)
    write_cache(class_of, names, offs_types,
                site_count + amp_site_count + dir_site_count)
    total = site_count + amp_site_count + dir_site_count
    n_amp = sum(1 for k in class_of if isinstance(k[1], tuple) and k[1][0] == 'a')
    n_dir = sum(1 for k in class_of if isinstance(k[1], tuple) and k[1][0] == 'i')
    print('files scanned:       %d' % len(set(k[0] for k in class_of)))
    print('deref sites:         %d (%d ptr + %d &addr + %d direct)' % (
        total, site_count, amp_site_count, dir_site_count))
    print('layouts (file,base): %d (%d addr-form, %d direct)' % (
        len(class_of), n_amp, n_dir))
    print('struct classes:      %d' % n_classes)
    print('struct fields:       %d' % n_fields)
    print('sites covered:       %d (%.1f%%)' % (n_sites, 100.0 * n_sites / total))
    print('header:              %s (%d KB)' % (OUT_H, os.path.getsize(OUT_H) // 1024))
    return 0


if __name__ == '__main__':
    sys.exit(main())