// RE-TRIAGED 2026-10-17: still 71.8% (re-measured, body unchanged). One fresh
// family=hand range=0x8002684C-0x80026A84 size=568B
// idea checked on paper and rejected without compiling: inlining the mask
// test (`if ((arg0->unk0x4 & 0x1000000) != 0)` with `= 0` in the else) would
// break want's `stw r8,0x1c(r31)` (the else stores the andis.-result register,
// already 0 — a literal 0 needs a new `li`). The temp_r8 shape is forced.
// PARKED 2026-09-27 (ag24): best 71.8% (unchanged from baseline — no variant improved it).
//   Residual = 40 word diffs, ALL register-colouring / scheduler coin-flips (doc-15 + doc-10):
//     1. HEAD (words 4-16): want base->r11 / mask->r8  vs  got base->r3 / mask->r11.
//        The head base and the 0x400000 cursor SEE-SAW for r11 (want base wins, got cursor
//        wins). Both are global pseudos (live across the if) -> global-alloc colouring.
//     2. 0x400000 block (words ~56-60): want cursor r9 vs got r11 (the other see-saw half).
//     3. align1 (words ~64-72): want `lwz r9,8(r1)` reload / mask r11 / t r0  vs  got
//        `mr r0,r9` store-to-load forward / mask r0 / t r11.
//     4. rowcount (words ~80-88): want lha34,lwz r11,lha r9,slwi,add,stw,stw,slwi  vs  got
//        lha34,lwz r9,slwi,lha r11,add,stw,slwi,stw (cursor/h36 colour swap + slwi interleave).
//     5. call block (words ~92-93): want add,stw,lwz r6  vs  got add,lwz r6,stw.
//     6. align2 (words ~100-104): want mask r11 / t r0  vs  got mask r0 / t r11.
//     7. fill loop (words ~108-114): want `li r29,0` after the entry guard + `cmplw/blt`
//        latch  vs  got `li r29,0` before + `cmpw/bne` latch (the price of the `!=` test
//        that stops GCC rotating the guarded do-while).
//   Tried (25+ distinct source shapes, all <= baseline): declaration reordering; flags/mask/base
//   birth-order swaps; char*/u32 temp types; member-address base (`&arg1->unk0x10`); else-stores-0;
//   rowcount named temps (h34/cur/h36 + separate h34x); fill for-loop and do-while-`<` (both
//   rotate the guard away, -28%); u32 fill counter; align1 volatile-store / memory-clobber /
//   read-once-into-temp / t-before-mask; call-site volatile store; variable recycling (broke);
//   file-scope register pins on base/mask (cascaded to 11%); flags -fno-schedule-insns{,2},
//   -fno-gcse, -fno-strength-reduce. Known family: doc-15 (arg-setup/register-role scheduling
//   coin-flip) + doc-10 (pure regalloc coin-flip). The base/mask/cursor are global pseudos, so
//   the colouring is global-alloc's, not reachable from source shape.
// WIP DRAFT (non-matching) — full semantic reconstruction 2026-09-26.
// Score: 71.8% NEAR at the EXACT 568B size (was 44.6% / 592B m2c baseline).
// Verify: tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8002684C
// Diff:   tools/venv/bin/python tools/want_got.py 0x8002684C
//
// WHAT THIS FUNCTION IS
//   Unpacks a serialized descriptor (arg1, Unk_F48B5CA1) into an expanded
//   record (arg0, Unk_DCC2F5B0), walking a byte cursor `sp8` through the
//   descriptor payload. 0x1000000 -> leading s32 table; 0x80000 -> leading
//   bitmap (byte size = ((v+30)>>5)+1 words past a 4-byte count); 0x400000 ->
//   per-row stride 4 vs 2 units; then one element fixup pass, a row-count
//   block (16 vs 8 units), a 4-arg stub call, and a trailing array fill.
//   Returns 0 if the trailing fill hits a premature end, else 1.
//
// RECONSTRUCTION NOTES (want = 568B / 142 insns, 4 saved regs, frame -0x20)
//  * `sp8[0]` is ONE function-local `s32` BYTE cursor at r1+8. The m2c draft
//    modelled it as a `s32 *` plus a file-scope `static s32 sp8`, which scaled
//    every cursor step by 4 (got `addi r11,r9,0x10` / `slwi r0,r0,6` where want
//    has `addi r11,r9,4` / `slwi r0,r0,4`). Byte arithmetic as plain s32 math.
//  * Declaring it as `s32 sp8[1]` (not a bare scalar) is LOAD-BEARING: with a
//    scalar, GCC 2.95 loop-invariant-motion hoists `&sp8` into a 5th
//    callee-saved register (frame 0x28 / `stmw r27`), want keeps the address
//    materialized in-loop as `addi r3,r1,8`. The 1-element array blocks the
//    hoist and reproduces want's exact 4-saved-reg frame.
//  * `var_r29 = 0` must sit OUTSIDE the guarded `if (... ) { do ... }` block
//    (immediately after the Mem_Alloc_3 call). Putting it back inside the
//    braces re-triggers the same `&sp8` hoist.
//  * The trailing-fill loop needs BOTH an entry guard and a bottom test
//    (want: `cmplw/bge` before the head AND `cmplw/blt` at the latch). With an
//    identical `if (c) { do {} while (c); }` GCC 2.95 rotates the guard away
//    (-2 insns). `while (var_r30_2 != n)` is used instead: var_r30_2 starts
//    at 0, steps by 1 and the guard proves n >= 1, so `!=` is exactly
//    equivalent to `<` here, and the unmergeable test keeps the guard.
//  * fn_80026A84 / fn_80026AA8 are the (obj, rowBase, index) element
//    accessor/writer pair. The counter is post-incremented as the 3rd
//    argument of the second call — that is what puts want's
//    `mr r5,r30; addi r30,r30,1; bl` (copy BEFORE update).
//  * fn_80026668 is a 4-arg `li r3,1; blr` stub: keep the call-site arity so
//    the dead r4/r5/r6 setup survives and no `crclr cr1eq` appears.
//  * Mem_Alloc_3 needs a prototype (otherwise `crclr cr1eq` precedes the bl).
//  * The fill stores through the RELOADED `arg0->unk0x28` pointer with a BYTE
//    offset (`(char *)(var_r29 + (s32)arg0->unk0x28)`) -> `stwx r3,r29,r9`,
//    with the offset in the rA slot. `((s32 *)arg0->unk0x28)[var_r29]` scales
//    the index instead and never matches.
//  * The 0x400000 block must read the cursor INSIDE both arms (a phi), which
//    is what makes GCC emit `lwz count / lwz cursor / slwi` per arm plus the
//    shared add+2 stores tail.
//  * The first 4-byte align reads the cursor through a `volatile` lvalue so
//    the just-stored value is re-read from 8(r1) as in want; without it the
//    function loses an instruction (564B) and drops to 29%.
//  * Declaration order of the head temporaries is an allocator lever
//    (§76-184): declaring mask, base, count in that order is worth ~2.5%.
//
// REMAINING BLOCKER (40 diffs, all confirmed against the raw DOL words)
//  1. REGISTER COLOURING (the bulk). want recycles r11 across five
//     short-lived webs (descriptor base, bitmap base+4, both align masks,
//     row-block cursor) and uses r9 for the 0x400000 cursor / row count, and
//     r8 for the 0x1000000 mask. This build puts the descriptor base in r3,
//     the mask in r11 and the 0x400000 cursor in r11. Declaration order,
//     `char *`/u32 temp types, variable recycling (one variable reused for the
//     head base and the bitmap base+4) and every schedule flag
//     (-fno-gcse / -fno-schedule-insns{,2} / -fno-sched-spec /
//     -fno-sched-interblock / -fno-expensive-optimizations) were tried and
//     all leave the same assignment. This is the doc-15/doc-10 allocator
//     coin-flip class; no source shape moved it.
//  2. 6-word instruction ORDER in the fn_80026AD4 row-count block: want emits
//     both `lha` loads before the `slwi` and both `stw`s before the trailing
//     `slwi`; every spelling tried (hoisting the second lha into a temp,
//     reordering the two stores, reordering the var_r9 assignment) changed
//     the score rather than fixing it.
//  3. `li r29, 0` (byte-offset init) lands before `stw r3,0x28(r31)`; want
//     has it after the entry `bge`. Moving it into the guarded block fixes the
//     position but re-triggers the `&sp8` hoist (1) and costs 24%.
//  4. Latch compare polarity: want `cmplw r30,r0 ; blt`, got `cmpw ; bne` —
//     the price of the `!=` test that keeps the entry guard (see above). The
//     only blocker-free alternative (`while (var_r30_2 + 1 <= n)`) matches the
//     guard but materialises a spurious `addi r11,r30,1` (572B, 61.5%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *Mem_Alloc_3(s32);
s32 fn_8002C638(s32 *);
void fn_80026668(s32, s32, s32, s32);
s32 fn_80026AD4(Unk_DCC2F5B0 *);
void fn_80026AA8(Unk_DCC2F5B0 *, void *, s32);
void fn_80026A84(Unk_DCC2F5B0 *, void *, s32);

s32 fn_8002684C(Unk_DCC2F5B0 *arg0, Unk_F48B5CA1 *arg1) {
    s32 sp8[1];
    s32 temp_r8;
    s32 temp_r11;
    s32 temp_r10;
    s32 temp_r9;
    s32 temp_r11_3;
    s32 temp_r11_2;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r9;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r29;
    temp_r10 = arg1->unk0x0;
    temp_r11 = (s32)((char *)arg1 + 0x10);
    arg0->unk0x8 = temp_r10;
    sp8[0] = temp_r11;
    temp_r8 = arg0->unk0x4 & QB_UNKNOWN_0x01000000;
    arg0->unk0x34 = (u16)arg1->unk0x6;
    arg0->unk0x36 = (u16)arg1->unk0xA;
    if (temp_r8 != 0) {
        arg0->unk0x1C = temp_r11;
        sp8[0] = sp8[0] + temp_r10 * 4;
    } else {
        arg0->unk0x1C = temp_r8;
    }
    if (arg0->unk0x4 & 0x80000) {
        arg0->unk0x20 = sp8[0];
        temp_r11_2 = sp8[0] + 4;
        temp_r9 = *(s32 *)sp8[0];
        sp8[0] = temp_r11_2;
        var_r0 = temp_r9 - 1;
        if (var_r0 < 0) {
            var_r0 = temp_r9 + 0x1E;
        }
        sp8[0] = temp_r11_2 + ((var_r0 >> 5) + 1) * 4;
    }
    if (arg0->unk0x4 & 0x400000) {
        var_r0_2 = arg0->unk0x8 * 4;
        temp_r11_2 = sp8[0];
    } else {
        var_r0_2 = arg0->unk0x8 * 2;
        temp_r11_2 = sp8[0];
    }
    arg0->unk0x18 = temp_r11_2;
    sp8[0] = temp_r11_2 + var_r0_2;
    temp_r11_3 = *(volatile s32 *)&sp8[0] & 3;
    if (temp_r11_3 != 0) {
        temp_r11_2 = *(volatile s32 *)&sp8[0] + 4;
        sp8[0] = temp_r11_2 - temp_r11_3;
    }
    var_r30 = 0;
    if (var_r30 < arg0->unk0x8) {
        do {
            fn_80026A84(arg0, (void *)arg0->unk0x18, var_r30);
            fn_80026AA8(arg0, (void *)arg0->unk0x18, var_r30++);
        } while (var_r30 < arg0->unk0x8);
    }
    if (fn_80026AD4(arg0) != 0) {
        var_r0_3 = sp8[0] + ((s16)arg0->unk0x34 * 0x10);
        arg0->unk0x10 = sp8[0];
        arg0->unk0x14 = var_r0_3;
        var_r9 = (s16)arg0->unk0x36 * 0x10;
    } else {
        var_r0_3 = sp8[0] + ((s16)arg0->unk0x34 * 8);
        arg0->unk0x10 = sp8[0];
        arg0->unk0x14 = var_r0_3;
        var_r9 = (s16)arg0->unk0x36 * 8;
    }
    sp8[0] = var_r0_3 + var_r9;
    fn_80026668((s32)arg0, 0, 0, arg0->unk0x4);
    temp_r11_3 = sp8[0] & 3;
    if (temp_r11_3 != 0) {
        temp_r11_2 = sp8[0] + 4;
        sp8[0] = temp_r11_2 - temp_r11_3;
    }
    if (arg1->unk0xC == 0) {
        arg0->unk0x28 = arg1->unk0xC;
        goto block_26;
    }
    var_r30_2 = 0;
    arg0->unk0x28 = (s32)Mem_Alloc_3(arg1->unk0xC * 4);
    var_r29 = 0;
    if (var_r30_2 < (u32)arg1->unk0xC) {
        do {
            temp_r11 = fn_8002C638(&sp8[0]);
            if (temp_r11 == 0) {
                return 0;
            }
            *(s32 *)((char *)(var_r29 + (s32)arg0->unk0x28)) = temp_r11;
            var_r30_2 += 1;
            var_r29 += 4;
        } while (var_r30_2 != (u32)arg1->unk0xC);
    }
block_26:
    arg0->unk0x38 = (u16)((Unk_A0557B61 *)arg1)->unk0xE;
    return 1;
}
