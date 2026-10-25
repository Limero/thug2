#!/usr/bin/env python3
"""Item-17/25/26 batch: widen calls missing leading passthrough args.

Uses the fixed self-read-aware callee_sig to detect callees that read more
int args than a call site passes. For each short call, tries prepending the
wrapper's own params (arg0, then arg0+arg1) to fill the gap, keeping only the
variant that raises the word-match count. Idempotent; safe to re-run.

Covers:
  - 0-arg call to a >=1-arg callee -> fn_XXXX(arg0[, arg1])  (item 26)
  - 1-arg call to a >=2-arg callee -> fn_XXXX(arg0, <a>)     (item 25/17)
  - 2-arg call to a >=3-arg callee -> fn_XXXX(arg0, <a>, <b>)

Usage:
    python3 tools/fix_missing_args.py 0 8
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


def call_sites(text):
    """Return list of (fnaddr, open_paren_index) for all fn_XXXX( call sites."""
    out = []
    for m in calls.finditer(text):
        out.append((m.group(1), m.end() - 1))
    return out


def call_arg_count(text, pos):
    """pos = index of '(' ; return count of top-level args (0 for empty)."""
    depth = 0
    j = pos + 1
    n = 1
    while j < len(text):
        c = text[j]
        if c == '(':
            depth += 1
        elif c == ')':
            if depth == 0:
                break
            depth -= 1
        elif c == ',' and depth == 0:
            n += 1
        j += 1
    k = pos + 1
    while k < j and text[k] in ' \t\n':
        k += 1
    if k == j:
        return 0
    return n


def wrapper_params(text):
    """Return the list of wrapper param names present (arg0, arg1, ...)."""
    params = []
    for name in ('arg0', 'arg1', 'arg2', 'arg3'):
        if re.search(r'\b%s\b' % name, text):
            params.append(name)
        else:
            break
    return params


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


def prepend_at(text, pos, params):
    """Return a new text with `params` (joined by ', ') inserted right after
    the '(' at pos. Assumes the existing args (if any) follow; we always
    prepend, so the caller must choose the right params to FILL the gap."""
    k = pos + 1
    while k < len(text) and text[k] in ' \t\n':
        k += 1
    if k < len(text) and text[k] == ')':
        # zero args -> insert params
        return text[:k] + ', '.join(params) + text[k:]
    # non-zero args -> insert params + ', '
    return text[:pos + 1] + ', '.join(params) + ', ' + text[pos + 1:]


def main():
    slice_idx = int(sys.argv[1])
    num_slices = int(sys.argv[2])
    candidates = []
    for fp in sorted(glob.glob('src/wip/fn_*.c')):
        text = open(fp).read()
        if 'family=stub' in text or 'family=tp' in text:
            continue
        params = wrapper_params(text)
        if not params:
            continue
        for addr, pos in call_sites(text):
            sig = callee_sig(int(addr, 16))
            if not sig:
                continue
            want = sig[0]
            if want < 1:
                continue
            got = call_arg_count(text, pos)
            if got < want:
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
        params = wrapper_params(text)
        best = before
        best_text = text
        for addr, pos in call_sites(text):
            sig = callee_sig(int(addr, 16))
            if not sig:
                continue
            want = sig[0]
            if want < 1:
                continue
            got = call_arg_count(text, pos)
            gap = want - got
            if gap <= 0:
                continue
            # try filling the gap with leading params (up to available)
            fill = params[:gap]
            for n in range(1, len(fill) + 1):
                newtext = prepend_at(text, pos, fill[:n])
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
