#!/usr/bin/env python3
"""Add a missing leading unused arg0 to function DEFINITIONS.

m2c drops an unused leading arg0: a Script handler `void fn(arg0, arg1)` that
only reads arg1 is emitted as `void fn(void *arg1)`. The wrapper then loads
arg1 from r3, but WANT reads it from r4 (mr rX, r4), so the whole body shifts
by one register and nothing matches.

Detection: disassemble the WANT prologue and find the first arg register
(r3..r10) that is READ before it is WRITTEN. If it is r4 (not r3), the
function has 1 unused leading arg -> prepend `void *arg0, `. If r5, prepend
two, etc.

Usage (slices):
    python3 tools/fix_missing_lead_arg0.py 0 8
"""
import re, sys, glob, os
sys.path.insert(0, 'tools')
import gen_leaves as gl
from capstone import CS_ARCH_PPC, CS_MODE_BIG_ENDIAN, Cs

md = Cs(CS_ARCH_PPC, CS_MODE_BIG_ENDIAN)
md.skipdata = True

sizes = {}
for line in open('config/G2TE52/symbols.txt'):
    m = re.match(r'^\S+ = \.text:0x([0-9A-Fa-f]{8}); // type:function size:0x([0-9A-Fa-f]+)', line)
    if m:
        sizes[int(m.group(1), 16)] = int(m.group(2), 16)


def first_read_arg(addr, maxn=16):
    """Return the lowest arg register (r3=1, r4=2, ...) read in the prologue
    before being written; None if no arg is read."""
    sz = sizes.get(addr)
    if not sz:
        return None
    b = bytes(gl.d[gl.t_off + (addr - gl.t_addr):gl.t_off + (addr - gl.t_addr) + min(sz, 0x60)])
    written = set()
    for ins in md.disasm(b, addr):
        if ins.address >= addr + maxn * 4:
            break
        op = ins.op_str
        dst = None
        srcs = []
        if ins.mnemonic in ('mr', 'or', 'or.'):
            parts = op.split(',')
            if len(parts) >= 2:
                dst = parts[0].strip().lower()
                srcs = [parts[1].strip().lower()]
        elif ins.mnemonic[:3] in ('lwz', 'lhz', 'lbz', 'lha', 'lfs', 'lfd', 'lfsu', 'lfdu'):
            m2 = re.match(r'(f?r\d+)\s*,\s*\S+\((r\d+)\)', op)
            if m2:
                dst = m2.group(1).lower()
                srcs = [m2.group(2).lower()]
        elif ins.mnemonic[:4] in ('addi', 'addis', 'mulli', 'subi', 'rlwinm'):
            m2 = re.match(r'(r\d+)\s*,\s*(r\d+)', op)
            if m2:
                dst = m2.group(1).lower()
                srcs = [m2.group(2).lower()]
        elif ins.mnemonic[:3] in ('stw', 'stfd', 'stfs', 'sth', 'stb'):
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
                num = int(s[1:])
                if 3 <= num <= 10:
                    return num - 2  # r3 -> 1, r4 -> 2, ...
        if dst and dst.startswith('r'):
            written.add(dst)
    return None


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


# function-definition line:  rettype Name(...) {
fndef = re.compile(r'^([A-Za-z_][A-Za-z0-9_ *]*\s+)?([A-Za-z_][A-Za-z0-9_]*)\s*\(([^)]*)\)\s*\{')


def param_count(params):
    params = params.strip()
    if not params or params == 'void':
        return 0
    d = 0
    n = 1
    for ch in params:
        if ch == '(':
            d += 1
        elif ch == ')':
            d -= 1
        elif ch == ',' and d == 0:
            n += 1
    return n


def main():
    slice_idx = int(sys.argv[1])
    num_slices = int(sys.argv[2])
    files = sorted(glob.glob('src/wip/fn_*.c'))
    mine = files[slice_idx::num_slices]
    improved = 0
    for fp in mine:
        ADDR = int(os.path.basename(fp)[3:11], 16)
        text = open(fp).read()
        nargs = first_read_arg(ADDR)
        if nargs is None or nargs <= 1:
            continue
        # find the function definition line
        m = None
        for line in text.splitlines():
            if not line.startswith('#') and not line.startswith('/') and not line.startswith('extern'):
                mm = fndef.match(line.strip())
                if mm:
                    m = mm
                    break
        if not m:
            continue
        ncur = param_count(m.group(3))
        # need nargs-1 leading unused args, but the signature already has ncur;
        # if the first read arg is argN (nargs), prepend (nargs - ncur) if ncur < nargs
        add = nargs - ncur
        if add <= 0:
            continue
        # only handle the common case: prepend `void *arg0, ` style unused args
        body = '\n'.join(l for l in text.splitlines() if not l.startswith('//'))
        before = match_count(ADDR, body)
        if before is None:
            continue
        # build new param list: prepend `void *argN` placeholders
        newparams = ', '.join(['void *arg%d' % i for i in range(add)]) 
        oldparams = m.group(3).strip()
        if oldparams:
            newparams = newparams + (', ' + oldparams if oldparams else '')
        newline = line.strip().replace(m.group(3), newparams, 1)
        newtext = text.replace(line.strip(), newline, 1)
        newbody = '\n'.join(l for l in newtext.splitlines() if not l.startswith('//'))
        after = match_count(ADDR, newbody)
        if after is None:
            continue
        bhit, bn = before
        ahit, an = after
        if ahit > bhit:
            open(fp, 'w').write(newtext)
            improved += 1
            print('%s: %d/%d -> %d/%d (added %d leading arg)' % (os.path.basename(fp), bhit, bn, ahit, an, add))
    print('slice done: improved=%d' % improved)


if __name__ == '__main__':
    main()
