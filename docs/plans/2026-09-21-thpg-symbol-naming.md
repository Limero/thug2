# Plan: name THUG2 functions/files from the Wii Proving Ground symbol corpus

**Status:** IN PROGRESS (2026-09-21) — corpus tables, xref table, and file-vote
table built; **10 renames applied across 4 batches** (see §8 actuals); DOL
byte-identical throughout. Next: medium-vote mining per the §8b recipe, or
`// Unit:` headers at promote time (§10).
**Owner:** unassigned
**Related:** `tools/rename_script_cmds.py:1`, `tools/rename_vtable_methods.py:1`, `tools/apply_wip_names.py:1`, `tools/rename_sdk_functions.py:1`, `tools/twin_scan.py:1`, `tools/near_twin_scan.py:1`, `docs/thpg-qb-names.tsv:1`, `docs/rodata2-script-command-registry.tsv:1`, `config/G2TE52/symbols.txt:1`

## 0. Short answer: yes, the Wii game is the useful one

- The Wii Proving Ground extracted build artifacts (linked ELF carrying a full
  symbol table plus per-build linker map reports with `ADDR SIZE FILE NAME`
  rows for functions and variables) are directly usable as a
  `{name, compilation-unit, size}` corpus: ~17.6k functions in the release
  map (~21k in the debug map) across ~1,000 units, including ~20k `STT_FUNC`
  symbols with CodeWarrior-mangled `Class::method` names and `STT_FILE`
  unit records plus debug sections.
- The PS2 Pro Skater 3/4 executables are stripped (no symbol table, no debug
  sections); they embed `__FILE__` assert strings (a `.cpp` vocabulary only,
  no function names). Checked 2026-09-21: main ELFs stripped, and the one
  unstripped binary on the THPS3 disc (the demo launcher) contains only
  Sony-SDK/demo-harness symbols — no game code. PS2 adds nothing; the
  file-vocabulary cross-check (§6) stays deprioritized unless a new dump
  (e.g. THPS4 v1.02) surfaces with `.symtab`/`.mdebug` intact.
- Names in the Wii corpus use CodeWarrior mangling (`Name__ClassFargs`), which
  GNU `c++filt` cannot demangle — budget a minimal purpose-built demangler.

## 1. Why this can work despite the gaps

Three gaps bound what transfers: (a) compiler gap — THUG2 game code is
ProDG/GCC-2.95, the Wii title is CodeWarrior PPC, so instruction bytes differ
almost everywhere except trivial leaves; (b) engine drift — 2001 (THPS3) →
2004 (THUG2) → 2007 (THPG), so methods were renamed/restructured and Wii-only
subsystems (Wii input, online, later story/goal systems, middleware `.obj`
units) have no THUG2 counterpart; (c) no address correspondence — linking must
be by content (bytes, strings, shapes), never by address. The plan below only
auto-applies renames on content evidence and keeps everything else as hypotheses.

## 2. Estimate: how much can actually be named

Measured inputs (census scripts, re-run before executing — numbers drift as
matching progresses):

- THUG2 pool: **9,465 unnamed** `.text` functions (`fn_` prefix) vs 2,017
  named (of which 1,185 are `Script*` from the in-game command registry).
  Unnamed sizes: 1,387 ≤ 16 B, 3,764 ≤ 64 B, 7,570 ≤ 256 B; median 88 B.
- Wii corpus (release map): 17,625 functions; minus ~2,067 Wii/Nintendo-SDK-ish
  rows and ~2,037 middleware `.obj` rows → **~13,521 candidate-shared
  functions in 779 files** (top: `SkaterCorePhysicsComponent.o` 297,
  `GoalResolvers.o` 219, `Goal.o` 201, `PedLogicComponent.o` 127, …).
- Shared-string sample: 108 of 334 clean THUG2 string literals (32%) appear
  verbatim in the Wii build — the anchor pool for Tier B is real.

| Tier | Evidence | Est. yield | Basis |
|---|---|---|---|
| A — twins | Cross-game identical bytes (trivial leaves only) | **~10–25 pending a second-evidence gate** (revised down, see §8) | Raw byte twins measured **0** (addresses differ everywhere); same-size+same-mnemonic matches cover 1,085 unnamed small functions, but only **21 are 1:1 unique-shape pairs** (~12 game-code, rest SDK-route: `GXInitLightPos`, `PushContext`, `GetAnimTimes` look right, `EnableMetroTRKInterrupts`-style collisions show why the gate matters) |
| B — string-anchored | Same unique string referenced + size gate | **7 one-to-one pairs → 4 graduated** (measured, see) | 1,318 shared strings → 235-row xref table; only 7 pairs are 1:1 with an unnamed THUG2 side (Wii recall capped at 20 — see recall note below) |
| C — script handlers | Wii script-function table vs THUG2 command registry | **Confirmation, not new names** (see §8) | After stripping the `Script` prefix, **824/1,329** THUG2 command names exist as Wii `Script*` functions (of 1,202 still-`fn_` handlers, 822 match) — renames stay sourced from THUG2's own registry per policy; Wii is the stability proof |
| **Total exact names** | Tiers A–C, high-confidence only | **10 applied; realistic tail ~10–30 more** | Direct-evidence veins (string 1:1s, structural twins) are mined out; remainder comes from vote mining at ~1 graduate per 10–20 reads (batches 3–4 hit rate) |
| D — file grouping (not names) | Component-unit majority vote from anchored neighbors | **2,000–4,000** attributable to a `.cpp` | 779 shared-candidate units; grouping value without exact-name risk |

Deliberately excluded from estimates: SDK/runtime units (already covered by
`rename_sdk_functions.py`), Wii-only subsystems, middleware `.obj` units.

## 3. Phase 0 — build the corpus tables (no tree writes beyond new docs/tools)

1. New parser `tools/parse_thpg_symbols.py`: read the ELF symbol table (FUNC +
   FILE records) **and** all per-build linker maps → emit
   `docs/thpg-func-names.tsv`
   (`mangled | class | method | unit | size | builds_seen`) and
   `docs/thpg-file-list.tsv` (unit inventory with SDK/middleware flags **plus
   `inferred_folder` and `folder_evidence` columns — `proven` where a full
   source path survives in the ELF debug data, `heuristic` where the folder
   is inferred from the §10 mapping table, `unknown` otherwise**).
   Reconcile builds (keep functions seen in ≥2, note size variance).
   Function rows inherit their unit's folder via join, so every Tier A–C
   rename proposal and every Tier D file vote carries a folder from day one.
2. Minimal CodeWarrior demangler (`Name__ClassFargs` → `Class::method`);
   validate on the large component units before trusting any rename.
3. Gate: corpus tables committed before any rename tool runs.

**Actuals (2026-09-21):** `tools/parse_thpg_symbols.py` built and run;
`docs/thpg-func-names.tsv` **18,727 rows** (56,953 map rows unioned across
the 3 builds; `rows` column preserves multiplicity), `docs/thpg-file-list.tsv`
**1,028 units** (`game 742 / sdk 177 / middleware 89 / thpg-only 15 /
wii-only 5`), **91 proven folders** (ELF `.debug` paths + pathed FILE
entries; third-party trees forced to `sdk`). ELF side: 19,991 `STT_FUNC` /
1,038 `STT_FILE` / 58 units with debug paths; 5,695 rows carry a mangled
name, 2,603 of those demangled to a class. Parser is deterministic
(re-run byte-identical) and read-only toward the decomp. Demangler caveat:
`Q<n>` counts need backtracking (`Q23Obj…` = Q2, not Q23); bare `__`-leading
helpers keep their raw name with empty class.

## 4. Phase 1 — high-confidence anchors (only auto-rename sources)

In order of evidence strength; every rename must pass its tier gate **and**
the global gates in §7:
1. **Byte twins** — measured DEAD (raw cross-game twins: 0). Do not re-run
   without a new normalization idea; the mnemonic-shape follow-up (1,085
   candidates → 21 unique pairs) is also exhausted (see Tier A second-evidence
   pass in §8).
2. **String-anchored matches** — for each shared unique string, list
   referencing functions on both sides; propose a name only when the
   candidate pair also agrees on size class and structural shape
   (leaf/wrapper/vcall-dispatch family).
3. **Script-table cross-check** — diff the Wii script-function table against
   `docs/rodata2-script-command-registry.tsv`; confirm existing `Script*`
   names, name the unnamed-handler remainder.

## 5. Phase 2 — file-level inference (hypotheses doc, never src renames)

- For each THUG2 function with ≥1 anchored neighbor (shared string,
  caller/callee edge, twin), take a majority vote of Wii units →
  `docs/thpg-file-votes.tsv`
  (`fn_ADDR | proposed unit | inferred_folder | votes | confidence`).
  Project convention keeps `src/fn_*.c` filenames address-based for now, so
  this answers "which file / which folder" without moving sources — it is
  the staging table for the eventual folder split (§10).

## 6. Phase 3 — tooling (mirror the existing renamers)

- New `tools/rename_thpg.py` copying `tools/rename_script_cmds.py`
  mechanics verbatim: `^fn_[0-9A-F]{8}$` guard, `+ scope:global`, `// Name @
  ADDR` marker, word-boundary caller sweep over `src/*.c` + `src/wip/*.c`,
  idempotent. **Default is dry-run** (prints every change, writes nothing);
  `--apply` writes but REFUSES on any collision or non-`.text`/non-`fn_`
  target. Every entry carries a tier/confidence column; only Tiers A–C
  high-confidence rows are applied. C names follow §6a; the tool validates
  them and **refuses on collision** (never silent overwrite). (Note: unlike
  the script renamer there is no `--all` mode — every THPG rename is an
  individual evidence decision.)
- PS2 follow-up only if Phase 0 leaves file-vocabulary gaps: extract SLUS
  `__FILE__` strings and diff against `docs/thpg-file-list.tsv`; proceed
  only if it surfaces pre-2007 modules the Wii corpus lacks.

### 6a. C++ methods in C: naming + signature rules

The corpus names are CodeWarrior C++ methods (`CompactPool::Free`), but all
THUG2 game code compiles as C — so every method flattens to a C identifier
with an explicit `this` parameter. This is already proven ground: matched
code passes object pointers as arg0 everywhere, and flat `Module_Function`
names are the existing convention (`Mem_Alloc`, `Mem_Free`, `Script*`).

1. **Name:** `Class::Method` → `Class_Method` (`::` → `_`). Class prefix
   keeps cross-class uniqueness for free.
2. **Overloads:** C cannot overload — first verified claim wins the plain
   name, later same-`Class_Method` claims get `_2`, `_3`, … plus a note.
   Same method in *different* classes needs no suffix.
3. **Ctors/dtors/file-inits:** `__ct`/`__dt` → `Class_ctor`/`Class_dtor`
   (`void` return, explicit `this` — verify per prologue); `__sinit_X_cpp`
   TU-init helpers keep their names (already C-linkage-shaped free
   functions). Template/operator spellings are sanitized case-by-case; the
   tool refuses anything ambiguous.
4. **Signature:** instance methods take `this` as arg0 in r3 — byte-identical
   ABI to the C++ call convention, so `s32 CompactPool_Free(void *this)` is
   exactly what the matched body already declares. Type it `Unk_X *` where
   the struct class is known (both first-batch allocator fns share
   `Unk_C8FEE62D`), else `void *`. Static/free functions unchanged.
   Corollary : Wii methods that take no `this` (static-member
   style, e.g. `Config::CommandLineContainsFlag(flag, argc, argv)`) keep the
   BARE method name — the `Class_` prefix is for instance methods that need
   the class to disambiguate, not for names already unique (`sIsPrefixedWith`,
   `Plat_Init` likewise).
5. **Traceability:** the TSV's `mangled|class|method` columns are the source
   of truth; the C name is a deterministic derivation, never hand-edited.
6. **Edge cases (park-if-seen, none in the first batch):** `this`-adjustment
   thunks from multiple inheritance, and virtual overrides sharing one body
   (one name per address — first-wins like `rename_vtable_methods.py`).
7. **`Script*` names are reserved for THUG2 registry handlers.** Even when a
   Wii `ScriptFoo` method size-matches a THUG2 function (mining hit
   this on `ScriptPushWorldLights`, `ScriptEnableFog/DisableFog`,
   `ScriptAutoRail`), the name may only be used if THUG2's own registry maps
   that command to that address — all four turned out to be real commands
   with DIFFERENT handlers, so every one was rejected. Same reason small
   getter pairs and set/clear twins (`fn_8001B8B0/B8C0` both shape-match one
   Wii callback) never graduate on shape alone.

## 7. Verification gates (before every rename commit)

1. Signed `@ha/@l` decode check on any address-derived evidence (a
   plausible-but-wrong name still scores masked-EXACT — established hazard).
2. Full rebuild + linked-DOL byte-identity check, then regenerate
   `PROGRESS.md`.
3. Re-run twin scans to catch duplicate-symbol/split-overlap breakage.
4. Record per-batch actuals vs the §2 estimates here (estimate → actual loop).

## 8. Pre-rename checklist (all read-only; no rename until every box ticks)

- [x] **Corpus tables** — `docs/thpg-func-names.tsv` (18,727) +
  `docs/thpg-file-list.tsv` (1,028 units, 91 proven folders). Deterministic,
  read-only toward the decomp.
- [x] **Demangler spot-validation** — `Obj::CCapCameraComponent::
  InitFromStructure(Script::CStruct*)`, `GX::DirectWrite_f32`, `Pip::`
  helpers all decode against their debug context; `Q<n>` backtracking and
  `__`-leading helpers handled.
- [x] **Tier A measurement** — raw twins 0; 1,085 same-shape candidates, of
  which 21 are 1:1 unique-shape pairs (candidate list reproducible from the
  map + ELF + DOL; probes were throwaway, rerun via a committed tool if
  needed).
- [x] **Tier C measurement** — 824/1,329 name stability proof recorded above.
- [x] **Tier A second-evidence pass (first batch, 2026-09-21)** — all four
  structural candidates are already matched (byte-identical sources), so
  semantics are directly readable. Verdicts:
  - `fn_80010A00` → `region.o::MemAvailable` — STRONG (nullable-sub-region
    free-space difference; same `Unk_C8FEE62D` allocator family as 12154).
  - `fn_80012154` → `CompactPool.o::Free` — STRONG (pool-slot pop/push;
    cross-confirms 10A00 via the shared struct).
  - `fn_80054860` → `nx.o::sRenderWorld` — MODERATE (6 no-arg subsystem
    calls; callees are large pipeline stages `0x264–0xDA4`).
  - `fn_8002DDAC` → `AnimController.o::GetAnimTimes` — WEAK (conditional-swap
    float copy; held for Tier B string evidence, NOT in first batch).
  - The ≤40B 1:1 pairs (bitstream/memman getters) fail the gate: no
    immediates, shape-only evidence. They wait for Tier B.
  - Register-sensitive 1:1 matching yields **0** — the compiler gap forces
    mnemonic-level comparison plus independent confirmation, never shape
    alone.
- [x] **Tier B xref table** — `tools/build_thpg_string_xrefs.py` committed;
  `docs/thpg-string-xrefs.tsv` built (1,318 shared strings, 236 rows with any
  xref; THUG2 recall 249, Wii recall 20). Only same-string + size/shape pairs
  graduate (7 one-to-one pairs → 4 renames).
- [x] **Tier D votes** — `tools/vote_thpg_files.py` committed;
  `docs/thpg-file-votes.tsv` (1,054 unnamed: 226 high / 806 medium / 22 low).
- [x] **Wii recall attack, CONCLUDED negative** — `mr`/small-data/reloc/table
  extends all measured zero gain (see recall note in actuals); do not reopen
  without a new idiom hypothesis.
- [x] **`tools/rename_thpg.py`** — built on the `rename_script_cmds.py`
  mechanics with tier/confidence columns; **default is dry-run** (verified on
  the first batch: 3 symbols.txt lines + 31 src + 12 wip files previewed,
  nothing written); `--apply` writes but REFUSES on any collision
  (batch-internal and vs existing symbols both probe-tested) or
  non-`.text`/non-`fn_` target; method cross-check warn-only against
  `docs/thpg-func-names.tsv`.
- [x] **Verification gates (§7)** green on every batch so far, actuals recorded
  below.

### 8b. Batch recipe (the exact loop batches 3–4 ran — reuse verbatim)

All commands run from the repo root with `tools/venv/bin/python` unless noted.
Probes go in `/tmp/` (never in `tools/` or the repo root); only promoted,
reusable tools land in `tools/` plus an AGENTS.md table row.

1. **Propose (vote + size):** join `docs/thpg-file-votes.tsv`
   (high first, then medium) against `docs/thpg-func-names.tsv` sizes for
   the voted unit; keep non-`Script*` Wii names within ~6–15% size diff.
   (Throwaway script territory — see probes.)
2. **Eliminate (registry grep, batch step zero):** every `Script*` candidate
   must be grepped against `docs/rodata2-script-command-registry.tsv` —
   if the command exists with a DIFFERENT handler, reject immediately
   (killed ~90% of candidates here).
3. **Verify (semantic read):** read each surviving `src/fn_*.c` (or wip draft)
   and confirm the body means what the Wii name says. Reject on any
   meaning gap (flush ≠ listing, pointer-builder ≠ boolean test, counter ≠
   setter); hold generic `Init`/getter/set-clear-twin cases for a second axis.
4. **Dry-run:** `tools/venv/bin/python tools/rename_thpg.py
   0xADDR:CName:TIER [...]` (default dry-run — writes nothing). Check the
   previewed files make sense.
5. **Apply + verify:** same command with `--apply`; then
   `tools/ninja build/G2TE52/main.dol` + `cmp orig/G2TE52/sys/main.dol
   build/G2TE52/main.dol` (must be identical — renames are names-only).
6. **Record:** append batch actuals below (§7 gate 4) and extend the renamed
   list in §8c.
7. **Refresh the derived tables:** renames invalidate downstream TSVs —
   regenerated `docs/thpg-file-votes.tsv` after batches 3–4 dropped exactly
   the 3 renamed rows (1054 → 1051; their last votes agreed with the new
   names, a nice post-hoc check). Re-run `vote_thpg_files.py` after every
   batch; consider promoting newly renamed functions into its `ANCHORS`
   dict when they have caller fan-out (still the original 7 — BannerCheck
   et al. are leaves with ~1 caller each, not worth it yet).

### 8c. Renamed symbols (running list — 137 total, all DOL byte-identical)

 (Tier A): `MemAvailable` (0x80010A00), `CompactPool_Free`
(0x80012154), `sRenderWorld` (0x80054860). (Tier B):
`GetFreshId` (0x800A5418), `PoolManager_SSetupPool` (0x80012170),
`NextRaceWaypoint` (0x80192D24), `SkaterGapComponent_end_gap` (0x801C30FC).
 (Tier D mining): `BannerCheck` (0x80015870), `queue_front`
(0x800169FC). (Tier D high votes): `s_find_trick_in_mapping`
(0x801A53C0).

**Actuals — (2026-09-21):** `MemAvailable` (0x80010A00),
`CompactPool_Free` (0x80012154), `sRenderWorld` (0x80054860) applied via
`rename_thpg.py --apply`: 3 symbols.txt lines (`+ scope:global`), 109 token
replacements across 31 src + 12 wip files, `// Name @ ADDR` markers placed.
Rebuild: `main.dol` **byte-identical** (`cmp` clean). Next: Tier B xref table for the next pass.

**Actuals — / Tier B (2026-09-21):** `tools/build_thpg_string_xrefs.py`
committed; `docs/thpg-string-xrefs.tsv` built: 1,317 shared strings,
235 with any xref (THUG2-side recall 249, Wii-side 20 — Wii `mr`-copied
address webs and table-driven loads are a known scanner gap, documented in
the tool; empty `wii_funcs` is never negative evidence). Graduated 4:
`GetFreshId` (0x800A5418, `autoid%d` sprintf-until-unique — verbatim match),
`PoolManager_SSetupPool` (0x80012170, type-name string into pool registrar),
`NextRaceWaypoint` (0x80192D24, 768B vs 756B + waypoint-script-id string),
`SkaterGapComponent_end_gap` (0x801C30FC, gap-default `Unnamed Gap` string).
Held: `GetAnimTimes` (conditional-swap copy, still string-only),
`animblendsubset::Init`, `gs_init::Init`, `config::Init` (generic `Init`
names need a second axis), all ≤40B getter pairs (no immediates).
Applied via `rename_thpg.py --apply` (12 tokens); rebuild **byte-identical**.
**Actuals — Tier D v1 (2026-09-21):** `tools/vote_thpg_files.py` committed;
`docs/thpg-file-votes.tsv`: **1,054 unnamed funcs (226 high / 806 medium /
22 low)**, 833 with folders. Signals: S1 strings (34 dual-side strings),
S2 verified renames (87 edge votes), S3 name-identical `Script*` commands
(3,180 edge votes from 1,185 anchors — the 824-overlap Tier C finding made
productive). Structural discovery en route: Wii groups script-callable C
functions into per-domain `Xfuncs.o` units (`cfuncs/scriptfuncs/gfxfuncs/
sfxfuncs/mcfuncs/skfuncs/netfuncs/…`) → new `Sk/Scripting` folder rule.
Tool is deterministic (caught + fixed one set-order tie-break). Refreshed
after batches 3–4: 1,051 rows (223 high) — the 3 dropped rows were exactly
the renamed functions, whose final votes matched their new names.
Running total: 7 symbols renamed, 1,054 grouped, 0 bytes changed.

**Actuals — Wii recall attack (2026-09-21, CONCLUDED negative):** three
extends to the xref scanner all measured zero gain — `mr`/`or` page-copy
propagation, r13/r2 small-data loads, ADDR32 relocation pre-application
(34,963 applied), and full pointer-table-indirection resolution. Decoding
showed why: the dominant Wii idiom (`lis` page + `lwzu` table entry +
indexed pointer load) reads tables that are **zero in-file**
(runtime-filled or non-string data), and most string traffic flows through
runtime pointers. Two probe bugs caught en route: wrong DOL header offsets
in the probe (not the tool) and an unsorted-map first-match testing the
wrong function bytes (a page-collision site, correctly negative — verified
by re-running on the true container). Tool + committed TSV re-synced
(1,318 shared, 236 rows, Wii 20). Recall work stops here; growth comes from
mining votes, not from the scanner. Debugging traps recorded for the next
traveler: always verify the test container's range arithmetic by hand, and
re-run on the true container before blaming the tool.

**Actuals — / Tier D mining (2026-09-21):** size-match mining over
high votes produced many 0%-diff pairs, but semantic reads rejected most —
`ScriptGetMemCardDirectoryListing` (flush ≠ listing), `IsElementInFocus`
(returns pointer, no test), `SetRootScreenElement` (returns a count),
`shouldReset` (GPU-fifo packer), `begin` (ambiguous 2-call body). Graduated 2:
`BannerCheck` (0x80015870, lazy banner-handle acquire + counter, release
sibling `fn_800158D8` shares its globals — Wii has no BannerRelease, so the
sibling stays unnamed), `queue_front` (0x800169FC, display-queue front work
with fullscreen-rect dims). Applied (44 tokens); rebuild **byte-identical**.
New §6a rule 7 (Script-name reservation) and the set/clear-twin exclusion
came out of this round's rejections. Running total: **9 symbols renamed**.

**Actuals — / Tier D high-vote mining (2026-09-21):** full high-vote
sweep (non-Script Wii names, ≤6% size diff) produced a long candidate list,
but the registry-elimination grep rejected ~90% in one stroke (every
`Script*` size-match — `PushWorldLights`, `EnableFog`, `AutoRail`,
`SpawnScript`, `AddScene`, … — maps to a different existing handler).
Semantic reads rejected the rest (`get_type_name`≠list-insert,
`UnregisterAllocator`≠reader, `sHide` too generic ×3 ambiguous,
`dump_printf`/`file_print`/`make_angle_in_range`/`s_is_angle` no fit,
`MultiParseNodeArray*` 3-way tie no fit, `ChangeLevelCode` unverifiable
without its string content). Graduated 1: `s_find_trick_in_mapping`
(0x801A53C0, trick-mapping lookup + TRICKNAME/TRICKSLOT/ISCAT extraction,
284B exact, v3.0). Applied (16 tokens); rebuild **byte-identical**.
Running total: **10 symbols renamed**. Lesson: vote+size proposes, registry
+ semantics disposes — keep the elimination grep as batch step zero.

**Actuals — / link-order clusters (2026-09-21):** user hypothesis
"order corresponds" tested on the Banner family — answer: order does NOT
transfer 1:1 (Wii: Exists→Check→Create→Move contiguous; THUG2:
Check→Release?→…→Move? with different neighbors — engine drift), and
`fn_800158D8` specifically is NOT `BannerCreate` (992B vs 100B): it is the
refcount-release sibling of `BannerCheck` (shared globals, adjacent
addresses = same TU, near-certain) with NO Wii counterpart in mcfuncs.o
(only Exists/Check/Create/Move exist) — do not force it; left unnamed.
What DOES transfer is **cluster co-location + adjacency**: the map file is
size-grouped, so sort by address for true link order; THUG2's 0x800158xx
run votes mcfuncs across 6 functions, matching Wii's mcfuncs Banner block.
Graduated 1 from this: `BannerExists` (0x80015B38, `CARDCheck`-gated
existence boolean, 92B exact, v3.0 high, same cluster). Held: `BannerMove`
candidate `fn_80015A58` (slot-address + validator call — plausible move,
unprovable; needs a second axis). Applied (7 tokens); rebuild
**byte-identical**. Running total: **11 symbols renamed**.

### 8d. Tier E — link-order cluster corroboration (never standalone)

New evidence axis from (not a rename source by itself):
1. Recover Wii link order by sorting map rows by address (the file groups
   by size — file neighbors are meaningless).
2. Adjacent THUG2 functions sharing globals (e.g. `BannerCheck`/`fn_800158D8`
   sharing two globals at adjacent addresses) are same-TU siblings —
   use this to *corroborate* a vote-based proposal, or to *predict* the
   family of an unnamed neighbor (release/acquire, set/clear pairs).
3. A same-TU sibling with no Wii counterpart is a legitimate negative
   (`fn_800158D8`): record it and move on instead of forcing the nearest
    size-match.

**Actuals — / GameNet + pair-pattern mining (2026-09-21):** exact-size
sweep over GameNet/skate/gap high votes; registry grep + semantic reads
decided each. Graduated 2: `FirstNewPlayerInfo` (0x8021A0CC, returns NAME of
first checksum-matching player entry, 192B exact), `StartNetworkLobby`
(0x8021B0E4, lobby setup block driving the level-code path, 232B exact).
Key structural find, HELD as a pair: `fn_8021D758`/`fn_8021D888` are
byte-near-identical 152B enumerator wrappers differing only in predicate
(`fn_8022986C` vs `fn_8022A848`), mirroring Wii's `NextItem`/`NextNewPlayerInfo`
pair at the same size — set-level match is high-confidence but individual
assignment is 50/50, so both wait for predicate semantics. Rejected:
`IsMultiplayerGame` (void field-writer), `ShouldBeAbsentNode`/`s_start_network_
game_code` (camera reassignment), `RestartLevel` (score summer), `GetGap`
(single caller cluster inconclusive), `sSgltnInstance`-family ties, 24B
`SetGameMode` lookalikes. Applied (8 tokens); rebuild **byte-identical**.
Running total: **13 symbols renamed**.
**Actuals — / enumerator-pair resolution (2026-09-21):** the held
pair decoded on three convergent axes. (1) Predicates are same-offset
bit-tests: bit0 (D758) vs bit0x80 (D888); the 0x80 bit is set during
player/king-announcement handling (`fn_8022A510`), i.e. transient new-player
state. (2) Caller profiles: D758 broad/generic (10: camera, net-goal, misc)
≈ generic `Item`; D888 narrow/state-specific (3, incl. king-announcement
which calls it first) ≈ `NewPlayerInfo`; Wii mirrors this
(`NextPlayerInfo`→`NextItem`, `handle_player_quit`→`NextNewPlayerInfo`).
(3) Pair pattern holds across builds: 152B/152B in cD/cR (the cf 56B
fragments are split-out helpers, not the wrappers — a TU-split variance
lesson: always check all three builds' sizes before citing one). Graduated:
`NextItem` (0x8021D758), `NextNewPlayerInfo` (0x8021D888). Applied (110
tokens — consistent with enumerator fan-out); rebuild **byte-identical**.
Running total: **15 symbols renamed**.

**Actuals — / broad high-vote sweep (2026-09-21):** widest mining
round yet (~25 semantic reads across GameNet/skate/gap/memcard/display/
trick zones). Registry grep + reads graduated 1: `remove_orphan_cluster`
(0x801A80DC, two-stage orphan removal in the trick-mapping neighborhood,
108B exact, high vote). Notable rejections: `ClientShutdown` (pure
forwarder), `s_mem_stat_close` (stat reader ≠ closer), `sDebugCheckForHoles`
(frame loop ≠ heap check), `s_generate_ascii_checksum` (actually a
printf-style formatter — interesting misdirect), `get_state_text` (lazy
allocator, no text), `make_angle_in_range` (slot-table sprintf),
`s_is_angle` (list pruner), `BannerMove` #2 (banner-path sprintf, not a
move), story-skater/menu mappers (QB/pointer switch tables, no Wii name
fit), `GetGap` (caller cluster inconclusive), `dump_*` family (pattern
reject), `SetActiveCamera`/`MassageFaceTexture` (registry handlers exist
elsewhere). Applied (3 tokens); rebuild **byte-identical**. Running total:
**16 symbols renamed**. Hit rate per read is falling (~1/25) — the
high-vote exact-size vein is nearly mined out; next growth is medium votes
or new anchors.

**Actuals — / medium-vote sweep (2026-09-21):** broadest round
(~15 reads + registry grep): 0 graduates. Rejections: `ToggleMetrics`
(dlist ctor), `make_angle_in_range` (slot sprintf), `s_is_angle`
(list pruner), `get_state_text` (lazy allocator), `sGetFixedFileSize`
(menu dispatcher), `UpdateSkaterInputHandlers` analog (level-request
sequence), `s_read_*`/`s_insert_*` story-skater mappers (switch tables),
`handle_obstacle_course_msg` (goal-tag dispatcher — calls `NextItem`,
consistent but unnamed), `DestroyElement` (lens-flare *creator*),
`setBackgroundColor` (hash forwarder). Most remaining medium candidates
are wip/missing sources or multi-way ties. **STOPPING POINT for active
mining** (see §8e).

### 8e. Stop criteria (reached 2026-09-21) — when to resume

Stop because all three hold: (1) batch hit rate fell to 0/15 reads after
three batches at ~1–2 graduates each; (2) every remaining candidate class
is structurally weak (multi-way ties, wip-only semantics, generic bodies);
(3) no new evidence axis is available (Wii recall capped, §8 recall note).
Resume when any one changes: new matched functions become anchors
(strengthening S2/S3 and the refresh loop), a new Wii idiom unlocks recall,
or the medium-vote pool is re-mined after the next refresh. The campaign
compounds: every future match is a potential anchor.
Running total: **16 symbols renamed**, 1,051 grouped, 0 bytes changed.

**Actuals — Wii call graph (2026-09-21):** `tools/build_thpg_callgraph.py`
committed; `docs/thpg-callgraph.tsv` (**36,998 edges**, `caller|callee` as
`unit::name`, deterministic). First version leaked VARIABLES rows into the
function list (20,123 entries) — fixed by parsing only past the FUNCTIONS
header. Reproduces the pair-investigation relations plus new context
(`handle_player_quit` also calls `GetNewPlayerInfoByObjectID`). Use for
symmetric caller queries in future mining rounds.

**Actuals — / config cluster (2026-09-21):** user-proposed,
analyst-verified. All four bodies match verbatim: `sIsPrefixedWith`
(case-insensitive prefix test), `GetCommandLineParam` (argv scan + =value
extraction, calls the former), `CommandLineContainsFlag` (lowercase argv
search), `Plat_Init` (OS-language switch + French font load). Structural
bonus: the three command-line functions are ADJACENT in THUG2 (B0BC/B148/
B23C) in the SAME order as Wii — Tier E corroboration. Size gaps (THUG2
20–40% smaller) recorded as platform-branch drift, not a blocker when
semantics are verbatim. New §6a rule 4 corollary (bare names for this-less
static members). Applied (21 tokens); rebuild **byte-identical**. Running
total: **20 symbols renamed**.

**Actuals — / stringutils run (2026-09-21):** user-proposed six,
all verified verbatim: `StrStr` (case-insensitive substring search),
`LowerCase`/`UpperCase` (in-place case folds), `PrintThousands`
(locale-separator number formatter — uses the language global `Plat_Init`
sets), `DehexifyDigit` (0-9/a-v/A-V nibble decode), `Compare`
(case-insensitive strcmp; resolves the file's own "stricmp?" note).
Structural best-case: all six are CONTIGUOUS in THUG2 (94D0→978C) and
co-located in Wii `stringutils.o` — one unbroken TU on both sides.
Naming per §6a rule 4 corollary (this-less static members keep bare names;
class is `Str`, so no stutter). Applied (49 tokens); rebuild
**byte-identical**. Running total: **26 symbols renamed**.

**Actuals — / user-proposed mixed set (2026-09-21):** 7 proposals,
all verified, 2 adjusted. `Crc_GenerateCRCCaseSensitive` (raw-byte table
CRC — exactly what distinguishes it from case-folding `fn_8000A778`),
`Script_AllocatePools` (10 sequential named pool allocs with progress UI;
registry-clean), `CSkaterCameraComponent_SetMode` (mode arg into camera
node, 1084B matched), `Pip_LoadPre` (pip.o HIGH vote + file-path arg +
preset-loader callers), `LoadAllStartupQBFiles` (language-switch startup
loading calling the former; wip caveat noted). Adjusted per rules:
`Mem::Malloc`/`Mem::Free` → `Mem_Alloc_3`/`Mem_Free_3` — both are
**byte-identical twins** (modulo `bl`) of existing `Mem_Alloc`/`Mem_Free`
(same pool global; `Mem_*2` taken by the same pattern), so the collision
rule forced `_3` and the repo `Alloc` spelling won over `Malloc`.
Applied (283 tokens); rebuild **byte-identical**. Running total: **33
symbols renamed**. Process note: a first apply attempt re-included batch
10's four (already renamed) and the tool's atomic REFUSE caught it — no
partial writes; batch proposals must be deduped against §8c first.

**Actuals — / audio+script-engine set (2026-09-21):** user-proposed
five. `sSameOrLowerPrecedence` (precedence-table `== → 1` else `tbl[a] <=
tbl[b]`, matched 60B), `AUDSimpleInitAudioDecoder` (AX voice acquire +
ADPCM/mixer state init, wip), `PlayStreamFromObject` (multi-channel stream
setup with volume/pitch args, wip), `AllocateChecksumNameLookupTables`
(two big pool allocs + table zeroing; uses fresh `Mem_Alloc_3`),
`CBaseMenu_PassTargetedEvent` (menu event dispatch with
`QB_NOTIFY_CHILD_LOCK` + child traversal; closest-by-size of five Wii
overloads is `CBaseMenu`'s 2160B — other overloads take `_2` per §6a rule 2
if ever claimed). Applied (15 tokens); rebuild **byte-identical**. Running
total: **38 symbols renamed**.

**Actuals — / menu+face+stringutils set (2026-09-21):** user-proposed
seven, all applied. `SetFacePointsStruct` (eye/nose/lips/H/S/V/width/height
writer, matched), `GetFacePointsStruct` (mirror reader; FaceMassage.o HIGH
vote), `dvd_file_close` (DVDClose wrapper, matched 68B), `Mth_Rnd` (the RNG
PRNG step in hand-written `src/rng.c` — definition renamed by the sweep
since no `src/fn_*.c` exists; class `Mth` from demangling, not bare `Rnd`),
`CBaseMenu_SetProperties` (menu script-param assignment; overload note as
with `PassTargetedEvent`), `CBlurEffect_SetMorph` (`BLUR_*` params prove the
class over closer-sized overloads — size is not the arbiter, params are),
`SetUp` (manual trick-state setup; bare method name per TSV, Wii `Debug.o`
twin noted for future `_2`). Applied (125 tokens); rebuild **byte-identical**.
Running total: **45 symbols renamed**.

**Actuals — / string-heap run (2026-09-21):** user-proposed six,
all applied — the cleanest family yet. `sAddToSpecialStringHeap`
(CRC-dedup intern; calls fresh `Crc_GenerateCRCCaseSensitive`),
`UseRegularStringHeap` (frees the table, clears the mode flag; calls fresh
`Mem_Free_3`), `CreateString` (dispatches on that flag: intern vs
heap-alloc+copy), `DeleteString` (heap-range-guarded free),
`SetScriptString` + `GetScriptString` (setter/getter pair on one
`(arg<<7)+base` slot table). All six contiguous (25088→252BC) and all in
Wii `string.o`. Notes: (1) `SetScriptString` reverses a rejection —
the *name* `make_angle_in_range` was wrong, not the function; the slot-table
pair structure is the second evidence that closed it. (2) Wii versions run
2–10x bigger (debug/error paths); sizes are not the arbiter when six bodies
in a row match verbatim. Applied (40 tokens); rebuild **byte-identical**.
Running total: **51 symbols renamed**.

**Actuals — / RNG + text-element set (2026-09-21):** user-proposed
four, all applied. `Mth_InitialRand` (dual-stream seeder), `Mth_Rnd2`
(stream-2 step, twin of `Mth_Rnd`) — both definitions live in hand-written
`src/rng.c` and were renamed by the sweep (no `src/fn_*.c` involved).
`Mth_PlusOrMinus` (maps `Mth_Rnd(10000)` into [-arg, arg]; parked only on
the FPR frame, logic documented from disassembly — calls fresh `Mth_Rnd`).
`CTextElement_SetProperties` (font/text/rot/blur/shadow property assignment
+ shared tail; class specificity per proposer, no contrary evidence).
Applied (36 tokens); rebuild **byte-identical**. Running total: **55
symbols renamed**. Stale prose refs to old names survive only in the
*generated* `qb_constants.h` comments (regeneration-owned, left alone).

**Actuals — / audio subsystem (2026-09-21):** user-proposed 19,
18 applied — the biggest batch (591 tokens, dense audio call graph). The
music/SFX zone verified as a family: `InitSoundFX` (calls both siblings),
`CleanUpSoundFX` (calls `StopAllSoundFX` + frees voices),
`StopAllSoundFX` (59-slot stop loop), `Pcm_Init` (calls `PCMAudio_Init` +
`GetInteger`; class per proposer, absent from TSV), `PCMAudio_Init`
(memset + mixer init), `PlayTrack` (track driver calling `_PlayMusicTrack`),
`Script_GetInteger` (script int/float extraction), `Script_GenerateCRC`
(calls the checksum fn), `PlayMusicStream` (volume-clamped stream start),
`PauseMusic`/`PauseStream` (twin state machines, `(arg,1)` vs `(arg,0)`),
`SetVolume`/`SetMusicStreamVolume` (twin clamp-stores to music/stream
globals), `AddTrackToPlaylist` (name-normalizing playlist append),
`ClearPlaylist` (playlist-table entry clear, same 0xCB0 stride),
`StopMusic` (state-gated stop flags), `_PlayMusicTrack` (guarded track
play; leading underscore kept — Wii file-static). Rejected 1:
`SetActiveTrackList` (conditionally *calls* the StopMusic candidate —
caller, not the thing itself). Sizes run 20–60% under Wii throughout
(platform drift, recorded). Applied; rebuild **byte-identical**. Running
total: **73 symbols renamed**.

**Actuals — / script-accessor family (2026-09-21):** user-proposed
overload set, all 10 applied — decoded the script value type-tag system:
Add triple `AddInteger(1)`/`AddString(3)`/`AddArrayPointer(0xC)` plus
`AddChecksum(0xD)` (identical bodies differing only in the tag constant),
Get triple `GetInteger(1)`/`GetFloat(2)`/`GetArray(0xC)` plus
`GetString(3|4)` — the `f32*` vs `s32*` out-param and tag constant decide
each. Conflict resolved: `fn_801282E0` was proposed as both GetStructure
and GetFloat — the `f32*` out-param + tag 2 make it GetFloat; `GetStructure`
goes to `fn_80125954` (type-0xA node-struct read) by elimination. Naming:
bare method names, NOT `Script_`-prefixed — the same method exists on
`struct.o`/`array.o`/`symboltable.o` in Wii, so no single class prefix is
right and the TSV method column is the name. Applied (5,269 tokens — these
accessors are called everywhere); rebuild **byte-identical**. Running
total: **83 symbols renamed**.

**Actuals — (2026-09-21):** `CModelAppearance_set_part` (0x8003A5DC,
model-appearance part assembly: HSV params + DESC_ID via the fresh
`AddInteger`/`AddChecksum`/`GetInteger` names). Applied (5 tokens); rebuild
**byte-identical**. Running total: **84 symbols renamed**.

**Actuals — / element/script-accessor set (2026-09-21):** user-proposed
seven, class prefixes adjusted per §6a (single-class methods prefixed,
multi-class methods bare — proposer's bare forms kept only where Wii shows
multiple owner classes). `GetText` (element wrapper delegating to fresh
`GetString`), `ContainsFlag` (recursive checksum-presence search, 0xD tag),
`GetPair` (float-pair store; wip caveat), `CScreenElement_resolve_rgba`
(RGBA byte-pack from script array via fresh `GetArray`),
`CTextElement_AttachBlurEffect` (allocates + attaches the same +0x1A8
handle `Detach` tears down — pair corroboration),
`CTextElement_DetachBlurEffect` (teardown), `CTextElement_SetShadowState`
(boolean state toggle). Applied (1,109 tokens — accessor fan-out);
rebuild **byte-identical**. Running total: **91 symbols renamed**.

**Actuals — / accessor-overflow set (2026-09-21):** user-proposed
8 (7 unique — `SetChecksumTag` listed twice, deduped). `GetVector`
(type-tag-6 vector load — completes the Get triple +1),
`GetChecksum_2` (recursive 0xD-checksum keyed lookup; `_2` per first-wins
since gave the plain name to the type-1 reader — the better fit
argues for a future swap, but no churn without stronger cause),
`SetChecksumTag` (init + `AddChecksum` on object field),
`RemoveFlagTag` (prunes the tag struct via the list-pruner),
`CScreenElement_SetProperties` (the SHARED TAIL called by the menu/text
`SetProperties` drafts + own property dispatch; no TSV row for this class
— class per proposer),
`CScreenElement_resolve_just` (LEFT/CENTER justification resolution via
`GetArray`/`GetChecksum`), `CScreenElement_SetJust` (justification position
update + dirty flag). Applied (1,742 tokens); rebuild **byte-identical**.
Running total: **98 symbols renamed**.

**Actuals — / DVD family (2026-09-21):** user-proposed 15, all
applied — a complete file-API family verified as a call graph: `dvd_read_safe`
(async read + wait), `DVDCheckAsync` (drive-status machine),
`dvd_file_fix_name` (separator/extension normalization),
`dvd_file_size` (lazy length, 36B exact), `dvd_file_open` (fix + lookup +
retry loop, calls both siblings), `dvd_file_eof` (pos >= size),
`dvd_file_read_anywhere` (aligned chunked reads via fresh `dvd_read_safe`),
`dvd_file_fill_cache` (cache drain + advance), `dvd_file_read` (buffered
read via fresh `eof` + `read_anywhere`), `dvd_file_seek` (SET/CUR/END),
`dvd_file_exist` (entry lookup), `dvd_file_getcharacter` (1-byte read via
fresh `read`), `dvd_file_gets` (newline loop via fresh `getcharacter`),
`dvd_file_tell` (position leaf, 8B exact), `Script_RunScript` (type-dispatched
call engine; registry-clean). The family's internal call edges
(open→fix/size, eof→size, fill→read_anywhere, read→eof/read_anywhere,
gets→getcharacter) corroborate every member. Applied (778 tokens);
rebuild **byte-identical**. Running total: **113 symbols renamed**.

**Actuals — / audio-decode family (2026-09-21):** user-proposed
nine, all applied. `AUDSimpleExitAudioDecoder` (voice teardown, mirror of
`Init`), `AUDSimpleAudioReset` (index reset under lock; same globals as
`GetFreeReadBufferSamples`), `AUDSimpleAudioSetVolume` (dual-voice
`AXSetVoiceVe`), `writeChannelData` (mono/stereo interleave copy),
`AUDSimpleAudioGetFreeReadBufferSamples` (ring-buffer free computation),
`audioDecode` (ring management calling the former two — passed AS the
callback to `VAUDDecode`), `AUDSimpleAudioDecode` (128B exact; drives
`VAUDDecode` + `audioDecode`), `VAUDDecode` (32B forwarder; role confirmed
by caller position in the decode path — moderate), `AUDSimplePause`
(dual-voice state set). Applied (32 tokens); rebuild **byte-identical**.
Running total: **122 symbols renamed**.

**Actuals — (2026-09-21):** `GetChecksum_3` (0x8009FDD8, component
lookup by QB-checksum key, 154 callers). Third claim on the name ('s
type-1 reader, keyed search) — returns the *entry*, not the value,
flagged moderate for that reason, but the checksum-key role is unambiguous
across all call sites. Applied (845 tokens — widest fan-out yet, as befits
the lookup workhorse); rebuild **byte-identical**. Running total: **123
symbols renamed**.

**Actuals — / placement-new pair (2026-09-21):** user-proposed
`new Script::CStruct()` decoded as two functions: `CStruct_new` (pool
allocator, called with 8 = sizeof at 468 sites) + `CStruct_ctor` (returns
`this` after running member-init through a leftover-r3 passthrough into
`fn_80126E9C` — recipe-23 pattern; 296× paired call sites). Named in C with
no C++ switch (plain functions + explicit `this` already match the ABI), as
`CStruct_*` (leaf class; outer namespace dropped per precedent). Applied
(1,478 tokens — the idiom's fan-out); full 1,572-step rebuild **byte-identical**
(sha1 `ff6faeb0…`). Environment note: the sandbox clock jumps backward
across commands, which sends ninja into a "manifest still dirty after 100
tries" loop (regenerated files date older than future-stamped deps); fix is
explicit `touch -d` ordering (deps 2026-09-01, build.ninja 2026-09-02),
never re-running configure with different flags. Running total: **125
symbols renamed**.

**Actuals — / overload resolution (2026-09-21):** user-proposed
overload set (same Wii name, different args), all 8 applied.
`GetChecksum_4` (name-keyed wrapper delegating to `GetChecksum_2` — a
genuine (checksum-key, name-key) overload pair, mirroring the `GetStructure`
pair below), `GetStructure_2` (tag-0xA member reader) + `GetStructure_3`
(name-keyed wrapper delegating to it — same pair pattern),
`Script_SpawnScript` (10-arg engine spawn routine; the QB handler
`ScriptSpawnScript` CALLS it, which both confirms the name and resolves the
rule-7 tension: underscore form = engine delegate, unprefixed = command
handler), `GetElement` (finder + rebuild-or-clear container),
`ShouldExecuteAction` (randomized AI action gate via fresh `GetFloat` +
`Mth_Rnd`), `AdjustSpeed` (motion-component speed scaler via fresh
`GetChecksum_3`), `SetChildLockState` (child-lock bit + lock/unlock
notifications). Naming rule refined (§6a rule 1): bare method name when
unique in practice, `Class_` prefix only when shared across classes or
generic enough to collide — recorded from the full 100+ sample. Applied
(559 tokens); rebuild **byte-identical**. Running total: **133 symbols
renamed**.

**Actuals — / goal-manager set (2026-09-21):** user-proposed five,
4 applied + 1 held. `Game_GetGoalManager` (singleton field getter),
`GoalManager_GetGoal` (find-by-id with cursor cache),
`Tmr_GetTime` (timer-delta math, wip), `Pcm_LoadMusicHeader` (guarded header
load, follows `Pcm_Init`). HELD: `GoalManager_LevelUnload` — the visible
~80% of the wip body *builds* goal structs (creates + writes
`GOALMANAGER_PARAMS`), i.e. load-direction work; unload evidence absent.
Do not apply without the tail. Applied (991 tokens); rebuild
**byte-identical**. Running total: **137 symbols renamed**.

**Actuals — / audio-neighbor sweep (2026-09-21):** 0 graduates
(169 unnamed neighbors triaged, ~12 bodies read). Findings, all negative
but load-bearing: the top hub `fn_8011BC38`/`fn_8011BC60` are twin
music/stream-active predicates (`mode==2 → 1` else `flag^1`) — roles
identified, but no Wii name evidenced (candidates `GetCurStreamFileChecksum`
/`SetVolumePlease` don't fit; `MusicIsPaused` is 8B), so they stay unnamed
rather than guessed. `fn_80120924` (flag-wait + subsystem poll),
`fn_8011E2B8` (playlist CRC check — calls fresh `Script_GenerateCRC`),
`fn_8011EC64` (voice-param filler), `fn_8011F3A4` (4B empty stub) likewise
have no Wii counterpart; `fn_80120A00`/`fn_801204CC`/`fn_801D870` are
wip/missing sources. Wii-side max shared callee is only 2x (no hub
analog). Lesson: dense call-graph proximity is NOT evidence by itself —
gated exactly as designed.

**Actuals — globals extraction (2026-09-21):** `parse_thpg_symbols.py`
extended (VARIABLES rows with `- ` separator handling + STT_OBJECT/file
association by symtab order) → committed `docs/thpg-globals.tsv`
(**2,733 globals**: `name|unit|folder|folder_evidence|size|builds_seen|rows`;
func/file TSVs re-verified byte-stable). Highlights: per-component
`spMemberFunctions` tables, `memman.o` heap buffers, `memory.o - __heaps`.
Linkage verdict (measured, negative for the cheap axes): only 9 Wii globals
are string-valued and 0 match THUG2 strings; shared strings are owned by NO
Wii global (anonymous rodata both sides) — so string content cannot name
data labels. Remaining viable axes are structural (`spMemberFunctions` vs
THUG2 component tables, distinctive pools by size+role) and need their own
research plus a data-aware renamer (claims + sources move together — the
function tool must NOT be reused). No data labels renamed.

## 9. Risks

- Engine drift makes exact method names less reliable than unit attribution —
  file votes (Tier D) may end up the largest durable win.
- Same method name in several `*Component` units → always rename with class
  qualification or skip.
- No policy precedent exists for borrowing game-code (non-SDK) function names
  across titles — this plan's tier gates are the policy; do not weaken them
  without review.

## 10. Folder reference + eventual `src/` split

### 10a. Recovered original-tree folders (ELF debug paths + filename heuristics)

Only ~59 full source paths survive in the Wii ELF debug data, but they fix
the tree roots; the rest is inferred from unit-name patterns. Folder roots
(`Sk` = game, `nxcommon*` = shared engine, ported to THUG2-era equivalents —
`sys/NGC` not `sys/wii`, no THPG-only branches):

| Inferred folder | Example units | THUG2 relevance |
|---|---|---|
| `Sk/Components/` | `SkaterCorePhysicsComponent.o` (297 fns), `SkaterCamera/Gap/Rotate/*Component.o`, `CapComponent.o`, `PedLogicComponent.o`, `WalkComponent.o` | high — core gameplay |
| `Sk/Modules/Skate/GoalMgr/` | `GoalManager.o`, `GoalResolvers.o`, `GoalScripts.o`, `GManTools.o` | high — story goals exist in THUG2 |
| `Sk/Objects/` (+ subdirs) | `AbilityFlags.cpp`, `GoalPoints.cpp` | medium |
| `Sk/Scripting/` | `scriptfuncs.o`, `cfuncs.o`, `playcontrolfuncs.cpp` | high — script engine |
| `Sk/Modules/Skate/` (other) | trick/gap/score modules | high |
| anim tree | `*AnimNode*.o`, `AnimNodeFactory.o`, `BonedAnim.o` | high |
| shared `gel/`, `core/`, `gfx/` | `ObjComponent.h`, `HashTable.h`, lookup tables | medium — stable across titles |
| shared `sys/<platform>/` | `p_gx.o`, `p_hwpad.o` | low — rewritten per console |
| Wii-only / THPG-only | `WPAD.o`, `NANDCheck.o`, `SkillTree/`, `Movies/wii/`, online (`CommonGameNet.o`), middleware `.obj` (`gaussianXMotionClassifier`, `dualArchive`, `lyt_*`) | exclude — no THUG2 counterpart |
| SDK/runtime | `AX*.c`, `dvd.o`, `snd_*`, MSL, MetroTRK | exclude — SDK renaming route |

`folder_evidence=proven` applies to the ~dozen units with surviving debug
paths; everything else is `heuristic` until corroborated (e.g. a unit whose
voted functions cluster under one folder across independent anchors).

### 10b. Staging toward real folders (target state)

1. **Metadata first (this plan):** folder rides along as a column —
   `inferred_folder` in `docs/thpg-file-list.tsv`, inherited by
   `thpg-func-names.tsv` rows and `thpg-file-votes.tsv` — plus a
   `// Unit: <folder>/<file>` header line stamped into promoted sources at
   promote time. Zero build impact.
2. **Physical split later:** move sources into `src/<folder>/…` mirroring the
   recovered tree. Blockers to clear first: objects with subdirectory names
   currently get no `base_path` in `objdiff.json` (per-function diff scores
   break), and the flat-file tooling (`add_gen_leaves.py`, sweeps, twin
   scans, all assuming `src/fn_*.c`) must learn subdirectory paths; splits
   must use matching paths. Do not move files until the file-vote table
   covers the moved set at high confidence — a misfiled source is harder to
   find than a flat one.
3. **Migration order when unblocked:** data units (`str_*`, `r2d_*`, …) never
   move (section-addressed, folder-meaningless); move matched game-code files
   folder by folder (Components first — largest anchored set), keeping
   `src/fn_*.c` flat names inside each folder so existing tooling needs only
   a directory-prefix change, not a rename.
