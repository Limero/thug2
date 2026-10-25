#!/usr/bin/env python3
"""Show the EXACT erroring source lines of WIP drafts (compile as-is).

Compiles the draft file directly (comments + include intact) so compiler
line numbers == draft line numbers. Prints each error message with the
actual offending draft line.

Usage: errlines.py <0xADDR>... [--all] [--json]
"""
import os, re, subprocess, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl

JSON = '--json' in sys.argv


def compile_file(a):
    fp = 'src/wip/fn_%08X.c' % a
    fname = 'fn_%08X' % a
    sp = '/tmp/leaf/%s.c' % fname
    with open(sp, 'w') as f:
        f.write(open(fp).read())
    env = dict(os.environ)
    env['SN_NGC_PATH'] = gl.C_DIR
    return subprocess.run(
        [gl.WIBO, f'{gl.C_DIR}/ngccc.exe', '-O2', '-G0', '-mcpu=750', '-fno-common',
         '-I', f'{gl.ROOT}/include', '-c', sp, '-o', '/tmp/leaf/%s.o' % fname],
        cwd=gl.ROOT, capture_output=True, text=True, env=env)


def main():
    addrs = [int(t, 16) for t in sys.argv[1:] if t.startswith('0x')]
    if not addrs:
        print('usage: errlines.py <0xADDR>...')
        sys.exit(1)
    out = []
    for a in addrs:
        fp = 'src/wip/fn_%08X.c' % a
        if not os.path.isfile(fp):
            out.append({'a': '0x%08X' % a, 'error': 'NO-FILE'})
            continue
        r = compile_file(a)
        if r.returncode == 0:
            out.append({'a': '0x%08X' % a, 'error': 'COMPILES'})
            continue
        lines = open(fp).read().splitlines()
        errs = [l for l in r.stderr.splitlines() if 'warning' not in l and l.strip()]
        hits = []
        for e in errs:
            m = re.match(r'^[^:]+:(\d+):\s*(.*)$', e)
            if not m:
                continue
            ln = int(m.group(1))
            txt = lines[ln - 1] if 0 < ln <= len(lines) else '?'
            hits.append({'ln': ln, 'msg': m.group(2), 'txt': txt})
        out.append({'a': '0x%08X' % a, 'error': 'FAIL', 'hits': hits[:8]})
    if JSON:
        print(repr(out))
    else:
        for o in out:
            print('=== %s: %s ===' % (o['a'], o['error']))
            for h in o.get('hits', []):
                print('L%d: %s' % (h['ln'], h['msg']))
                print('     %s' % h['txt'].rstrip())


if __name__ == '__main__':
    main()
