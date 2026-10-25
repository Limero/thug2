"""crclr harvest: add correct callee prototypes to drafts that call undeclared
fn_* functions.

Why: fill_wip_drafts.py strips all callee prototypes (relying on implicit decl),
and ngccc 3.7 emits a spurious 'crclr cr1eq' before every implicit-decl call.
That extra instruction shifts alignment for everything after it, wrecking match
rates. Adding a correct prototype removes the crclr.

Signatures are inferred from the callee's disassembly (arg registers read in
the prologue). An edit is kept only if the match count improves, so wrong
guesses never make things worse.

Usage (run slices in parallel, 8 slices typical):
    python3 tools/fix_crclr_protos.py 0 8
    ...
    python3 tools/fix_crclr_protos.py 7 8

Results M5.34: 2744 candidate drafts, 92% had extra crclr; 10 became EXACT
(80015B94 8018CD3C 80195124 80015DE4 8013A9D0 8019519C 80224B70 80195214
800561B4 8001AD50) and several others improved.
"""
import re, sys, glob
sys.path.insert(0, 'tools')
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.skipdata = True

calls = re.compile(r'\bfn_([0-9A-F]{8})\s*\(')
# A real prototype has a return type before fn_: `void fn_X(...);` or
# `s32 fn_X(...);`. The old bare `\bfn_...` form ALSO matched call statements
# `fn_X(...);`, so every call site was counted as "already declared" and the
# candidate set (called-but-undeclared) collapsed to empty.
protos = re.compile(
    r'\b(?:unsigned\s+|signed\s+)?'
    r'(?:void|s32|u32|s16|u16|s8|u8|f32|f64|char|int|short|long|float|double|bool)'
    r'(?:\s*\*)*\s*fn_([0-9A-F]{8})\s*\([^;]*\)\s*;')

sizes = {}
for line in open('config/G2TE52/symbols.txt'):
    # Parse EVERY function symbol, not just fn_-prefixed ones: renamed
    # functions (ScriptWeatherSetRainHeight etc.) have their size listed
    # under a non-fn_ name, and the old `^fn_` filter silently skipped them
    # (match_count returned None -> candidate never even checked).
    m = re.match(r'^\S+ = \.text:0x([0-9A-Fa-f]{8}); // type:function size:0x([0-9A-Fa-f]+)', line)
    if m:
        sizes[int(m.group(1), 16)] = int(m.group(2), 16)


def callee_sig(addr, maxn=24):
    """Infer (n_int_args, n_float_args) by scanning the callee's prologue for
    reads of r3..r10 / f1..f8 that happen before the register is written."""
    sz = sizes.get(addr)
    if not sz:
        return None
    b = bytes(gl.d[gl.t_off + (addr - gl.t_addr):gl.t_off + (addr - gl.t_addr) + min(sz, 0x60)])
    insns = list(md.disasm(b, addr))
    written = set()
    fwritten = set()
    read = set()
    fread = set()
    for ins in insns[:maxn]:
        op = ins.op_str
        dst = None
        srcs = []
        if ins.mnemonic in ('mr', 'or'):
            parts = op.split(',')
            if len(parts) >= 2:
                dst = parts[0].strip().lower()
                srcs = [parts[1].strip().lower()]
        elif ins.mnemonic.startswith('lwz') or ins.mnemonic.startswith('lhz') or \
             ins.mnemonic.startswith('lbz') or ins.mnemonic.startswith('lha') or \
             ins.mnemonic.startswith('lfs') or ins.mnemonic.startswith('lfd') or \
             ins.mnemonic.startswith('lfsu') or ins.mnemonic.startswith('lfdu'):
            m2 = re.match(r'(f?r\d+)\s*,\s*\S+\((r\d+)\)', op)
            if m2:
                dst = m2.group(1).lower()
                srcs = [m2.group(2).lower()]
        elif ins.mnemonic.startswith('addi') or ins.mnemonic.startswith('addis') or \
             ins.mnemonic.startswith('mulli') or ins.mnemonic.startswith('subi') or \
             ins.mnemonic.startswith('rlwinm'):
            m2 = re.match(r'(r\d+)\s*,\s*(r\d+)', op)
            if m2:
                dst = m2.group(1).lower()
                srcs = [m2.group(2).lower()]
        elif ins.mnemonic.startswith('stw') or ins.mnemonic.startswith('stfd') or \
             ins.mnemonic.startswith('stfs') or ins.mnemonic.startswith('sth') or \
             ins.mnemonic.startswith('stb'):
            m2 = re.match(r'(f?r\d+)\s*,\s*\S+\((r\d+)\)', op)
            if m2:
                srcs = [m2.group(1).lower(), m2.group(2).lower()]
                dst = None
        elif ins.mnemonic in ('cmpw', 'cmpwi', 'cmplw', 'cmplwi'):
            srcs = [r.lower() for r in re.findall(r'[fr]\d+', op)]
            dst = None
        else:
            continue
        # Sources are read BEFORE the destination is written, so check them
        # first. This matters for self-read ops like `lwz r3, 0x40(r3)` (load a
        # field from the object passed in arg0) and `addi r3, r3, imm` — with
        # the old order the dest was already in `written`, so the arg register
        # was silently dropped from `read` and the callee looked like it took
        # 0 args.
        for s in srcs:
            if s.startswith('r') and s not in written:
                read.add(s)
            elif s.startswith('f') and s not in fwritten:
                fread.add(s)
        if dst:
            if dst.startswith('r'):
                written.add(dst)
            else:
                fwritten.add(dst)
    nint = 0
    nflt = 0
    for r in read:
        num = int(r[1:])
        if 3 <= num <= 10:
            nint = max(nint, num - 2)
    for r in fread:
        num = int(r[1:])
        if 1 <= num <= 8:
            nflt = max(nflt, num)
    return (nint, nflt)


def count_call_args(text, fnaddr):
    """Max arg count across all call sites of fnaddr in the body."""
    best = 0
    for m in calls.finditer(text):
        if m.group(1) != fnaddr:
            continue
        i = m.end() - 1
        depth = 0
        j = i
        while j < len(text):
            if text[j] == '(':
                depth += 1
            elif text[j] == ')':
                depth -= 1
                if depth == 0:
                    break
            j += 1
        args = text[i + 1:j].strip()
        if not args:
            n = 0
        else:
            d = 0
            n = 1
            for ch in args:
                if ch == '(':
                    d += 1
                elif ch == ')':
                    d -= 1
                elif ch == ',' and d == 0:
                    n += 1
        best = max(best, n)
    return best


def build_proto(fnaddr, nint, nflt):
    parts = ['f32'] * nflt + ['void *'] * nint
    return 's32 fn_%08X(%s);' % (fnaddr, ', '.join(parts) if parts else 'void')


def load_body(ADDR):
    text = open('src/wip/fn_%08X.c' % ADDR).read()
    return text


def match_count(ADDR, body):
    sz = sizes.get(ADDR, 0)
    if not sz:
        return None
    got, masks = gl.compile_fn(ADDR, body)
    if got is None:
        return None
    WANT = bytes(gl.d[gl.t_off + (ADDR - gl.t_addr):gl.t_off + (ADDR - gl.t_addr) + sz])
    n = min(sz // 4, len(got) // 4)
    hit = 0
    for i in range(n):
        m = (masks or {}).get(i * 4, 0xFFFFFFFF)
        w = int.from_bytes(WANT[i * 4:(i + 1) * 4], 'big')
        g = int.from_bytes(got[i * 4:(i + 1) * 4], 'big')
        if (w & m) == (g & m):
            hit += 1
    return (hit, n)


def main():
    slice_idx = int(sys.argv[1])
    num_slices = int(sys.argv[2])
    candidates = []
    for fp in sorted(glob.glob('src/wip/fn_*.c')):
        text = open(fp).read()
        declared = set(protos.findall(text))
        used = set(calls.findall(text))
        name = fp.split('/')[-1][3:11].upper()
        missing = used - declared - {name}
        if missing:
            candidates.append(fp)
    mine = candidates[slice_idx::num_slices]
    print('slice %d/%d: %d candidates' % (slice_idx, num_slices, len(mine)))
    improved = 0
    kept = 0
    for fp in mine:
        ADDR = int(fp.split('/')[-1][3:11], 16)
        text = load_body(ADDR)
        if '#include' in text:
            rest = text.split('#include', 1)[1]
            rest = '#include' + rest
        else:
            # draft without an include line: process its comment-stripped text
            rest = text
        body = '\n'.join(l for l in rest.splitlines() if not l.startswith('//') and 'types.h' not in l)
        before = match_count(ADDR, body)
        protos_to_add = []
        for fnaddr in sorted(set(calls.findall(text))):
            sig = callee_sig(int(fnaddr, 16))
            if sig is None:
                continue
            nint, nflt = sig
            calln = count_call_args(text, fnaddr)
            if calln > nint + nflt:
                nint = calln - nflt
            if nint + nflt == 0:
                continue
            protos_to_add.append(build_proto(int(fnaddr, 16), nint, nflt))
        if not protos_to_add:
            continue
        newbody = '\n'.join(protos_to_add) + '\n' + body
        after = match_count(ADDR, newbody)
        if before is None or after is None:
            continue
        bhit, bn = before
        ahit, an = after
        if ahit > bhit:
            text = open(fp).read()
            lines = text.split('\n')
            idx = -1
            for i, l in enumerate(lines):
                if l.startswith('#include'):
                    idx = i
            ins = '\n'.join(protos_to_add)
            if idx >= 0:
                lines.insert(idx + 1, ins)
            else:
                lines.insert(0, ins)
            open(fp, 'w').write('\n'.join(lines))
            kept += 1
            improved += 1
            print('%s: %d/%d -> %d/%d' % (fp.split('/')[-1], bhit, bn, ahit, an))
    print('slice done: improved/kept=%d' % improved)


main()
