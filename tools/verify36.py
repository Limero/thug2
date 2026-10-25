#!/usr/bin/env python3
"""Verify postprocessor fixes: run disasm->m2c->postprocess->compile on known-FAIL addresses."""
import sys, re, os

sys.path.insert(0, 'tools')
import gen_leaves as gl
import fill_wip_drafts as fw

addrs = [
    0x8008076C, 0x801596D4, 0x80187A98, 0x8000E104, 0x80014150, 0x8028C448,
    0x80134844, 0x80254CEC, 0x80042180, 0x8012935C, 0x800FE19C, 0x8015B314,
    0x8004A4D8, 0x80193678, 0x8001F738, 0x801F76E4, 0x800A0564, 0x80262780,
    0x8024402C, 0x8024DD84, 0x80017128, 0x801367D8, 0x80034030, 0x8017E398,
    0x80269D80, 0x80038094, 0x8005A3AC, 0x8008BA68, 0x802822CC, 0x80262FD8,
    0x80018834, 0x8001F0F8, 0x8001F164, 0x80159078, 0x8026B0E0, 0x80042110,
]

ok = fail = 0
fail_list = []
for a in addrs:
    fp = 'src/wip/fn_%08X.c' % a
    if not os.path.isfile(fp):
        print('0x%08X: NO FILE' % a)
        continue
    text = open(fp).read()
    m = re.search(r'size=(\d+)B', text)
    if not m:
        print('0x%08X: NO SIZE' % a)
        continue
    size = int(m.group(1))
    asm_lines, _ = fw.disasm_with_labels(a, size)
    raw = fw.run_m2c('\n'.join(asm_lines) + '\n')
    if raw is None:
        print('0x%08X: m2c FAILED' % a)
        fail += 1
        fail_list.append(a)
        continue
    body = fw.postprocess(raw)
    got, err = gl.compile_fn(a, body)
    if got is not None:
        ok += 1
        print('0x%08X: OK' % a)
    else:
        fail += 1
        fail_list.append(a)
        print('0x%08X: FAIL  %s' % (a, (err or '').strip().splitlines()[:1]))

print()
print('RESULT: %d OK, %d FAIL' % (ok, fail))
if fail_list:
    print('FAILS:', ' '.join('0x%08X' % a for a in fail_list))
