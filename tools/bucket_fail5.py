#!/usr/bin/env python3
"""Bucket the remaining compile-FAIL drafts by error category."""
import sys, os, re
sys.path.insert(0, 'tools')
import gen_leaves as gl
from collections import Counter

addrs = [int(l.strip(), 16) for l in open('/tmp/fail4.txt') if l.strip()]
addrs = [a for a in addrs if os.path.isfile('src/wip/fn_%08X.c' % a)]
print('remaining FAIL with files:', len(addrs))

buckets = Counter()
examples = {}
for a in addrs:
    fp = 'src/wip/fn_%08X.c' % a
    srclines = open(fp).read().splitlines()
    body = '\n'.join(l for l in srclines if not l.startswith('//') and 'types.h' not in l).strip()
    got, err = gl.compile_fn(a, body)
    if got is not None:
        buckets['NOW-COMPILES'] += 1
        continue
    errs = []
    for ln in (err or '').splitlines():
        m = re.match(r'^([^:]+):(\d+): (.*)', ln.strip())
        if not m or 'warning' in ln or 'In ' in ln:
            continue
        lineno = int(m.group(2))
        msg = m.group(3).strip()
        src = srclines[lineno + 3].strip() if lineno + 3 <= len(srclines) else '?'
        errs.append((msg, src))
    if not errs:
        # GCC 2.95 emits "fn_X.c:LINE:" then "parse error before..." on NEXT line
        lines = (err or '').splitlines()
        for i, ln in enumerate(lines):
            if re.match(r'^[^:]+:\d+:', ln.strip()) and 'warning' not in ln and 'In ' not in ln:
                lineno = int(ln.split(':')[1])
                msg = ln.split(':', 2)[-1].strip()
                src = srclines[lineno + 3].strip() if lineno + 3 <= len(srclines) else '?'
                errs.append((msg, src))
    if not errs:
        buckets['UNPARSEABLE'] += 1
        continue
    msg, src = errs[0]
    # categorize
    key = msg[:60]
    if 'parse error' in msg or 'parse error before' in msg:
        key = 'PARSE: ' + src[:60]
    elif 'undeclared' in msg:
        key = 'UNDECLARED: ' + src[:60]
    elif 'called object' in msg:
        key = 'CALLED-OBJECT: ' + src[:60]
    elif 'not a structure' in msg or 'member' in msg:
        key = 'MEMBER: ' + src[:60]
    elif 'incompatible' in msg:
        key = 'INCOMPATIBLE: ' + src[:60]
    elif 'invalid' in msg:
        key = 'INVALID: ' + src[:60]
    buckets[key] += 1
    examples.setdefault(key, []).append(a)
    if len(examples[key]) <= 2:
        pass

print()
for k, c in buckets.most_common(25):
    ex = ', '.join('0x%08X' % a for a in examples.get(k, [])[:2])
    print('%4d  %s   [%s]' % (c, k, ex))
