#!/usr/bin/env python3
"""Resolve Neversoft QB hash constants in the DOL.

Pipeline:
1. The QB hash function was reverse-engineered from fn_8000A778 (tools/qb_hash.py)
   and verified against [hash][string] pairs embedded in the .prg files.
2. The .prg files also store many plaintext names (anim paths, QB symbols).
   Hash each plaintext name -> build a hash->name dictionary.
3. Scan the DOL .text for lis+ori 32-bit constants and resolve them via the
   dictionary.

Usage:
    python tools/resolve_qb_hashes.py [--pre PRE_DIR] [--out OUT.tsv]
"""
import argparse
import glob
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

import gen_leaves  # noqa: E402
import qb_extract  # noqa: E402
from qb_hash import load_table, qb_hash  # noqa: E402

DOL_PATH = 'orig/G2TE52/sys/main.dol'


# ---------- 1. plaintext names from .prg files ----------

# NOTE: the {1,} tail only matters if a caller lowers min_len below 5 (the
# default extract_names gate) — short-name rescue (Wait/Kill/Goto/CD/...)
# actually flows through the structured sources (registry TSV name column,
# decoded QB symbol table) which bypass the printable-run filter entirely.
NAME_RE = re.compile(r'^[A-Za-z_][A-Za-z0-9_./\\\-\[\](){}<> ]{1,}$')


def extract_names_bytes(data, min_len=5):
    """Printable-run scan over raw bytes -> plausible QB name strings.

    Requires >= min_len printable chars and the name to look like a real
    identifier (separator char, or an upper/lower case transition)."""
    names = set()
    n = len(data)
    i = 0
    while i < n - min_len:
        if not (32 <= data[i] < 127):
            i += 1
            continue
        j = i
        while j < n and 32 <= data[j] < 127:
            j += 1
        s = data[i:j].decode('latin1')
        if len(s) >= min_len and NAME_RE.match(s):
            # require it to look like a real name (mix of case/digits or path)
            if ('.' in s) or ('_' in s) or ('\\' in s) or ('/' in s) or \
               re.search(r'[a-z][A-Z]|[A-Z][a-z]', s):
                names.add(s)
        i = j
    return names


def extract_names(path, min_len=5):
    data = open(path, 'rb').read()
    return extract_names_bytes(data, min_len)


def tsv_names(path):
    """Name column (col 1) of a script-command registry TSV, verbatim.

    Every row of docs/rodata2-script-command-registry.tsv is one QB script
    command name (registry at DOL .data 0x80303464) — including 2-4 char
    names (Wait, Kill, CD, PAL ...) that the printable-run filter drops.
    The func/addr columns are ignored; only the name column feeds the dict."""
    names = set()
    for ln in open(path):
        if ln.startswith('#') or not ln.strip():
            continue
        col = ln.split('\t', 1)[0].strip()
        if col:
            names.add(col)
    return names


def dol_rodata2_names(min_len=5, max_len=40):
    """Plaintext names inside the DOL .rodata2 (sec 8) string region.

    The rodata2 slice holds read-only strings (command names, param keys,
    sentences, ...). Strings longer than max_len chars are prose/sentences,
    not hashable names, so they are rejected here (not by changing the
    shared NAME_RE — the slice is a different class of data)."""
    data = gen_leaves.d[gen_leaves.r2_off:gen_leaves.r2_off + gen_leaves.r2_size]
    return {s for s in extract_names_bytes(data, min_len) if len(s) <= max_len}


def merge_qb_file_names(d, table, qb_globs=()):
    """Lowest-priority gap-fill over the raw compiled QB script FILES.

    The build_dict loop only printable-run scans levels/*.qb (and never
    touched the GC .qb.ngc variants). This re-runs the FULL extraction
    (hash-validated \x2B pairs + runs + NUL-delimited tokens) over every
    .qb/.qb.ngc file, gap-fill only, AFTER the decoded archives — so it
    recovers names the run filter drops (all-lowercase/all-caps words like
    WARN in mainmenu_cas.qb.ngc) without ever overriding a spelling the
    earlier sources chose."""
    globs = list(qb_globs) or [
        os.path.join('orig/G2TE52/disc/files/levels', '**', '*.qb'),
        os.path.join('orig/G2TE52/disc/files/levels', '**', '*.qb.ngc'),
    ]
    n = 0
    for pat in globs:
        for path in sorted(glob.glob(pat, recursive=True)):
            for h, s in qb_extract.script_names(open(path, 'rb').read(),
                                                 table, qb_hash).items():
                if h not in d:
                    d[h] = s
                    n += 1
    print('qb file names: %d new' % n, file=sys.stderr)
    return d


def merge_dol_tokens(d, table, min_len=3, max_len=64):
    """Lowest-priority dict source: NUL-delimited standalone name-shaped
    tokens in every DOL data section (indices 2..17; .init/.text excluded).

    Catches what the run scans drop: all-caps / all-lowercase / short names
    and names with separators — the NGC script-name table (sec 9,
    ngc_pal60/ngc_dvd_* at vaddr 0x802B23A0), the "FS "/"BS " trick-name
    prefixes and "arg1" (sec 8 rodata2), the ScriptSetConfig flag table
    (NTSC). A \0-delimited identifier token in a DOL data section is a
    genuine string (not float-pool junk — min_len 3 keeps 2-char byte
    artifacts out).

    Gap-fill only (never overrides): runs last, after the decoded inner-QB
    names, so a case-variant duplicate (DOL "FAM" vs a script's "fam" —
    the hash is case-insensitive) keeps the script's spelling. Callers run
    this AFTER qb_extract.merge_archive_names. rodata2 (sec 8) is scanned
    FIRST so its spellings keep the priority they had before the other
    sections were added."""
    data = gen_leaves.d
    token_re = re.compile(rb'^[A-Za-z_][A-Za-z0-9_./\\\-\[\](){}<> ]{%d,%d}$'
                          % (min_len - 1, max_len - 1))
    n = 0
    order = [8] + [i for i in range(2, 18) if i != 8]
    for i in order:
        off, size = gen_leaves.offs[i], gen_leaves.sizes[i]
        if not off or not size:
            continue
        for tok in data[off:off + size].split(b'\0'):
            if min_len <= len(tok) <= max_len and token_re.match(tok):
                s = tok.decode('latin1')
                h = qb_hash(s, table)
                if h not in d:
                    d[h] = s
                    n += 1
    print('dol data-section tokens: %d new' % n, file=sys.stderr)
    return d


# [u32 hash LE][name\0] records (the DOL script-name table, sec 9 at
# vaddr 0x802B23A0). Self-validating: a record only counts if the embedded
# u32 equals qb_hash(name), so byte coincidences cannot enter.
REC_RE = re.compile(rb'[A-Za-z_][A-Za-z0-9_./\\\-\[\](){}<> ]{1,63}\x00')


def merge_dol_hash_records(d, table):
    """Lowest-priority dict source: hash-validated [u32 LE][name\0] records
    in every DOL data section.

    The sec 9 script-name table stores each name next to its own hash
    (ngc_pal60 -> 0x84BF17AB, ngc_dvd_cover_open -> 0xC3B9A031, plus the
    2-char keys sa/sr/ub/... that no filter would accept). Every record is
    verified by re-hashing the name against the embedded u32, so nothing
    bogus can enter. Gap-fill only, after the decoded archives."""
    data = gen_leaves.d
    n = 0
    for i in range(2, 18):
        off, size = gen_leaves.offs[i], gen_leaves.sizes[i]
        if not off or not size:
            continue
        sec = data[off:off + size]
        for m in REC_RE.finditer(sec):
            if m.start() < 4:
                continue
            h = struct.unpack('<I', sec[m.start() - 4:m.start()])[0]
            s = m.group(0)[:-1].decode('latin1')
            if qb_hash(s, table) == h and h not in d:
                d[h] = s
                n += 1
    print('dol hash records: %d new' % n, file=sys.stderr)
    return d


DBG_NAMES_TSV = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                            'docs', 'thpg-qb-names.tsv')


def merge_dbg_names(d, table, path=DBG_NAMES_TSV):
    """Lowest-priority dict source: QB hash/name pairs from THPG's own
    debugger name table (debugger_names.dbg, PS2/Wii), committed as
    docs/thpg-qb-names.tsv.

    THPG's Neversoft QB hash is identical to THUG2's (verified: 3401/3401
    agreement with THUG2 disc-derived names, VertStickerSlap/Wallplant
    validate). Each line is re-validated by re-hashing the name against the
    game's own table, so a stray line can't enter. Gap-fill only, after all
    disc-derived sources, so disc evidence always wins the spelling."""
    n = 0
    skip = 0
    for line in open(path, encoding='latin1'):
        line = line.strip()
        if not line or line.startswith('#'):
            continue
        parts = line.split(None, 1)
        if len(parts) != 2:
            continue
        try:
            h = int(parts[0], 16)
        except ValueError:
            continue
        s = parts[1]
        if qb_hash(s, table) != h:
            skip += 1
            continue
        if h not in d:
            d[h] = s
            n += 1
    print('thpg dbg names: %d new (%d hash-mismatch skipped)' % (n, skip),
          file=sys.stderr)
    return d


def build_dict(pre_dir, table, extra_globs=()):
    """Hash->name dict from .prg plaintext plus any extra file globs.

    extra_globs adds more sources beyond the classic pre/*.pr* scan. Each
    extra pattern may be a plain file glob (compiled QB scripts,
    levels/**/*.qb), a path to a registry .tsv (name-per-line, col 1) or a
    path to the DOL itself (whose .rodata2 slice is scanned). Processing
    order (pre first, then each extra glob in list order) keeps first-wins
    priority for hashes shared between sources."""
    d = {}
    seen = set()
    for pat in [os.path.join(pre_dir, '*.pr*')] + list(extra_globs):
        # recursive=True so '**' in a glob (e.g. levels/**/*.qb) really
        # recurses.
        for path in sorted(glob.glob(pat, recursive=True)):
            if path in seen:
                continue
            seen.add(path)
            if path.endswith('.tsv'):
                names = tsv_names(path)
            elif path.endswith('.dol'):
                names = dol_rodata2_names()
            else:
                names = extract_names(path)
            for s in names:
                h = qb_hash(s, table)
                if h not in d:
                    d[h] = s
            print('%s: %d names' % (os.path.basename(path), len(names)), file=sys.stderr)
    print('dictionary: %d hashes' % len(d), file=sys.stderr)
    return d


# ---------- 2. DOL lis+ori scan ----------

def find_lis_ori_constants():
    text = gen_leaves.d[gen_leaves.t_off:gen_leaves.t_off + gen_leaves.t_size]
    base = gen_leaves.t_addr
    results = []
    for off in range(0, len(text) - 8, 4):
        w0 = int.from_bytes(text[off:off + 4], 'big')
        w1 = int.from_bytes(text[off + 4:off + 8], 'big')
        if (w0 & 0xFC1F0000) != 0x3C000000:  # lis rD,imm
            continue
        if (w1 & 0xFC000000) != 0x60000000:  # ori rA,rS,imm
            continue
        rd0 = (w0 >> 21) & 0x1F
        rd1 = (w1 >> 21) & 0x1F
        ra1 = (w1 >> 16) & 0x1F
        if rd0 != rd1 or rd0 != ra1:
            continue
        val = (((w0 & 0xFFFF) << 16) | (w1 & 0xFFFF)) & 0xFFFFFFFF
        results.append((base + off, val))
    return results


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--pre', default='orig/G2TE52/disc/files/pre',
                    help='directory of .prg files')
    ap.add_argument('--qb', default='orig/G2TE52/disc/files/levels/**/*.qb',
                    help='glob of compiled QB scripts to also scan (** recurses)')
    ap.add_argument('--out', default=None, help='output TSV (default: stdout)')
    args = ap.parse_args()

    table = load_table(open(DOL_PATH, 'rb').read())
    d = build_dict(args.pre, table,
                   extra_globs=[args.qb, 'docs/rodata2-script-command-registry.tsv',
                                DOL_PATH])
    # inner QB symbol names from the LZSS pre archives (same as the header
    # generator uses, so docs/dol-qb-hash-resolved.tsv stays in sync).
    qb_extract.merge_archive_names(d, table)
    # all lowest-priority gap-fills (never override): DOL data-section
    # tokens (NTSC/"FS " — rodata2 first, keeping its historic spellings),
    # inner-script tokens (fixblend/...), raw .qb/.qb.ngc files, and
    # hash-validated [u32][name] records (ngc_*), then THPG's debugger
    # name table (noextramemory -> 0xAF11B50F, language, warn, led, ...).
    merge_dol_tokens(d, table)
    qb_extract.merge_inner_tokens(d, table)
    merge_qb_file_names(d, table)
    merge_dol_hash_records(d, table)
    merge_dbg_names(d, table)
    consts = find_lis_ori_constants()
    print('DOL lis+ori constants: %d' % len(consts), file=sys.stderr)

    out = args.out or sys.stdout
    f = open(out, 'w') if isinstance(out, str) else out
    f.write('# addr\tconstant\tname\n')
    resolved = 0
    for addr, val in consts:
        name = d.get(val)
        if name:
            resolved += 1
            f.write('%08X\t%08X\t%s\n' % (addr, val, name))
    if isinstance(out, str):
        f.close()
    print('resolved: %d/%d (%.1f%%)' % (resolved, len(consts),
                                         100.0 * resolved / max(1, len(consts))),
          file=sys.stderr)


if __name__ == '__main__':
    main()
