# Plan: Maximize `QB_*` constants for magic `0x89E8C244` class

**Status:** ✅ EXECUTED (2026-09-04, M6.87) — Q1 (TSV + DOL .rodata2) + Q2
(inner-QB decode via `tools/qb_extract.py`) + Q3 (lazy header) + Q4
(hex-sort kept; warning-only `--check` in `tools/final_verify.sh`) all done.
Results vs estimates below; header `372 → 3,863` defines, DOL `.text`
resolution `528/3177 (16.6%) → 2,577/3177 (81.1%)`, `0x89E8C244`
`VertStickerSlap` (DOL @ `0x802055AC`) + `0xCF74F6B7` `Wallplant` both
named, DOL byte-identical after rebuild.  
**Owner:** M6.87 (AGENTS.md)  
**Related:** `AGENTS.md M6.86b/M6.87`, `tools/gen_qb_constants.py:1`, `tools/resolve_qb_hashes.py:56`, `tools/qb_extract.py:1` (NEW), `tools/qb_hash.py:54`, `include/qb_constants.h:1`, `docs/rodata2-script-command-registry.tsv:1`, `docs/dol-qb-hash-resolved.tsv:1`

## 0. Context — why `VertStickerSlap 0x89E8C244` / `WallPlant 0xCF74F6B7` have no macro today

Current header `include/qb_constants.h:372` defines comes solely from `tools/gen_qb_constants.py:113` `build_dict(PRE_DIR, table, extra_globs=[QB_GLOB])` where `QB_GLOB` `tools/gen_qb_constants.py:45` is `levels/**/*.qb` (19 files). `PRE_DIR` `tools/gen_qb_constants.py:44` `pre/*.pr*` adds `122,163` hashes but `VertStickerSlap` lives only in `DOL .data 0x80303464` registry `docs/rodata2-script-command-registry.tsv:1305` `VertStickerSlap - - N -` (GC `li;blr` stub, never in `.pr*` plaintext) and `WallPlant` lives inside `pre/qb_scripts.prg` inner QB `walltricks.qb:206` `docs/qdir-script-sources.txt:206` compiled bytecode — `extract_names()` `tools/resolve_qb_hashes.py:34` on the archive sees only `209` path strings, not inner symbol tables. Both hashes appear as `src/wip` literals (`src/wip/fn_80205574.c:14` `case 0x89E8C244:` / `src/wip/fn_802113EC.c:139` `0xCF74F6B7`) so `referenced_values()` `tools/gen_qb_constants.py:55` counts them, but `v not in d` `tools/gen_qb_constants.py:122` → no `#define`. We identified them by `DOL` `lis -0x7618; ori 0xC244` at `0x802055AC` + `qb_hash("VertStickerSlap")==0x89E8C244` `tools/qb_hash.py:54`, not via the dict.

`*_wip` census today (estimates — confirm in Step 1 baseline): `src+wip` `3926` distinct non-DOL literals (`2845` in `wip`), `71` hashable (`2.5%`) and all `71` already named — `0` unresolved hashable under current dict. Remaining `2774` distinct are `96.8%` float bits (`0x43300000` `135×`), masks (`0xFFFFFFFC` `37×`), `MMIO 0xCC008000` — correctly unnamed per `AGENTS.md M6.86b`. `docs/dol-qb-hash-resolved.tsv:1` is stale at `380` rows; a live `tools/resolve_qb_hashes.py:86` run with the current dict resolves `528/3177 16.6%` (`380` = committed file, `528` = live dict — regenerate the TSV in Step 6 to reunite them).

Goal is to make “as many `0x89E8C244` as possible” resolve *without* naming floats/masks.

**Actuals (Step 1 baseline, 2026-09-04):** census had grown since the
esitmates — `4,813` distinct non-DOL src+wip literals (`3,815` in wip),
`98` resolvable under the old dict, `0` unresolved hashable misses; the
rest float bits / masks / MMIO. `gen --check` was already stale by one
define (`371` would change vs `372` committed — a macro-usage keep-alive
lost a ref after a draft refill; regeneration converged it). Step 2+4
execution results: TSV `1,327` names (`1,185` new hashes — matches the
estimate), sec8 slice `2,156` names (`~799` net-new after dedup), inner-QB
decode of all `pre/*_scripts.pr*` archives (`396` scripts) `~89k`
hash-revalidated `\x2B`-pair symbols + `~31k` printable-run fallback names
(qb_scripts.prg alone: `31,719`). Header `372 → 3,863` defines; sweep
renamed `8,756` literals across `1,995` files (`1,013` promoted, `982`
wip); DOL byte-identical (`sha1 ff6faeb0…`), `--check` stable post-sweep.

## 1. Approved decisions

**Q1 — Do both `TSV` + `DOL .rodata2`:** both approved. `docs/rodata2-script-command-registry.tsv:4` (`1327` commands, est. `1185` new hashes after `+0` garbage filter — confirm in Step 1) + `DOL sec8 0x8028FB60 size 0x22840` (est. `2192` raw strings via `extract_names()`, `2003` new, `+326` distinct rescues: `goal_id×15`, `key_combo×10`, `SetWobbleDetails×6` — confirm in Step 1). `TSV` is the clean zero-garbage subset; `sec8` filtered `len≤40` adds `834` non-registry param keys with only `45` long-sentence rejects.

**Q2 — Extract all inner QB:** approved. Build a minimal QB bytecode parser for `pre/qb_scripts.prg` PRE→QB entries (≈209 scripts, `levels/mainmenu/casmenu.qb:42` names proves compiled `01 23 16 2B` does embed plaintext) — estimates `~8000` names vs today’s `209` path-only. Raw `extract_names()` on `qb_scripts.prg` will never rescue `VertStickerSlap`; only a `QB` string-table walk will.

**Q3 — Lazy `src/wip`-only header (recommended, keep):** see §3.

**Q4 — Hex-sorted header + `--check` CI (recommended, keep):** see §4.

## 2. What Q3 and Q4 mean (expanded per request)

### Q3 — Lazy `src/wip`-referenced vs eager DOL-wide

*Current (lazy) — `tools/gen_qb_constants.py:106` `main()` `referenced_values()` → `vals` → `if v in d: resolved[v]=d[v]` `tools/gen_qb_constants.py:122`.* Header `372` = exactly the `71` hashable `wip` literals + `~300` keep-alives `tools/gen_qb_constants.py:114` `cmap` (`QB_*` still referenced as macro after sweep). `docs/dol-qb-hash-resolved.tsv`’s `113` distinct `DOL` hashes have no header entry until a `src/wip` draft actually writes `0x...` — `0x89E8C244` would have stayed raw forever until you edited `fn_80205574.c:14`.

*Eager alternative — add `find_lis_ori_constants()` `tools/resolve_qb_hashes.py:86` values to `vals` before the loop.* Header would become `372 → ~528` (today) / `~500-700` after Q1+Q2, matching the `528/3177` live-dict resolvable DOL hashes even though `~180` distinct values never appear in any decompiled function. Pro: future `fill_wip_drafts.py:1070` `subst_qb_constants()` draft would be named on first generation. Con: `+42%` bloat of dead defines for DOL-only hashes never referenced in `src/wip`, header diff noise on every dict expansion, obscures the `71` that actually matter. `122k` full-dict eager is `not` proposed.

*Why lazy recommended:* the user request (“as many `0x89E8C244` as possible as `const`”) is satisfied by making `v in d` true for more `v` (Q1+Q2), not by pre-defining unused `DOL` hashes. Keep lazy, add an optional `tools/gen_qb_constants.py --all-dol` audit flag that diffs header vs `TSV` for occasional coverage checks.

### Q4 — Hex sort + CI `--check`

*Sort — `tools/gen_qb_constants.py:87` `render_header(sorted(resolved))` `tools/gen_qb_constants.py:98` `#define %-28s 0x%08X`.* Already hex-sorted, uppercased via `macro_name()` `tools/gen_qb_constants.py:76` `re.sub [^A-Za-z0-9]→_` + `_N` collision loop, deterministic. Name-sorted would churn. Keep hex.

*CI — `tools/gen_qb_constants.py:108` `--check` exits `1` if header would change `tools/gen_qb_constants.py:136`, needs `orig/G2TE52/sys/main.dol` + `build/G2TE52/report.json` (import of `gen_leaves`).*

- **No CI:** today’s drift (`372` vs `528`, `src/fn_801A4D1C.c:41` raw `0x9B65D7B8u` pre-sweep) recurs whenever `fill_wip_drafts.py --force` reverts a name.
- **CI:** wire `tools/venv/bin/python tools/gen_qb_constants.py --check` + `tools/venv/bin/python tools/apply_qb_constants.py --dry-run` (fail if raw resolvable literal remains) into `tools/final_verify.sh:1` as a **warning-only (non-blocking)** step. (No `.github/workflows` exists in this repo, so that path is not actionable — create the workflow first if PR-gating is wanted.) Cost is milliseconds, catches Q1/Q2 regeneration drift. Needs `report.json` artifact only if import path kept; otherwise guard with `if [ -f build/G2TE52/report.json ]`.

Keep hex sort, add `--check` as warning-only `final_verify.sh` step (must NOT `exit 1` — the script runs under `set -e`).

## 3. Implementation steps

### Step 1 — Baseline (read-only)

```sh
tools/venv/bin/python tools/gen_qb_constants.py --check; echo $?
tools/venv/bin/python tools/resolve_qb_hashes.py --out /tmp/qb.tsv 2>&1 | tail
grep -c "#define QB_" include/qb_constants.h  # 372
grep -R "0x89E8C244\|0xCF74F6B7" src/wip --include="*.c" -n
```

Record `resolved 528/3177`, `2845` distinct wip non-DOL, `0` unresolved hashable.

### Step 2 — Add `TSV` + `DOL .rodata2` to dict

Edit `tools/gen_qb_constants.py:45` `QB_GLOB` → list `REGISTRY_TSV = "docs/rodata2-script-command-registry.tsv"` + `DOL_RODATA2` via new helper `extract_dol_rodata2_names()` (slice `DOL` `sec8 0x8028FB60 0x22840` — needs NEW `gen_leaves` rodata2 addr/size exports since `gen_leaves.d`/`t_off` in `tools/resolve_qb_hashes.py:87` are `.text`-only — then run `extract_names()` with the `len≤40` sentence filter applied in the new helper, not by changing the shared `NAME_RE`). Wire:

```python
# tools/gen_qb_constants.py:113
d = build_dict(PRE_DIR, table, extra_globs=[QB_GLOB, REGISTRY_TSV, DOL_RODATA2])
# and teach build_dict to handle .tsv (line-per-name, col 1) and raw .dol slice
```

Add `tools/resolve_qb_hashes.py:56` `build_dict` branch: if `pat.endswith(".tsv")` → parse column 1, skipping `#` comment lines (the `-` func/addr columns are ignored — only the name column feeds the dict); if `pat.endswith(".dol")` → read `sec8` slice. First-wins `if h not in d: d[h]=s` `tools/resolve_qb_hashes.py:77` keeps `pre/*.pr*` priority.

*Expected (estimates — confirm in Step 1):* `+1185` (TSV) + `+2003` (sec8) new hashes, `+326` distinct rescues, header `372 → ~698`.

### Step 3 — Fix `NAME_RE` short-name loss (+15)

`tools/resolve_qb_hashes.py:31` `NAME_RE {4,}` drops `Wait/Kill/Goto/CD/PAL/Sin` (`15/1327`). Change to `{1,}` or add `TSV`-driven exception list (since `TSV` names bypass `extract_names()` they are immune; only `sec8` raw scan benefits). Verify `grep -c "0x82117C1A" src/wip` now resolves.

### Step 4 — QB bytecode parser for `pre/qb_scripts.prg` inner scripts (≈8000 names)

New `tools/qb_extract.py`:
- Enumerate `pre/qb_scripts.prg` PRE entries (read `QB` `01 23 16 2B` inner header, walk debug string table — proven in `levels/mainmenu/casmenu.qb:42`).
- Yield plaintexts (`VertStickerSlap`, `WallPlant`, `StickerSlap`-family) → merge via direct `d.update()` in the caller (NOT as an `extra_globs` entry — `build_dict` takes file-glob patterns via `glob.glob`, not `module:function` paths).

*Probe first:* `python -c "import qb_extract; print(qb_extract.extract('pre/qb_scripts.prg')[:5])"` should show `VertStickerSlap` among the `~8000` (estimate — confirm count in Step 1). Until the parser exists, prefer a tiny dict-source override (e.g. a two-line TSV fed to `build_dict`) over hand-editing the header: the header is AUTO-GENERATED DO NOT EDIT, and a hand-added `#define` survives regen only via the `cmap` keep-alive branch (`tools/gen_qb_constants.py:125-126`, macro must stay referenced in `src/wip`) — so if hand-adding, add the define AND run the `apply_qb_constants.py` sweep in the same commit, or the next regen wipes it.

### Step 5 — Regenerate & sweep (byte-safe)

```sh
tools/venv/bin/python tools/gen_qb_constants.py  # writes include/qb_constants.h:698
tools/venv/bin/python tools/apply_qb_constants.py --dry-run  # expect 2+ files: fn_80205574.c, fn_802113EC.c
tools/venv/bin/python tools/apply_qb_constants.py
# fill_wip keeps names on refill (verify with grep, not --help):
grep -n "subst_qb_constants" tools/fill_wip_drafts.py  # line 1070 in postprocess
tools/ninja build/G2TE52/main.dol && cmp orig/G2TE52/sys/main.dol build/G2TE52/main.dol  # must be identical: #define expands to literal
```

Handle collisions via `macro_name()` `_N` (`tools/gen_qb_constants.py:81`), keep `ensure_include()` `tools/apply_qb_constants.py:42` idempotent. `DOL_LO/HI` filter `tools/gen_qb_constants.py:49` prevents `0xCC008000`/`0xFFFFFFFC` false positives.

### Step 6 — Docs & CI

- Keep `include/qb_constants.h:6` guard, `sorted` order.
- Add to `tools/final_verify.sh:1` as a warning-only step (NOT `exit 1` — the script runs under `set -e`):
  ```sh
  if [ -f build/G2TE52/report.json ]; then
    tools/venv/bin/python tools/gen_qb_constants.py --check || echo "warning: qb_constants.h stale"
  fi
  ```
  (guard with `test -f build/G2TE52/report.json` per `tools/gen_qb_constants.py:25` — the `gen_leaves` import needs it).
- Optionally regenerate `docs/dol-qb-hash-resolved.tsv:1` via `tools/resolve_qb_hashes.py --out docs/dol-qb-hash-resolved.tsv` (stale `380` rows → live `~528` rows, `0x89E8C244 VertStickerSlap` appears once the dict covers it).

## 4. Verification checklist (results, 2026-09-04)

- ✅ `grep -c QB_ include/qb_constants.h` → `3,863` (↑ from `372`, far above the `~700` estimate), `QB_VERTSTICKERSLAP` → `0x89E8C244`, `QB_WALLPLANT` → `0xCF74F6B7`.
- ✅ `grep -R "0x89E8C244" src` → `0`; `QB_VERTSTICKERSLAP` used in `src/wip/fn_80205574.c`; `QB_WALLPLANT` in `fn_802113EC.c` + `fn_801DBCAC.c` (`0xCF74F6B7` sits in two drafts, both swept; `fn_801DBCAC.c` also gained `QB_WALLPLANT_TRICK` from the same decode).
- ✅ `gen_qb_constants.py --check` → `0` (stable post-sweep), `tools/ninja build/G2TE52/ok` → `OK`, `cmp orig build` → identical (`sha1 ff6faeb0f2b524ecbe1aeaff78ff154a284c27c9`). 8/8 touched wip drafts compile standalone.
- ✅ QB-extracted `VertStickerSlap` + `WallPlant` present via `tools/qb_extract.py` (both hash-validated pairs); `0x82117C1A` (`Wait`) resolves via the registry TSV.
- ✅ Step 3/6 extras: `docs/dol-qb-hash-resolved.tsv` regenerated `380 → 2,577` rows (`81.1%` of the `3,177` lis+ori constants); warning-only gen `--check` + apply `--dry-run` zero-literals check added to `tools/final_verify.sh`.
- ✅ Followup (2026-09-04): `.rodata2` NUL-delimited word harvest (`merge_dol_tokens`, lowest-priority gap-fill after the decoded archives) names the config-flag table at vaddr `0x8029007C` — `0x86137A88` → `QB_NTSC` in `fn_80119094.c` (header `3,863 → 3,864`, exactly `1` literal swept, DOL still byte-identical `sha1 ff6faeb0…`, TSV doc unchanged). `0xAF11B50F` remains raw by design: its hashed string (`NoExtraMemory`) exists nowhere on the disc — only `NoExtraMem` (→ `0xECB06BC6`, a different constant) is present. Exhaustive proof: hashing every printable run + NUL word in all 18 DOL sections, all 163 pre archives (raw + decoded) and every other disc file finds ZERO strings → `0xAF11B50F`.
- ✅ Followup 2 (2026-09-04): 45-candidate census → 23 recovered (`3,864 → 3,887` defines, 30 literals swept, `docs/dol-qb-hash-resolved.tsv` `2,577 → 2,587` rows, 81.4%). Sources: `qb_extract.merge_inner_tokens` (inner-script NUL tokens: `fixblend`/`modulate`/`diffuse`/`fixsub`…), `resolve_qb_hashes.merge_dol_tokens` (all DOL data sections, rodata2 first), `merge_qb_file_names` (raw `*.qb` + `*.qb.ngc`), `merge_dol_hash_records` (sec-9 `[u32 LE][name\0]` script-name table, hash-self-validated: `ngc_pal60`/`ngc_dvd_*`/`ngc_60hz`/`ngc_50hz`/`showmessage`). All gap-fill — header diff is pure additions. `LED`/`WARN` stay raw (non-NUL runs only, unprovable). DOL byte-identical (`sha1 ff6faeb0…`).
- ✅ Followup 3 (2026-09-04): all 1,197 remaining unnamed literals get `QB_UNKNOWN_0x<value>` placeholders (`3,887 → 5,084` defines, 2,246 literals swept across 923 files, 0 churn). Value-embedded names are stable across regenerations — identifying one later = rename the macro + its uses. Floats/masks/MMIO appear only as placeholders, never misnamed. DOL byte-identical (`sha1 ff6faeb0…`).
- ✅ Followup 4 (2026-09-04): THPG debugger name table (`debugger_names.dbg`, PS2/Wii, tcrf.net — same Neversoft QB hash, verified 3,401/3,401 agreement + 0/200 sample mismatch) committed as `docs/thpg-qb-names.tsv`, consumed by new `merge_dbg_names` (lowest-priority gap-fill, re-hash-validated on load, 0 skipped). **574 of 1,197 `QB_UNKNOWN_0x…` placeholders identified** incl. `0xAF11B50F → QB_NOEXTRAMEMORY` (its name existed only as a compile-time constant) and `0x2B248E4A → QB_LANGUAGE`; `apply_qb_constants.py` gained an idempotent placeholder-rename pass (`qb_hash.subst_qb_placeholders`) so identifying constants later is a one-shot gen+apply round-trip. 1,394 placeholder refs renamed across 350 files; `docs/dol-qb-hash-resolved.tsv` `2,587 → 2,777` rows (87.4%). 623 placeholders remain (floats/masks + names absent from both disc and THPG table). DOL byte-identical (`sha1 ff6faeb0…`).
- ✅ Followup 5 (2026-09-04): context-verified NON-QB names for the provable subset — new `gen_qb_constants.MANUAL_NAMES` ({value: fixed macro name + comment}, checked BEFORE the dict so a coincidental hash can't steal a context-verified name) names 5 constants with game-file evidence: the fn_8012xxxx streamed-file parser's ASCII chunk fourccs (`0x48454144` HEAD / `0x56494431` VID1 / `0x4652414D` FRAM / `0x56415544` VAUD — compared against buffer reads) and the PRNG LCG multiplier `0x41C64E6D` (`state*0x41C64E6D + 0x3039`, fn_8026AA08). Placeholders `5,084 → 5,079`. Census of the remaining 623: ~226 are hash-role values with NO evidence of their name (stays `QB_UNKNOWN` by design), ~191 value-shape floats/masks + ~30 float thresholds + ~111 other-role magics — most deliberately stay unknown because naming-by-role risks wrong names (e.g. `0x3FF00000` = hi word of double 1.0 in fdlibm `pow`, NOT f32 1.875). DOL byte-identical (`sha1 ff6faeb0…`).
- ✅ Followup 7 (2026-09-04): 26 provable-role placeholders promoted from comment to fixed name (`4,999 → 4,973` defines, 236 refs renamed across 108 files) — new `MANUAL_NAMES` entries, each verified role-unambiguous at every usage site and dict-collision-free: `QB_UINT32_MAX` (`0xFFFFFFFF`), streamed-file fourccs `QB_FOURCC_AUDD/AUDH/VIDD/VIDH` + `QB_STREAM_STATE_NONE`, GX grays `QB_COLOR_GRAY8/GRAY64` (`0x080808FF`/`0x404040FF`), `QB_MASK_BYTE1/BYTE2`, the fn_802556C4 bit-reversal set `QB_BITREV_MASK_{BYTE,NIBBLE,2BIT,BIT}_{HI,LO}` (even/odd bit naming corrected), `QB_SWAR_ONES`, `QB_RNG_STEP`, write-only magics `QB_OBJ_MAGIC`/`QB_MAGIC_DEADBEEF`/`QB_MAGIC_DEADDEAD`, boot triple `QB_BOOT_SENTINEL_1..3`, `QB_INT_TO_DOUBLE_BIAS` (2^52). Multi-role values (`0xFFFF0000`, `0x80808080`) keep role comments instead. DOL byte-identical (`sha1 ff6faeb0…`), `gen --check` stable, apply dry-run 0/0, `final_verify.sh` exit 0.
- ✅ Followup 6 (2026-09-04): placeholder comments role-accurate; 80 spurious placeholders dropped (`5,079 → 4,999` defines, 87 commented). `referenced_values` now masks strings/comments before counting literals → inline-asm `.long` opcode words (fn_800FE42C, fn_801BBAE0 …) no longer create placeholder macros; new `UNKNOWN_COMMENTS` {value: comment} in `gen_qb_constants.py` labels provable-role placeholders from usage context — 40 fdlibm fp bit patterns (hi-words/masks/poly-splits, f32-vs-f64 verified at each usage site), 6 GC MMIO registers, and 41 structural values: SWAR/bit-reverse masks (fn_802556C4, fn_8026B3A4 DETECTNULL, rng.c), object-state flag bits, field masks (`0x0FFFFFFF`…`0x7FFFFFFF`), sentinels (DEADBEEF/DEADDEAD/1234ABCD/FADEBABE+FACCED00+CACCFACC triple), streamed-file fourccs (AUDD/AUDH/VIDD/VIDH/NONE), RGBA colors (`0x080808FF`, `0x404040FF`), ARGB channel masks, `0xFFFFFFFF` (UINT32_MAX + QB-hash init). The rest keep `/* unknown */` (hash-role values). 1,296 objects rebuilt byte-identical (`sha1 ff6faeb0…`), `gen --check` stable, apply dry-run 0/0, `final_verify.sh` exit 0.

## 5. Risks & non-goals

- **Do not wire `**/*.ngc|*.ps2`** (plan-survey counts `61 .ngc` → `3013` names, `1804` new, `0` rescues; `AGENTS.md M6.86b` reports the fuller `.ngc`+`.ps2` survey as `89` files / `3228` runs / `0` rescues — same conclusion either way) — `100%` garbage `A9dVT`, survey `tools/resolve_qb_hashes.py:70` recursive note.
- **Float/mask safety:** `71/2845` hashable already named; new sources add only true `QB` strings, so `0x43300000` etc. never get misnamed `QB_<NAME>` (dict miss). No new `DOL_LO/HI` filter needed. Post-M6.87c they appear ONLY as `QB_UNKNOWN_0x…` placeholders (never misnamed) — verified: no `#define QB_` line for any of `0x43300000`/`0x3F800000`/`0xFFFFFFFC`/`0xCC008000`/`0x40490FDB` that isn't a `QB_UNKNOWN_0x` name.
- **Short-name / run-scan hygiene (executed decision):** `NAME_RE` relaxed `{4,}→{1,}` per Step 3, but raw scans keep `min_len=5`, so the float-pool 2-4 char junk (`A0`, `C4`, `Ea` from rodata2 float constants) stays out; the registry TSV col-1 feed carries the 15 short registry names (`Wait` → `0x82117C1A` now resolves) and the decoded-QB `\x2B` pairs are hash-revalidated before entering the dict.
- **`.prf/.prd` already covered** via `pre/*.pr*` `tools/resolve_qb_hashes.py:65`.

## 6. Open decisions (resolved)

- Q1 both `TSV + sec8` → approved, implement both.
- Q2 full QB extract → approved, implement parser.
- Q3 lazy → keep `src/wip`-only header, add `--all-dol` audit flag later if needed.
- Q4 hex sort + CI → keep hex, add warning-only `--check` to `final_verify.sh`.
