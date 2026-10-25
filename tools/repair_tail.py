#!/usr/bin/env python3
"""Per-function repair for the unique FAIL tail.

WIP drafts aren't in the build — a compiling non-matching draft is strictly
better than a FAIL. These repairs only need to make it COMPILE.

Usage: repair_tail.py --addr-file F [--apply]
"""
import os, re, subprocess, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_leaves as gl


def compile_draft(a, body):
    fname = 'fn_%08X' % a
    sp = '/tmp/leaf/%s.c' % fname
    with open(sp, 'w') as f:
        f.write('#include "types.h"\n' + body)
    env = dict(os.environ)
    env['SN_NGC_PATH'] = gl.C_DIR
    return subprocess.run(
        [gl.WIBO, f'{gl.C_DIR}/ngccc.exe', '-O2', '-G0', '-mcpu=750', '-fno-common',
         '-I', f'{gl.ROOT}/include', '-c', sp, '-o', '/tmp/leaf/%s.o' % fname],
        cwd=gl.ROOT, capture_output=True, text=True, env=env)


def body_lines(text):
    return '\n'.join(l for l in text.splitlines()
                     if not l.startswith('//') and 'types.h' not in l).strip().split('\n')


PASSES = [
    # (name, pattern, repl, count)
    # void* index var in deref sum: *((s32 *)X + var_rN) -> *((s32 *)X + (s32)var_rN)
    (r"\*\*\(s32 \*\*\*\)\s*\*", r"", 0),
]


def repair(body):
    """Apply compile-only rewrites; return new body."""
    # 1. void*-typed index var inside a deref/cast sum
    body = re.sub(r"\+\s*(var_r\d+)\b(?=\s*[)]) ", lambda m: f"+ (s32){m.group(1)}", body)
    # *((s32 *)X + var_rN) / *((s32 *)*(s32 *)(..) + var_rN): cast the index
    body = re.sub(r"\*\(\*\(s32 \*\*\)\) ", r"", body)
    body = re.sub(r"\+\s*(var_r\d+)\b", r"+ (s32)\1", body)
    body = re.sub(r"-\s*(var_r\d+)\b", r"- (s32)\1", body)
    # 2. ptr - ptr (byte offsets): ((temp_r5 + 1) - var_r6) -> ((temp_r5 + 1) - (s32)var_r6)
    body = re.sub(r"\((\w+ [+-] [^()]*)\) \- (var_\w+|temp_\w+)\b", r"(\1) - (s32)\2", body)
    body = re.sub(r"\(([^()]*) [+-] (var_\w+|temp_\w+)\b\)", lambda m: f"({m.group(1)} - (s32){m.group(2)})" if '-' in m.group(0) else f"({m.group(1)} + (s32){m.group(2)})", body)
    # 3. f32 deref used in bitwise op: *(f32 *)X & M -> *(s32 *)X & M
    body = re.sub(r"\(f32 \*\)\(([^)]*)\)(&|[|^])", r"(s32 *)(\1)\2", body)
    # 4. unary * on a parenthesized int sum: *(((arg0 * 4) & 0x3FFC) + P) -> *((s32 *)((..)))
    body = re.sub(r"\*\(\*\(\(\w+ \* 4\)[^)]*\) \+ \*?\(s32 \*\)0x[0-9A-Fa-f]+\)",
                  lambda m: f"*((s32 *)({m.group(0)[2:-1]}))", body)
    # *0 constant deref
    body = re.sub(r"\*\s*\(?0\)?\b(?!x)", r"*((s32 *)0)", body)
    # 5. *(arg0 + N) where arg0 is void*: *((s32 *)(arg0 + N))
    body = re.sub(r"\*\((arg\d+) \+ ([^)]*)\)", r"*((s32 *)(\1 + \2))", body)
    # 6. **var_rN deref of deref (s16 store): **var_r9 -> *((s16 *)var_r9)
    body = re.sub(r"\*\*(var_\w+)\b", lambda m: f"*((s16 *){m.group(1)})", body)
    # 7. (void *) cast of a float/int expr in an assignment: (void *)(X) -> (void *)(s32)(X)
    body = re.sub(r"\(void \*\)\s*\(\(?f32\)?\s*\*?\(?", lambda m: "(void *)(s32)(", body)
    body = re.sub(r"= \(void \*\) \(?", "= (void *)(s32)", body)
    # 8. f32 ptr cast to char* deref: (char *)*(f32 *)X -> (char *)(s32)*(s32 *)X
    body = re.sub(r"\(char \*\)\*?\(?f32 \*?\)?\s*\*?\(?", lambda m: "(char *)(s32)*(s32 *)(", body)
    # 9. ptr == float compare: temp_r4 == *((f32 *)&sp1C) -> (s32) cast one side
    body = re.sub(r"(\w+) == \*\(\(f32 \*\)([^)]*)\)", r"(s32)\1 == (s32)*((f32 *)\2)", body)
    # 10. ptr & mask: (temp_r3 + 0x2F) & 0xFFFFFFE0 with ptr -> ((s32)temp_r3 + 0x2F) & M
    body = re.sub(r"\(\b(temp_\w+)\b \+ (0x[0-9A-Fa-f]+)\) & (0x[0-9A-Fa-f]+)", r"((s32)\1 + \2) & \3", body)
    # 11. (arg0 - 0xADDR) / N with ptr arg -> ((s32)arg0 - 0xADDR) / N
    body = re.sub(r"\((arg\d+) - (0x[0-9A-Fa-f]+)\) \/ (\d+)", r"((s32)\1 - \2) / \3", body)
    # 12. (sp - N) - var -> ((s32)sp - N) - (s32)var
    body = re.sub(r"\(sp - (0x[0-9A-Fa-f]+)\) - (var_\w+)\b", r"((s32)sp - \1) - (s32)\2", body)
    # 13. duplicate case value: drop second identical case label
    lines = body.split('\n')
    seen = set()
    out = []
    for ln in lines:
        m = re.match(r'^(\s*)case (0x[0-9A-Fa-f]+|[0-9]+):', ln)
        if m and m.group(2) in seen:
            out.append(m.group(1) + ';')  # neutralize duplicate
            continue
        if m:
            seen.add(m.group(2))
        out.append(ln)
    body = '\n'.join(out)
    return body


def main():
    apply_ = '--apply' in sys.argv
    addr_set = {int(l.strip(), 16) for l in open(sys.argv[sys.argv.index('--addr-file') + 1]) if l.strip()}
    fixed = already = 0
    still = []
    for a in sorted(addr_set):
        fp = 'src/wip/fn_%08X.c' % a
        if not os.path.isfile(fp):
            continue
        text = open(fp).read()
        lines = body_lines(text)
        body = '\n'.join(lines)
        r = compile_draft(a, body)
        if r.returncode == 0:
            already += 1
            continue
        new = repair(body)
        if new != body:
            r2 = compile_draft(a, new)
            if r2.returncode == 0:
                fixed += 1
                if apply_:
                    header = [l for l in text.splitlines() if l.startswith('//')]
                    open(fp, 'w').write('\n'.join(header) + '\n#include "types.h"\n' + new + '\n')
                continue
        still.append(a)
    print(f'=== fixed {fixed}, already {already}, still failing {len(still)} ===')
    if still:
        print('still:', ' '.join('0x%08X' % a for a in still[:40]))


if __name__ == '__main__':
    main()
