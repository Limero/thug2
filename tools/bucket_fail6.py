#!/usr/bin/env python3
"""Bucket ALL FAILs by real error (full stderr, not compile_fn's 200-char cut)."""
import sys, os, re, subprocess
sys.path.insert(0, 'tools')
import gen_leaves as gl
from collections import Counter, defaultdict

addrs = [int(l.strip(), 16) for l in open('/tmp/fail6.txt') if l.strip()]
addrs = [a for a in addrs if os.path.isfile('src/wip/fn_%08X.c' % a)]
print('FAIL with files:', len(addrs))

def full_compile(a, body):
    fname = 'fn_%08X' % a
    sp = '/tmp/leaf/%s.c' % fname
    with open(sp, 'w') as f:
        f.write('#include "types.h"\n' + body)
    env = dict(os.environ)
    env['SN_NGC_PATH'] = gl.C_DIR
    r = subprocess.run(
        [gl.WIBO, f'{gl.C_DIR}/ngccc.exe', '-O2', '-G0', '-mcpu=750', '-fno-common',
         '-I', f'{gl.ROOT}/include', '-c', sp, '-o', '/tmp/leaf/%s.o' % fname],
        cwd=gl.ROOT, capture_output=True, text=True, env=env)
    return r

def first_error(r):
    for ln in r.stderr.splitlines():
        if 'warning' in ln or 'In function' in ln or not ln.strip():
            continue
        m = re.match(r'^[^:]+:(\d+): (.*)', ln.strip())
        if m:
            return m.group(2).strip()
    return None

def key_of(msg):
    if 'not a structure' in msg or 'invalid type argument' in msg:
        return 'MEMBER/ARROW: ' + msg
    if 'too few arguments' in msg or 'too many arguments' in msg:
        return 'ARGCOUNT: ' + msg
    if 'label' in msg and 'not defined' in msg:
        return 'UNDEF-LABEL'
    if 'called object' in msg:
        return 'CALLED-OBJECT'
    if 'parse error' in msg:
        return 'PARSE'
    if 'undeclared' in msg:
        return 'UNDECLARED'
    if 'incompatible' in msg:
        return 'INCOMPATIBLE'
    if 'invalid' in msg:
        return 'INVALID'
    if 'cannot convert' in msg:
        return 'CANNOT-CONVERT'
    if 'void value' in msg:
        return 'VOID-VALUE'
    if 'duplicate' in msg or 'redefinition' in msg:
        return 'REDEF'
    return 'OTHER: ' + msg

buckets = defaultdict(list)
for a in addrs:
    fp = 'src/wip/fn_%08X.c' % a
    srclines = open(fp).read().splitlines()
    body = '\n'.join(l for l in srclines if not l.startswith('//') and 'types.h' not in l).strip()
    r = full_compile(a, body)
    if r.returncode == 0:
        buckets['COMPILES-OK'].append(a)
        continue
    msg = first_error(r)
    if not msg:
        buckets['NO-ERROR-LINE'].append(a)
        continue
    buckets[key_of(msg)].append(a)

for key, addrs in sorted(buckets.items(), key=lambda kv: -len(kv[1])):
    print(f'{len(addrs):3d}  {key}')
    print('      ' + ' '.join('0x%08X' % a for a in sorted(addrs)))
