#!/usr/bin/env python3
"""--fn-args style pass: extend fn definitions to the arity callers use.

A def like `void fn_8001473C(void)` while retail callers load an argument
into r3 before the call means the ORIGINAL prototype had the parameter and
the callee just does not read it (m2c drops unused leading params and keeps
slot-derived names on the rest, e.g. `(f32 *arg2, f32 *arg3)` in a function
whose callers pass 4 args). When the corpus's MOST COMMON real call-site
arity E exceeds the def arity D (with >= 2 calls at E), the def is extended
to E parameters — appended after the existing ones and typed per the
majority caller declaration, so the body's register reads are untouched and
unused params emit no code (byte-identical by construction). Caller files'
forward declarations are left alone: each already declares exactly what its
own calls pass (Metrowerks rejects calls whose arg count mismatches the
in-scope prototype, so a low-arity caller cannot be re-declared higher).
Redundant casts at call sites of these functions are dropped (identity
`(T)x` over a `T`-typed param, and `(s32)/(u32)/(int)` over an address-y
operand passed to a pointer-typed param). Variadic-like functions (call
sites spread across several arities with no dominant one) and single-stray
high-arity callers are left alone.

src files are byte-verified per file; inert wip drafts get a compile-sanity
check (revert only when the edit breaks a previously-compiling body).
"""
import os
import re
import sys
import glob
import collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)
sys.path.insert(0, os.path.join(ROOT, 'tools'))

import apply_structs as ap

APPLY = '--apply' in sys.argv
LIMIT = None
if '--limit' in sys.argv:
    LIMIT = int(sys.argv[sys.argv.index('--limit') + 1])

FN_RE = ap.FN_RE


# --------------------------------------------------------------------------
# text helpers
# --------------------------------------------------------------------------
def _bal(txt, j):
    """txt[j] == '(' : index of the matching ')'."""
    d = 0
    while j < len(txt):
        c = txt[j]
        if c == '(':
            d += 1
        elif c == ')':
            d -= 1
            if d == 0:
                return j
        j += 1
    return -1


def _split_args(s):
    """Top-level comma split of an argument list body."""
    if s.strip() in ('', 'void'):
        return []
    out, d, cur = [], 0, ''
    for c in s:
        if c == '(':
            d += 1
            cur += c
        elif c == ')':
            d -= 1
            cur += c
        elif c == ',' and d == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += c
    if cur.strip():
        out.append(cur.strip())
    return out


# token right before an fn name in a *declaration* is one of these (or `*`)
_TYPE_LAST = re.compile(
    r'^(?:const\s+)?(?:Unk_[0-9A-F]+|%s|S_[0-9A-F]+_?[0-9]*|s8|u8|s16|u16|'
    r's32|u32|s64|u64|f32|f64|char|short|int|long|float|double|void|bool|'
    r'signed|unsigned|size_t|struct|extern)$' % '|'.join(ap.ds.ALIASES.values()))


def _is_decl(txt, name_start):
    """True when the fn mention at name_start is a prototype declaration
    (not a call). A decl has a return-type chain between the statement start
    and the fn name; a call never does."""
    seg_start = max(txt.rfind(';', 0, name_start),
                    txt.rfind('{', 0, name_start),
                    txt.rfind('}', 0, name_start),
                    txt.rfind('\n', 0, name_start)) + 1
    seg = txt[seg_start:name_start]
    if not seg.strip():
        return False  # bare expression statement `fn_X(...);`
    if '=' in seg or '(' in seg:
        return False  # assignment / if / return / args forms
    words = re.findall(r'[A-Za-z_]\w*', seg)
    if not words:
        return False
    last = words[-1]
    return bool(_TYPE_LAST.match(last)) or re.search(r'\*\s*$', seg)


def _param_type(pt):
    """(type, name) of a parameter; opaque (whole) for fn-ptr/array params."""
    pt = pt.strip()
    if pt == '...':
        return '...', ''
    if '(' in pt or '[' in pt:
        return pt, ''
    m = re.match(r'^(.*?)([A-Za-z_]\w*)\s*$', pt)
    if not m:
        return pt, ''
    prefix, name = m.group(1).strip(), m.group(2)
    if not prefix:
        return pt, ''
    pwords = re.findall(r'[A-Za-z_]\w*', prefix)
    if pwords and (_TYPE_LAST.match(pwords[-1]) or prefix.endswith('*')):
        return prefix, name
    return pt, ''


# --------------------------------------------------------------------------
# candidate scan
# --------------------------------------------------------------------------
def _better_def(new, old):
    """Prefer the byte-verified src copy over an inert wip draft as the def
    target when a fn exists in both dirs (same basename)."""
    if old is None:
        return True
    def _wip(path):
        return path.startswith(os.path.join(ROOT, 'src', 'wip', ''))
    return not _wip(new['file']) and _wip(old['file'])


def scan(files):
    defs = {}                       # addr -> dict(file, params, dopen, dclose, is_src)
    decls = collections.defaultdict(lambda: collections.defaultdict(list))
    selfdecls = collections.defaultdict(list)   # addr -> [(file, op, cp, params)]
    calls = collections.defaultdict(collections.Counter)  # addr -> {arity: n}

    for f in files:
        m = FN_RE.match(os.path.basename(f))
        addr = m.group(1)
        raw = open(f, encoding='utf-8', errors='replace').read()
        txt = ap.ds.mask_comments_strings(raw)
        for dm in re.finditer(r'\bfn_%s\s*\(' % addr, txt):
            cp = _bal(txt, dm.end() - 1)
            if '{' in txt[cp + 1:cp + 40].split(';')[0]:
                params = _split_args(raw[dm.end():cp])
                nd = dict(file=f, params=params, dopen=dm.end(),
                          dclose=cp, defpos=dm.start())
                if _better_def(nd, defs.get(addr)):
                    defs[addr] = nd
                break

    for f in files:
        raw = open(f, encoding='utf-8', errors='replace').read()
        txt = ap.ds.mask_comments_strings(raw)
        b = os.path.basename(f)
        for cm in re.finditer(r'\bfn_([0-9A-F]{8})\s*\(', txt):
            addr = cm.group(1)
            if addr not in defs:
                continue
            cp = _bal(txt, cm.end() - 1)
            params = _split_args(raw[cm.end():cp])
            if b == 'fn_%s.c' % addr:
                # own file: skip the definition itself, record extra decls
                if cm.start() == defs[addr]['defpos']:
                    continue
                if _is_decl(txt, cm.start()):
                    selfdecls[addr].append((f, cm.end(), cp, params))
                continue
            if _is_decl(txt, cm.start()):
                decls[addr][f].append((cm.start(), cm.end(), cp, params))
            else:
                calls[addr][len(params)] += 1

    cand = {}
    for addr, d in defs.items():
        cc = calls.get(addr)
        if not cc:
            continue
        D = len(d['params'])
        E, Ec = max(cc.items(), key=lambda kv: (kv[1], kv[0]))
        # strict dominance: E's count must beat every other arity's count,
        # otherwise the call sites are spread across arities with no
        # dominant one (variadic-like / overload ambiguity) and the def is
        # left alone.
        runner = max((c for a, c in cc.items() if a != E), default=0)
        if E > D and Ec >= 2 and Ec > runner:
            cand[addr] = dict(d, D=D, E=E, counts=dict(cc))
    return defs, decls, calls, cand, selfdecls


def _canon_slots(decls_for_addr, E):
    """Per-slot majority (type, name) over caller decls that have that slot.
    Missing slots get ('s32', '') so appended params are always typed."""
    per = [collections.Counter() for _ in range(E)]
    for _f, dlist in decls_for_addr.items():
        for (_st, _op, _cp, params) in dlist:
            for i, p in enumerate(params[:E]):
                per[i][_param_type(p)] += 1
    out = []
    for i in range(E):
        if per[i]:
            (t, n), _c = per[i].most_common(1)[0]
            out.append((t, n))
        else:
            out.append(('s32', ''))
    return out


def _fmt_slot(slot):
    t, n = slot
    return ('%s %s' % (t, n)).strip() if n else t


# --------------------------------------------------------------------------
# cast-drop helpers
# --------------------------------------------------------------------------
_INTCAST = re.compile(r'\(\s*(s32|u32|s16|u16|s8|u8|int|long)\s*\)\s*(.*)$', re.S)


def _drop_cast_arg(arg, ptype):
    """Replacement for one call argument when its cast is redundant, else
    None. Identity `(T)x` over an exactly-`T` param, and int-casts over
    address-y operands passed to pointer params."""
    a = arg.strip()
    if a.startswith('('):
        m = _INTCAST.match(a)
        if m:
            ct, inner = m.group(1), m.group(2).strip()
            pt = ptype.strip()
            if pt.endswith('*') and (inner.startswith('&') or
                                     inner.startswith('lbl_')):
                return inner
            if _norm(ct) == _norm(pt):
                return inner
            return None
        # pointer identity `(void *)x` over a `void *` param, etc.
        m2 = re.match(r'\(\s*([A-Za-z_]\w*(?:\s*\*)*)\s*\)\s*(.*)$', a, re.S)
        if m2 and m2.group(1).strip().endswith('*'):
            ct, inner = m2.group(1).strip(), m2.group(2).strip()
            if _norm(ct) == _norm(ptype.strip()):
                return inner
    return None


def _norm(t):
    return (t.replace('int', 's32').replace('float', 'f32')
            .replace('signed', '').strip())


def _is_float_type(t):
    t = t.strip().rstrip('*').strip()
    return t in ('f32', 'f64', 'float', 'double', '__ps_t')


def _def_param_list(d, canon):
    """Final param list for the def: existing params verbatim (fn-pointer /
    array declarators must not be decomposed), appended slots typed per the
    majority caller decl and always NAMED (mwcc rejects anonymous params in
    definitions). Synthesized argN / fargN names never collide with any
    identifier already present in the existing params."""
    old = d['params']
    E = d['E']
    used = set()
    for p in old:
        used.update(re.findall(r'[A-Za-z_]\w*', p))
    out = list(old)
    for i in range(len(old), E):
        t, n = canon[i]
        if not n:
            prefix = 'farg' if _is_float_type(t) else 'arg'
            k = 0
            while ('%s%d' % (prefix, k)) in used:
                k += 1
            n = '%s%d' % (prefix, k)
            used.add(n)
        out.append(_fmt_slot((t, n)))
    return out


# --------------------------------------------------------------------------
# main
# --------------------------------------------------------------------------
def main():
    files = sorted(glob.glob(os.path.join(ROOT, 'src', '*.c')) +
                   glob.glob(os.path.join(ROOT, 'src', 'wip', '*.c')))
    files = [f for f in files if FN_RE.match(os.path.basename(f))]
    if LIMIT is not None:
        files = files[:LIMIT]

    defs, decls, calls, cand, selfdecls = scan(files)

    rows = []
    per_file = collections.defaultdict(list)   # file -> [(start, end, repl)]
    n_deffix = n_castdrop = 0

    for addr in sorted(cand):
        d = cand[addr]
        canon = _canon_slots(decls.get(addr, {}), d['E'])
        # 1. def edit
        oldbody = ', '.join(d['params']) if d['params'] else 'void'
        newbody = ', '.join(_def_param_list(d, canon)) or 'void'
        if newbody != oldbody:
            per_file[d['file']].append((d['dopen'], d['dclose'], newbody))
            n_deffix += 1
        # 1b. redundant self-prototypes must follow the def. Each entry
        # records its OWN file (src and wip copies share the basename), so
        # spans always apply to the text they were measured in.
        for (sfile, op, cp, params) in selfdecls.get(addr, ()):
            if len(params) >= d['E']:
                continue
            # if the occurrence is the OTHER copy's definition (not a
            # prototype), appended params must be named (mwcc rejects
            # anonymous params in definitions).
            stxt = open(sfile, encoding='utf-8', errors='replace').read()
            if '{' in stxt[cp + 1:cp + 40].split(';')[0]:
                sd = dict(file=sfile, params=params, E=d['E'])
                app = _def_param_list(sd, canon)[len(params):]
            else:
                app = [_fmt_slot(canon[i]) for i in range(len(params), d['E'])]
            nb = ', '.join(params + app) if (params + app) else 'void'
            per_file[sfile].append((op, cp, nb))
            n_deffix += 1
        rows.append((addr, os.path.basename(d['file']), d['D'], d['E'],
                     d['counts'], len(decls.get(addr, {}))))

    # 3. cast drops: one pass per file over candidate-fn call sites
    for f in files:
        txt = open(f, encoding='utf-8', errors='replace').read()
        masked = ap.ds.mask_comments_strings(txt)
        for cm in re.finditer(r'\bfn_([0-9A-F]{8})\s*\(', masked):
            addr = cm.group(1)
            if addr not in cand or f == cand[addr]['file']:
                continue
            if _is_decl(masked, cm.start()):
                continue
            dlist = decls.get(addr, {}).get(f)
            if not dlist:
                continue
            decl_params = dlist[0][3]
            cp = _bal(masked, cm.end() - 1)
            # walk top-level args with exact character spans
            i = cm.end()
            depth = 0
            seg_lo = i
            di = 0
            while i <= cp:
                c = masked[i] if i < cp else ','
                if c == '(':
                    depth += 1
                elif c == ')':
                    depth -= 1
                elif c == ',' and depth == 0:
                    raw = masked[seg_lo:i]
                    a = raw.strip()
                    if a and di < len(decl_params):
                        pt, _n = _param_type(decl_params[di])
                        repl = _drop_cast_arg(a, pt)
                        if repl is not None and repl != a:
                            alo = seg_lo + raw.index(a)
                            per_file[f].append((alo, alo + len(a), repl))
                            n_castdrop += 1
                    di += 1
                    seg_lo = i + 1
                i += 1

    print('fn-arg candidates (apply=%s):' % APPLY)
    for addr, fb, D, E, cc, nd in rows:
        print('  %s %-24s def(%d) -> E=%d  calls=%s  caller-files=%d'
              % (addr[:8], fb, D, E, cc, nd))
    print('  def fixes: %d, cast drops: %d' % (n_deffix, n_castdrop))
    if not APPLY:
        print('  pass --apply to write')
        return 0

    written = reverted = 0
    reverted_files = []
    for f in sorted(per_file):
        edits = sorted(set(per_file[f]), key=lambda e: -e[0])
        txt = open(f, encoding='utf-8', errors='replace').read()
        new_txt = txt
        for a, b, rep in edits:
            new_txt = new_txt[:a] + rep + new_txt[b:]
        if new_txt == txt:
            continue
        mn = FN_RE.match(os.path.basename(f))
        addr = int(mn.group(1), 16) if mn else None
        is_src = f.startswith(os.path.join(ROOT, 'src', '')) and not \
            f.startswith(os.path.join(ROOT, 'src', 'wip', ''))
        ok = True
        if is_src and addr is not None:
            sym_size = ap.SYM_SIZE.get(addr)
            ok = sym_size is not None and ap.verify_src(addr, sym_size, new_txt)
        else:
            if addr is not None and ap.verify_compiles(addr, txt) and \
                    not ap.verify_compiles(addr, new_txt):
                ok = False
        if ok:
            open(f, 'w').write(new_txt)
            written += 1
        else:
            reverted += 1
            reverted_files.append(f)
    print('  %d files written, %d reverted' % (written, reverted))
    for rf in sorted(reverted_files):
        print('    REVERT %s' % rf.replace(ROOT + '/', ''))
    return 0


if __name__ == '__main__':
    main()
