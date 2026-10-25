#!/usr/bin/env python3
"""Parse Wii Proving Ground symbol artifacts into the rename-corpus tables.

Reads a linked ELF (symbol table + debug paths) and one or more linker map
reports (`ADDR SIZE FILE NAME` rows for FUNCTIONS), and emits the Phase 0
corpus tables from docs/plans/2026-09-21-thpg-symbol-naming.md:

  docs/thpg-func-names.tsv   mangled | class | method | unit | folder
                             | folder_evidence | size | builds_seen | rows
  docs/thpg-file-list.tsv    unit | folder | folder_evidence | category | funcs
  docs/thpg-globals.tsv      name | unit | folder | folder_evidence | size
                             | builds_seen | rows   (VARIABLES sections +
                             STT_OBJECT cross-check; never touches the decomp)

Folder inference (plan section 9): `proven` only when a full source path
survives for the unit — either in the ELF `.debug` section or as a pathed
FILE entry in a map. Everything else is matched against FOLDER_RULES
(`heuristic`) or left `unknown`. SDK/runtime, Wii-only and middleware units
are flagged in `category` so later tiers can exclude them.

This tool only READS the other game's artifacts and WRITES the two TSVs. It
never touches symbols.txt, splits.txt, configure.py or any src/ file — no
rename happens here (see tools/rename_thpg.py, not yet built).

Usage:
  tools/venv/bin/python tools/parse_thpg_symbols.py --elf ELF \
      --maps A.txt [B.txt ...] [--out-dir docs]

  --elf ELF        linked ELF with .symtab (for mangled names, STT_FILE units
                   and .debug source paths)
  --maps A.txt     one or more linker map reports (FUNCTIONS section). The
                   first map is the primary build (its addresses/sizes win);
                   remaining maps only add builds_seen coverage.
  --out-dir DIR    where to write the TSVs (default: docs)
"""
import argparse
import collections
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

# ---------------------------------------------------------------------------
# Minimal CodeWarrior demangler.
#
# CW PPC mangling (NOT Itanium — GNU c++filt cannot read it):
#   method__ScopeFargs        e.g. sSeeIfFileIsInAnyPre__3PipFUi
#   method__Q<n><len-prefixed scope chain>Fargs
#       e.g. InitFromStructure__Q23Obj19CCapCameraComponentFPQ26Script7CStruct
# File-static init helpers carry no scope at all (__sinit_\\<file>_cpp).
# The TSV always keeps the raw mangled form, so demangle failures are
# non-fatal: class falls back to "" and method to the raw name.
# ---------------------------------------------------------------------------

_ARG_CHARS = set("vibcsilfdujPQRCEMKFUNOZ0123456789_")


def _read_len_name(s, i):
    m = re.match(r"(\d+)", s[i:])
    if not m:
        return None, i
    n = int(m.group(1))
    j = i + len(m.group(1))
    return s[j:j + n], j + n


def _read_scope(s, i):
    """Read one scope element (plain len-name or Q<n> chain).

    Q<n> is ambiguous under greedy digit matching (Q23Obj... = Q2 +
    [3Obj, ...], not Q23), so candidate counts are tried longest-valid
    first: the winner must parse all its names AND land on an arg-list
    introducer (F), a nested Q, or end-of-string.
    """
    if i < len(s) and s[i] == "Q":
        m = re.match(r"Q(\d+)", s[i:])
        digits = m.group(1)
        for width in range(len(digits), 0, -1):
            count = int(digits[:width])
            if not 1 <= count <= 30:
                continue
            j = i + 1 + width
            parts = []
            ok = True
            for _ in range(count):
                name, j = _read_len_name(s, j)
                if name is None:
                    ok = False
                    break
                parts.append(name)
            if ok and (j >= len(s) or s[j] in "FQ"):
                return parts, j
        return [], i
    name, i = _read_len_name(s, i)
    return ([name] if name else []), i


def demangle_cw(mangled):
    """-> (class, method). class is "" when the symbol carries no scope."""
    text = mangled.replace("\\", "::")
    if "__" not in mangled:
        return "", text
    method, _, tail = mangled.partition("__")
    if not method:
        # File-static helpers (__sinit_\<file>_cpp): no scope to extract.
        return "", text
    scope, _ = _read_scope(tail, 0)
    if not scope:
        return "", method
    *cls, _ = scope  # last element may be a redeclaration; keep it simple
    # Common shape is [scope..., method-dup]; the class is all but the last
    # element when the tail repeats the method, else the whole chain.
    if scope[-1] == method:
        cls = scope[:-1]
    else:
        cls = scope
    return "::".join(c.replace("\\", "") for c in cls), method


# ---------------------------------------------------------------------------
# Folder inference (plan section 9a).
# ---------------------------------------------------------------------------

# (regex on unit basename, inferred folder, reason)
FOLDER_RULES = [
    (r"Component\.o$", "Sk/Components", "component unit"),
    (r"^(Goal|GMan|GoalMan|GoalConversion|GoalScripts|GoalResolvers)", "Sk/Modules/Skate/GoalMgr", "goal-manager family"),
    (r"(AnimNode|BonedAnim|AnimBlender|AnimStateMachine|AnimTree|AnimCache)", "Sk/Anim", "anim-tree family"),
    (r"^(scriptfuncs|cfuncs|machine|ftables|playcontrolfuncs)", "Sk/Scripting", "script-engine family"),
    (r"funcs\.o$", "Sk/Scripting", "per-domain script-callable group (Wii-era Xfuncs.o pattern)"),
    (r"(Skater|skater)", "Sk/Skater", "skater family"),
    (r"(PedLogic|Ped[A-Z]|Crowd)", "Sk/Ped", "pedestrian family"),
    (r"(Trick|Gap|Score|Combo)", "Sk/Modules/Skate/Trick", "trick/score family"),
    (r"(Camera|CameraComponent)", "Sk/Camera", "camera family"),
    (r"(Particle|Fx|Effect)", "Sk/Effects", "effects family"),
    (r"(Coll|Collision|Occlu)", "Sk/Collision", "collision family"),
    (r"(Net|Lobby|Server)", "Sk/Net", "network family"),
    (r"^(p_gx|p_hw|p_Mc|p_nx|p_sfx|p_async|p_pad)", "Sys/NGC", "platform sys file"),
    (r"\.s$", "Sys/NGC", "platform asm"),
    (r"^(snd_|music|soundfx|AX)", "Sys/Audio", "audio family"),
    (r"(Movie|MOT|Cutscene)", "Gel/Movies", "movie family"),
    (r"(dvd|gki_|GX|OS|VI|SI|EXI|AI|AR|THP|WPAD|KPAD|WUD|NAND|SC|CONF)", "SDK", "Nintendo SDK unit"),
    (r"\.obj$", "Middleware", "prebuilt middleware object"),
]

# (regex on unit basename, category) — checked before FOLDER_RULES output use
CATEGORY_RULES = [
    (r"\.obj$", "middleware"),
    (r"^(AX|WPAD|KPAD|WUD|NANDCheck|OSNet|OSExec|dvd|gki_|snd_|M4Decoder|ut_Text|HBMBase)", "sdk"),
    (r"^(snd_|music|soundfx|p_hw|p_Mc|p_nx|p_sfx|p_async|p_gx|p_pad|dvd|gki_)", "sdk"),
    (r"^(WPAD|KPAD|WUD|NAND|SC|CONF|GameNet|CommonGameNet|p_AsyncFilesys|p_nxtexproj|p_hwpad|p_hwinit)", "wii-only"),
    (r"(SkillTree|NailTheTrick|ntg|Gaussian|Classifier|consolePersistList|consoleMatrixBase|summarize|lyt_)", "thpg-only"),
]


def categorize(unit):
    for pat, cat in CATEGORY_RULES:
        if re.search(pat, unit):
            return cat
    return "game"


def infer_folder(unit):
    for pat, folder, _ in FOLDER_RULES:
        if re.search(pat, unit):
            return folder, "heuristic"
    return "unknown", "unknown"


ROW_RE = re.compile(r"\s*\d+\s+([0-9a-fA-F]+)\s+(\d+)\s+(.*?)\s{2,}(.*)$")


def parse_map(path):
    """-> (functions, variables, var_count).
    functions = [(addr, size, file_raw, name)].
    variables = [(addr, size, file_raw, name)] from the VARIABLES section
    (`FILE  -  VAR NAME` rows — the `- ` separator is stripped)."""
    text = open(path, encoding="utf-8", errors="replace").read().splitlines()
    fi = next(i for i, l in enumerate(text) if l.strip().startswith("FUNCTIONS"))
    try:
        vi = next(i for i, l in enumerate(text) if l.strip().startswith("VARIABLES"))
    except StopIteration:
        vi = 0
    funcs = []
    for line in text[fi + 3:]:
        if not line.strip():
            break
        m = ROW_RE.match(line)
        if m:
            addr, size, f, name = m.groups()
            funcs.append((int(addr, 16), int(size), f.strip(), name.strip()))
    var_rows = []
    var_count = 0
    if vi:
        for line in text[vi + 3:]:
            s = line.strip()
            if not s or s.startswith("---") or s.startswith("FUNCTIONS"):
                if s.startswith("FUNCTIONS"):
                    break
                continue
            m = ROW_RE.match(line)
            if m:
                var_count += 1
                name = m.group(4).strip()
                if name.startswith("- "):
                    name = name[2:]
                var_rows.append((int(m.group(1), 16), int(m.group(2)),
                                 m.group(3).strip(), name))
    return funcs, var_rows, var_count


def split_unit(file_raw):
    """Pathed FILE entries (C:\\...\\foo.o) carry a proven folder; the rest
    are bare basenames."""
    if ":" in file_raw or "\\" in file_raw or "/" in file_raw:
        norm = file_raw.replace("\\", "/")
        parts = [p for p in norm.split("/") if p not in ("", ".")]
        unit = parts[-1]
        # Drop drive letters / generic roots, keep the meaningful tail.
        while parts and re.match(r"^[A-Za-z]:$", parts[0]):
            parts.pop(0)
        folder = "/".join(parts[:-1]) if len(parts) > 1 else ""
        return unit, folder if folder else None
    return file_raw, None


def elf_debug_unit_paths(elf_path):
    """{basename -> full source path} from the ELF .debug section.

    Only a subset of units carries debug paths (small .debug here), so most
    units stay heuristic/unknown — that is expected, not an error.
    """
    from elftools.elf.elffile import ELFFile

    out = {}
    with open(elf_path, "rb") as f:
        elffile = ELFFile(f)
        sec = elffile.get_section_by_name(".debug")
        if sec is None:
            return out
        data = sec.data()
    for m in re.finditer(rb"[A-Za-z]:[^\x00-\x1f\"<>|?*]{3,}?\.(?:cpp|c|s|h)", data):
        # A length/type byte precedes the path; the regex start may sit one
        # byte in — realign to the drive letter.
        s = m.group(0).decode("ascii", "replace")
        s = s[s.index(":") - 1:]
        base = s.replace("\\", "/").split("/")[-1]
        out.setdefault(base, s)
    return out


def elf_symbols(elf_path):
    """-> (mangled_by_addr {addr: (mangled, size)}, file_units [in order],
    objects [(name, addr, size, unit|None)] for STT_OBJECT symbols, with the
    owning STT_FILE unit tracked by symtab order)."""
    from elftools.elf.elffile import ELFFile

    by_addr = {}
    files = []
    objects = []
    cur_file = None
    with open(elf_path, "rb") as f:
        elffile = ELFFile(f)
        symtab = elffile.get_section_by_name(".symtab")
        if symtab is None:
            return by_addr, files, objects
        for sym in symtab.iter_symbols():
            stype = sym["st_info"]["type"]
            if stype == "STT_FILE" and sym.name:
                files.append(sym.name)
                cur_file = sym.name
            elif stype == "STT_FUNC" and sym.name and sym["st_value"]:
                by_addr[sym["st_value"]] = (sym.name, sym["st_size"])
            elif stype == "STT_OBJECT" and sym.name:
                objects.append((sym.name, sym["st_value"], sym["st_size"], cur_file))
    return by_addr, files, objects


# Windows paths are case-insensitive; the debug data mixes Sk/Components
# with sk/components etc. Normalize the known Sk-tree segments so votes join.
SK_CASEMAP = {"components": "Components", "objects": "Objects",
              "skilltree": "SkillTree", "scripting": "Scripting",
              "modules": "Modules", "skate": "Skate", "goalmgr": "GoalMgr"}


def _normalize_folder(folder):
    parts = folder.split("/")
    if parts and parts[0].lower() == "sk":
        parts[0] = "Sk"
        parts[1:] = [SK_CASEMAP.get(p.lower(), p) for p in parts[1:]]
    return "/".join(parts)


# Proven folders that are third-party trees, not Neversoft sources.
VENDOR_PATH_RE = re.compile(r"products/|layout/|MetroTRK|MSL|RVL|rnt|gamedev", re.IGNORECASE)


def debug_folder_for(path):
    """Map a full Neversoft source path to a repo-style folder + evidence."""
    p = path.replace("\\", "/")
    m = re.search(r"Code/Sk/(.+)/[^/]+$", p, re.IGNORECASE)
    if m:
        return _normalize_folder("Sk/" + m.group(1)), "proven"
    m = re.search(r"code/(gel|core|gfx|sys)/(.+)/[^/]+$", p, re.IGNORECASE)
    if m:
        return "Engine/%s/%s" % (m.group(1), m.group(2)), "proven"
    m = re.search(r"code/sys/NGC/?([^/]*)$", p, re.IGNORECASE)
    if m:
        return "Sys/NGC", "proven"
    return "unknown", "unknown"


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--elf", required=True)
    ap.add_argument("--maps", nargs="+", required=True)
    ap.add_argument("--out-dir", default="docs")
    args = ap.parse_args()

    map_names = []
    for p in args.maps:
        base = os.path.basename(p)
        tag = os.path.splitext(base)[0].split("skate9")[-1] or "map"
        map_names.append(tag or base)
    prim_tag = map_names[0]

    # func_key (unit, name) -> {rows: [(size, build)], proven: folder|None}.
    # Same-name rows within one map (duplicates, template instantiations)
    # are all kept — the key only groups builds_seen coverage.
    funcs = collections.OrderedDict()
    vglobals = collections.OrderedDict()
    var_counts = {}
    row_counts = {}
    for tag, path in zip(map_names, args.maps):
        rows, vrows, var_count = parse_map(path)
        var_counts[tag] = var_count
        row_counts[tag] = len(rows)
        for addr, size, file_raw, name in rows:
            unit, proven_folder = split_unit(file_raw)
            key = (unit, name)
            e = funcs.setdefault(key, {"rows": [], "proven": None})
            e["rows"].append((size, tag))
            if proven_folder and not e["proven"]:
                e["proven"] = proven_folder
        for addr, size, file_raw, name in vrows:
            unit, proven_folder = split_unit(file_raw)
            key = (unit, name)
            e = vglobals.setdefault(key, {"rows": [], "proven": None})
            e["rows"].append((addr, size, tag))
            if proven_folder and not e["proven"]:
                e["proven"] = proven_folder

    print("maps: " + ", ".join(
        "%s: %d func rows/%d vars" % (t, row_counts[t], v)
        for t, v in zip(map_names, var_counts.values())))

    mangled_by_addr, elf_files, elf_objects = elf_symbols(args.elf)
    print("elf: %d STT_FUNC symbols, %d STT_FILE units, %d STT_OBJECT symbols" % (
        len(mangled_by_addr), len(elf_files), len(elf_objects)))
    dbg_paths = elf_debug_unit_paths(args.elf)
    print("elf: %d units with .debug source paths" % len(dbg_paths))

    # Proven folders per unit: map FILE paths first, ELF .debug second.
    proven = {}
    for (unit, _), e in funcs.items():
        if e["proven"] and unit not in proven:
            proven[unit] = e["proven"]
    for base, full in dbg_paths.items():
        folder, ev = debug_folder_for(full)
        if ev == "proven":
            # .debug paths name real sources; map FILE entries may use a
            # different but equivalent spelling — key on basename variants.
            proven.setdefault(base, folder)
    # .o unit <-> .cpp debug basename bridge (CapComponent.o ↔ CapComponent.cpp)
    for base, full in dbg_paths.items():
        stem = os.path.splitext(base)[0]
        for ext in (".o", ".obj"):
            proven.setdefault(stem + ext, debug_folder_for(full)[0])

    # Mangled names attach via primary-build addresses.
    prim_addrs = {}
    rows, _, _ = parse_map(args.maps[0])
    for addr, size, file_raw, name in rows:
        unit, _ = split_unit(file_raw)
        prim_addrs[addr] = (unit, name)

    outfunc_rows = []
    for (unit, name), e in funcs.items():
        sizes = sorted(s for s, _ in e["rows"])
        size = sizes[len(sizes) // 2]
        builds = "+".join(t for t in map_names
                          if any(b == t for _, b in e["rows"]))
        if unit in proven:
            folder, ev = proven[unit], "proven"
        else:
            folder, ev = infer_folder(unit)
        n_dup = len(e["rows"])
        outfunc_rows.append((unit, name, folder, ev, size, builds, n_dup))

    # Attach mangled names for primary-build rows.
    mangled = {}
    for addr, (mname, msize) in mangled_by_addr.items():
        if addr in prim_addrs:
            mangled[prim_addrs[addr]] = mname

    func_rows = []
    for unit, name, folder, ev, size, builds, n_dup in outfunc_rows:
        mname = mangled.get((unit, name), "")
        cls, method = demangle_cw(mname) if mname else ("", name)
        func_rows.append((mname, cls, method, unit, folder, ev, size, builds,
                          n_dup))
    func_rows.sort(key=lambda r: (r[4], r[3], r[2]))

    units = collections.OrderedDict()
    for unit, _, folder, ev, _, _, n_dup in outfunc_rows:
        u = units.setdefault(unit, {"folder": folder, "ev": ev, "n": 0})
        u["n"] += n_dup

    os.makedirs(args.out_dir, exist_ok=True)
    fp = os.path.join(args.out_dir, "thpg-func-names.tsv")
    with open(fp, "w", encoding="utf-8") as f:
        f.write("mangled\tclass\tmethod\tunit\tfolder\tfolder_evidence\tsize\tbuilds_seen\trows\n")
        for mname, cls, method, unit, folder, ev, size, builds, n_dup in func_rows:
            f.write("%s\t%s\t%s\t%s\t%s\t%s\t%d\t%s\t%d\n" % (
                mname, cls, method, unit, folder, ev, size, builds, n_dup))
    fl = os.path.join(args.out_dir, "thpg-file-list.tsv")
    with open(fl, "w", encoding="utf-8") as f:
        f.write("unit\tfolder\tfolder_evidence\tcategory\tfuncs\n")
        for unit in sorted(units):
            u = units[unit]
            cat = categorize(unit)
            if (cat == "game" and u["ev"] == "proven"
                    and VENDOR_PATH_RE.search(u["folder"])):
                cat = "sdk"  # third-party tree (RVL/MetroTRK/MSL/…) despite game-ish name
            f.write("%s\t%s\t%s\t%s\t%d\n" % (
                unit, u["folder"], u["ev"], cat, u["n"]))
    n_proven = sum(1 for u in units.values() if u["ev"] == "proven")
    print("wrote %s (%d functions), %s (%d units, %d proven folders)" % (
        fp, len(func_rows), fl, len(units), n_proven))

    g_rows = []
    for (unit, name), e in vglobals.items():
        sizes = sorted(s for _, s, _ in e["rows"])
        size = sizes[len(sizes) // 2]
        builds = "+".join(t for t in map_names
                          if any(b == t for _, _, b in e["rows"]))
        if unit in proven:
            folder, ev = proven[unit], "proven"
        else:
            folder, ev = infer_folder(unit)
        g_rows.append((name, unit, folder, ev, size, builds, len(e["rows"])))
    g_rows.sort(key=lambda r: (r[2], r[1], r[0]))
    fg = os.path.join(args.out_dir, "thpg-globals.tsv")
    with open(fg, "w", encoding="utf-8") as f:
        f.write("name\tunit\tfolder\tfolder_evidence\tsize\tbuilds_seen\trows\n")
        for name, unit, folder, ev, size, builds, n_dup in g_rows:
            f.write("%s\t%s\t%s\t%s\t%d\t%s\t%d\n" % (
                name, unit, folder, ev, size, builds, n_dup))
    print("wrote %s (%d globals)" % (fg, len(g_rows)))


if __name__ == "__main__":
    main()
