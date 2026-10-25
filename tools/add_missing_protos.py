#!/usr/bin/env python3
"""Batch A/B: add missing callee prototypes to wip drafts.

For each draft: find callees (promoted fn_*) with no declaration in the
draft, insert their real prototypes after the last existing include, score,
keep only improvements. Addresses may be passed as args (hex, 0x optional);
default: all NEAR addresses found in /tmp/sweep3_*.log.
"""
import glob
import os
import re
import subprocess
import sys

SCORE = re.compile(r"score: (\d+)/(\d+) = ([\d.]+)%")


def sig_of(name):
    p = "src/%s.c" % name
    if not os.path.exists(p):
        return None
    t = open(p).read()
    m = re.search(r"^(\w[\w \t\*]*?)\s*\b%s\(([^)]*)\)\s*\{" % name, t, re.M)
    if not m:
        return None
    ret = m.group(1).strip()
    params = []
    for a in m.group(2).split(","):
        a = a.strip()
        if not a:
            continue
        a = re.sub(r"\s*\b\w+\s*$", "", a).strip()
        params.append(a or "s32")
    return "%s %s(%s);" % (ret, name, ", ".join(params))


def score(addr):
    r = subprocess.run(["tools/venv/bin/python", "tools/my_diff.py", "0x" + addr],
                       capture_output=True, text=True, timeout=240)
    m = SCORE.search(r.stdout)
    return (int(m.group(1)), int(m.group(2))) if m else None


def process(addr):
    p = "src/wip/fn_%s.c" % addr
    if not os.path.exists(p):
        return
    t = open(p).read()
    base = score(addr)
    if base is None or base[1] == 0 or base[0] >= base[1]:
        return
    callees = set(re.findall(r"\b(fn_[0-9A-F]{8})\s*\(", t))
    missing = []
    for c in sorted(callees):
        # already declared? a prototype ends in ';' before the body
        if not re.search(r"\b%s\s*\([^;{}]*\)\s*;" % c, t):
            s = sig_of(c)
            if s:
                missing.append(s)
    if not missing:
        return
    # insert after the last #include line in the file
    lines = t.rstrip("\n").split("\n")
    inc = [i for i, l in enumerate(lines) if l.startswith("#include")]
    if not inc:
        return
    last_inc = max(inc)
    lines[last_inc + 1:last_inc + 1] = missing
    t2 = "\n".join(lines) + "\n"
    open(p, "w").write(t2)
    new = score(addr)
    if new and new[0] / new[1] > base[0] / base[1]:
        print("%s: %d/%d -> %d/%d KEEP (+%d protos)" % (addr, base[0], base[1], new[0], new[1], len(missing)))
    else:
        open(p, "w").write(t)
        print("%s: %d/%d -> %s revert (%d protos)" % (addr, base[0], base[1], new, len(missing)))


def main():
    if len(sys.argv) > 1:
        addrs = [a.replace("0x", "").replace("0X", "").upper() for a in sys.argv[1:]]
    else:
        addrs = set()
        for log in glob.glob("/tmp/sweep3_*.log"):
            for m in re.finditer(r"NEAR\s+m2c\s+0x([0-9A-F]{8})", open(log).read()):
                addrs.add(m.group(1))
        addrs = sorted(addrs)
    for a in addrs:
        try:
            process(a)
        except Exception as e:
            print(a, "ERR", str(e)[:80])


if __name__ == "__main__":
    main()
