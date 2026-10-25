#!/usr/bin/env python3
"""RELOAD/ARG PIN sweep — the docs/parkings/75 lever, automated.

`tools/pin_sweep.py` already pins the *declared locals* of a draft to the
want-side registers named by `regdiff_scan.py`.  Doc-74 found a lever that is
orthogonal to it: pin a value that is **not** a declared local at all — the
reload of a callee-written out-param slot, or a call's argument — and a single
pin can clear a residual that looks like several independent scheduling
problems.  Two solved examples:

  * `fn_80191E8C` 95.1% -> EXACT: `register s32 sp8r4 __asm__("r4"); sp8r4 = sp8;`
    after `GetChecksum_2(..., &sp8, 0)`.  Fixing the `lwz r4` vs `lwz r0`
    reload ALSO fixed the `ori r4`/`mr r3,r31` arg-order word.
  * `fn_8016D52C` 95.6% -> EXACT: `register void *carg __asm__("r3"); carg = a0;`
    before the `fn_8016E1B4(carg)` call.  Fixing the hoisted `mr r3,r29` ALSO
    fixed the delayed `mr r25,r24` home copy.
  * `fn_8022BA54` 83.3% -> 95.8%: `register void *pv9 __asm__("r9");` on the
    second reload of `sub->unk0x10`.

So this sweeper, for each draft:

  1. finds every `NAME = &LOCAL;` / `NAME = *EXPR;` / `f(NAME = ...)` site that
     could be a reload or a call argument;
  2. synthesises a variant that introduces ONE `register T NAMEpin __asm__("rN");`
     declaration plus the matching assignment, for each candidate register
     r0..r31;
  3. compiles each through `gen_leaves.compile_fn` and reports only STRICT
     improvements over the draft's own score.

This is deliberately narrow (one pin, one site, one register) so it stays
cheap; the existing `pin_sweep.py` remains the tool for multi-pin and
local-pin work.

Usage:
    tools/venv/bin/python tools/reload_pin_sweep.py ADDR [ADDR ...]
    tools/venv/bin/python tools/reload_pin_sweep.py --file-list F [--jobs N]
    tools/venv/bin/python tools/reload_pin_sweep.py --dry-run 0x800F4450

Prints `verdict<TAB>delta<TAB>addr<TAB>site<TAB>reg<TAB>score`.
Positive-control note (recipes §7e): always confirm the tool rediscovers the
two known wins before trusting a "0 wins" run.
"""
import concurrent.futures
import os
import re
import sys
import tempfile
import threading

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import gen_leaves as gl  # noqa: E402

WIP = os.path.join(ROOT, "src", "wip")

# function-top single-declarator locals, per pin_sweep.py's DECL
DECL = re.compile(r"^    ((?:const\s+)?(?:volatile\s+)?(?:unsigned\s+|signed\s+)?"
                  r"(?:\w+)\s*\*?)\s*([A-Za-z_]\w*)\s*(?:=[^;]*)?;\s*$")
PINNED = re.compile(r"^    register\s+.*__asm__")

# a statement that assigns to a plain local (candidate reload site).  Any
# indent >= 4: drafts nest these inside if/loop scopes, so a fixed 8 was wrong.
ASSIGN = re.compile(r"^ {4,}([A-Za-z_]\w*)\s*=\s*([^;]+);\s*$")
# a call whose arguments are plain names/expressions (candidate arg site)
CALL = re.compile(r"^ {4,}([A-Za-z_]\w*)\((.*)\);\s*$")

# registers worth trying: the volatile arg/call-clobber set plus the two the
# HI16 reload set uses (docs/parkings/73).  Callee-saved r13-r31 are already
# reachable through the draft's own pins, so trying them again just burns time.
CANDIDATE_REGS = ["r0", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10",
                  "r11", "r12"]

# Map the draft's declared type onto the type the pin should carry.  Pointer
# types must stay POINTERS: emitting `register s32 x` for a `void *` variable
# silently changes the arithmetic (and cc1 may drop the pin entirely).
def pin_type(decl_type):
    t = decl_type.strip()
    if t.endswith("*"):
        return t + " "
    return {"void": "s32", "int": "s32", "s32": "s32", "u32": "s32",
            "f32": "f32", "f64": "f64", "char": "s32", "short": "s32",
            "u8": "s32", "u16": "s32"}.get(t, "s32") + " "


def split_banner(path):
    """Return (comment_banner_lines, code) for a draft."""
    raw = open(path, errors="ignore").read()
    flags = []
    for line in raw.splitlines():
        m = re.match(r"^//\s*(?:FLAG|extra_cflags):\s*(.+)$", line)
        if m:
            flags += [t for t in m.group(1).split() if gl.FLAG_TOKEN_RE.match(t)]
    idx = raw.find("#include")
    banner = raw[:idx] if idx > 0 else ""
    return banner, raw[idx:] if idx > 0 else raw, flags


def decls_of(body):
    """[(line, type, name)] for the function's OWN top-level locals.

    Only the run of declarations immediately after the function's opening
    brace counts.  Scanning every line also matched nested block locals and
    `if (...)` bodies, which produced phantom names ('m' from '...name',
    'v' from '...prev') in the first cut.
    """
    out = []
    started = False
    for l in body.splitlines():
        if not started:
            if re.match(r"^\w[\w \*]*\s+\w+\s*\([^;]*\)\s*\{\s*$", l):
                started = True
            continue
        m = PINNED.match(l)
        if m:
            m2 = re.match(r"^    register\s+(.*?)\s*([A-Za-z_]\w*)\s+__asm__", l)
            if m2:
                out.append((l, m2.group(1).strip(), m2.group(2)))
            continue
        m = DECL.match(l)
        if m:
            out.append((l, m.group(1).strip(), m.group(2)))
            continue
        if l.strip() == "":
            continue
        break
    return out


_TID = threading.local()
_ROOT_TMP = None


def _scratch():
    """Per-THREAD scratch dir.

    `gen_leaves.compile_fn` writes `<LEAF_TMPDIR>/fn_ADDR.c|.o`, so every
    thread compiling the SAME address onto one directory races and reads a
    half-written object (it surfaces as an ELFParseError from elftools, not as
    a compile error).  gen_leaves documents LEAF_TMPDIR for exactly this, but
    it only guards across PROCESSES, so the thread pool needs its own split.
    """
    if getattr(_TID, "dir", None) is None:
        _TID.dir = tempfile.mkdtemp(prefix=f"rpin_{threading.get_ident()}_",
                                    dir=_ROOT_TMP)
    return _TID.dir


def score(addr, body, flags):
    prev = os.environ.get("LEAF_TMPDIR")
    os.environ["LEAF_TMPDIR"] = _scratch()
    try:
        got, masks = gl.compile_fn(addr, body, extra_flags=flags or None)
    finally:
        if prev is not None:
            os.environ["LEAF_TMPDIR"] = prev
        else:
            os.environ.pop("LEAF_TMPDIR", None)
    if got is None:
        return None, masks
    off = gl.t_off + (addr - gl.t_addr)
    wsize = want_size(addr)
    if wsize is None:
        return None, masks
    want = gl.d[off:off + wsize]
    n = min(len(want), len(got)) // 4
    if n == 0:
        return 0.0, masks
    diff = 0
    for i in range(n):
        gw = int.from_bytes(want[i * 4:i * 4 + 4], "big")
        gg = int.from_bytes(got[i * 4:i * 4 + 4], "big")
        m = masks.get(i * 4, 0xFFFFFFFF)
        diff += (gw & m) != (gg & m)
    return 100.0 * (n - diff) / n, masks


def want_size(addr):
    for cand in (os.path.join(WIP, f"fn_{addr:08X}.c"),):
        if not os.path.exists(cand):
            continue
        m = re.search(r"^//\s*family=\S+\s+range=0x([0-9A-Fa-f]+)-0x([0-9A-Fa-f]+)",
                      open(cand, errors="ignore").read(), re.M)
        if m and int(m.group(1), 16) == addr:
            return int(m.group(2), 16) - addr
    syms = os.path.join(ROOT, "config/G2TE52/symbols.txt")
    m = re.search(r"^fn_%08X = \.text:0x[0-9A-Fa-f]+;.*?size:0x([0-9A-Fa-f]+)" % addr,
                  open(syms, errors="ignore").read(), re.M)
    return int(m.group(1), 16) if m else None


def candidate_sites(body):
    """[(line_index, name, replacement_line)] reload/arg pin sites.

    The pin's TYPE is derived from the variable's own declaration at build
    time (see `pin_type`), so it is not carried here.
    """
    lines = body.splitlines()
    decls = decls_of(body)
    types = {n: t for _, t, n in decls}
    sites = []
    for i, l in enumerate(lines):
        m = ASSIGN.match(l)
        if m:
            name = m.group(1)
            if name in types and not name.startswith("temp_f"):
                # A pin only constrains the allocator if the VALUE FLOWS
                # THROUGH the pinned variable, so build_variant retypes the
                # WHOLE web -- renaming only the assignment leaves the uses on
                # the old variable and the pin does nothing (that is why the
                # first cut scored 0 wins on the positive control).
                pin = f"{name}pin"
                sites.append((i, name,
                              l.replace(f"{name} = ", f"{pin} = ", 1)))
            continue
        m = CALL.match(l)
        if m:
            callee, argl = m.group(1), m.group(2)
            args = [a.strip() for a in argl.split(",")]
            # pin the FIRST argument only: that is the one whose `mr r3` is the
            # doc-75 shape (a later arg is usually a literal or an FPR).
            if args and re.match(r"^[A-Za-z_]\w*(\s*[-+].*)?$", args[0]) \
                    and args[0].split()[0] in types:
                name = args[0].split()[0]
                pin = f"{name}pin"
                sites.append((i, name,
                              f"        {pin} = {args[0]};\n        "
                              f"{callee}({pin}, {argl[len(args[0]):]})"))
    return sites


def build_variant(body, site_idx, repl, name):
    """Retype the whole `name` web onto a pinned variable.

    * the top-level DECLARATION of `name` is renamed (it keeps its own line,
      so it is matched by name rather than by the generic DECL regex)
    * every later use of `<name>` becomes `<name>pin`
    * the statement at `site_idx` is replaced by `repl`
    """
    lines = body.splitlines()
    pin = f"{name}pin"
    pat = re.compile(rf"\b{re.escape(name)}\b")
    out = []
    started = False
    for i, l in enumerate(lines):
        if not started:
            if re.match(r"^\w[\w \*]*\s+\w+\s*\([^;]*\)\s*\{\s*$", l):
                started = True
            out.append(l)
            continue
        if re.match(rf"^    \S.*\b{re.escape(name)}\s*;\s*$", l) and not PINNED.match(l):
            out.append(pat.sub(pin, l))          # the declaration itself
            continue
        if i == site_idx:
            out.append(pat.sub(pin, repl))
            continue
        out.append(pat.sub(pin, l))
    return "\n".join(out) + "\n"


def run_addr(addr, jobs, dry):
    path = os.path.join(WIP, f"fn_{addr:08X}.c")
    if not os.path.exists(path):
        return []
    _, body, flags = split_banner(path)
    if "__ps_t" in body and "-mps-float" not in flags:
        flags = flags + ["-mps-float"]
    base_pct, _ = score(addr, body, flags)
    if base_pct is None:
        return []
    sites = candidate_sites(body)
    results = []

    types = {n: t for _, t, n in decls_of(body)}

    def one(args):
        idx, name, repl, reg = args
        v = build_variant(body, idx, repl, name)
        lines = v.splitlines()
        # find the DECLARATION of the pinned name by name, not by "first line
        # matching DECL" -- body statements like `item = fn_...;` also match
        # DECL once the web has been retyped, and picking the first one pinned
        # the wrong variable.  next(..., None) + None-return: a missing decl is
        # a dead variant, not an exception (a StopIteration raised inside a
        # ThreadPoolExecutor map aborts the entire run).
        tgt = next((i for i, l in enumerate(lines)
                    if re.match(rf"^    \S.*\b{re.escape(name)}pin\s*;\s*$", l)
                    and not l.strip().startswith(("if", "for", "while", "return"))),
                   None)
        if tgt is None:
            return (name, reg, None)
        decl_type = pin_type(types.get(name, "s32"))
        lines[tgt] = f'    register {decl_type}{name}pin __asm__("{reg}");'
        pct, _ = score(addr, "\n".join(lines) + "\n", flags)
        return (name, reg, pct)

    work = [(idx, name, repl, reg)
            for (idx, name, repl) in sites
            for reg in CANDIDATE_REGS]
    if dry:
        for w in work:
            print(f"0x{addr:08X}\tbase={base_pct:.2f}\t{w[1]} -> {w[3]}\tline {w[0]}")
        return []
    with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as ex:
        for name, reg, pct in ex.map(one, work):
            if pct is not None and pct > base_pct + 1e-9:
                results.append((f"WIN", pct - base_pct, addr, name, reg,
                                f"{base_pct:.2f} -> {pct:.2f}"))
    for r in sorted(results, key=lambda x: -x[1]):
        print("\t".join(str(x) for x in r))
    if not results:
        print(f"none\t0\t{addr}\t-\t-\t{base_pct:.2f}")
    return results


def main():
    args = sys.argv[1:]
    jobs = 8
    dry = False
    addrs = []
    i = 0
    while i < len(args):
        if args[i] == "--jobs":
            jobs = int(args[i + 1]); i += 2
        elif args[i] == "--dry-run":
            dry = True; i += 1
        else:
            addrs.append(int(args[i], 16)); i += 1
    if not addrs:
        print(__doc__)
        return 2
    global _ROOT_TMP
    _ROOT_TMP = tempfile.mkdtemp(prefix="reload_pin_")
    os.environ["LEAF_TMPDIR"] = _ROOT_TMP
    for a in addrs:
        run_addr(a, jobs, dry)
    return 0


if __name__ == "__main__":
    sys.exit(main())