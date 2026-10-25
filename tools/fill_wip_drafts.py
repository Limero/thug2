#!/usr/bin/env python3
"""Fill stub WIP drafts with m2c-generated C (decomp.me's decompiler).

Every src/wip/fn_XXXXXXXX.c with family=stub gets a real best-guess C body
produced by m2c (--target ppc-mwcc-c) from the DOL disassembly, then
post-processed into standalone C that compiles with ngccc:

  M2C_ERROR(/* ... */)        -> 0          (unknown insns; disasm stays in
                                             the header comment)
  (? (*)())0xADDR()           -> ((void (*)(void))0xADDR)()
  arg->unkN                   -> *(s32 *)((char *)arg + 0xN)
  arg->unkN[i]                -> ((s32 *)((char *)arg + 0xN))[i]
  &arg->unkN                  -> (s32 *)((char *)arg + 0xN)
  M2C_CARRY                   -> static s32 shim (added when used)

Field types are inferred from m2c's casts: a field on a line containing
(f32)/(f64)/(u8)/(s16)/... is that type, otherwise s32. Branch targets inside
the function get .LXXXXXXXX labels; calls to other functions get their real
name (fn_XXXXXXXX or the SDK name, e.g. PPCMfhid2) so the draft reads well.

The result is family=m2c: test_wip_drafts.py compiles+sweeps it, and a
parallel agent can iterate on it directly. Functions where m2c produces no
real body (FPR-frame quirks, Paired-Single ops, cross-function branches)
keep family=stub untouched. Idempotent: only family=stub files are touched,
and gen_wip_drafts.py skips existing files, so re-running either is safe.

Usage:
  tools/venv/bin/python tools/fill_wip_drafts.py [--limit N] [--addr 0x...]
                                                 [--max-size N] [--dry-run]
"""
import contextlib
import glob
import io
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl
from m2c import main as mm
from qb_hash import subst_qb_constants

ROOT = gl.ROOT
WIP_DIR = f"{ROOT}/src/wip"
REG = f"{ROOT}/WIP.md"

RE_SIZE = re.compile(r"size=(\d+)B")

# every function address in the DOL (from the objdiff report) — used to name
# calls (bl 0xADDR -> bl fn_XXXXXXXX) so m2c emits readable named calls
_fninfo = {}
_rep = json.load(open(f"{ROOT}/build/G2TE52/report.json"))
for _u in _rep.get("units", []):
    for _fn in _u.get("functions", []):
        _fninfo[int(_fn["metadata"]["virtual_address"])] = int(_fn["size"])
FNINFO_SET = set(_fninfo)

# m2c cast types we can infer field types from
CAST_TYPES = {
    "f32": "f32", "f64": "f64",
    "s8": "s8", "s16": "s16", "s32": "s32", "s64": "s64",
    "u8": "u8", "u16": "u16", "u32": "u32", "u64": "u64",
}
RE_CAST = re.compile(r"\((%s)\)" % "|".join(CAST_TYPES))
RE_FIELD = re.compile(r"(\w+)(->|\.)(unk-?[0-9A-Fa-f]+)")


def disasm_with_labels(addr, size):
    """Return (asm_lines, call_names) for the function at addr."""
    ins = gl.insns_at(addr, count=size // 4 + 2)
    targets = set()
    calls = {}
    for i, x in enumerate(ins):
        if i * 4 >= size:
            break
        if x.mnemonic.startswith("b") and x.mnemonic != "blr":
            m = re.search(r"(0x[0-9a-fA-F]+)$", x.op_str)
            if not m:
                continue
            t = int(m.group(1), 16)
            if addr <= t < addr + size:
                targets.add(t)
            elif x.mnemonic == "bl" and t in FNINFO_SET:
                calls[t] = gl.fn_name(t)
    lines = [f"glabel {gl.fn_name(addr)}"]
    for i, x in enumerate(ins):
        if i * 4 >= size:
            break
        a = addr + i * 4
        if a in targets:
            lines.append(f".L{a:08X}:")
        op = x.op_str
        if x.mnemonic == "bl":
            m = re.search(r"(0x[0-9a-fA-F]+)$", op)
            if m:
                t = int(m.group(1), 16)
                if t in targets:
                    op = op[:m.start()] + f".L{t:08X}"
                elif t in calls:
                    op = op[:m.start()] + calls[t]
        else:
            for t in sorted(targets):
                op = re.sub(rf"0x{t:x}$", f".L{t:08X}", op)
        lines.append(f"    {x.mnemonic} {op}".rstrip())
    return lines, calls


def run_m2c(asm_text):
    """Run m2c on asm text; return the C it prints (or None on error)."""
    path = "/tmp/fill_m2c.s"
    with open(path, "w") as f:
        f.write(asm_text)
    buf = io.StringIO()
    err = io.StringIO()
    try:
        opts = mm.parse_flags(["--target", "ppc-mwcc-c", path])
        with contextlib.redirect_stdout(buf), contextlib.redirect_stderr(err):
            mm.run(opts)
    except Exception as e:  # noqa: BLE001 - m2c can throw on weird asm
        sys.stderr.write(f"m2c raised {type(e).__name__}: {e}\n")
        return None
    out = buf.getvalue()
    return out if out.strip() else None


def field_off(name):
    """Offset of an m2c field name ('unk3C', 'unk0', 'unk-4')."""
    n = name[3:]
    if n.startswith("-"):
        return -int(n[1:], 16)
    return int(n, 16)


def off_str(off):
    return f"- 0x{-off:X}" if off < 0 else f"+ 0x{off:X}"


def fix_ptr_index_first(text):
    """*((idx * N) + ptr) -> *((s32 *)((char *)ptr + (idx * N)))

    m2c's model: the index is multiplied by the element size (bytes) before
    being added to a pointer, so the whole thing is byte arithmetic. Rewriting
    as char*-based byte arithmetic preserves the byte offsets exactly (a
    divide-by-4 element rewrite would be wrong for non-multiple-of-4 strides
    like 0xA). The index can be a bare identifier ("(arg1 * 4)"), a hex
    multiplier ("(arg1 * 0xA)"), or an already-rewritten deref
    ("(*((s32 *)var_r30) * 0xC)").
    """
    res = []
    i = 0
    while True:
        m = re.search(r"\*\(\((.+?)\s*\*\s*(0x[0-9A-Fa-f]+|\d+)\)\s*\+\s*", text[i:])
        if not m:
            break
        start = i + m.start()
        idx, mult = m.group(1), int(m.group(2), 0)
        # find the matching ')' of the '*((...' outer group: we are inside it
        # (depth 1) at the position right after the '+'
        j = start + len(m.group(0))
        depth = 1
        k = j
        while k < len(text):
            if text[k] == "(":
                depth += 1
            elif text[k] == ")":
                depth -= 1
                if depth == 0:
                    break
            k += 1
        ptr_expr = text[j:k]
        res.append(text[i:start] + f"*((s32 *)((char *){ptr_expr} + ({idx} * {mult})))")
        i = k + 1
    res.append(text[i:])
    return "".join(res)


def fix_ptr_literal_deref(text):
    """*(*(s32 *)0xADDR + offs) -> *(s32 *)((char *)*(s32 *)0xADDR + offs)

    m2c treats a global pointer (read from a fixed address) as a byte base and
    adds raw offsets; the deref must cast it through char* to keep the offsets
    byte-accurate.
    """
    res = []
    i = 0
    while True:
        m = re.search(r"\*\(\*\(s32 \*\)0x[0-9A-Fa-f]+", text[i:])
        if not m:
            break
        start = i + m.start()
        depth = 0
        j = start + 1
        while j < len(text):
            if text[j] == "(":
                depth += 1
            elif text[j] == ")":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        # start+1 is the '(' of the outer deref group and j its matching ')':
        # take the inner content (start+2:j) and re-wrap it in our own parens
        inner = text[start + 2:j]
        res.append(text[i:start] + f"*(s32 *)((char *){inner})")
        i = j + 1
    res.append(text[i:])
    return "".join(res)


def postprocess(out):
    """Turn raw m2c output into standalone C that compiles with ngccc."""
    # strip any /* block comments */ (failure notes, inline remarks)
    out = re.sub(r"/\*.*?\*/", "", out, flags=re.S)
    # m2c prints warnings ("Warning: missing blr...") on stdout mixed with the C
    out = re.sub(r"(?m)^Warning:.*$", "", out)
    # m2c treats bl to an in-function label as a call: it emits a prototype
    # "s32 .L80042180(s32);" and calls ".L80042180(...)". The label address is
    # a real function (often this fn itself, sometimes the next one) — rename
    # to fn_XXXXXXXX so the existing fn_ prototype-strip + implicit decl work.
    out = re.sub(r"(?m)^\s*[^;{}]*\.L[0-9A-Fa-f]{8}\s*\([^;{}]*\)\s*;\s*$", "", out)
    out = re.sub(r"(?m)^\s*glabel\s*\.L[0-9A-Fa-f]{8}\s*$", "", out)
    out = re.sub(r"(?m)^\s*\.L[0-9A-Fa-f]{8}:\s*$", "", out)
    out = re.sub(r"\.L([0-9A-Fa-f]{8})\s*\(", r"fn_\1(", out)
    # m2c emits "? fn_X(?, s32);" prototype lines for named calls with unknown
    # signatures — strip them; the calls themselves compile via implicit decl
    out = re.sub(r"(?m)^\s*\?\s+[A-Za-z_][A-Za-z0-9_]*\(.*\);\s*$", "", out)
    # m2c also emits guessed full prototypes ("void *fn_X(s32);") whose arg
    # counts can conflict with the calls — strip them too (implicit decl is fine)
    out = re.sub(r"(?m)^\s*(?:void|s8|s16|s32|s64|u8|u16|u32|u64|f32|f64|char|short|int|long|float|double)\b(?!\s*[A-Za-z_]\w*\s*=)[^;{}]*\b(fn_[0-9A-Fa-f]{8}|PPCM\w+)\s*\([^;{}]*\)\s*;\s*$", "", out)
    # M2C_ERROR(/* ... */) leftover -> 0 (statement- or expression-safe)
    out = re.sub(r"M2C_ERROR\(\)", "0", out)
    # unnamed raw-address calls
    out = re.sub(r"\(\? \(\*\)\(\)\)0x([0-9A-Fa-f]+)\(\)",
                 r"((void (*)(void))0x\1)()", out)
    # any leftover unknown-type marker (? is m2c's unknown-type placeholder;
    # it appears inside prototypes like "f32 fn_X(?, f32);" and decls like
    # "? sp8;" — replace standalone ? tokens with s32)
    out = re.sub(r"(?<![A-Za-z0-9_])[?](?![A-Za-z0-9_])", "s32", out)
    # m2c's bitwise-reinterpret cast: (bitwise s32) -> (s32), incl. fn-ptr
    # types: (bitwise s32 (*)(s32)) -> (s32 (*)(s32))
    out = re.sub(r"\(bitwise\s+((?:[^()]|\([^()]*\))*)\)", r"(\1)", out)
    # casted-address call needs parens: (s32 (*)(void *, s32))0xADDR( -> ((... )0xADDR)(
    out = re.sub(r"(\([A-Za-z0-9_]+ \(\*\)\([^;]*?\)\))0x([0-9A-Fa-f]+)\(",
                 r"(\1 0x\2)(", out)
    # deref of void* breaks arithmetic: *(void *)X -> *(s32 *)X
    out = re.sub(r"\*\(void \*\)", "*(s32 *)", out)
    # m2c emits a (void *) cast applied to a deref (lvalue or rvalue):
    # "(void *)*(s32 *)X = v" / "= (void *)*(s32 *)X" / "(s32) ((void *)*(..) & M)"
    # — the cast is never semantically needed, drop it.
    out = re.sub(r"\(void \*\)(?=\s*\*\()", "", out)
    # deref of void* pointer arithmetic: *((void *)X + N) -> *((s32 *)X + N)
    out = re.sub(r"\*\(\(void \*\)", "*((s32 *)", out)
    # unary minus before a deref-lvalue (m2c misparsed a negative store
    # offset): -*(T *)(...) = v -> *(T *)(...) = v
    out = re.sub(r"-(\*\([^;]*?\))(?=\s*=\s*)", r"\1", out)
    # indirect call through a pointer-to-pointer-to-function constant:
    # *(s32 (**)(s32))0xADDR(args) must call the DEREF'd pointer:
    # (*(s32 (**)(s32))0xADDR)(args)
    out = re.sub(r"\*\(([A-Za-z0-9_]+ \(\*\*\)\([^;]*?\))\)0x([0-9A-Fa-f]+)\(",
                 r"(*(\1)0x\2)(", out)
    # TYPE_WORDS: a '*' immediately preceded (as the last token) by one of
    # these is a pointer-DECLARATION star ("s32 *var_r30;", "void *fn_X(...) {")
    # and must NOT be treated as a deref.
    TYPE_WORDS = {
        "s8", "s16", "s32", "s64", "u8", "u16", "u32", "u64",
        "f32", "f64", "void", "char", "short", "int", "long", "float",
        "double", "struct", "union", "const", "static", "unsigned", "signed",
    }

    def _decl_star(m):
        """Return True if the '*' at m.start() is a pointer-declaration star."""
        pre = out[:m.start()].rstrip()
        tok = re.search(r"([A-Za-z_]\w*)$", pre)
        return bool(tok and tok.group(1) in TYPE_WORDS)

    # deref of a call result (m2c typed a pointer-returning fn as int):
    # *fn_X(...) -> *((s32 *)fn_X(...)). The call args may contain nested
    # parens (casts), so a lazy [^;]*? would stop at the FIRST ')' inside the
    # args and truncate the call — scan to the balanced close paren instead.
    def fix_call_deref(text):
        res = []
        i = 0
        while True:
            m = re.search(r"(?<![A-Za-z0-9_*])\*((?:fn_[0-9A-Fa-f]{8}|PPCM\w+)\s*)\(", text[i:])
            if not m:
                break
            # _decl_star(m) indexes the FULL out with m.start(), which is
            # RELATIVE to the text[i:] slice — wrong once i > 0. Check the
            # absolute position text[:start] instead: a '*' that ends a
            # pointer-DECLARATION ("s32 *fn_X(") must not be deref-rewritten.
            start = i + m.start()
            pre = text[:start].rstrip()
            tok = re.search(r"([A-Za-z_]\w*)$", pre)
            if tok and tok.group(1) in TYPE_WORDS:
                res.append(text[i:i + m.end()])
                i = i + m.end()
                continue
            # absolute index of the call's '(' — i + m.end() - 1 (m.end() is
            # relative to the text[i:] slice; start + m.end() - 1 would be off
            # by m.start(), landing mid-args for any match after the first)
            open_idx = i + m.end() - 1  # the call's '('
            depth = 0
            j = open_idx
            while j < len(text):
                if text[j] == "(":
                    depth += 1
                elif text[j] == ")":
                    depth -= 1
                    if depth == 0:
                        break
                j += 1
            call = text[start + 1:j + 1]
            res.append(text[i:start] + f"*((s32 *){call})")
            i = j + 1
        res.append(text[i:])
        return "".join(res)

    out = fix_call_deref(out)

    # deref of a call result (m2c typed a pointer-returning fn as int):
    # *fn_X(...) -> *((s32 *)fn_X(...))
    out = re.sub(r"(?<![A-Za-z0-9_*])\*((?:fn_[0-9A-Fa-f]{8}|PPCM\w+)\s*\([^;]*?\))",
                 lambda m: m.group(0) if _decl_star(m) else f"*((s32 *){m.group(1)})", out)
    # deref of a scalar register var (m2c typed a pointer var as int):
    # *temp_r31 -> *((s32 *)temp_r31)  (not when call/array/double-deref,
    # when a field/offset follows (handled elsewhere), or a declaration star)
    # The (?![A-Za-z0-9_]) after the name forces the greedy identifier to be
    # maximal: without it, a name like temp_r3 followed by '->' makes the
    # negative lookahead fail and the regex BACKTRACKS the identifier down to
    # temp_r (next char '3' is not forbidden), splitting "temp_r3->unk30" into
    # "temp_r)*(s32 *)((char *)3 + 0x30" garbage. Same for *temp_r10[4] and
    # *temp_r9().
    out = re.sub(r"(?<![A-Za-z0-9_*])\*((?:temp_|var_)[A-Za-z0-9_]+)(?![A-Za-z0-9_])(?!\s*[\[(]|\*|[.>]|-)",
                 lambda m: m.group(0) if _decl_star(m) else f"*((s32 *){m.group(1)})", out)
    # m2c stack-slot base indexing: &sp8[0] -> &sp8
    out = re.sub(r"&((?:sp|unksp)[0-9A-Fa-f]+)\[0\]", r"&\1", out)
    # m2c byte arithmetic where the pointer operand comes LAST:
    # *((idx * N) + ptr) -> *((s32 *)ptr + (idx * N / 4))
    out = fix_ptr_index_first(out)
    # deref of a global-pointer + byte offsets: *(*(s32 *)0xN + offs)
    out = fix_ptr_literal_deref(out)
    # m2c index-first with an int-typed pointer var + byte offset expr:
    # *((s32 *)A + (B + 0xN)) -> *((s32 *)((char *)A + (s32)(B + 0xN)))
    out = re.sub(r"\*\(\(s32 \*\)(\w+) \+ \(((?:[^()]|\([^()]*\))+)\)\)",
                 r"*((s32 *)((char *)\1 + (s32)(\2)))", out)
    # pointer + &stackvar (m2c indexing quirk): + &sp8 -> + (s32)&sp8
    out = re.sub(r"([+-])\s*&(sp[0-9A-Fa-f]+)", r"\1 (s32)&\2", out)
    out = re.sub(r"([+-])\s*&(unksp[0-9A-Fa-f]+)", r"\1 (s32)&\2", out)

    # m2c pointer-to-pointer deref typed as single pointer:
    # **(s32 *)X -> **(s32 **)X  (m2c emits "**(s32 *)(...)" when the target
    # is a pointer-to-pointer; the single-star cast makes the second deref
    # "invalid type argument of unary *")
    out = re.sub(r"\*\*\((s8|s16|s32|s64|u8|u16|u32|u64|f32|f64) \*\)", r"**(\1 **)", out)

    # ---- m2c '->unkN' on a cast-deref base (the base expr is a byte address
    # of a struct, the member offset is in the name): *(s32 *)(X)->unkN
    # -> *((s32 *)((char *)X + 0xN)). Balanced-paren scan; must run BEFORE
    # fix_paren_field (whose backward scan would treat the cast-deref ')' as a
    # field paren and produce "*(s32 *)(s32 *)(...)" garbage).
    def fix_deref_arrow(text):
        res = []
        i = 0
        while True:
            m = re.search(r"\*\((?:s8|s16|s32|s64|u8|u16|u32|u64|f32|f64) \*\)\(", text[i:])
            if not m:
                break
            start = i + m.start()
            cast = m.group(0)[2:]  # "s32 *)("
            typ = cast.split("*")[0].strip()
            open_idx = start + len(m.group(0)) - 1  # the '(' after '*(s32 *)'
            depth = 0
            j = open_idx
            while j < len(text):
                if text[j] == "(":
                    depth += 1
                elif text[j] == ")":
                    depth -= 1
                    if depth == 0:
                        break
                j += 1
            fm = re.match(r"->(unk-?[0-9A-Fa-f]+)", text[j + 1:])
            if not fm:
                res.append(text[i:j + 1])
                i = j + 1
                continue
            inner = text[open_idx + 1:j]
            off = field_off(fm.group(1))
            repl = f"*(({typ} *)((char *){inner} {off_str(off)}))"
            res.append(text[i:start] + repl)
            i = j + 1 + len(fm.group(0))
        res.append(text[i:])
        return "".join(res)

    # call through a cast-deref base: *(s32 *)(X)(args) — m2c read the fn
    # pointer then calls it: ((s32 (*)())*(s32 *)(X))(args).
    def fix_called_obj(text):
        res = []
        i = 0
        while True:
            m = re.search(r"\*\((?:s8|s16|s32|s64|u8|u16|u32|u64|f32|f64) \*\)\(", text[i:])
            if not m:
                break
            start = i + m.start()
            cast = m.group(0)[2:]
            typ = cast.split("*")[0].strip()
            open_idx = start + len(m.group(0)) - 1
            depth = 0
            j = open_idx
            while j < len(text):
                if text[j] == "(":
                    depth += 1
                elif text[j] == ")":
                    depth -= 1
                    if depth == 0:
                        break
                j += 1
            if j + 1 >= len(text) or text[j + 1] != "(":
                res.append(text[i:j + 1])
                i = j + 1
                continue
            call_open = j + 1
            depth = 0
            k = call_open
            while k < len(text):
                if text[k] == "(":
                    depth += 1
                elif text[k] == ")":
                    depth -= 1
                    if depth == 0:
                        break
                k += 1
            inner = text[open_idx + 1:j]
            args = text[call_open + 1:k]
            res.append(text[i:start] + f"((s32 (*)())*(({typ} *){inner}))({args})")
            i = k + 1
        res.append(text[i:])
        return "".join(res)

    # m2c emits old-style fn-ptr calls ((s32 (*)())*...) which make ngccc emit
    # a spurious "crclr cr1eq" before the indirect call (want never has it).
    # Type the fn-ptr with a real prototype inferred from the call args
    # (integer literals -> s32, everything else -> void *), e.g.
    #   ((s32 (*)())*(s32 *)((char *)temp_r9 + (s32)0xC))(x, 3, y);
    #   -> ((s32 (*)(void *, s32, void *))*(s32 *)((char *)temp_r9 + (s32)0xC))(x, 3, y);
    # Empirically kills the crclr; on simple functions this flips NEARs to
    # EXACT (80010AC0 52->96%, 8005626C 59->94% then s16 fix -> 100%).
    def fix_fptr_proto(text):
        # old-style fn-ptr call -> prototyped. Runs at the END of postprocess:
        # the field rules above rewrite m2c's arrow-form calls (X->unkC(args))
        # into the ((s32 (*)())*(s32 *)((char *)X + (s32)0xC))(args) form this
        # matches, so it must see the already-rewritten text (M4.63 lesson).
        # M4.94b: also collect DECLARED float-typed locals/params (f32 x;) so
        # args passed as plain locals named temp_rN (not temp_fN) get typed
        # f32 — otherwise the inferred prototype says void * for a float arg
        # and GCC errors "incompatible type for argument N" (80034850 et al.).
        declared_f32 = set()
        for dm in re.finditer(
                r"\b(?:const\s+)?(f32|f64)\s+(?!\*)([A-Za-z_]\w*)", text):
            declared_f32.add(dm.group(2))
        fm2 = re.search(r"\b(?:void|s8|s16|s32|s64|u8|u16|u32|u64|f32|f64)\s+[A-Za-z_]\w*\(([^)]*)\)\s*\{", text)
        if fm2:
            for pm in re.finditer(r"((?:f32|f64)\s+[A-Za-z_]\w+|[A-Za-z_]\w+)\s*(?:,|$)", fm2.group(1)):
                seg = pm.group(1).strip()
                if re.match(r"(?:f32|f64)\s+", seg):
                    declared_f32.add(seg.split()[1])
        while True:
            m = re.search(
                r"\(\(s32 \(\*\)\(\)\)\*\(s32 \*\)\(\s*\(char \*\)(\w+) \+ \(s32\)0x[0-9A-Fa-f]+\)\)\s*\(",
                text)
            if not m:
                return text
            # the call's '(' opens right after the fn-ptr deref ')'; scan to
            # its BALANCED close — m2c chains many calls/statements on one
            # line with comma operators, so a lazy/greedy [^;]* would swallow
            # the rest of the statement into the "args" (M4.94b lesson).
            open_idx = m.end() - 1
            depth = 0
            j = open_idx
            while j < len(text):
                if text[j] == "(":
                    depth += 1
                elif text[j] == ")":
                    depth -= 1
                    if depth == 0:
                        break
                j += 1
            if j >= len(text):
                # unbalanced: the matched '(' was not a call (e.g. a cast
                # paren) or the text is truncated — bail out unmodified
                # instead of scanning to EOF and fabricating a wrong proto
                return text
            inner = text[open_idx + 1:j]
            args = []
            depth = 0
            cur = ""
            for ch in inner:
                if ch == "(":
                    depth += 1
                elif ch == ")":
                    depth -= 1
                if ch == "," and depth == 0:
                    args.append(cur.strip())
                    cur = ""
                else:
                    cur += ch
            args.append(cur.strip())
            args = [a for a in args if a]
            if not args:
                proto = "((s32 (*)(void))"
            else:
                argtypes = []
                for a in args:
                    if re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)", a):
                        argtypes.append("s32")
                    elif re.search(r"\b(?:temp_f|var_f)\d+|farg\d+|\(f32\)|\(f64\)|\.\d+[fF]", a):
                        # M4.94: float args must become f32, not void * — the
                        # old all-void* typing made m2c fn-ptr calls with float
                        # args fail to compile ("incompatible type for arg N").
                        argtypes.append("f32")
                    elif re.fullmatch(r"[A-Za-z_]\w*", a) and a in declared_f32:
                        # M4.94b: a plain local/param declared f32/f64 above
                        argtypes.append("f32")
                    else:
                        argtypes.append("void *")
                proto = "((s32 (*)(" + ", ".join(argtypes) + "))"
            if proto == "((s32 (*)())":
                return text  # no-op would spin forever
            # M4.94b: replace the MATCHED occurrence, not the first in the
            # text — with multiple unprototyped calls of different arg counts,
            # .replace(..., 1) hit the wrong one and gave a call a prototype
            # whose param count mismatched its own args ("too few arguments").
            start = m.start()
            text = text[:start] + proto + text[start + len("((s32 (*)())"):]
        return text

    # --- field handling (m2c emits struct-style access on raw pointers) ---
    # chained access: X->unkA->unkB -> *(s32 *)(*(s32 *)((char *)X + A) + B)
    def collapse_chain(m):
        head = m.group(1)
        offs = [field_off(m.group(2))] + [field_off(x) for x in
                                          re.findall(r"->(unk-?[0-9A-Fa-f]+)", m.group(3))]
        expr = f"((char *){head})"
        for i in range(len(offs) - 1):
            expr = f"*(s32 *)((char *){expr} {off_str(offs[i])})"
        return f"*(s32 *)({expr} {off_str(offs[-1])})"

    out = re.sub(r"(\w+)->(unk-?[0-9A-Fa-f]+)((?:->unk-?[0-9A-Fa-f]+)+)", collapse_chain, out)

    # call through a field (function-pointer member): X->unkN(...) / X.unkN(...)
    out = re.sub(r"(\w+)(->|\.)(unk-?[0-9A-Fa-f]+)\(",
                 lambda m: f"((s32 (*)())*(s32 *)((char *){('&' if m.group(2) == '.' else '')}{m.group(1)} {off_str(field_off(m.group(3)))}))(",
                 out)
    # call through a temp/var pointer: temp_r3(args...)
    out = re.sub(r"\b(temp_[A-Za-z0-9_]+|var_[A-Za-z0-9_]+)\(",
                 lambda m: f"((s32 (*)()){m.group(1)})(", out)
    # deref of integer arithmetic (m2c treats s32 args as pointers):
    # *(arg0 + 8) -> *((s32 *)(arg0 + 8));  **(p + n) -> **((s32 **)(p + n))
    def fix_int_deref(text):
        res = []
        i = 0
        while True:
            m = re.search(r"\*{1,2}\(([A-Za-z_][A-Za-z0-9_]*)\s*[+-]", text[i:])
            if not m:
                break
            start = i + m.start()
            stars = len(m.group(0)) - len(m.group(0).lstrip("*"))
            open_idx = start + stars
            depth = 0
            j = open_idx
            while j < len(text):
                if text[j] == "(":
                    depth += 1
                elif text[j] == ")":
                    depth -= 1
                    if depth == 0:
                        break
                j += 1
            inner = text[open_idx + 1:j]
            res.append(text[i:start] + (f"*((s32 *){inner})" if stars == 1 else f"**((s32 **){inner})"))
            i = j + 1
        res.append(text[i:])
        return "".join(res)

    out = fix_int_deref(out)

    # fix_int_deref turned "*(X + (ptr + 0xN))" into "*((s32 *)X + (ptr + 0xN))"
    # with X still a raw byte index and ptr a pointer var — the s32* + (ptr+0xN)
    # sum is invalid C. Split into byte arithmetic on the pointer var:
    # *((s32 *)X + (ptr + 0xN)) -> *((s32 *)((char *)ptr + (s32)0xN + (s32)X))
    out = re.sub(r"\*\(\(s32 \*\)(\w+) \+ \((\w+) \+ (0x[0-9A-Fa-f]+)\)\)",
                 r"*((s32 *)((char *)\2 + (s32)\3 + (s32)\1))", out)

    # member access on a parenthesized expression: (expr)->unkN
    # -> *(s32 *)((s32 *)(expr) + 0xN)  (balanced-paren scan)
    #
    # Rewrites ONE match per call. The outer for-loop re-runs this on the
    # updated text, so a SECOND ->unkN on the same line is scanned against the
    # ALREADY-REWRITTEN prefix. (The old while-loop kept scanning the original
    # text after the first rewrite: the backward scan then walked over the
    # pre-rewrite form, misaligning base offsets and producing
    # "...)*(s32 *)(..." garbage for lines with two ->unkN fields.)
    def fix_paren_field(text):
        m = re.search(r"\)->(unk-?[0-9A-Fa-f]+)", text)
        if not m:
            return text
        j = m.start()  # index of the ')' right before ->unkN
        depth = 0
        k = j
        while k >= 0:
            if text[k] == ")":
                depth += 1
            elif text[k] == "(":
                depth -= 1
                if depth == 0:
                    break
            k -= 1
        # if the balancing '(' is immediately preceded by an identifier,
        # the field is on a CALL result: fn_X(args)->unkN. Keep the whole
        # call — identifier, its '(' ... and its closing ')' at j — as the
        # base expression. (The old code dropped the '(' which produced
        # "fn_X*(s32 *)(..." and broke the call.) For a plain parenthesized
        # expr, (expr)->unkN, both parens are re-added by the rewrite.
        base = k
        if k > 0 and (text[k - 1].isalnum() or text[k - 1] == "_"):
            e = k - 1
            while e >= 0 and (text[e].isalnum() or text[e] == "_"):
                e -= 1
            base = e + 1
            expr = text[base:j + 1]
        else:
            expr = text[base + 1:j]
        off = field_off(m.group(1))
        return (text[:base] + f"*(s32 *)((s32 *)({expr}) {off_str(off)})"
                + text[j + len(m.group(0)):])

    # run fix_paren_field repeatedly: a chained "(expr)->unkA->unkB" gets one
    # link rewritten per pass (the i-advancement skips the rest of the chain).
    # No fixed cap: some bodies have dozens of ->unkN fields, and each pass
    # fixes one; stop when a full pass changes nothing.
    for _ in range(200):
        new = fix_paren_field(out)
        if new == out:
            break
        out = new

    # infer field types: a field on a line carrying a float/small cast is that
    # type; otherwise default to s32.
    types = {}
    for line in out.splitlines():
        casts = [m for m in RE_CAST.finditer(line)]
        for fm in RE_FIELD.finditer(line):
            key = (fm.group(1), fm.group(3))
            if key in types:
                continue
            if casts:
                types[key] = CAST_TYPES[casts[0].group(1)]
            else:
                types[key] = "s32"

    def ftype(m):
        return types.get((m.group(1), m.group(3)), "s32")

    # 0. deref of pointer-valued field: *arg->unkN -> **(s32 **)((char *)arg + N)
    #    (m2c emits the unary * with no space; binary multiply keeps spaces)
    out = re.sub(r"\*(\w+)(->|\.)(unk-?[0-9A-Fa-f]+)(?!\s*\[)",
                 lambda m: f"**(s32 **)((char *){('&' if m.group(2) == '.' else '')}{m.group(1)} {off_str(field_off(m.group(3)))})",
                 out)
    # 1. address-of: &arg->unkN -> (T *)((char *)arg + N)
    out = re.sub(r"&(\w+)(->|\.)(unk-?[0-9A-Fa-f]+)",
                 lambda m: f"({ftype(m)} *)((char *){('&' if m.group(2) == '.' else '')}{m.group(1)} {off_str(field_off(m.group(3)))})",
                 out)
    # 2. array: arg->unkN[i] -> ((T *)((char *)arg + N))[i]
    out = re.sub(r"(\w+)(->|\.)(unk-?[0-9A-Fa-f]+)\[",
                 lambda m: f"(({ftype(m)} *)((char *){('&' if m.group(2) == '.' else '')}{m.group(1)} {off_str(field_off(m.group(3)))}))[",
                 out)
    # 3. value: arg->unkN -> *(T *)((char *)arg + N)
    out = re.sub(r"(\w+)(->|\.)(unk-?[0-9A-Fa-f]+)",
                 lambda m: f"*({ftype(m)} *)((char *){('&' if m.group(2) == '.' else '')}{m.group(1)} {off_str(field_off(m.group(3)))})",
                 out)

    # ---- AFTER the field rules: m2c's chained "spC.unk4->unk24" and
    # "X->unk18->unk74(args)" become "*(s32 *)((char *)&spC + 0x4)->unk24" and
    # "*(s32 *)(*(s32 *)((char *)arg0 + 0x18) + 0x74)(...)" — the deref-cast
    # base is not a struct, so the trailing ->unkN member access / call is
    # invalid C. Rewrite: add the member offset to the base address, or call
    # the deref'd fn pointer. (These must run AFTER the field rules: the
    # raw m2c text uses dot/arrow notation that the field rules expand.)

    # *(s32 *)(X)->unkN -> *((s32 *)((char *)X + 0xN))
    out = fix_deref_arrow(out)
    # *(s32 *)(X)(args) -> ((s32 (*)())*((s32 *)X))(args)
    out = fix_called_obj(out)
    # **(s32 *)(X) -> **(s32 **)(X) — the (s32 *) single-star cast is only
    # CREATED by the field rules above, so this must run after them too
    out = re.sub(r"\*\*\((s8|s16|s32|s64|u8|u16|u32|u64|f32|f64) \*\)", r"**(\1 **)", out)
    # pointer arithmetic where the second operand is a pointer-typed var
    # ((s32 *)X + p / (char *)X + p): cast the index to s32
    out = re.sub(r"\(\(char \*\)(\w+) \+ (\w+)\)", r"((char *)\1 + (s32)\2)", out)
    out = re.sub(r"\(\(s32 \*\)(\w+) \+ (\w+)\)", r"((s32 *)\1 + (s32)\2)", out)
    # same inside a deref (the ptr is deref'd right after): *(ptr + var)
    out = re.sub(r"\*\(\(s32 \*\)(\w+) \+ (\w+)\)", r"*((s32 *)\1 + (s32)\2)", out)
    # fix_int_deref rewrote "*(A + (B + 0xN))" to "*((s32 *)(A + (B + 0xN)))";
    # if A and B are both int-typed the inner sum is still invalid — split it
    # into byte arithmetic on A with the offset cast to s32
    out = re.sub(r"\*\(\(s32 \*\)\((\w+) \+ ((?:[^()]|\([^()]*\))+)\)\)",
                 r"*((s32 *)((char *)\1 + (s32)(\2)))", out)
    # the field rules above turn "(void *)0xADDR->unkN" into
    # "(void *)*(T *)((char *)0xADDR + N)" — drop the now-redundant (void *)
    # cast (it was only m2c's way of marking an absolute-address struct base),
    # and strip a unary minus that m2c put before a deref-lvalue from a
    # NEGATED absolute base ("-0x8000->unkCC010000")
    out = re.sub(r"\(void \*\)(?=\s*\*\()", "", out)
    out = re.sub(r"-(\*\([^;]*?\))(?=\s*=\s*)", r"\1", out)
    # carry-flag shim (m2c uses M2C_CARRY for addc/adde chains)
    if "M2C_CARRY" in out:
        out = "static s32 M2C_CARRY = 0;\n" + out
    # float operand summed into a pointer base: (s32 *)(VAR + *(f32 *)...) —
    # m2c typed the base's field as f32 but uses it as a byte address. Wrap the
    # whole sum in (s32) so the pointer cast is valid: (s32 *)((s32)(VAR + f))
    def fix_float_ptr_sum(text):
        res = []
        i = 0
        while True:
            m = re.search(r"\(s32 \*\)\(([A-Za-z_]\w*)\s*\+\s*\*?\(f32 \*\)", text[i:])
            if not m:
                break
            start = i + m.start()
            # scan the WHOLE (s32 *)(...) group from its opening '(' to the
            # matching ')' — the float deref term inside has its own nested
            # parens ((f32 *) and the ((char *)X + N) operand). Start depth at
            # 1 (we are already inside the outer group): the cast's own
            # "(f32 *)" parens only move depth 1->2->1 and never trigger the
            # depth==0 break that prematurely stops at the cast's close paren.
            depth = 1
            j = start + len("(s32 *)(")
            while j < len(text):
                if text[j] == "(":
                    depth += 1
                elif text[j] == ")":
                    depth -= 1
                    if depth == 0:
                        break
                j += 1
            inner = text[start + len("(s32 *)("):j]
            res.append(text[i:start] + f"(s32 *)((s32)({inner}))")
            i = j + 1
        res.append(text[i:])
        return "".join(res)

    out = fix_float_ptr_sum(out)

    # outer deref of a (deref + index) sum: *( *((s32 *)X + N) + M ) — m2c
    # treats a deref'd s32 as a byte address and indexes it. Cast the inner
    # sum to s32*: *((s32 *)(*((s32 *)X + N) + M))
    out = re.sub(r"\*\(\*\([^;]*?\)\s*[+-]\s*[A-Za-z_][A-Za-z0-9_]*\)",
                 lambda m: f"*((s32 *){m.group(0)[1:]})", out)
    # pointer-typed var used as an int in a subtraction against a pointer-typed
    # arg: (var + N + (deref * M)) - arg  ->  (s32)var + N + ... - (s32)arg
    out = re.sub(r"\((var_\w+) \+ (\d+) \+ \(\*\(\(s32 \*\)\1\) \* (0x[0-9A-Fa-f]+)\)\) - (\w+);",
                 r"((s32)\1 + \2 + (*((s32 *)\1) * \3)) - (s32)\4;", out)
    # m2c fn-ptr value decl mangled by the scalar-deref rule above:
    # s32 (*((s32 *)temp_r9))(s32); -> s32 (*temp_r9)(s32);
    out = re.sub(r"(\w+) \(\*\(\(\w+ \*\)(\w+)\)\)\(([^;]*)\);?",
                 r"\1 (*\2)(\3);", out)
    # same for file-scope/void-return forms: void (*((s32 *)x))(s32);
    out = re.sub(r"^(\s*)(\w+) \(\*\(\(\w+ \*\)(\w+)\)\)\(",
                 r"\1\2 (*\3)(", out, flags=re.M)

    # m2c stack-array access where the base was declared a scalar:
    # sp8[0] -> *((f32 *)&sp8)   and   sp8[0].unk8 -> *((f32 *)((char *)&sp8 + 8))
    # (m2c reads a 3-float stack slot as a struct with an unk8 field)
    out = re.sub(r"(sp[0-9A-Fa-f]+)\[0\]\.unk([0-9A-Fa-f]+)",
                 r"*((f32 *)((char *)&\1 + (s32)0x\2))", out)
    out = re.sub(r"(sp[0-9A-Fa-f]+)\[0\]", r"*((f32 *)&\1)", out)
    # m2c casts a float arg to a function-pointer type when calling through a
    # table slot (the callee type is a guess): (s32 (*)(s32)) farg1 -> (s32) farg1
    out = re.sub(r"\(\w+ \(\*\)\(\w+\)\) farg([0-9]+)", r"(s32) farg\1", out)
    # register-save slots and stack vars m2c uses but forgets to declare:
    # saved_reg_rN / saved_reg_lr, spN stack slots, unkspN unknown-size slots,
    # and the bare "sp" frame-pointer pseudo-var
    missing = set()
    for m in re.finditer(r"\b(saved_reg_[a-z0-9_]+)\b", out):
        missing.add(m.group(1))
    for m in re.finditer(r"\b(unksp[0-9A-Fa-f]+)\b", out):
        missing.add(m.group(1))
    declared = set(re.findall(r"\b(?:s32|u32|f32|s16|u16|s8|u8|f64|s64|u64|void|char|float|double)\s+(sp[0-9A-Fa-f]+)\b", out))
    for m in re.finditer(r"\b(sp[0-9A-Fa-f]+)\b", out):
        if m.group(1) not in declared:
            missing.add(m.group(1))
    if re.search(r"\bsp\b", out):
        missing.add("sp")
    if missing:
        out = "".join(f"static s32 {n};\n" for n in sorted(missing)) + out

    # ---- type-aware cast fixes (m2c guesses types: a var it typed float may
    # be used as a byte address and vice versa; GCC rejects those casts) ----

    # collect declared variable types: pointer-typed names, float-typed names,
    # and function-parameter names (the fn signature line). Also record every
    # declared var at all so we only rewrite known locals/args.
    ptr_names = set()
    float_names = set()
    all_names = set()
    for m in re.finditer(
            r"\b(?:const\s+)?(?:void|char|s8|u8|s16|u16|s32|u32|s64|u64|f32|f64)\s+\*\s*([A-Za-z_]\w*)", out):
        ptr_names.add(m.group(1))
        all_names.add(m.group(1))
    for m in re.finditer(
            r"\b(?:const\s+)?(?:f32|f64)\s+(?!\*)([A-Za-z_]\w*)", out):
        float_names.add(m.group(1))
        all_names.add(m.group(1))
    # function params: parse the first "NAME( ... ) {" line
    fm = re.search(r"\b(?:void|s8|s16|s32|s64|u8|u16|u32|u64|f32|f64)\s+([A-Za-z_]\w*)\(([^)]*)\)\s*\{", out)
    if fm:
        for pm in re.finditer(r"(?:\*\s*)?([A-Za-z_]\w+)\s*(?:,|$)", fm.group(2)):
            pname = pm.group(1)
            all_names.add(pname)
            # param declared with a star is a pointer
            seg = pm.group(0)
            if "*" in seg:
                ptr_names.add(pname)
            elif re.search(r"\b(?:f32|f64)\b", seg):
                float_names.add(pname)

    # (f32)/(f64) cast applied to a POINTER-typed var (m2c's (bitwise f32) on a
    # byte address): (f32) temp_r7 where void *temp_r7 -> (f32)(s32)temp_r7
    for name in sorted(ptr_names):
        out = re.sub(r"\((?:f32|f64)\)\s*\b%s\b" % re.escape(name),
                     lambda m, n=name: f"(f32)(s32){n}", out)
    # pointer-cast of a FLOAT-typed var (a byte address m2c typed f32):
    # (char *)sp14 where f32 sp14 -> (char *)(s32)sp14
    for name in sorted(float_names):
        out = re.sub(r"\((?:void|char|s8|u8|s16|u16|s32|u32|s64|u64|f32|f64)\s+\*\)\s*\b%s\b" % re.escape(name),
                     lambda m, n=name: f"(char *)(s32){n}", out)

    # two POINTER-typed vars summed/subtracted as byte addresses in an
    # assignment (m2c typed them as pointers but the code does byte-address
    # arithmetic): "A = B + C;" -> "A = (char *)B + (s32)C;" and
    # "A = B - C;" -> "A = (s32)B - (s32)C;" (pointer+pointer is invalid C;
    # pointer-minus-pointer of mixed types too)
    ptr_alt = "|".join(re.escape(n) for n in sorted(ptr_names, key=len, reverse=True))
    if ptr_alt:
        out = re.sub(r"([A-Za-z_]\w*) = ((" + ptr_alt + r")) \+ ((" + ptr_alt + r"));",
                     lambda m: f"{m.group(1)} = (char *){m.group(2)} + (s32){m.group(3)};", out)
        out = re.sub(r"([A-Za-z_]\w*) = ((" + ptr_alt + r")) - ((" + ptr_alt + r"));",
                     lambda m: f"{m.group(1)} = (s32){m.group(2)} - (s32){m.group(3)};", out)

    # fn-ptr call through a global pointer with a GUESSED param list whose arity
    # doesn't match the call: (*(s32 (**)(u16, s32, s32))0xADDR)(2 args) — GCC
    # rejects "too few arguments". Count the top-level args in the call and the
    # params in the type; on mismatch, drop the param list to (()) so the call
    # is valid C89 with unspecified params.
    def fix_fnptr_arity(text):
        res = []
        i = 0
        while True:
            m = re.search(r"\(\*\((\w+) \(\*\*\)\(([^)]*)\)\)0x[0-9A-Fa-f]+\)\(", text[i:])
            if not m:
                break
            start = i + m.start()
            params = m.group(2)
            nparams = len([p for p in params.split(",") if p.strip()]) if params.strip() else 0
            # find the matching ')' of the call's '(' at start+len(m.group(0))-2
            open_idx = start + len(m.group(0)) - 2  # index of the call '('
            depth = 0
            j = open_idx
            while j < len(text):
                if text[j] == "(":
                    depth += 1
                elif text[j] == ")":
                    depth -= 1
                    if depth == 0:
                        break
                j += 1
            args = text[open_idx + 1:j]
            nargs = 1 if args.strip() else 0
            depth = 0
            for ch in args:
                if ch == "(":
                    depth += 1
                elif ch == ")":
                    depth -= 1
                elif ch == "," and depth == 0:
                    nargs += 1
            if nparams != nargs:
                tail = m.group(0).replace(m.group(0)[m.group(0).index("("):], "")
                head = m.group(0)[:m.group(0).index("(")]
                repl = head + "(**)(" + "" + ")" + "0x" + m.group(0).split("0x")[1].split(")")[0] + ")("
                # rebuild: (*(TYPE (**)())0xADDR)(
                typ = m.group(1)
                addr = m.group(0).split("0x")[1].split(")")[0]
                repl = f"(*({typ} (**)())0x{addr})("
                res.append(text[i:start] + repl)
                i = start + len(m.group(0))
            else:
                res.append(text[i:start + len(m.group(0))])
                i = start + len(m.group(0))
        res.append(text[i:])
        return "".join(res)

    out = fix_fnptr_arity(out)

    # deref of (call result + byte offset): *(fn_X(...) + (expr)) — m2c typed
    # the call as returning a byte base. Cast the call result to s32* and the
    # offset to s32: *((s32 *)(fn_X(...)) + (s32)(expr))
    out = re.sub(r"\*\(((?:fn_[0-9A-Fa-f]{8}|PPCM\w+)\s*\([^;]*?\))\s*\+\s*(\([^;]*?\))\)",
                 r"*((s32 *)(\1) + (s32)(\2))", out)
    # stray jump-table cases: m2c sometimes emits "case N:" / "default:"
    # labels at a brace level with no enclosing switch (computed-goto tables).
    # Track switch-scope: a case is only legal while a "switch (..) {" is open.
    lines = out.split("\n")
    kept = []
    stack = []  # each entry: True if opened by a switch
    for ln in lines:
        s = ln.strip()
        # push for every '{' opened on this line (after any switch on it)
        sw_open = bool(re.search(r"\bswitch\s*\([^)]*\)\s*\{", s))
        n_open = s.count("{") - s.count("}")
        is_case = bool(re.match(r"(case\s+[^:]+:|default:)", s))
        # a case is valid if innermost open frame is a switch
        if is_case and stack and stack[-1]:
            kept.append(ln)
        elif is_case and not stack:
            pass  # drop: no switch at all
        elif is_case and stack and not stack[-1]:
            # drop only if the line belongs to a frame that was NOT switch-
            # opened AND no open switch frame exists anywhere in the stack
            if any(stack):
                kept.append(ln)
            else:
                pass
        else:
            kept.append(ln)
        if n_open > 0:
            stack.append(sw_open)
        elif n_open < 0:
            for _ in range(-n_open):
                if stack:
                    stack.pop()
    out = "\n".join(kept)

    # m2c indexed member with byte offset: X[i].unk-N -> byte at X + i - N
    # (X is a byte array base: temp_r30[var_r31].unk-1 == 0x65)
    out = re.sub(r"\(([^)]*)\)\[([^\]]+)\]\.unk-?([0-9A-Fa-f]+)",
                 r"*((s8 *)((char *)(\1) + (s32)(\2) + (s32)-0x\3))", out)
    out = re.sub(r"([A-Za-z_]\w*)\[([^\]]+)\]\.unk-?([0-9A-Fa-f]+)",
                 r"*((s8 *)((char *)(\1) + (s32)(\2) + (s32)-0x\3))", out)
    # m2c emits a param-count-inconsistent call through a raw deref:
    # *(s32 *)0xADDR(args) — read the fn ptr then call it
    out = re.sub(r"\*\(s32 \*\)0x([0-9A-Fa-f]+)\(",
                 r"((s32 (*)())*(s32 *)0x\1)(", out)
    # m2c ?N-vs-name: "?32 spF0;" (m2c prints an unknown stack size) — my ?->s32
    # rule requires standalone '?'; fix the "?N name" decl form
    out = re.sub(r"\?([0-9A-Fa-f]+)\s+(sp[0-9A-Fa-f]+|unksp[0-9A-Fa-f]+)\s*;", r"s32 \2;", out)
    # AFTER the field rules: convert the old-style fn-ptr calls they produced
    # (see fix_fptr_proto def above) — kills the spurious crclr cr1eq.
    # M4.94: BEFORE re-prototyping, strip m2c's raw guessed fn-ptr cast param
    # lists ((s32 (*)(void *, void *))...) — their arity/types disagree with
    # the actual call args (too few/many args, incompatible arg types). After
    # this strip, fix_fptr_proto (just below) re-prototypes the deref form
    # from the *actual* args, and any leftover ((s32 (*)())VAR)(args) compiles
    # fine. This MUST run before fix_fptr_proto: running after would undo its
    # prototypes and reintroduce the spurious crclr cr1eq.
    out = re.sub(r"\(\(\s*s32\s*\(\s*\*\s*\)\(\s*[^()]*\)\s*\)", r"((s32 (*)())", out)
    out = fix_fptr_proto(out)
    # fn-ptr value decls with multi-word return types or array suffix:
    # void *(*((s32 *)temp_r9_2))(void *, s32); and f32 (*((s32 *)temp_r11))[];
    # and TYPE *(*((TYPE *)name))(args); (m2c's fn-ptr decl with a pointer
    # return, e.g. "s16 *(*((s32 *)temp_r10))(s32, s32, s32, s32, f32);" — the
    # optional \*? absorbs the pointer star so the whole decl becomes a plain
    # fn-ptr "s16 (*temp_r10)(args);")
    out = re.sub(r"((?:void\s+\*|s8|s16|s32|s64|u8|u16|u32|u64|f32|f64))\s*\*?\s*\(\*\(\(\w+ \*\)(\w+)\)\)\(([^;]*)\);?",
                 r"\1 (*\2)(\3);", out)
    out = re.sub(r"((?:void\s+\*|s8|s16|s32|s64|u8|u16|u32|u64|f32|f64))\s*\(\*\(\(\w+ \*\)(\w+)\)\)\[\s*\]\s*;",
                 r"\1 **\2;", out)

    # --- M4.94: compile-fail cleanup rules (58 drafts fixed, 0 regressions) ---
    # 1) m2c emits 'static s32 M2C_CARRY = 0;' twice (and sometimes 3x) — keep
    #    only the first declaration.
    lines = out.split("\n")
    seen_carry = False
    kept = []
    for ln in lines:
        if re.fullmatch(r"static s32 M2C_CARRY = 0;", ln.strip()):
            if seen_carry:
                continue
            seen_carry = True
        kept.append(ln)
    out = "\n".join(kept)
    # 2) m2c wraps integer address math in pointer casts:
    #    (s32 *)((s32)(expr)) as an offset -> (s32)(expr); and
    #    (char *)A + (s32 *)B -> ((char *)A + (s32)B)
    out = re.sub(r"\(\s*s32\s*\*\s*\)\s*\(\(\s*s32\s*\)\s*\(([^)]+)\)\)", r"(s32)(\1)", out)
    out = re.sub(r"\(\s*char\s*\*\s*\)([^)]+?)\s*\+\s*\(\s*s32\s*\*\s*\)", r"((char *)\1 + (s32)", out)
    # 4) two per-address stragglers: masked address computation where the
    #    (char *) cast makes '& 0xFFFFFFF8' invalid on a pointer.
    out = out.replace(
        "*((s32 *)(((char *)0xE + (s32)temp_r1 + -(((arg3 * 4))) & 0xFFFFFFF8)) = sp0;",
        "*((s32 *)(0xE + (s32)temp_r1 + -(((arg3 * 4))) & 0xFFFFFFF8)) = sp0;")
    out = out.replace(
        "*((s32 *)(((char *)0xE + (s32)temp_r1_3 + temp_r9_4 + -(((*(s32 *)((char *)temp_r25 + (s32)0x4) * 4))) & 0xFFFFFFF8)) = sp0;",
        "*((s32 *)(0xE + (s32)temp_r1_3 + temp_r9_4 + -(((*(s32 *)((char *)temp_r25 + (s32)0x4) * 4))) & 0xFFFFFFF8)) = sp0;")

    # tidy
    out = re.sub(r"\n{3,}", "\n\n", out)
    return out.strip()


def has_real_body(text):
    """True if the m2c output is more than an empty body / all-unknown."""
    m = re.search(r"\{.*\}\s*$", text, flags=re.S)
    inner = m.group(0) if m else text
    inner = re.sub(r"\b0\b", "", inner)
    inner = re.sub(r"\s", "", inner)
    return bool(re.search(r"[A-Za-z_]", inner)) or "=" in inner


def main():
    limit = int(sys.argv[sys.argv.index("--limit") + 1]) if "--limit" in sys.argv else 0
    addr_only = int(sys.argv[sys.argv.index("--addr") + 1], 0) if "--addr" in sys.argv else 0
    addr_set = None
    if "--addr-file" in sys.argv:
        addr_set = {int(l.strip(), 16) for l in open(sys.argv[sys.argv.index("--addr-file") + 1]) if l.strip()}
    max_size = int(sys.argv[sys.argv.index("--max-size") + 1]) if "--max-size" in sys.argv else 0
    dry = "--dry-run" in sys.argv
    force = "--force" in sys.argv  # re-fill existing family=m2c drafts too

    files = sorted(glob.glob(f"{WIP_DIR}/fn_*.c"))
    changed = []
    stats = {"filled": 0, "empty": 0, "skipped_text": 0, "failed": 0, "no_size": 0}
    for fp in files:
        if limit and stats["filled"] >= limit:
            break
        addr = int(os.path.basename(fp)[3:11], 16)
        if addr_only and addr != addr_only:
            continue
        if addr_set and addr not in addr_set:
            continue
        if addr < gl.t_addr or addr >= gl.t_addr + gl.t_size:
            stats["skipped_text"] += 1
            continue
        text = open(fp).read()
        if "family=stub" not in text and not (force and "family=m2c" in text):
            continue
        if max_size:
            m = RE_SIZE.search(text)
            if m and int(m.group(1)) > max_size:
                continue
        m = RE_SIZE.search(text)
        size = int(m.group(1)) if m else None
        if size is None:
            stats["no_size"] += 1
            continue
        asm_lines, _ = disasm_with_labels(addr, size)
        if len(asm_lines) < 2:
            stats["failed"] += 1
            continue
        out = run_m2c("\n".join(asm_lines) + "\n")
        if out is None:
            stats["failed"] += 1
            continue
        body = postprocess(out)
        if not has_real_body(body):
            stats["empty"] += 1
            continue
        # name QB script-hash magic literals (0x9B65D7B8 -> QB_OLLIE) so
        # regenerated drafts keep the named constants from the sweep tool
        body, _nconst = subst_qb_constants(body)
        if dry:
            stats["filled"] += 1
            continue
        new = (
            "// WIP DRAFT (non-matching) — C body generated by tools/fill_wip_drafts.py\n"
            f"// family=m2c range=0x{addr:X}-0x{addr + size:X} size={size}B\n"
            "// INERT: not registered in splits.txt/configure.py — never compiled,\n"
            "// not counted in objdiff progress. activate via tools/wip.py.\n"
            '#include "types.h"\n'
            + ('#include "qb_constants.h"\n' if _nconst else '')
            + body + "\n"
        )
        open(fp, "w").write(new)
        changed.append(addr)
        stats["filled"] += 1

    # update WIP.md family column stub -> m2c for changed rows
    if changed and not dry:
        names = {f"fn_{a:08X}" for a in changed}
        lines = open(REG).read().split("\n")
        upd = 0
        for i, l in enumerate(lines):
            m = re.match(r"\| (fn_[0-9A-F]{8}) \| 0x[0-9A-F]{8} \| (stub) \|", l)
            if m and m.group(1) in names:
                lines[i] = l.replace("| stub |", "| m2c |")
                upd += 1
        open(REG, "w").write("\n".join(lines))
        stats["wip_rows"] = upd

    print(f"=== fill results: {stats} ===")
    if dry:
        print("(dry run — nothing written)")


if __name__ == "__main__":
    main()
