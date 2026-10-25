#!/usr/bin/env python3
"""Item-26 batch: 0-arg calls to callees that actually read args.

The fixed callee_sig (self-read aware, see fix_crclr_protos.py) can now
reliably detect callees that read r3 (arg0) via `lwz rX, off(r3)` etc. Many
wip drafts call such a callee with NO args (`fn_XXXX()`) when the original
actually passes the wrapper's own arg0 through — the classic item-26
save-order-flip trigger.

For each draft, find 0-arg call sites whose callee reads >=1 int arg, then
try widening the call to `fn_XXXX(arg0)` and keep only if the match count
improves. Idempotent; safe to re-run.

Usage (slices):
    python3 tools/fix_missing_arg0.py 0 8
"""
import re, sys, glob, os
sys.path.insert(0, 'tools')
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.skipdata = True

calls = re.compile(r'\bfn_([0-9A-F]{8})\s*\(')

sizes = {}
for line in open('config/G2TE52/symbols.txt'):
    m = re.match(r'^\S+ = \.text:0x([0-9A-Fa-f]{8}); // type:function size:0x([0-9A-Fa-f]+)', line)
    if m:
        sizes[int(m.group(1), 16)] = int(m.group(2), 16)


def callee_sig(addr, maxn=24):
    """Infer (n_int_args, n_float_args) from the callee prologue.

    Sources are checked BEFORE the dest is marked written, so self-read ops
    like `lwz r3, 0x40(r3)` count r3 as a read arg.
    """
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
            p = op.split(',')
            if len(p) >= 2:
                dst = p[0].strip().lower()
                srcs = [p[1].strip().lower()]
        elif ins.mnemonic[:3] in ('lwz', 'lhz', 'lbz', 'lha') or \
             ins.mnemonic[:3] in ('lfs', 'lfd') or ins.mnemonic[:4] in ('lfsu', 'lfdu'):
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


def zero_arg_call_sites(text):
    """Return list of (fnaddr, char_pos) for `fn_XXXX()` zero-arg call sites."""
    out = []
    for m in calls.finditer(text):
        addr = m.group(1)
        i = m.end() - 1  # position of '('
        j = i + 1
        # skip whitespace to see if it's immediately ')'
        while j < len(text) and text[j] in ' \t':
            j += 1
        if j < len(text) and text[j] == ')':
            out.append((addr, i))
    return out


def has_arg0(text):
    # function signature contains an arg0 parameter
    return re.search(r'\barg0\b', text) is not None


def match_count(addr, body):
    sz = sizes.get(addr, 0)
    if not sz:
        return None
    got, masks = gl.compile_fn(addr, body)
    if got is None:
        return None
    WANT = bytes(gl.d[gl.t_off + (addr - gl.t_addr):gl.t_off + (addr - gl.t_addr) + sz])
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
        if 'family=stub' in text or 'family=tp' in text:
            continue
        if not has_arg0(text):
            continue
        zc = zero_arg_call_sites(text)
        if not zc:
            continue
        # any callee that reads >=1 int arg
        for addr, pos in zc:
            sig = callee_sig(int(addr, 16))
            if sig and sig[0] >= 1:
                candidates.append(fp)
                break
    mine = candidates[slice_idx::num_slices]
    print('slice %d/%d: %d candidates' % (slice_idx, num_slices, len(mine)))
    improved = 0
    for fp in mine:
        ADDR = int(os.path.basename(fp)[3:11], 16)
        text = open(fp).read()
        body = '\n'.join(l for l in text.splitlines() if not l.startswith('//') and 'types.h' not in l)
        before = match_count(ADDR, body)
        if before is None:
            continue
        # try widening each 0-arg call to (arg0), one at a time, keep best
        best = before
        best_text = text
        zc = zero_arg_call_sites(text)
        for addr, pos in zc:
            sig = callee_sig(int(addr, 16))
            if not sig or sig[0] < 1:
                continue
            # replace 'fn_XXXX()' with 'fn_XXXX(arg0)' at this position
            # find the full call text
            j = pos + 1
            while j < len(text) and text[j] in ' \t':
                j += 1
            # text[j] == ')'
            newtext = text[:j] + 'arg0' + text[j:]
            newbody = '\n'.join(l for l in newtext.splitlines() if not l.startswith('//') and 'types.h' not in l)
            after = match_count(ADDR, newbody)
            if after is not None and after[0] > best[0]:
                best = after
                best_text = newtext
        if best[0] > before[0]:
            open(fp, 'w').write(best_text)
            improved += 1
            print('%s: %d/%d -> %d/%d' % (os.path.basename(fp), before[0], before[1], best[0], best[1]))
    print('slice done: improved=%d' % improved)


main()
