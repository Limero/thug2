# 40 — Hand-written context-switch / machine-state blob sliced into pseudo-functions

**Status: OPEN (2026-08-26).** ~11 functions in `0x8025AB94–0x8025B6F4`
are **not compiler output at all** — the original authors wrote a
context-save/restore + console-interrupt blob in assembly (context pointer
carried in r31, privileged ops, cross-symbol control flow), and dtk's function
boundaries slice it into "functions" that no standalone C translation can
reproduce. Park on sight; do not draft-grind.

## Zone map

| addr | identity | size | verdict |
|---|---|---|---|
| 0x8025ABB0 | `Vtable0x80308A40_m16` ctx-field reader | 20B | **EXACT** (see recipes below) |
| 0x8025ABC4 | fragment: unsaved-r31 read, dead `beq .+4`, args staged for a call OUTSIDE the split | 40B | PARKED |
| 0x8025ABEC | MMIO status read + dead mask, returns 0 | 24B | **EXACT** |
| 0x8025AC04 | HW-status spin (`*(volatile u32*)`) | 20B | **EXACT** |
| 0x8025AC18 | flag coupling ACROSS a bl: caller's `bne` consumes the callee's `andi.` CR0 | 196B | PARKED |
| 0x8025ACDC | r31 ctx + mfspr/mtspr + `blrl` via ctx fn-ptr + external branch | 88B | PARKED |
| 0x8025AD64 | interrupt-return tail: full GPR restore from ctx, `mtcrf`, **`rfi`** | 216B | PARKED |
| 0x8025AE3C | `bl` into a MID-BODY label of another symbol; tail `b` into another symbol | 176B | PARKED |
| 0x8025AEEC | makes a call then exits via RAW branch (never `blr`) → any standalone object must burn frame+LR save, shifting every word | 44B | PARKED |
| 0x8025AF18 | strlen entry + shared tail externally entered at +0x24; r28/r29/r31 never saved | 100B | PARKED (16.7%) |
| 0x8025AF7C | SPR/GPR restore from ctx (mtspr ×8) | 68B | EXACT w/ caveat: 47% asm wedge share — reviewer call, disclosed in header |
| 0x8025AFC0 | FP/PS state RESTORE helper (mfmsr/mtmsr/mtfsf/HID2/GQR + psq_l×32 + lfd f0-f31) | 448B | PARKED |
| 0x8025B180 | FP/PS state SAVE twin (stfd×32 + psq_st×32 + mffs FPSCR) | 448B | PARKED |
| 0x8025B340 | pure machine-state save: 66 mfspr/mfsr→stw pairs (XER/CTR/HID/BAT/SR/SPRG/DMA/WPAR) | 532B | PARKED |

Callers that preload r31 and own CR/MSR/LR saves themselves:
`0x8025AD88`, `0x8025B6F4-B6F8`, `0x8025BBE4-BBE8`. The `rfi` lives at
`0x8025AE38` — everything around it is one hand-written unit dtk cannot see.

## Why unmatchable in C (per-member walls)

1. **No prologue / incoming r31.** The helpers receive their context base in a
   register the CALLER preloaded. A standalone compiled function must either
   save/restore it (prologue bytes want doesn't have) or use a file-scope
   global register var — which works for READ-ONLY access (recipe below) but
   cannot express the save/restore twins.
2. **Privileged / FPSCR ops** (`mfmsr`, `mtmsr`, `isync`, `mtfsf`, `mfspr`
   HID2, GQR writes, `rfi`): inline-asm-only encodings; ngccc has no builtin
   or C route.
3. **Dead-FPR traffic.** `lfd f0..f31` / `psq_l` runs load registers nothing
   reads afterwards — GCC DCEs them at every -O level; a bare register restore
   of unnamed FPRs is inexpressible (register-pin locals get copy-propagated
   away or spill to memory).
4. **Cross-symbol control flow**: `bl` into mid-body labels of other symbols,
   raw `b` exits instead of `blr`, shared tails entered externally. Any
   standalone object must add frame/LR-save overhead the want doesn't carry,
   misaligning the whole stream after the first such edge.
5. Asm-share rule: honest reconstruction would be ≥50–85% asm (banned
   transcription territory per AGENTS.md recipe 180) and STILL 0% due to
   cause 1.

## What DID crack in this zone (recipes)

1. **File-scope global register var = save-free access to caller-carried
   registers** — `register s32 *ctx __asm__("r31");` at FILE scope emits bare
   `lwz/stw off(r31)` with zero prologue. Read-only uses are safe; ASSIGNING
   through it forces preservation code. Cracked fn_8025AF7C's prologue-free
   ctx reads. (Extends AGENTS.md §74-161a "file-scope pins get no
   save/restore" to a positive technique.)
2. **Volatile `"=r"` li-birth wedges pin constant emission position** — the
   NON-volatile form still gets scheduled early; `__asm__ volatile("li %0,0"
   : "=r"(z))` holds the li exactly where want has it (fn_8025ABB0: keeps the
   zero out of the lis/ori address pair).
3. **Two-phase asm-consumed dead values** reproduce `[load][andi.][li 0]`
   dead-op sequences no single C expression survives as: compute into a web
   consumed by an input-only asm barrier, then a second barrier consumes the
   overwrite value (fn_8025ABEC).

## Retry hints

- If a future split/tooling change re-draws these boundaries (e.g. claiming
  the whole blob as ONE auto-asm unit), this doc's members collapse with it.
- The glue tails inside AFC0/B180 (lbl_8025BD3C/lbl_8025BC14 calls gated on
  `*(u32*)0x800000D4/D8`) ARE C-emittable — they only fail because they sit
  behind causes 1–4. If anyone ever splits the blob differently, start there.
