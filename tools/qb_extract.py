#!/usr/bin/env python3
"""Extract plaintext symbol names from the inner compiled QB scripts packed
inside the Neversoft PRE archives (pre/*_scripts.prg).

The .prg "pre" archives (THUG2) are ring-buffer LZSS-compressed
containers — the format was determined empirically from the archive bytes:
header version word 0xabcd0003, 4096-byte ring buffer, max match length 18,
threshold 2 (the decoder below reproduces every archive entry exactly, and
the recovered names hash-validate against the DOL table). Each archive
holds a qdir.txt index plus the compiled .qb scripts of a level (or the
whole game, for pre/qb_scripts.prg — 209 scripts).

The compiled QB bytecode embeds each symbol reference it makes as a
\0x2B + u32(LE) hash + NUL-terminated plaintext name triple (the hash is
the Neversoft QB hash of the name — verified against tools/qb_hash.py).
Walking those triples (plus a printable-run fallback, mirroring the
levels/**/*.qb scan) yields the true script symbol names — VertStickerSlap
(0x89E8C244), WallPlant (0xCF74F6B7), trick names, param keys — that the
raw archive scan can never see because the payload is compressed.

Usage (probe):
    tools/venv/bin/python tools/qb_extract.py pre/qb_scripts.prg

Probe (importable):
    python -c "import qb_extract; print(qb_extract.extract('pre/qb_scripts.prg')[:5])"
"""
import argparse
import glob
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PRE_DIR = 'orig/G2TE52/disc/files/pre'
# every container that carries inner .qb scripts is named *_scripts.pr*;
# .prd/.prf/.prg are the three build variants of each archive.
ARCHIVE_GLOB = os.path.join(PRE_DIR, '*_scripts.pr*')

# LZSS decoder parameters, determined from the .pr* archive layout.
RING_BUFFER_SIZE = 4096
MATCH_LIMIT = 18          # F upper limit for match length
THRESHOLD = 2             # encode string into position and length

# name triple: 0x2B then u32(LE) QB hash then NUL-terminated plaintext
PAIR_OP = b'\x2b'

NAME_RE = re.compile(r'^[A-Za-z_][A-Za-z0-9_./\\\-\[\](){}<> ]{4,}$')


def decode_lzss(data):
    """Neversoft ring-buffer LZSS decompressor (format from the .pr* archives)."""
    text_buf = bytearray([0x20] * RING_BUFFER_SIZE)
    out = bytearray()
    r = RING_BUFFER_SIZE - MATCH_LIMIT
    flags = 0
    i = 0
    n = len(data)
    while True:
        flags >>= 1
        if (flags & 256) == 0:
            if i >= n:
                break
            flags = data[i] | 0xff00
            i += 1
        if flags & 1:
            if i >= n:
                break
            c = data[i]
            i += 1
            out.append(c)
            text_buf[r] = c
            r = (r + 1) & (RING_BUFFER_SIZE - 1)
        else:
            if i >= n:
                break
            oi = data[i]
            i += 1
            if i >= n:
                break
            oj = data[i]
            i += 1
            off = oi | ((oj & 0xf0) << 4)
            length = (oj & 0x0f) + THRESHOLD
            for k in range(length + 1):
                c = text_buf[(off + k) & (RING_BUFFER_SIZE - 1)]
                out.append(c)
                text_buf[r] = c
                r = (r + 1) & (RING_BUFFER_SIZE - 1)
    return bytes(out)


def _resolve(path):
    """Resolve repo-relative paths against ROOT when not found from the cwd."""
    if os.path.isabs(path) or os.path.exists(path):
        return path
    return os.path.join(ROOT, path)


def pre_entries(path):
    """Yield (name, data_size, comp_size, payload) for every PRE entry.

    Entry record layout (observed in the archive headers):
        +0  u32 data_size (uncompressed)
        +4  u32 compressed_data_size (0 = stored raw)
        +8  u16 name length (incl. NUL)
        +16 name, then payload (compressed unless comp_size == 0);
        records are 4-byte aligned.
    """
    data = open(_resolve(path), 'rb').read()
    num = struct.unpack_from('>I', data, 8)[0]
    p = 12
    for _ in range(num):
        data_size, comp_size, text_size = struct.unpack_from('>IIH', data, p)
        name = data[p + 16:p + 16 + text_size].split(b'\0')[0].decode('latin1', 'replace')
        actual = comp_size if comp_size else data_size
        payload = data[p + 16 + text_size:p + 16 + text_size + actual]
        yield name, data_size, comp_size, payload
        p += 16 + text_size + ((actual + 3) & ~3)


def _pair_names(script, table, qb_hash):
    """Walk \\x2B + u32(LE) hash + NUL-string triples, hash-validated."""
    names = set()
    i = 0
    n = len(script)
    while True:
        i = script.find(PAIR_OP, i)
        if i < 0 or i + 5 >= n:
            break
        (h,) = struct.unpack_from('<I', script, i + 1)
        j = script.find(b'\x00', i + 5)
        if j < 0:
            break
        s = script[i + 5:j].decode('latin1', 'replace')
        if s and len(s) <= 64 and qb_hash(s, table) == h:
            names.add(s)
            i = j
        else:
            i += 1
    return names


def _run_names(script):
    """Printable-run fallback (same filter as the levels/*.qb scan)."""
    names = set()
    n = len(script)
    i = 0
    while i < n - 5:
        if not (32 <= script[i] < 127):
            i += 1
            continue
        j = i
        while j < n and 32 <= script[j] < 127:
            j += 1
        s = script[i:j].decode('latin1')
        if len(s) >= 5 and NAME_RE.match(s):
            if ('.' in s) or ('_' in s) or ('\\' in s) or ('/' in s) or \
               re.search(r'[a-z][A-Z]|[A-Z][a-z]', s):
                names.add(s)
        i = j
    return names


# standalone NUL-delimited symbol token, any case shape. The run filter's
# case-shape test drops all-lowercase/all-caps words (fixblend, WARN, ...),
# but inside a compiled QB script a \0-delimited identifier is the game's own
# symbol storage (param keys, command names) and is genuine regardless of
# case. len >= 3 keeps 2-char float-byte artifacts ("C4", "B0") out.
TOKEN_RE = re.compile(rb'^[A-Za-z_][A-Za-z0-9_./\\\-\[\](){}<> ]{2,63}$')


def _token_names(script):
    names = set()
    for tok in script.split(b'\0'):
        if 3 <= len(tok) <= 64 and TOKEN_RE.match(tok):
            names.add(tok.decode('latin1'))
    return names


def script_names(script, table, qb_hash_fn):
    """All symbol names embedded in ONE compiled QB script buffer.

    Priority: hash-validated \x2B triples, then the printable-run fallback
    (exactly the historic two passes — callers that want the standalone
    NUL-delimited tokens use merge_inner_tokens / _token_names as a
    LOWEST-priority gap-fill so they never override a pair/run spelling)."""
    names = {}
    for s in sorted(_pair_names(script, table, qb_hash_fn)):
        names.setdefault(qb_hash_fn(s, table), s)
    for s in sorted(_run_names(script)):
        names.setdefault(qb_hash_fn(s, table), s)
    return names


def merge_inner_tokens(d, table, qb_hash_fn=None, archive_glob=None):
    """Lowest-priority gap-fill: NUL-delimited symbol tokens in the decoded
    inner QB scripts, AFTER merge_archive_names and the DOL token harvest.

    Recovers all-lowercase/all-caps words the run filter drops (fixblend,
    modulate, diffuse, ...) without ever overriding a pair/run spelling or a
    DOL-rodata2 spelling. Gap-fill only (h not in d)."""
    if qb_hash_fn is None:
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        from qb_hash import qb_hash  # noqa: PLC0415
        qb_hash_fn = qb_hash
    n = 0
    for path in sorted(glob.glob(archive_glob or ARCHIVE_GLOB)):
        got = 0
        for name, data_size, comp_size, payload in pre_entries(path):
            if not name.endswith('.qb'):
                continue
            script = payload if comp_size == 0 else decode_lzss(payload)
            for s in _token_names(script):
                h = qb_hash_fn(s, table)
                if h not in d:
                    d[h] = s
                    got += 1
        n += got
        print('%s: %d new inner-qb tokens' % (os.path.basename(path), got),
              file=sys.stderr)
    print('inner-qb tokens total: %d new' % n, file=sys.stderr)
    return d


def extract(pre_path, table=None, qb_hash_fn=None):
    """Plaintext names embedded in one PRE archive's inner .qb scripts.

    Returns a dict {hash: name} (hash-validated pair names first, then the
    printable-run fallback, then standalone tokens) so callers can merge
    with d.update().

    The table/qb_hash_fn args let a caller reuse its own loaded hash table;
    without them the DOL table is loaded on first use.
    """
    if table is None or qb_hash_fn is None:
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        from qb_hash import load_table, qb_hash  # noqa: PLC0415
        if table is None:
            table = load_table(open(os.path.join(ROOT, 'orig/G2TE52/sys/main.dol'), 'rb').read())
        qb_hash_fn = qb_hash
    names = {}
    for name, data_size, comp_size, payload in pre_entries(pre_path):
        if not name.endswith('.qb'):
            continue
        script = payload if comp_size == 0 else decode_lzss(payload)
        for h, s in script_names(script, table, qb_hash_fn).items():
            names.setdefault(h, s)
    return names


def merge_archive_names(d, table, qb_hash_fn=None, archive_glob=None):
    """Merge every decoded inner-QB name under archive_glob into d (first-wins).

    d is the hash->name dict built by resolve_qb_hashes.build_dict; this is
    the Q2 "extract all inner QB" source: the .prg payloads are LZSS, so a
    raw scan of the archive never sees the script symbol tables. Called by
    gen_qb_constants/main() and resolve_qb_hashes/main().
    """
    for path in sorted(glob.glob(archive_glob or ARCHIVE_GLOB)):
        names = extract(path, table, qb_hash_fn)
        for h, s in names.items():
            if h not in d:
                d[h] = s
        print('%s: %d inner-qb names' % (os.path.basename(path), len(names)),
              file=sys.stderr)
    return d


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('archive', nargs='?', default=os.path.join(PRE_DIR, 'qb_scripts.prg'),
                    help='PRE archive to probe (default: pre/qb_scripts.prg)')
    args = ap.parse_args()

    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    from qb_hash import load_table, qb_hash  # noqa: PLC0415
    table = load_table(open(os.path.join(ROOT, 'orig/G2TE52/sys/main.dol'), 'rb').read())
    names = extract(args.archive, table, qb_hash)
    print('%s: %d distinct names (e.g. %s ...)' %
          (args.archive, len(names), sorted(names.values())[:8]))
    for want in ('VertStickerSlap', 'WallPlant'):
        h = qb_hash(want, table)
        print('  qb_hash(%r) = 0x%08X -> %s' % (want, h, names.get(h)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
