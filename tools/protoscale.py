#!/usr/bin/env python3
"""Parallel doc-56 rescan (2026-09-16): the serial proto_undeclared_scan.py adds ONE
prototype per round and gives up when a round finds no improvement, so drafts with
SEVERAL undeclared callees (the common case) are reported as having no fix.  This
does the opposite: splice prototypes for ALL undeclared callees at once, above the
function DEFINITION (not the top of the file - structs.h types are not in
scope there), and keep only strict improvements.

Parallel doc-56 rescan: for every draft that compiles to a `crclr/crset`,
add prototypes for ALL undeclared callees at once and keep strict wins.

Usage: protoscale.py <list-of-draft-paths> [nproc]
Winners are written to /tmp/protowin/fn_XXXXXXXX.c and printed.
"""
import os, re, sys

sys.path.insert(0, os.path.abspath("tools"))
import gen_leaves as gl
from test_wip_drafts import test_one
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

_md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
_md.skipdata = True

# every name registered in symbols.txt is a candidate callee
SYMS = set()
try:
    for ln in open("config/G2TE52/symbols.txt"):
        m = re.match(r"^\s*([A-Za-z_][\w]*)\s*=", ln)
        if m:
            SYMS.add(m.group(1))
except OSError:
    pass

KEYWORDS = {
    "if", "while", "for", "switch", "return", "sizeof", "do", "else", "goto",
    "void", "int", "char", "short", "long", "float", "double", "s32", "u32",
    "s16", "u16", "s8", "u8", "s64", "u64", "f32", "f64", "NULL", "defined",
}
LIBC = {
    "memset", "memcpy", "memmove", "strlen", "strcpy", "strcmp", "strncpy",
    "strcat", "printf", "sprintf", "floor", "ceil", "fabs", "sqrt", "sin",
    "cos", "atan2", "pow", "fmod", "__builtin_va_end", "va_start", "va_end",
}

# a DECLARATION starts a line (optionally `extern`) and ends with `;`; a call
# assigned/stored into something must NOT count (that bug made every callee
# look declared).
DECL = re.compile(
    r"^[ \t]*(?:extern[ \t]+)?(?:[A-Za-z_][\w \t\*]*?[ \t\*]+)"
    r"([A-Za-z_]\w*)[ \t]*\([^;{}]*\)[ \t]*;", re.M)
CALL = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
DEF = re.compile(
    r"^[ \t]*(?:static[ \t]+)?([A-Za-z_][\w \t\*]*?[ \t\*]+)"
    r"([A-Za-z_]\w*)[ \t]*\(([^;{)]*)\)[ \t]*\{", re.M)

_sigcache = {}


def real_sig(name):
    if name in _sigcache:
        return _sigcache[name]
    val = None
    for d in ("src", "libs"):
        p = os.path.join(d, name + ".c")
        if os.path.exists(p):
            m = DEF.search(open(p, errors="ignore").read())
            if m:
                val = (m.group(1).strip(), m.group(3).strip())
                break
    _sigcache[name] = val
    return val


def arity_of(body, name):
    """arg count of the first call to `name`, 0 if it cannot be parsed."""
    i = 0
    while True:
        m = re.search(r"\b%s\s*\(" % re.escape(name), body[i:])
        if not m:
            return None
        j = i + m.end()
        depth = 1
        args = 0
        seen = False
        while j < len(body) and depth:
            c = body[j]
            if c in "([{":
                depth += 1
            elif c in ")]}":
                depth -= 1
                if depth == 0:
                    break
            elif depth == 1 and c == ",":
                args += 1
            if not c.isspace() and depth >= 1:
                seen = True
            j += 1
        return (args + 1) if seen else 0


def candidates(body):
    declared = set(m.group(1) for m in DECL.finditer(body))
    own = DEF.search(body)
    called = {}
    for m in CALL.finditer(body):
        n = m.group(1)
        if n in KEYWORDS or n in LIBC or n in declared:
            continue
        if not (re.fullmatch(r"fn_[0-9A-Fa-f]{8}", n) or n in SYMS):
            continue
        called.setdefault(n, True)
    if own:
        called.pop(own.group(2), None)
    out = []
    for n in called:
        sig = real_sig(n)
        if sig:
            out.append("%s %s(%s);" % (sig[0], n, sig[1]))
        else:
            a = arity_of(body, n)
            if a is None:
                continue
            out.append("void %s(void);" % n if a == 0
                       else "void %s(%s);" % (n, ", ".join(["void *"] * a)))
    return out


def with_decls(body, decls):
    """Splice declarations immediately above the function DEFINITION (not at the
    top of the file, where the structs.h types they use are not yet known)."""
    m = DEF.search(body)
    pos = m.start() if m else 0
    return body[:pos] + "\n".join(decls) + "\n" + body[pos:]


def has_cr(body, addr):
    try:
        got, _ = gl.compile_fn(addr, body, extra_flags=gl.draft_flags(body) or None)
    except Exception:
        return False
    if not got:
        return False
    return any(i.mnemonic in ("crclr", "crset") for i in _md.disasm(got, addr))


def work(path):
    os.environ["LEAF_TMPDIR"] = "/tmp/leafps%d" % (os.getpid() % 24)
    if not os.path.exists(path):
        return None
    addr = int(os.path.basename(path)[3:11], 16)
    text = open(path).read()
    body = "\n".join(l for l in text.splitlines()
                     if not l.startswith("//") and "types.h" not in l).strip()
    flags = gl.draft_flags(text) or None
    try:
        s0, p0, _ = test_one(addr, body, flags)
    except Exception:
        return None
    if s0 == "EXACT":
        return None
    if not has_cr(body, addr):
        return None
    decls = candidates(body)
    if not decls:
        return None
    best = (p0, None)
    for scope in [decls] + [[d] for d in decls]:
        cand = with_decls(body, scope)
        try:
            _s1, p1, _ = test_one(addr, cand, flags)
        except Exception:
            continue
        if p1 > best[0] + 0.05:
            best = (p1, cand)
    if best[1] is None:
        return ("NOCR", p0, addr, path)
    os.makedirs("/tmp/protowin", exist_ok=True)
    out = "/tmp/protowin/fn_%08X.c" % addr
    open(out, "w").write("// protoscale winner (doc-56 all-at-once)\n" + best[1])
    return ("BETTER", p0, best[0], addr, out)


if __name__ == "__main__":
    files = [l.strip() for l in open(sys.argv[1]) if l.strip()]
    n = int(sys.argv[2]) if len(sys.argv) > 2 else 16
    from multiprocessing import Pool
    rows = []
    with Pool(n) as pool:
        for r in pool.imap_unordered(work, files, chunksize=4):
            if r:
                rows.append(r)
    rows.sort(key=lambda r: -r[2])
    for r in rows:
        if r[0] == "BETTER":
            print("BETTER 0x%08X %.1f -> %.1f  %s" % (r[3], r[1], r[2], r[4]))
        else:
            print("crclr-but-nofix 0x%08X %.1f %s" % (r[2], r[1], r[3]))
    print("scanned %d, hits %d" % (len(files), len(rows)))
