# 45 — Compiler-generated savegpr/restgpr stubs are not expressible in C

**Status: SOLVED (2026-09-25) — BOTH halves are promoted byte-exact:
`__save_gpr` (0x80274A78, 0x4C) and `__restore_gpr` (0x80274AC4, 0x4C).**
See "Solved" at the bottom; the original verdict below is kept for the
reasoning trail.

**Original status: OPEN. Identified (2026-08-26).**

## Members

| addr | size | symbols.txt name |
|---|---|---|
| 0x80274A78 | 0x4C | `__save_gpr` / `_savegpr_14` (scope:global) |
| 0x80274AC4 | 0x4C | `__restore_gpr` / `_restgpr_14` (scope:global) |

## Root cause

These are the runtime library's callee-saved register spill/restore entry
points, not ordinary functions: the save half stores registers r14 through r31 word-wise from the incoming r11 base at negative displacements ending 4 below it, and the restore half loads the same register range from the same base, each ending with a return. The saved area base is the **incoming r11** (the caller's frame pointer,
passed by convention when the caller needs many saves) and the set of
registers touched is **arbitrary caller state**. No C body can reproduce
this: the function has no frame, receives its addressability through a
non-ABI register, and must spill registers the compiler believes are its own
callee-saves. Every reconstruction attempt under both compilers (mwcc
GC/1.2.5n harness and ngccc) either collapses to a different register set or
requires transcribing the whole 19-insn body as inline asm.

## Why we don't asm-transcribe them

The whole-body-asm ban (`AGENTS.md` §4g ASM_FUNC pattern + recipe 180's
≤30% law): objdiff would score an asm transcription EXACT while nothing is
decompiled. dtk already carries these as auto-asm with their `scope:global`
labels, so callers resolve at link; there is nothing to gain.

## What matched instead (context)

The three ProDG-newlib functions immediately after them DID match as real C
in (see `AGENTS.md` §6as): fn_80274B10/B4C/B80 are newlib
abort_exit machinery, not part of this stub family.

## Retry hints

Only worth revisiting if the project ever allows per-function raw-asm units
outside the banned pattern (e.g. a sanctioned `.s` split like decomp projects
that implement `_savegpr_14` in assembly source files). No C shape, flag, or
register-pin trick can reach it.

## Solved 2026-09-25 — file-scope register variables bind the incoming registers

`__save_gpr` (0x80274A78, 0x4C, `scope:global`) is **promoted byte-exact** as
ordinary C. The insight is that the "non-ABI register" objection is exactly
what GCC's file-scope register variables exist for:

```c
register unsigned int save_base __asm__("r11");   /* the caller's spill base */
register unsigned int save_r14  __asm__("r14");
/* ... one per r15..r31 ... */

void __save_gpr(void) {
    __asm__(".globl _savegpr_14\n_savegpr_14:");   /* zero-width label only */
    *(unsigned int *)(save_base - 0x48) = save_r14;
    __asm__(".globl _savegpr_15\n_savegpr_15:");
    *(unsigned int *)(save_base - 0x44) = save_r15;
    /* ... */
}
```

Why this works where the earlier attempts did not:

1. **File-scope (not local) register vars** are the only spelling that binds an
   operand to a register ngccc does not allocate — and, as with the MetroTRK
   context blobs (doc 36/40), they emit **no** save/restore prologue of their
   own. Local `register ... __asm__("rN")` pins inside the function body would
   make ngccc push a frame.
2. ngccc only *warns* (`call-clobbered register used for global register
   variable`); it compiles cleanly and the object's `.text` is exactly 0x4C
   with **no** `.rodata` and no `.rela.text`.
3. The `_savegpr_14..31` jump-in labels are preserved with zero-width
   `__asm__(".globl _savegpr_N\n_savegpr_N:")` directives — these are *label
   directives*, not transcribed instructions, so recipe 180's ≤30 % asm law is
   not in play (asm share here is 0 instructions; the whole body is C stores).

**The link trap (the real time sink).** The first promote attempt failed with
`patch_dol`'s `Init r2 setup computes 0x803D2F40, expected 0x803D2F80` and a
`.text` exactly 0x4C short: nothing references `__save_gpr`, so mwld
dead-stripped it and the sequential LCF placement packed every later section
down by 0x4C. The `force_active:` entry was written as `fn_80274A78` — the
*split key* — which is not a symbol; mwld needs the real name `__save_gpr`.
See doc 13's 2026-09-25 section for the one-command `nm` diagnosis
(a plausible symbol sitting at the *previous* function's address means that
previous function was dropped).

`__restore_gpr` (0x80274AC4) is byte-for-byte the same shape (`lwz` instead of
`stw`, same `r11` base, same `_restgpr_14..31` labels) and **is now also
promoted byte-exact** with the identical recipe plus a `- __restore_gpr`
force_active entry. Both objects compile with only the call-clobbered-register
warning, `.text` = 0x4C, no `.rela.text`, no `.rodata`.
