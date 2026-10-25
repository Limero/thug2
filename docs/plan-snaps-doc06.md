# Plan: SNAPS intrinsics + cross-clone transfer (doc 06 and beyond)

Status: EXECUTED (steps 1-3) - idiom RESOLVED, exemplar PARKED on regalloc.
Owner: whoever picks this up next.

## Execution findings (2026-08-20)

Steps 1-3 of the primary work were executed. The SNAPS idiom hypothesis is
CONFIRMED, but the exemplar `fn_8020D530` does NOT byte-match — the residual
gap is a scheduler/register-allocator coin flip, not the idiom.

1. **Step 1 (probe) — VERIFIED.** `__builtin_ps_muls0` -> `ps_muls0`,
   `__builtin_ps_merge00` -> `ps_merge00`, `__builtin_ps_sum0` -> `ps_sum0`,
   `__builtin_ps_madd` -> `ps_madd`, `__builtin_ps_add` -> `ps_add`,
   `__builtin_ps_mul` -> `ps_mul`, all emitted exactly by 3.9.3 under
   `-mps-float`. The wanted block1/block2 opcodes are directly callable.

2. **Step 2 (in-tree PS header) — DONE, but largely REDUNDANT.**
   THUG2's ProDG 3.9.3 already ships the paired-single API as *builtins*:
   `__ps_t` (the PS pair type, == `sn_ps`), the `SN_PS_type` union (`.ps` /
   `.flt.hi` / `.flt.lo`), and every `__builtin_ps_*`. The in-tree header at
   `include/dolphin/SN_PS.h` documents the same interface (one harmless
   "useless keyword" warning — its `typedef union SN_PS_type {...}`
   re-states the builtin union), but it adds nothing: the `ps_*` macros
   just alias `__builtin_ps_*`. The exemplar draft therefore calls the
   builtins directly (`__ps_t` + `__builtin_ps_*` + builtin `SN_PS_type`).
   Also found:
   reading a float out of a PS pair via `*(float *)&pair` ICEs 3.9.3 at
   expmed.c:1115 — use the builtin `SN_PS_type` union (`.flt.hi` = lane 0)
   instead.

3. **Step 3 (rewrite) — semantics nailed, byte-match BLOCKED.** The SNAPS
   reconstruction of `fn_8020D530` compiles to **536B vs 564B WANT** and now
   emits the exact `ps_muls0`/`ps_merge00`/`ps_sum0` idioms (the previous
   `__ps_t`-arithmetic draft fused into `ps_madd`/`ps_mul`). The remaining
   28B = 7 instructions is a **scheduler/register-allocator difference**
   that no source shape or flag (`-fno-schedule-insns`/`-fno-schedule-insns2`/
   `-fno-peephole`, `volatile` products) reproduces: the game's compiler
   **spills the two `ps_muls0` products to a stack pair slot (sp8/sp16 +
   base pointer `r28`) and reloads one**, while 3.9.3 keeps both in
   registers (and emits no `ps_mr` scale copy). Same class as the M5.0e
   `mr r9, r3` / `or. r0,r3,r3` artifacts: an earlier-compiler codegen
   difference, not a source-level one. The improved draft is committed to
   `src/wip/fn_8020D530.c` (inert; see its header comment).

Net: **the idiom is no longer the blocker** (M5.0h is now verified end-to-end),
but steps 4-5 (sweep/promote/bulk) will only match functions whose schedule
3.9.3 happens to reproduce. Re-run the bulk sweep anyway — simpler PS leaves
may still promote — and treat the exemplar's spill as a parked regalloc class.
Clones available locally (cloned for research, read-only references):

- `~/ai/nfsmw` - NFS: Most Wanted GC, ProDG GCC 2.95.3 SN BUILD v1.76 (same compiler family as THUG2)
- `~/ai/Sims2DECOMP` - The Sims 2 GC (G4ZE69, SN-NGC ProDG, build F.09.12.0 Sep 12 2005)

Target doc: `docs/parkings/06-paired-single-ops.md` (currently PARTIALLY SOLVED M5.0).
Remaining gap: `ps_muls0` / `ps_merge00` / `ps_sum0` idiom shapes. Exemplar `fn_8020D530`
compiles to 544B vs 564B WANT; sole diffs are the two idioms.

---

## Findings that changed the picture

1. **The paired-single source API is known.** The game's sources spell PS
   ops through a small header interface, documented in-tree at
   `include/dolphin/SN_PS.h`:
   - `typedef float sn_ps __attribute__((mode(PS)));`
   - `#define PS_BUILD(hi,lo) *(sn_ps*)(float[]){(lo),(hi)}`
   - Intrinsic macros for EVERY missing idiom, all as `__builtin_ps_*`:
     `ps_muls0(x,y)`, `ps_merge00(x,y)`, `ps_sum0(x,y,z)`, `ps_madd(x,y,z)`,
     plus `ps_mul/ps_add/ps_mr/ps_sel/ps_rsqrte/ps_res`, `psq_l/st` family, GQR defines.

2. **THUG2's in-tree compiler has all the builtins.** `strings` on
   `thug2/build/compilers/ProDG/3.9.3/cc1.exe` shows:
   `__builtin_ps_sum0`, `__builtin_ps_muls0`, `__builtin_ps_merge00`, `__ps_t`,
   and the `b_muls0ps3`-style expansion templates
   (`ps_muls0 %0,%1,%2`, `ps_merge00. %0,%1,%2`, `ps_sum0 %0,%1,%2,%3`).
   So the missing idioms are directly callable - no compiler mystery remains.

3. **Scale**: 49,296 PS instructions in the DOL. Gap idiom counts:
   `ps_muls0` 2,033, `ps_merge00` 1,498, `ps_sum0` 995 (~4.5k instructions,
   ~895 functions affected).

4. **Sims2DECOMP Day-0 compiler A/B** (`docs/tracking/walls.md` advisory,
   2026-06-09): all four installed ProDG versions are codegen-identical
   (609 functions x 4 versions, zero flips). Consequence for THUG2 docs:
   any hypothesis of the form "try 3.8.1/3.7/3.5" or "point-version
   difference" is a dead end. ProDG 3.9.3 is the right compiler; use source
   shape, not compiler swaps.

5. **Sims2DECOMP walls doc documents the same allocator wall classes** THUG2
   parks (char-param spill-vs-promote, keep-in-reg + cached-CR, r0-threading,
   branch-prediction layout), all confirmed version-invariant. This supports
   THUG2's existing allocator parks as legitimate.

6. **Scheduling flag knowledge (corrected attribution, 2026-08 cross-clone
   audit; ladder RE-corrected 2026-08 per Sims2 evidence)**. Sims2DECOMP's
   corpus (10,967 files with `// FLAGS:`) uses `-fno-schedule-insns` on
   ~10,340 files (94% - THE workhorse, fixes basic-block store-order),
   `-fno-schedule-insns2` on ~27, and NEVER uses
   `-fno-sched-spec`/`-fno-sched-interblock` in matched code (fuzzer-only,
   no recorded success). The THUG2-proven pair is
   `-fno-sched-spec` + `-fno-sched-interblock` (THUG2's own AGENTS.md §4r,
   M6.23/24: 801F6580 + 800361xx families). Sims2 also adds a flag THUG2
   never swept: `-fno-peephole` (register-swap walls). Corrected priority
   order for scheduling walls: DEFAULT flags FIRST, then
   `-fno-schedule-insns` ALONE (their workhorse - never auto-pair it),
   then volatile-store source casts, then `-fno-peephole`, then the
   sched-spec+interblock pair (last, THUG2-proven). RE-CORRECTION:
   `-fno-schedule-insns2` alone made things WORSE in Sims2 and their
   r11/r9 coloring wall cracked by REMOVING insns2 from defaults - treat
   insns2 as a REMOVAL-tool, not an addition, except THUG2's own
   re-proven cases (AGENTS.md §4p recipes 48/49: call-site order /
   arg0-home). Their `-O1 == -O2` for tested shapes (the scheduler flags
   are the lever, not the -O tier) - expected to inform plan Item D.
   Docs: `Sims2DECOMP/docs/tracking/walls.md`, `Sims2DECOMP/CLAUDE.md`
    recipes 4r/48/49, `thug2/AGENTS.md` §4r.

---

## Primary work: crack doc 06

### Step 1 - probe compile (verify the builtins emit the wanted shapes)

Compile tiny probes with the exact ngccc cmd (`-O2 -G0 -mcpu=750 -mps-float
-fno-common`) using:

```c
typedef float sn_ps __attribute__((mode(PS)));
sn_ps a, b, c;
void t(void) {
    c = __builtin_ps_muls0(a, b);      // want: ps_muls0
    c = __builtin_ps_merge00(a, b);    // want: ps_merge00
    c = __builtin_ps_sum0(a, b, c);    // want: ps_sum0
}
```

Check the 3 wanted shapes from `fn_8020D530`:
- block1 (0x8020D614..64C): `ps_muls0` pair x scalar-lane-0, spill to stack, reload, `ps_add`
- block2 (0x8020D6C8..6E4): `ps_mr f13,f11; ps_mul f13,f13,f13; ps_merge00 f13,f13,f12;
  ps_madd f0,f0,f0,f13; ps_sum0 f0,f0,f0,f0` (dot-product / lane-merge + horizontal sum)

### Step 2 - in-tree PS header (DONE)

The paired-single interface lives in-tree at `include/dolphin/SN_PS.h` —
the type/macro spellings the game sources use, over the compiler's
`__builtin_ps_*` builtins.

### Step 3 - rewrite fn_8020D530 draft

Edit `thug2/src/wip/fn_8020D530.c`:
- Keep `__ps_t` plain pair copies as-is (they already match).
- Block 1: express as `ps_muls0` + `ps_add` via the macros (kills the compiler's
  unwanted `ps_madd`/`ps_mul` fusion).
- Block 2: express the dot-product as `ps_merge00` + `ps_madd` + `ps_sum0`
  macro calls (compiler was generating scalar `fadds`/`fmuls` for `__ps_t`
  lane arithmetic).
- Keep the header `// extra_cflags: -mps-float` marker.

### Step 4 - sweep + promote

```sh
tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8020D530 --extra-cflags "-mps-float"
# on EXACT:
tools/venv/bin/python tools/promote_wip.py 0x8020D530
# verify DOL byte-clean:
tools/ninja build/G2TE52/ok && cmp orig/G2TE52/sys/main.dol build/G2TE52/main.dol
```

### Step 5 - bulk sweep of the two idioms

Scan all ~895 PS functions for the two idiom shapes (block1 scale/add with
stack spill, block2 merge00+sum0 dot), rewrite drafts in SNAPS macro form,
sweep all slices with `--extra-cflags "-mps-float"`, promote EXACTs
one-at-a-time (never parallel - concurrent promote runs corrupt
configure/build state, per AGENTS.md 6e).

### Step 6 - docs

- Update `docs/parkings/06-paired-single-ops.md` (M5.0h: SNAPS intrinsics via
  `SN_PS.h`; status PARTIALLY SOLVED -> SOLVED once exemplar + bulk done).
- Update `docs/parkings/README.md` row 06.
- Reference the Day-0 A/B disproval: "try an SN newer than v1.76 / point
  version" is a dead end (Sims2DECOMP proved all 4 versions codegen-identical).
- Grab the vector math source shapes from the SDK copies for reference:
  `bfbb/src/dolphin/src/mtx/vec.c`, `quat.c`, `psmtx.c` (same files exist in
  nfsmw `bWare/GameCube/dolphinsdk/src/mtx/`) - these show the hand-asm PS
  shapes (`ps_muls0` scale, `ps_madd+ps_sum0` mag/dot) the SDK used.

---

## Secondary work: transfer findings to other parking docs

1. **Flag-recipe port.** Add a flag-matrix mode to `tools/test_wip_drafts.py`
   covering, in priority order: DEFAULT (baseline), `-fno-schedule-insns`
   alone, volatile-store/`// FLAG:` source variants, `-fno-peephole`,
   `-fno-sched-spec`, `-fno-sched-spec -fno-sched-interblock` (best verdict
   wins, tagged with the winning flag like the M5.0b `[dummy]` handling).
   Do NOT add `-fno-schedule-insns2` as an addition-test (2026-08
   re-correction: it made things WORSE in Sims2; their r11/r9 coloring
   wall cracked by REMOVING insns2 from defaults) - keep it only as a
   removal-tool or for THUG2's own re-proven cases (§4p recipes 48/49).
   Order matters: Sims2's 94% workhorse is `-fno-schedule-insns` (and
   their `-O1 == -O2` for tested shapes - the scheduler flags are the
   lever); the sched-spec/interblock pair is THUG2-proven (§4r), not
   Sims2-proven (their corpus never used it). Spot-test on the parked 8
   `mr r9, r3` PS copies (M5.0c/d) and on allocator/scheduling parks
   whose docs claim "every flag tried"
   (e.g. docs 02/03/11/12/15/16/17 family).
2. **Doc-13 linker lead reminder**: tww shares mwldeppc GC/1.3.2 with thug2's
   CRT; if doc 13 (linker drop at 0x8025254C) is revisited, tww is the only
   local clone with the same linker version.
3. **Parking-doc annotations**: in each parking doc whose "candidate next
   steps" suggest a compiler swap, add a one-line note that
   Sims2DECOMP's Day-0 A/B (609 fns x 4 ProDG versions, zero flips) disproves
   version-sensitivity for ProDG 3.5-3.9.3.

---

## Reference material (read-only sources of truth)

- `include/dolphin/SN_PS.h` - the in-tree paired-single interface
- `thug2/build/compilers/ProDG/3.9.3/cc1.exe` - verified to contain all `__builtin_ps_*`
- `thug2/tools/disasm.py` - note: does NOT pass `CS_MODE_PS`; for PS regions use an
  inline capstone one-liner with `CS_ARCH_PPC | CS_MODE_BIG_ENDIAN | CS_MODE_PS`
- `thug2/docs/parkings/06-paired-single-ops.md` - the target doc
- `Sims2DECOMP/docs/tracking/walls.md` - Day-0 A/B advisory + wall classes + flag recipes
- `bfbb/src/dolphin/src/mtx/{psmtx,vec,quat}.c`, `tww/src/JSystem/J3DGraphBase/J3DTransform.cpp`
  - SDK hand-asm PS shape references

## Constraints / gotchas

- `-mps-float` must stay PER-OBJECT (never global - breaks 133 FPR-frame
  functions, proven in `docs/parkings/solved/01-fpr-frame-quirk.md`).
- `promote_wip.py` REFUSEs non-byte-exact drafts; keep the range marker in the
  draft header sized to the real symbol (`symbols.txt` size).
- DOL must stay byte-identical after every promote (`cmp` + `ok` target).
- The 8 `mr r9, r3` copy parks may still be genuine regalloc (the game emits
  `mr r9, r3` once, 3.9.3 stores via r3); try the flag matrix, then the
  `__asm__("" ::: "r3")` clobber trick already proven in M5.0e, then park.