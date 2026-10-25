#!/usr/bin/env python3
"""Retype function parameters that are only ever used through struct casts.

Generated code carries object pointers as untyped params and re-casts them at
every use:

    void fn_8025A258(s32 arg0, void *arg1) {
        ...
        ((Unk_E80761A5 *)arg1)->unk0x19C |= 0x400;
        v = *((u32 *)&((Unk_E80761A5 *)arg1)->unk0x198);
    }

When every use of a param is (or is reducible to) struct-pointer access, the
param is retyped to the struct pointer directly and the redundant casts are
dropped:

    void fn_8025A258(s32 arg0, Unk_E80761A5 *arg1) {
        ...
        arg1->unk0x19C |= 0x400;
        v = *((u32 *)&arg1->unk0x198);
    }

Per-param qualification (a param is retyped only when ALL of its occurrences
are safe under the new pointer type):

  * cast-preceded uses — the identifier sits inside an explicit cast
    (`((Unk_X *)NAME)`, `(void *)NAME`, `(char *)NAME`, `(s32)NAME`, ...).
    After retyping, the cast stays (or is dropped when it matches the new
    type); either way the expression means the same thing. Explicit POINTER
    casts (`(void *)NAME`, `(char *)NAME`) are safe under any pointer type
    and count as pointer evidence for the void rule below.
  * bare uses in benign contexts — comparisons (`NAME == 0`), boolean /
    ternary tests, call arguments, assignments/returns (pointer<->int
    conversions are register moves, codegen-identical).
  * GOOD evidence uses: `((Unk_X *)NAME)` — the cast type T is chosen as the
    majority GOOD type; the decl becomes `T *NAME` and every `((T *)NAME)`
    cast is dropped.
  * occurrences are scanned BODY-only: a param's name inside other
    functions' prototype declarations is not a use of the param.

Dangerous uses disqualify the param: bare pointer arithmetic / scaling
(`NAME + k`, `NAME[k]`, `NAME++`) that would re-scale against the new pointee
size, subscript-INDEX use (`x[NAME]` — an integer role), address-of
(`&NAME`), bitwise/shift/divide ops on the bare value, and assignment to the
param.

PROPAGATION rule (M6.89i): an INTEGER/void param with no struct (GOOD)
evidence can still BE a struct pointer when its only uses are forwarding.
Bare passes are judged against the callee's DECOMPILED DEFINITION signature
(a lazily-built corpus map of fn_-named defs' per-index param types): an
`Unk_X *` position retypes the param to that class directly — m2c drafts
declared these QB-block args as s32/void* because they only forward them, so
`ScriptSetConfig(s32 arg0)` whose arg0 flows into `fn_801286D0(Unk_2EF06E12
*, ...)` becomes `Unk_2EF06E12 *arg0`. Iterating the pass to a fixed point
walks forwarding chains (fn_80128228 -> fn_80127F60 -> ...). Each caller's
extern prototypes of decompiled callees are synced to the definition's real
signature (`sync_callee_decls`; arity-matched, shared-header pointer types
only, `(void)` wrappers skipped) so the forward declarations carry the
struct. Without a class (only file-local pointer guesses / explicit
`(void *)` casts) the param falls back to `void *`. The function DEFINITION
is found by its generated `fn_ADDR` name, falling back to any
`name(params) {` — promoted/renamed functions (the Script* QB command
handlers) are covered too.

Files that promote drafts often declare the function's own prototype above the
definition (`s32 fn_X(void *);`). A retyped definition would conflict with the
stale prototype, so retypes are mirrored positionally into every in-file
self-prototype (their param segments become unnamed `Unk_X *` entries, which
keeps the two declarations consistent; prototype parameter names are optional
in C).

Safety net (same as tools/apply_structs.py): every rewritten src/fn_*.c file
is compiled with the real ngccc flags and byte-compared against the retail
bytes — any file that doesn't come back 100% identical is reverted. WIP drafts
get a compile-sanity check (revert only when the rewrite breaks a previously
compiling body). Pointer retyping is a pure type-level change, so codegen
should never move; the verification proves it per file.

Idempotent: params whose declaration already names a `Unk_` type are skipped.

The same cleanup applies to function-top LOCAL variables that only ever hold
struct pointers (`void *base;` assigned once, then read through
`((Unk_XXXX *)base)`). Locals differ from params in three ways: their
declaration lives inside the body (discovered by scanning the function-top
declaration statements), they are routinely WRITTEN (`p = expr;` — allowed,
since the write target type never rescales anything; only p's OWN arithmetic
qualifies as dangerous), and there are no self-prototypes to mirror. Locals
declared `volatile`/`const`/arrays/fn-pointers or in multi-declarator
statements are skipped.

Usage:
    tools/venv/bin/python tools/type_params.py --dry-run
    tools/venv/bin/python tools/type_params.py --apply [--jobs 8]
    tools/venv/bin/python tools/type_params.py --plan-file <path>   # debug
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
import apply_structs as ap

APPLY = '--apply' in sys.argv
JOBS = 8
if '--jobs' in sys.argv:
    JOBS = int(sys.argv[sys.argv.index('--jobs') + 1])
LIMIT = None
if '--limit' in sys.argv:
    LIMIT = int(sys.argv[sys.argv.index('--limit') + 1])
PLAN_FILE = None
if '--plan-file' in sys.argv:
    PLAN_FILE = sys.argv[sys.argv.index('--plan-file') + 1]

FN_NAME_RE = re.compile(r'\bfn_[0-9A-F]{8}\b')
# ap.CLASS matches canonical Unk_* names and display aliases (CStruct, ...);
# ap.canonical() maps a match back to the Unk_ cache key, ap.display() to the
# corpus spelling. Votes stay canonical; every emission uses the display name.
GOOD_PRE = re.compile(r'\(\s*\(\s*(' + ap.CLASS_CI + r')\s*\*\s*\)\s*$')
# explicit pointer casts: `(void *)NAME`, `(char *)NAME`, ... — the draft's
# own admission that the value is a pointer (evidence for the void* retype)
PTRCAST_PRE = re.compile(
    r'\(\s*((?:const\s+|volatile\s+)*(?:void|char|s8|u8|s16|u16|s32|u32|'
    r's64|u64|f32|f64|int|short|long|bool|size_t|%s)\s*\*)\s*$' % ap.CLASS_INNER_CI)
DECL_UNK_RE = re.compile(r'\b(?:Unk_[0-9A-Fa-f]+|%s)\b' % '|'.join(ds.ALIASES.values()))
# integer scalars that are register-passed like pointers (f32/f64 excluded:
# they travel in the FP register file, so they can never be pointer-forwarded)
INT_SCALAR_RE = re.compile(
    r'^(?:s32|u32|s16|u16|s8|u8|s64|u64|char|short|int|long|bool|size_t|'
    r'__ps_t)$')
CTRL_KW = set('if while for switch return sizeof case do else'.split())
PROTO_DECL_RE = re.compile(
    r'(?m)^\s*(?:extern\s+)?'
    r'((?:s32|u32|s16|u16|s8|u8|f32|f64|void|char|int|bool|size_t|short|'
    r'long|%s|\w+_t)\s*\*?)\s*([A-Za-z_]\w*)\s*\(' % ap.CLASS_INNER_CI)
SHADOW_RE = re.compile(
    r'\b(?:register\s+|static\s+|const\s+|volatile\s+)*(?:s32|u32|s16|u16|s8|u8|'
    r'f32|f64|char|void|int|bool|size_t|%s|\w+_t)\s*\*?\s*'
    r'NAME\s*(?:=|;|\[|,)' % ap.CLASS_INNER_CI)
# risky leading operators on a bare identifier
PREFIX_RISKY = set('&*+-~%^|/')
# risky operators directly after a bare identifier
POST_RISKY = set('+-[*')
# Byte-addressed params (void*/char*): their bare `NAME +/- EXPR` arithmetic
# is byte-based, so a struct retype is safe when those sites are rewritten to
# explicit `(char *)NAME +/- EXPR` (fn_8005E660's `arg0 + temp_r9->unk0x20`
# family). Every OTHER disqualifying shape still rejects the retype.
BYTE_PTR_DECL_RE = re.compile(r'^(?:const\s+|volatile\s+)*(?:void|char)\s*\*$')


def fixable_byte_arith(pre, post):
    """True when the occurrence is the bare `NAME +/-` left operand of byte
    arithmetic (NAME not part of a cast/address/arrow chain before the op)."""
    pl = post.lstrip()
    if not pl or pl[0] not in '+-':
        return False
    if pl[:2] in ('++', '--'):
        return False  # postfix ++/-- would need `((char *)NAME)++` — reject
    pre = pre.rstrip()
    if not pre:
        return False
    c = pre[-1]
    if c in ')*&>]' or c.isalnum() or c == '_':
        return False  # cast result / indirection / address / member / index
    if c in '+-*/%':
        return False  # inside a longer binary/scale chain
    return True


def split_segments(ptext):
    """Top-level comma split of a param-list string -> [(start, end)]."""
    segs = []
    depth = 0
    start = 0
    for i, c in enumerate(ptext):
        if c in '([':
            depth += 1
        elif c in ')]':
            depth -= 1
        elif c == ',' and depth == 0:
            segs.append((start, i))
            start = i + 1
    segs.append((start, len(ptext)))
    return segs


def parse_params(ptext, base):
    """Parse `ptext` (at masked offset `base`) into per-segment entries.

    Returns a list aligned 1:1 with the raw segments, each
    (decl, name, decl_start, name_start) with decl/name None when the segment
    is not a simple scalar/pointer param (fn-ptr / array / unnamed).
    Offsets are file-global.
    """
    out = []
    for a, b in split_segments(ptext):
        seg = ptext[a:b]
        m = re.search(r'\b([A-Za-z_]\w*)\s*$', seg) if seg.strip() else None
        if not m:
            out.append((None, None, base + a, None))
            continue
        decl = seg[:m.start()].strip()
        if not decl or '(' in decl or '[' in decl or ')' in decl:
            out.append((None, None, base + a, None))
            continue
        out.append((decl, m.group(1), base + a, base + a + m.start()))
    return out


def occ_class(pre, post, allow_assign=False):
    """Classify one occurrence of a variable name.

    pre  = masked text immediately before the identifier
    post = masked text immediately after it
    allow_assign — locals are routinely written (`p = expr;`); for them a
    bare `=` write target is safe (only the variable's OWN arithmetic or
    address-of is dangerous). Params are never reassigned in generated code,
    so their writes stay disqualifying.
    Returns (safe, good_type, ptr_cast) — good_type is the Unk_ type when the
    use is the `((Unk_X *)NAME)` cast shape (the retype evidence + drop
    target); ptr_cast is True when the use is an explicit pointer cast like
    `(void *)NAME` / `(char *)NAME` (evidence for the void* retype, and safe
    under any pointer type).
    """
    pws = pre.rstrip()
    if not pws:
        return False, None, False
    gm = GOOD_PRE.search(pws)
    if gm:
        # evidence only when the cast wraps NAME completely: `((T *)NAME)`
        # (close paren right after the name). `((T *)NAME->member` is a cast
        # OF THE MEMBER, not of NAME — counting it would flip-flop the type
        # once an inner cast is dropped (fn_80184CD0 temp_r3).
        if not post.lstrip().startswith(')'):
            return False, None, False
        return True, ap.canonical(gm.group(1)), False
    pm = PTRCAST_PRE.search(pws)
    if pm:
        # explicit pointer cast wrapping NAME: `(void *)NAME`. Safe under any
        # pointer type (after the void* retype this cast is dropped); never
        # evidence for a specific Unk_ class.
        if not post.lstrip().startswith(')'):
            return False, None, False
        return True, None, True
    if pws[-1] == '[':
        # NAME is a SUBSCRIPT INDEX (`x[NAME]`) — an integer role a pointer
        # cannot fill. Retyping would break the compile, so reject (the
        # subscript-base case `NAME[i]` is caught by POST_RISKY below).
        return False, None, False
    if re.search(r'\bswitch\s*\(\s*$', pws):
        # `switch (NAME)` — the operand must be an integer, so a pointer
        # retype breaks the compile (fn_800B48D4 arg1)
        return False, None, False
    if pws.endswith(')'):
        # cast- or grouping-preceded: binary operators after the closing paren
        # act on the cast RESULT, so they are safe under the new pointer type
        # (the cast stays or is dropped, but the meaning is unchanged). But a
        # POSTFIX operator directly on the name binds tighter than the cast
        # (`(s32)NAME[k]` indexes NAME, `(char *)NAME->f` derefs NAME) and
        # would re-scale against the new pointee — reject those.
        pl2 = post.lstrip()
        if pl2[:2] in ('->', '++', '--') or (pl2 and pl2[0] in '[.'):
            return False, None, False
        return True, None, False
    lastc = pws[-1]
    if lastc in PREFIX_RISKY:
        # allow && / || boolean prefixes
        if not ((lastc in '&|') and pws.endswith(lastc * 2)):
            return False, None, False
    if lastc in '<>' and len(pws) >= 2 and pws[-2] == lastc:
        return False, None, False  # shift: NAME on RHS
    pl = post.lstrip()
    if not pl:
        return True, None, False
    nc = pl[0]
    if nc in POST_RISKY:
        return False, None, False
    if nc == '&' and not pl.startswith('&&'):
        return False, None, False
    if nc == '|' and not pl.startswith('||'):
        return False, None, False
    if nc == '=' and not pl.startswith('=='):
        return allow_assign, None, False  # write target: locals only
    if nc in '/%^~':
        return False, None, False
    if nc in '<>' and len(pl) >= 2 and pl[1] == nc:
        return False, None, False  # shift
    return True, None, False


def _def_at(masked, name, op):
    """If `name` at open-paren `op` opens a function definition, return
    (fname, ptext, pstart, pend, popen) as find_definition does."""
    depth = 0
    k = op
    while k < len(masked):
        c = masked[k]
        if c == '(':
            depth += 1
        elif c == ')':
            depth -= 1
            if depth == 0:
                break
        k += 1
    if depth != 0:
        return None
    ptext = masked[op + 1:k]
    if ptext.strip() and masked[k + 1:].lstrip().startswith('{'):
        return name, ptext, op + 1, k, op
    return None


def find_definition(masked):
    """Locate the function DEFINITION.

    Tries `fn_ADDR(<params>) {` first (the generated name); promoted files
    whose definition was renamed off the fn_ prefix (Script* command
    handlers, etc.) are found by the generic `name(<params>) {` fallback.
    Returns (fname, ptext, pstart, pend, popen) with popen the open-paren
    offset, or (None,)*5. Candidates whose param list is empty (a
    `while (fn()) {` false positive) are skipped, as are control keywords.
    """
    for m in FN_NAME_RE.finditer(masked):
        j = masked.find('(', m.end())
        if j < 0 or masked[m.end():j].strip() != '':
            continue
        r = _def_at(masked, m.group(0), j)
        if r is not None:
            return r
    for m in re.finditer(r'\b([A-Za-z_]\w*)\s*\(', masked):
        name = m.group(1)
        if name in CTRL_KW or FN_NAME_RE.match(name):
            continue
        r = _def_at(masked, name, m.end() - 1)
        if r is not None:
            return r
    return None, None, None, None, None


def self_proto_segments(masked, fname, popen):
    """Segments of every `fname(...);` prototype declared before the def."""
    segs_list = []
    for m in re.finditer(r'\b%s\s*\(' % re.escape(fname), masked):
        if m.start() >= popen:
            break
        op = m.end() - 1
        depth = 0
        k = op
        while k < len(masked):
            c = masked[k]
            if c == '(':
                depth += 1
            elif c == ')':
                depth -= 1
                if depth == 0:
                    break
            k += 1
        if depth != 0:
            continue
        if masked[k + 1:].lstrip().startswith(';'):
            segs_list.append([(op + 1 + a, op + 1 + b)
                              for a, b in split_segments(masked[op + 1:k])])
    return segs_list


def _proto_spans(masked):
    """Yield (name, op, close, seg_spans) for every line-anchored prototype
    `TYPE name(...);` in the file — call statements (`fn_X(args);` in the
    body) never start a line with a type, so they cannot match. seg_spans
    are file-global offsets of the param segments."""
    for m in PROTO_DECL_RE.finditer(masked):
        name = m.group(2)
        if name in CTRL_KW:
            continue
        op = m.end() - 1
        depth = 0
        k = op
        while k < len(masked):
            c = masked[k]
            if c == '(':
                depth += 1
            elif c == ')':
                depth -= 1
                if depth == 0:
                    break
            k += 1
        if depth != 0 or not masked[k + 1:].lstrip().startswith(';'):
            continue
        yield name, op, k, [(op + 1 + a, op + 1 + b)
                            for a, b in split_segments(masked[op + 1:k])]


def extern_ptr_map(masked):
    """callee -> {arg_idx: True/False} from top-level `TYPE name(...);`
    prototypes declared in the file (the per-file guesses of the still-asm
    callees' signatures). True = that position is declared pointer-typed.
    """
    out = {}
    for name, _op, _k, segs in _proto_spans(masked):
        idxs = {}
        for ai, (a, b) in enumerate(segs):
            seg = masked[a:b].strip()
            if not seg or '(' in seg or '[' in seg:
                continue
            idxs[ai] = '*' in seg
        if idxs:
            out.setdefault(name, {}).update(idxs)
    return out


def call_arg_index(text, pos):
    """(callee_name, arg_index) for an identifier occurrence ending at pos.
    Returns (None, None) when the occurrence is not a call argument."""
    depth = 0
    i = pos
    while i >= 0:
        c = text[i]
        if c == ')':
            depth += 1
        elif c == '(':
            if depth == 0:
                m = re.search(r'([A-Za-z_]\w*)\s*$', text[:i])
                if not m or m.group(1) in CTRL_KW:
                    return None, None
                d2 = 0
                idx = 0
                for k in range(i + 1, pos):
                    c2 = text[k]
                    if c2 in '([':
                        d2 += 1
                    elif c2 in ')]':
                        d2 -= 1
                    elif c2 == ',' and d2 == 0:
                        idx += 1
                return m.group(1), idx
            depth -= 1
        i -= 1
    return None, None


# lazily-built corpus map: callee name -> per-index param decl strings, from
# the DECOMPILED DEFINITION of every fn_-named function (callers' file-local
# prototypes are per-file guesses; the definition is the type truth)
_DEF_SIGS = [None]


def def_sigs():
    if _DEF_SIGS[0] is not None:
        return _DEF_SIGS[0]
    sigs = {}
    files = sorted(glob.glob(os.path.join(ROOT, 'src', '*.c')) +
                   glob.glob(os.path.join(ROOT, 'src', 'wip', '*.c')))
    for fp in files:
        if not ap.FN_RE.match(os.path.basename(fp)):
            continue
        try:
            text = open(fp, encoding='utf-8', errors='replace').read()
            masked = ds.mask_comments_strings(text)
        except OSError:
            continue
        fname, ptext, ps, pe, _po = find_definition(masked)
        if fname is None or not FN_NAME_RE.match(fname):
            continue  # renamed defs (Script* etc.) are never C-call targets
        decls = [p[0] for p in parse_params(ptext, ps)]
        if decls and all(decls):
            sigs[fname] = decls
    _DEF_SIGS[0] = sigs
    return sigs


def _segment_type_repl(seg, new_type):
    """Replacement for one prototype param segment: swap the type while
    keeping any parameter name. `void *arg0` -> `Unk_X *arg0`; unnamed
    `void *`/`s32`/`s32 *` -> `Unk_X *`. Returns None for fn-ptr/array/
    comment or already-matching segments."""
    if '(' in seg or '[' in seg or '/*' in seg or '*/' in seg:
        return None
    lead = seg[:len(seg) - len(seg.lstrip(' \t'))]
    core = seg.strip()
    if not core:
        return None
    if core.endswith('*'):
        # unnamed pointer segment (`void *`, `s32 *`) — no param name
        if core.replace(' ', '') == new_type.replace(' ', ''):
            return None
        return lead + new_type
    mm = re.search(r'\b([A-Za-z_]\w*)\s*$', core)
    if not mm:
        return None
    last = mm.group(1)
    if last in TYPE_KW:
        # unnamed scalar segment (`s32`)
        if core.replace(' ', '') == new_type.replace(' ', ''):
            return None
        return lead + new_type
    if last.startswith('Unk_') or last in ds.ALIASES.values() \
            or last in CTRL_KW:
        return None  # already-typed or keyword-looking — leave
    # named segment: `s32 arg0`, `void *arg0`, `f32 * arg2`
    typ = core[:mm.start()].rstrip()
    if not typ or typ.replace(' ', '') == new_type.replace(' ', ''):
        return None
    return '%s%s %s' % (lead, new_type, last)


def sync_callee_decls(text, masked, fname):
    """proto_fixes for extern prototypes of DECOMPILED callees whose param
    type contradicts the callee's definition (the per-file guesses say
    `void *`/`s32` where the definition says `Unk_X *`). The file's own
    self-prototypes are skipped (the mirror logic handles those)."""
    sigs = def_sigs()
    fixes = []
    for cname, op, k, segs in _proto_spans(masked):
        if cname == fname or cname not in sigs:
            continue
        ddecls = sigs[cname]
        if len(segs) != len(ddecls) or not segs:
            continue  # arity mismatch vs the definition — leave the decl
        if segs and masked[segs[0][0]:segs[0][1]].strip() == 'void':
            continue  # `(void)` = deliberate no-arg wrapper (C idiom)
        for ai, (a, b) in enumerate(segs):
            want = ddecls[ai]
            if not want:
                continue
            # only sync to types every file can name: Unk_ classes (or their
            # display aliases) from the shared header (ensure_include adds
            # it) or builtin pointers. Hand-named structs (S_80013F94,
            # Big56, ...) live in the callee's own file and would fail to
            # compile here.
            if not re.match(
                    r'^(?:Unk_[0-9A-Fa-f]+|%s|void|char|s8|u8|s16|u16|s32|u32|'
                    r's64|u64|f32|f64|int|short|long|bool|size_t)\s*\*$'
                    % '|'.join(ds.ALIASES.values()),
                    want):
                continue
            repl = _segment_type_repl(text[a:b], want)
            if repl is not None and repl.strip() != text[a:b].strip():
                fixes.append((a, b, repl))
    return fixes


TYPE_KW = set('s32 u32 s16 u16 s8 u8 f32 f64 char void int bool size_t '
              'short long float double const volatile register unsigned '
              'signed static'.split())


def plan_params(text, masked):
    """Return (entries, proto_fixes).

    entries: (idx, name, decl_start, name_start, new_decl, drops) for each
             param to retype — drops are (cast_start, close_idx) spans to
             replace with the bare name.
    proto_fixes: [(seg_start, seg_end, replacement)] mirroring the retyped
             params into in-file self-prototypes.

    Two retype rules, per param:
      * struct rule — at least one `((Unk_X *)NAME)` use (the majority Unk
        type wins, decl becomes `Unk_X *`, matching casts dropped);
      * void rule — NO struct evidence, but the param is provably a pointer:
        an explicit `(void *)NAME`-style cast, or a bare pass into a callee
        position whose file-local prototype declares it pointer-typed. The
        decl (an integer scalar) becomes `void *` and redundant pointer
        casts are dropped. Fire only when every occurrence is safe.
    """
    fname, ptext, ps, pe, popen = find_definition(masked)
    if fname is None:
        return [], []
    params = parse_params(ptext, ps)
    protos = self_proto_segments(masked, fname, popen)
    ptrpos = extern_ptr_map(masked)
    # sync this file's extern prototypes of DECOMPILED callees to the real
    # definition signatures (the forward decls the caller's own guesses made
    # stale: `s32 fn_801286D0(s32, ...)` where the def derefs a QB block)
    callee_fixes = sync_callee_decls(text, masked, fname)
    entries = []
    proto_fixes = list(callee_fixes)
    for idx, (decl, name, dstart, nstart) in enumerate(params):
        if decl is None or DECL_UNK_RE.search(decl):
            continue  # already struct-typed / unparseable (idempotency)
        if re.search(r'^\s*#define\s+%s\b' % re.escape(name),
                     text, re.M):
            continue  # the name is macro-redefined later in the file
        if '/*' in text[dstart:nstart]:
            continue  # inline comment in the decl span — leave alone
        body = masked[:ps - 2] + ' ' * (pe - ps + 3) + masked[pe + 1:]
        if SHADOW_RE.search(body.replace('NAME', name)):
            continue  # body re-declares the name
        # occurrences must lie INSIDE the function body — names in other
        # functions' prototype declarations (`extern s32 fn_X(s32 arg0);`)
        # are not uses of this param and must never count as evidence or
        # drop sites (they once let the void rule fire on UNUSED params and
        # mangled the extern line itself)
        body_open = masked.find('{', pe + 1)
        if body_open < 0:
            continue
        occs = [u for u in re.finditer(r'\b%s\b' % re.escape(name), body)
                if u.start() > body_open]
        if not occs:
            continue
        good = collections.Counter()
        defcls = collections.Counter()
        ptr_ev = 0
        all_safe = True
        fixes = []
        sigs = def_sigs()
        for u in occs:
            pre = body[max(0, u.start() - 96):u.start()]
            post = body[u.end():u.end() + 12]
            safe, gt, pcast = occ_class(pre, post)
            if gt is not None:
                good[gt] += 1
            elif pcast:
                ptr_ev += 1
            elif safe:
                # bare use: passing NAME into a callee position. The callee's
                # DECOMPILED DEFINITION signature is the type truth — when it
                # says `Unk_X *` the param is that struct (the m2c drafts
                # declared these QB-block args as s32/void* because they only
                # FORWARD them). Fall back to the file-local prototype guess
                # (still-asm callees) which yields at most a generic pointer.
                cname, cidx = call_arg_index(text, u.start())
                if cname is not None and cidx is not None:
                    dsig = sigs.get(cname)
                    if dsig is not None and cidx < len(dsig) and dsig[cidx]:
                        st = dsig[cidx]
                        mc = re.match(r'^(%s)\s*\*$' % ap.CLASS_INNER_CI, st)
                        if mc:
                            defcls[ap.canonical(mc.group(1))] += 1
                        elif st.endswith('*'):
                            ptr_ev += 1
                    elif ptrpos.get(cname, {}).get(cidx) is True:
                        ptr_ev += 1
            elif BYTE_PTR_DECL_RE.match(decl) and fixable_byte_arith(pre, post):
                # bare byte arithmetic on a void*/char* param: retyping to a
                # struct pointer would re-scale, so pin the byte semantics
                # with an explicit `(char *)` cast at this site.
                fixes.append((u.start(), u.end(), '(char *)%s' % name))
                continue
            if not safe:
                all_safe = False
                break
        if not all_safe:
            continue
        if good:
            # ---- struct rule: retype to the majority Unk_ type
            t = good.most_common(1)[0][0]
            newdecl = '%s *' % ap.display(t)
            drops = []
            for u in occs:
                raw_pre = text[max(0, u.start() - 96):u.start()]
                m = re.search(
                    r'\(\s*\(\s*%s\s*\*\s*\)\s*$' % ap.class_alt(t),
                    raw_pre)
                if not m:
                    continue
                pm = re.match(r'\s*\)', text[u.end():u.end() + 8])
                if not pm:
                    continue
                drops.append((u.start() - len(m.group(0)),
                              u.end() + pm.end()))
        elif defcls:
            # ---- definition-propagation rule: the param is only forwarded
            # into DECOMPILED callee positions typed `Unk_X *` — retype to
            # that class (drop redundant `(void *)` casts if any)
            t = defcls.most_common(1)[0][0]
            newdecl = '%s *' % ap.display(t)
            drops = []
            for u in occs:
                raw_pre = text[max(0, u.start() - 96):u.start()]
                m = PTRCAST_PRE.search(raw_pre)
                if not m:
                    continue
                pm = re.match(r'\s*\)', text[u.end():u.end() + 8])
                if not pm:
                    continue
                drops.append((u.start() - len(m.group(0)),
                              u.end() + pm.end()))
        elif ptr_ev and INT_SCALAR_RE.match(decl):
            # ---- void rule: only generic pointer evidence (no struct class
            # known yet) — the value is a forwarded pointer
            newdecl = 'void *'
            drops = []
            for u in occs:
                raw_pre = text[max(0, u.start() - 96):u.start()]
                m = PTRCAST_PRE.search(raw_pre)
                if not m:
                    continue
                pm = re.match(r'\s*\)', text[u.end():u.end() + 8])
                if not pm:
                    continue
                drops.append((u.start() - len(m.group(0)),
                              u.end() + pm.end()))
        else:
            continue
        # (char *) arith fixes only make sense under the struct-good rule; the
        # void/defcls rules (drops only) never retype an arithmetically-used
        # byte param, so any stray fixes are dropped with them.
        if fixes and good:
            entries.append((idx, name, dstart, nstart, newdecl, drops, fixes))
        else:
            entries.append((idx, name, dstart, nstart, newdecl, drops))
        # mirror into self-prototypes (arity must match the raw def segments)
        if not protos or any(len(p) != len(params) for p in protos):
            continue
        if idx >= len(protos[0]):
            continue
        for psegs in protos:
            a, b = psegs[idx]
            raw_seg = text[a:b]
            if '/*' in raw_seg or '(' in raw_seg or '[' in raw_seg:
                continue
            lead = raw_seg[:len(raw_seg) - len(raw_seg.lstrip(' \t'))]
            proto_fixes.append((a, b, lead + newdecl))
    return entries, proto_fixes


LOC_TYPE = (r'(?:register\s+|static\s+)*(?:s32|u32|s16|u16|s8|u8|f32|f64|'
            r'char|void|int|bool|size_t|Unk_[0-9A-Fa-f]+|\w+_t)')
LOC_DECL_RE = re.compile(
    r'^\s*((?:register\s+|static\s+)*(?:s32|u32|s16|u16|s8|u8|f32|f64|'
    r'char|void|int|bool|size_t|%s|\w+_t)'
    r'(?:\s*\*)*)\s*([A-Za-z_]\w*)(.*)$' % ap.CLASS_INNER_CI)


def top_level_statement_spans(masked, start):
    """Yield (stmt_start, stmt_end) of function-top statements from `start`
    (just inside the body brace). Statements split at ';' when the brace
    depth is 0; nested `{...}` blocks are consumed whole, so declarations
    inside them are invisible (function-top C89 decls only)."""
    n = len(masked)
    i = start
    while i < n:
        depth = 0
        st = i
        j = i
        while j < n:
            c = masked[j]
            if c == '(':
                j += 1
                d2 = 1
                while j < n and d2:
                    if masked[j] == '(':
                        d2 += 1
                    elif masked[j] == ')':
                        d2 -= 1
                    j += 1
                continue
            if c == '{':
                depth += 1
            elif c == '}':
                depth -= 1
                if depth < 0:
                    return  # end of the function body
            elif c == ';' and depth == 0:
                break
            j += 1
        yield st, j
        i = j + 1


def plan_locals(text, masked, param_names):
    """Retype function-top locals that only hold struct pointers.

    Returns entries as (idx=-1, name, decl_type_start, name_start, new_decl,
    drops). A local qualifies when its declaration is a single declarator of a
    plain scalar/pointer type (no volatile/const/arrays/fn-pointers/asm), it
    has >=1 `((Unk_X *)NAME)` use, and every OTHER occurrence is safe under
    the new pointer type (writes allowed — the write target never rescales).
    """
    fname, ptext, ps, pe, popen = find_definition(masked)
    if fname is None:
        return []
    body_open = masked.find('{', pe + 1)
    if body_open < 0:
        return []
    entries = []
    for st, en in top_level_statement_spans(masked, body_open + 1):
        seg = masked[st:en]
        if '__asm__' in seg or 'volatile' in seg or 'const' in seg:
            continue
        m = LOC_DECL_RE.match(seg)
        if not m:
            continue
        quals, name, rest = m.group(1), m.group(2), m.group(3)
        if DECL_UNK_RE.search(m.group(1)):
            continue  # already struct-typed (idempotency)
        if 'register' in quals:
            quals = 'register '
        else:
            quals = ''
        # single declarator only: no top-level comma or array suffix
        if ',' in rest or '[' in rest or '(' in rest:
            continue
        if name in param_names or name in ('argc', 'argv'):
            continue
        if re.search(r'^\s*#define\s+%s\b' % re.escape(name), text, re.M):
            continue
        type_start = st + m.start(1)
        name_start = st + m.start(2)
        if '/*' in text[type_start:name_start]:
            continue
        # occurrence scan over the body, decl statement blanked
        occ_text = masked[:st] + ' ' * (en - st) + masked[en:]
        occs = [u for u in re.finditer(r'\b%s\b' % re.escape(name), occ_text)
                if u.start() > body_open]
        if not occs:
            continue
        good = collections.Counter()
        all_safe = True
        for u in occs:
            safe, gt, _pcast = occ_class(
                occ_text[max(0, u.start() - 96):u.start()],
                occ_text[u.end():u.end() + 12],
                allow_assign=True)
            if gt is not None:
                good[gt] += 1
            if not safe:
                all_safe = False
                break
        if not all_safe or not good:
            continue
        t = good.most_common(1)[0][0]
        newdecl = quals + '%s *' % ap.display(t)
        drops = []
        for u in occs:
            raw_pre = text[max(0, u.start() - 96):u.start()]
            dm = re.search(r'\(\s*\(\s*%s\s*\*\s*\)\s*$' % re.escape(t),
                           raw_pre)
            if not dm:
                continue
            pm = re.match(r'\s*\)', text[u.end():u.end() + 8])
            if not pm:
                continue
            drops.append((u.start() - len(dm.group(0)), u.end() + pm.end()))
        entries.append((-1, name, type_start, name_start, newdecl, drops))
    return entries


STACK_TYPE = (r'(?:register\s+)*(?:s32|u32|s16|u16|s8|u8|f32|f64|char|short|'
              r'int|long|float|double|bool|size_t|__ps_t)')
STACK_DECL_RE = re.compile(
    r'^\s*(' + STACK_TYPE + r')\s+([A-Za-z_]\w*)(.*)$')
SV_CAST_PRE = re.compile(
    r'\(\s*\(\s*(' + ap.CLASS_CI + r')\s*\*\s*\)\s*&\s*$')


def plan_stackvals(text, masked, skip_names):
    """Retype stack-value locals (`u16 sp8;`) whose ADDRESS is cast to a
    struct (`((Unk_XXXX *)&sp8)->unk0xNN`) into actual struct locals
    (`Unk_XXXX sp8;`).

    These are the address-form (amp) bases whose declaration is still the
    m2c-inferred narrow scalar. Every occurrence must be address-based (the
    `((Unk_X *)&NAME)` cast, or plain `&NAME`) or a whole-value access of the
    ORIGINAL scalar width, which is rewritten to `*((T *)&NAME)` so it stays
    an exact same-slot access once the decl becomes the struct. Rewrites:
      decl        `u16 sp8;`  ->  `Unk_XXXX sp8;`
      cast+arrow  `((Unk_XXXX *)&sp8)->unkN`  ->  `sp8.unkN`
      cast value  `((Unk_XXXX *)&sp8)`        ->  `&sp8`
      bare value  `sp8`                       ->  `*((u16 *)&sp8)`
    Returns (repls, n_cands): repls are (start, end, text) spans (right-to-
    left), n_cands the retyped locals.
    """
    fname, ptext, ps, pe, popen = find_definition(masked)
    if fname is None:
        return [], 0
    body_open = masked.find('{', pe + 1)
    if body_open < 0:
        return [], 0
    repls = []
    n_cands = 0
    for st, en in top_level_statement_spans(masked, body_open + 1):
        seg = masked[st:en]
        if '__asm__' in seg or 'volatile' in seg or 'const' in seg:
            continue
        m = STACK_DECL_RE.match(seg)
        if not m:
            continue
        quals, typ, name, rest = (m.group(1).strip(), m.group(1).strip(),
                                  m.group(2), m.group(3))
        typ = typ.replace('register ', '')
        if DECL_UNK_RE.search(m.group(1)):
            continue  # already struct-typed (idempotency)
        if ',' in rest or '[' in rest or '(' in rest:
            continue  # multi-declarator / array / fn-ptr
        if name in skip_names:
            continue
        if re.search(r'^\s*#define\s+%s\b' % re.escape(name), text, re.M):
            continue
        # occurrence scan over the body, decl statement blanked
        occ_text = masked[:st] + ' ' * (en - st) + masked[en:]
        good = collections.Counter()
        occs = [u for u in re.finditer(r'\b%s\b' % re.escape(name), occ_text)
                if u.start() > body_open]
        if not occs:
            continue
        for u in occs:
            pre = occ_text[max(0, u.start() - 96):u.start()]
            gm = SV_CAST_PRE.search(pre.rstrip())
            if gm:
                good[ap.canonical(gm.group(1))] += 1
        if not good:
            continue
        c = good.most_common(1)[0][0]
        quals_pre = 'register ' if quals.startswith('register') else ''
        # decl span: [type start, name start)
        type_start = st + m.start(1)
        name_start = st + m.start(2)
        if '/*' in text[type_start:name_start]:
            continue
        repls.append((type_start, name_start, quals_pre + ap.display(c) + ' '))
        for u in occs:
            raw_pre = text[max(0, u.start() - 96):u.start()]
            gm = SV_CAST_PRE.search(raw_pre.rstrip())
            if gm and gm.group(1) == c:
                # drop the redundant address cast: ((C *)&NAME) -> &NAME
                cast_open = u.start() - len(gm.group(0))
                pm = re.match(r'\s*\)', text[u.end():u.end() + 8])
                if not pm:
                    continue
                close = u.end() + pm.end()
                if text[close:close + 2] == '->':
                    # ((C *)&NAME)->unkN  ==  NAME.unkN
                    repls.append((cast_open, close + 2, '%s.' % name))
                else:
                    repls.append((cast_open, close, '&%s' % name))
            elif gm:
                continue  # other struct view of the slot — leave the cast
            elif raw_pre.rstrip().endswith('&'):
                continue  # plain &NAME — fine as-is
            elif re.search(r'sizeof\s*$', raw_pre.rstrip()):
                continue
            else:
                # whole-value access of the original scalar: keep it an exact
                # same-slot access through the struct-typed local
                repls.append((u.start(), u.end(), '*((%s *)&%s)' % (typ, name)))
        n_cands += 1
    return repls, n_cands


def apply_plan(text, plan):
    """Rewrite decl swaps + cast drops + proto mirrors (right-to-left).
    `plan` is the plan_file 4-tuple (entries, proto_fixes, n_params,
    n_locals)."""
    entries, proto_fixes = plan[0], plan[1]
    repls = []
    for e in entries:
        idx, name, dstart, nstart, newdecl, drops = e[:6]
        raw_decl = text[dstart:nstart]
        lead = raw_decl[:len(raw_decl) - len(raw_decl.lstrip(' \t'))]
        repls.append((dstart, nstart, lead + newdecl))
        for a, b in drops:
            repls.append((a, b, name))
        if len(e) > 6:
            repls.extend(e[6])
    for a, b, new in proto_fixes:
        repls.append((a, b, new))
    out = text
    for a, b, new in sorted(repls, key=lambda r: -r[0]):
        out = out[:a] + new + out[b:]
    for a, b, new in sorted(plan[4], key=lambda r: -r[0]):
        out = out[:a] + new + out[b:]
    return out


def plan_file(text, masked):
    """Combine the param, local and stack-value retype plans.

    Returns (entries, proto_fixes, n_params, n_locals, sv_repls, n_sv)."""
    p_entries, proto_fixes = plan_params(text, masked)
    fname, ptext, ps, pe, popen = find_definition(masked)
    param_names = set()
    if fname is not None:
        param_names = {p[1] for p in parse_params(ptext, ps) if p[1]}
    l_entries = plan_locals(text, masked, param_names)
    chosen = {e[1] for e in p_entries} | {e[1] for e in l_entries}
    sv_repls, n_sv = plan_stackvals(text, masked, chosen)
    return (p_entries + l_entries, proto_fixes, len(p_entries),
            len(l_entries), sv_repls, n_sv)


def process_file(args):
    fp, = args
    m = ap.FN_RE.match(os.path.basename(fp))
    is_src = fp.startswith(os.path.join(ROOT, 'src', '')) and \
        not fp.startswith(os.path.join(ROOT, 'src', 'wip', ''))
    text = open(fp, encoding='utf-8', errors='replace').read()
    masked = ds.mask_comments_strings(text)
    plan = plan_file(text, masked)
    if not plan[0] and not plan[1] and not plan[4]:
        return None
    new_text = ap.ensure_include(apply_plan(text, plan))
    addr = int(m.group(1), 16) if m else None
    if is_src and m:
        if APPLY:
            sym_size = ap.SYM_SIZE.get(addr)
            if sym_size is None:
                status = 'reverted-no-size'
            elif ap.verify_src(addr, sym_size, new_text):
                status = 'src-verified'
            else:
                status = 'reverted-mismatch'
        else:
            status = 'src'
    else:
        if APPLY and addr is not None:
            if ap.verify_compiles(addr, text) and \
                    not ap.verify_compiles(addr, new_text):
                status = 'reverted-breaks-compile'
            else:
                status = 'wip'
        else:
            status = 'wip'
    n = sum(1 + len(e[5]) + (len(e[6]) if len(e) > 6 else 0)
            for e in plan[0]) + len(plan[1]) + len(plan[4])
    nl = plan[3]
    nsv = plan[5]
    if status.startswith('reverted'):
        return (fp, status, n, nl, nsv, text)
    return (fp, status, n, nl, nsv, new_text)


def main():
    files = sorted(glob.glob(os.path.join(ROOT, 'src', '*.c')) +
                   glob.glob(os.path.join(ROOT, 'src', 'wip', '*.c')))
    files = [f for f in files if ap.FN_RE.match(os.path.basename(f))]
    if PLAN_FILE:
        text = open(PLAN_FILE, encoding='utf-8', errors='replace').read()
        masked = ds.mask_comments_strings(text)
        entries, proto_fixes, n_params, n_locals, sv, n_sv = \
            plan_file(text, masked)
        print('%s: %d params + %d locals + %d stack-values to retype, '
              '%d proto mirrors, %d sv edits'
              % (PLAN_FILE, n_params, n_locals, n_sv, len(proto_fixes),
                 len(sv)))
        for e in entries:
            idx, name, dstart, nstart, newdecl, drops = e[:6]
            kind = 'param' if idx >= 0 else 'local'
            extra = (' + %d arith-fix(es)' % len(e[6])) if len(e) > 6 else ''
            print('  [%-5s] %-8s decl -> %-24s (%d cast sites dropped%s)'
                  % (kind, name, newdecl + name, len(drops), extra))
        for a, b, txt in sv:
            if ' *' not in txt and not txt.endswith('.'):
                print('  [stack] decl/use edit @ %d: %r' % (a, txt[:40]))
        return 0
    if LIMIT is not None:
        files = files[:LIMIT]
    print('scanning %d fn_*.c files (apply=%s jobs=%d)'
          % (len(files), APPLY, JOBS))
    args = [(fp,) for fp in files]
    if APPLY:
        ctx = mp.get_context('fork')
        with ctx.Pool(JOBS) as pool:
            results = [r for r in pool.imap_unordered(process_file, args)
                       if r is not None]
    else:
        results = []
        for a in args:
            r = process_file(a)
            if r is not None:
                results.append(r)
    stats = collections.Counter()
    total = 0
    n_locals = 0
    n_sv = 0
    for fp, status, n, nl, nsv, _txt in results:
        stats[status] += 1
        total += n
        n_locals += nl
        n_sv += nsv
    print('files with var retypes: %d   sites (decl+cast drops+mirrors+sv): %d'
          '   locals retyped: %d   stack-values retyped: %d'
          % (len(results), total, n_locals, n_sv))
    for k in sorted(stats):
        print('  %-18s %d' % (k, stats[k]))
    if APPLY:
        for fp, status, n, nl, nsv, txt in results:
            if not status.startswith('reverted'):
                open(fp, 'w').write(txt)
    return 0


if __name__ == '__main__':
    sys.exit(main())
