#!/usr/bin/env python3
"""M8.31 CALLEE RETURN-TYPE flip sweep, corpus-wide.

A draft whose residual is a call-arg-setup ORDER diff (doc-15) is often
fixed by declaring the called function with the other return type: making
a call's result dead (`void`) or live (`s32`) changes the ready-list order
and therefore where the arg0 `mr` lands relative to a constant's
`lis`/`ori` completion.  Verified on 0x80195668 (AddChecksum s32->void,
97.9% -> EXACT) and on 0x80188BBC / 0x80188FA8 (s32->void, M8.31).

Unlike tools/rt_sweep.py this walks EVERY callee prototype in the file
(one at a time, so a win is attributable) and tries both directions, so
a draft that was previously probed with only ONE of the two types is
re-covered.

usage:  rt2_sweep.py <file> [<file> ...]
prints: <file>\t<pct>\t<proto>\t<from>-><to>\t<verdict>
"""
import os
import re
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import test_wip_drafts as T  # noqa: E402

PROTO = re.compile(
    r"^(extern\s+)?(s32|u32|int|long|void|f32|float|double|f64|s16|u16|s8|u8)"
    r"(\s+\**)(\w+)\(([^;]*)\);\s*$")


def variants(body):
    """yield (label, new_body) for every single return-type flip"""
    lines = body.split("\n")
    for i, l in enumerate(lines):
        m = PROTO.match(l)
        if not m:
            continue
        ext, typ, star, name, args = m.groups()
        for new in ("void", "s32"):
            if new == typ:
                continue
            out = list(lines)
            out[i] = f"{ext or ''}{new}{star}{name}({args});"
            yield (f"{name}:{typ}->{new}", "\n".join(out))


def main(paths):
    tmp = tempfile.mkdtemp(prefix="rt2_")
    os.environ["LEAF_TMPDIR"] = tmp
    for fn in paths:
        p = os.path.join(ROOT, "src/wip", fn)
        if not os.path.exists(p):
            continue
        raw = open(p).read()
        body = "\n".join(x for x in raw.splitlines()
                         if not x.lstrip().startswith("//"))
        flags = T.gl.draft_flags(raw)
        addr = int(fn[3:-2], 16)
        try:
            st, pct0, _ = T.test_one(addr, body, extra_flags=flags or None)
        except Exception:  # noqa: BLE001
            continue
        best = (pct0, "-", "-", st)
        for label, src in variants(body):
            try:
                st2, pct, _ = T.test_one(addr, src, extra_flags=flags or None)
            except Exception:  # noqa: BLE001
                continue
            if pct > best[0] + 1e-9:
                best = (pct, label.split(":")[0], label, st2)
        if best[0] > pct0 + 1e-9:
            print(f"{fn}\t{pct0:.2f}\t{best[1]}\t{best[2]}\t{best[0]:.2f} "
                  f"{best[3]}", flush=True)
        else:
            print(f"{fn}\t{pct0:.2f}\t-\t-\t{pct0:.2f} {st}", flush=True)


if __name__ == "__main__":
    main(sys.argv[1:])
