# 90 — E9AC SDK accessor cluster (carved 2026-10-08, 7 of 8)

**Status: 7 carved + split + sweepable; `EC94` blocked on a dtk wall (below).**
The 924B span `0x8025E9AC–0x8025ED48` (after `PSVECCrossProduct`, previously one
`lbl_` + auto gap) is **eight** blr-delimited functions, not one. Seven are
carved in `symbols.txt` with explicit split units (`splits.txt`, sourceless =
byte-extracted like the neighboring `mtx/*.c` units; wiring to C happens
per-function at promotion time). Report regen 2026-10-08 confirms all 8 as
named units (`main/fn_8025E9AC` … `main/fn_8025EC94`, sizes
`156/8/8/8/8/48/508/180`); `fn_8025E9AC`'s re-scoped draft sweeps a true DIFF
(expected — mwcc wall, blocker 3). Remaining: mint per-function WIP drafts
via `gen_wip_drafts.py` (report is fresh; only the gen step pends).

## Cluster map (all sizes verified: prologue→`blr`, contiguous, sum = 0x39C)

| symbol | range | size | shape | note |
|---|---|---|---|---|
| `fn_8025E9AC` | `E9AC–EA48` | `0x9C` | frame `0x20`, r28–r31 saved individually; calls `80264768/90`, `8025F3E0/298/340`, `EA68`; retail arg0 includes literal `0x8025EA98` at some callers (needs symbol form `lis+addi`, cf. blocker 2 below) | re-scoped WIP draft `src/wip/fn_8025E9AC.c` (marker now `0x9C`) is the sweep candidate |
| `fn_8025EA48` | `EA48–EA50` | `0x8` | `stw r3,-0x7738(r13); blr` (setter) | |
| `fn_8025EA50` | `EA50–EA58` | `0x8` | `lwz r3,-0x773C(r13); blr` (getter) | |
| `fn_8025EA58` | `EA58–EA60` | `0x8` | `lwz r3,-0x7740(r13); blr` (getter) | |
| `fn_8025EA60` | `EA60–EA68` | `0x8` | `lwz r3,-0x7F18(r13); blr` (getter; `-0x7F18` = `lbl_803CA368`, `.sdata` scope-local) | |
| `fn_8025EA68` | `EA68–EA98` | `0x30` | frame `0x10`; calls `80262FC0/D0`; r13 traffic `-0x7748/-0x7744` | |
| `fn_8025EA98` | `EA98–EC94` | `0x1FC` | frame `0x30`; many `8025Fxxx`/`8026xxxx`/`80274xxx` calls; **`bctrl`** at `EC78` through fn-ptr; OS-time math | |
| `lbl_8025EC94` (+split `fn_8025EC94.c`) | `EC94–ED48` | `0x1B4` | frame `0x20`; ends `mtlr/addi/blr` at `ED40–44`; next is `fn_8025ED48` | **BLOCKED — still `lbl_8025EC94` (dtk wall below); explicit split unit kept in place for the day it unblocks** |

Known callers (all `bl`, no data pointers into the range — ptrscan clean):
`fn_8001BCA8` calls `fn_8025E9AC(0x180000, …)` and `fn_8025EA48(…)` (WIP draft
`src/wip/fn_8001BCA8.c` already updated to the `fn_` names); `fn_8025ED48`'s
draft takes `&lbl_8025EC94` as an arg.

## The EC94 dtk wall (bisected 2026-10-08, do not re-attempt blindly)

Renaming `lbl_8025EC94` → `fn_ + size:0x1B4` aborts `dtk dol split` with
`Found multiple functions inside a symbol: 1:0x8025EC94 and 1:0x8025ED48`,
**with or without** explicit splits, **with or without** `skip_cfa_ranges`
covering the span. Bisector (`<scratch> pattern — rerun on
demand): orig PASS; EC94-only FAIL; E9AC-only PASS; 7fn+lbl_EC94+splits PASS.
Best-fit rule: dtk walks fallthrough from each start through its still-open
`blr` block (`ED28→ED48` visible uncut, `finalized: false`) and trips when the
walk reaches another start at the symbol's inclusive end; why the identical
abutments elsewhere (e.g. `B180/B340`) survive is unexplained — order effects
suspected. Consequence: EC94 keeps its `lbl_` until dtk is fixed/upgraded; its
explicit split unit stays as a placeholder. Re-verify any retry with
`tools/dtk dol split config/G2TE52/config.yml build/G2TE52` (fast, no
compile) BEFORE touching the tree.

## Blockers carried over from the old cluster draft (2026-10-06 analysis)

1. **Missing `.sbss` globals** (no `symbols.txt` labels): `-0x7734(r13)` =
   `0x803CAB4C` (init flag), `-0x7740` = `0x803CAB40`, `-0x7748` = `0x803CAB38`,
   `-0x773C` = `0x803CAB44`, `-0x7738` = `0x803CAB48`. Extern refs fail
   promotion-link; defining new `.sbss` is stripped by the build's objcopy
   (`-R .sbss`). Workaround precedent: inline-asm r13 wedges (M4.11 wave-1,
   6 of ~39 insns = 15%, under the 30% cap). With `-msdata=eabi -G4` the wedges
   and the `lbl_803CA368` store emit the correct r13-relative forms.
2. Unnamed callees `fn_8025F3E0/F298/F340` need `symbols.txt` additions before
   any link (compile standalone OK — relocs masked).
3. **Compiler identity: evidence points to MWCC, not ngccc** (same as the rest
   of the SDK region): retail saves r28–r31 *individually*
   (`stw r31,0x1c(r1)`…, frame `0x20`) where ngccc emits `stmw/lmw r28` +
   frame `0x18` here; store interleave matches mwcc scheduling. Cluster
   rebuilds should target mwcc GC/1.2.5n `cflags_dolphin`. Best ngccc attempt
   at `E9AC`: 1/35 insns.

---

## Status addendum — 2026-10-09 (post-promotion sweep)

Carved cluster after today's rounds: **5 of 8 promoted to C** (`EA48`, `EA50`,
`EA58`, `EA60`, `EA68` — ProDG/3.9.3 `-msdata=eabi -G4`, all 100% in the
objdiff report). `ED48` (the `fn_8025FAD8(fn_8025EC94)` thunk) is also
promoted. The three still-asm units are `E9AC`, `EA98`, `EC94`, and their
drafts are now pure-C rebuilds with pinned blockers:

* **`E9AC`** — every original blocker is gone (the five `.sbss` slots have
  labels; the `0x8025EA98` address goes through the *symbol*). mwcc GC/1.3.2
  reproduces the whole body except **two shared-value materialisations**: the
  reference keeps `1` in `r6` and the `0x8026` high half in `r4` across the
  global stores and reuses both for the `8025F3E0` call, ours re-emits them
  (164B vs 156B; the literal-address form is 160B). Swept 6 statement orders,
  `base` temps, 3 type pairs, 10 flag sets, 8 mwcc versions — GC/1.2.5n hits
  156B but uses the old prologue, so it is not this region's compiler.
* **`EA98`** — reconstructed code is a draft only (`tb_conv()` math + the
  `bctrl` hook dispatch through `-0x7738(r13)` remain); the call structure and
  the `CAB3C + (idx<<12)` base are known.
* **`EC94`** — exact size (180B) and 80% of words at `s32 irq; s32 level;
  u32 w;`; the residual is one callee-saved swap (reference: param→`r28`,
  `w`→`r31`; ours: param→`r31`, `w`→`r28`). All 6 declaration orders ×
  {`s32`,`u16`} `irq` and 7 mwcc versions tested.

`E9AC`/`EA98`/`EC94` stay as sourceless split units (built as asm objects by
dtk) until an mwcc patch whose constant-CSE/colouring matches; the DOL hash is
unaffected either way (`ok` check: `ff6faeb0…c27c9`).
