// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80059A30-0x80059ACC (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

// === PARKED (2026-10-01, r4; 2026-10-15: 84.6% -> 94.87%, 2 words left) ===
// Best: NEAR 94.87%, object .text = 156B = symbols.txt size:0x9C = this range marker
// 2026-10-15 LOAD-BEARING (each measured): `register s32 *sda r30` sdata-base
// pin + `sda = 0x80300000` after the first call (first anchor lis lands on
// want's slot with r30; also preserves the stmw-r27 frame), sda[i] indexed
// stores (r30-based, no extra bases), `__asm__ volatile("" : "+r"(sda))` +
// reassign before the alloc block (second lis re-materialises on slot),
// hoisted `s32 bytes = arg1 * 4` (slwi precedes the lis), and extern-scalar
// refs for the two TAIL stores (allocator recomputes fresh r9/r11 bases
// like want instead of reusing r30). Residual: `mr r4,r29` before
// `stw r3,0x8b4(r30)` (got sinks the store first) — a call-arg-setup order
// coin; a named ctor-result temp only adds `mr r0,r3`. Single-scheduler
// variants (-fno-schedule-insns XOR -fno-schedule-insns2) preserve everything
// including the pair — the tie never breaks toward mr. Same family as the
// parked fn_80056308 add-last wall.
// (baseline inherited draft: 4.8%).
// 2026-10-16: fused call-arg assign (`fn(sda[0x22D] = ctor(...), arg3)`),
// comma form, and an early a3-temp all keep the identical 2-word mr/stw
// residual. The tie is sched-only (both ready after the ctor bl); leave
// parked — do not retry arg-fusion/temp ladders.
//
// Load-bearing fixes (4.8% -> 84.6%):
//  1. SEMANTIC: the copy loop was descending (`copy[-i] = arg0[-i]`). want is an
//     ASCENDING doloop `mtctr r31; li r9,0; lwzx r0,r9,r28; stwx r0,r9,r3;
//     addi r9,r9,4; bdnz` -> plain `for (i=0;i<arg1;i++) copy[i]=arg0[i];`.
//     Nested `if (arg1 > 0) { for ... }` emitted a SECOND `cmpwi/ble` (160B);
//     the bare `for` is the only form that is size-exact.
//  2. SEMANTIC/CR: the two `cmpwi arg1,0` tests were CSE'd across `bl
//     Mem_Alloc_3`, making cc1 cache the flag in a callee-saved CR field
//     (`mfcr rX / stw rX / cmpwi crN / mtcrf`). A zero-code
//     `__asm__("" : "+r"(arg1));` between the `lbl_803008A0` store and the loop
//     splits the two tests -> two plain `cmpwi r31,0` (removed again once (3)
//     fixed the length; it is no longer load-bearing, ablation T1_nb).
//  3. ANCHOR PLACEMENT: `copy = (s32 *)lbl_803008A0 = (s32)Mem_Alloc_3(...)`
//     makes `expand` compute the lbl address BEFORE the call (verified in the
//     post-reload RTL: `insn 51 high:SI lbl_803008A0` sits ahead of the `slwi`
//     and the `call_insn`), so the HI16 reload lands at want's slot 19 and
//     survives the `+0x8A0` displacement folding. Plain
//     `copy = ...; lbl = (s32)copy;` puts it AFTER the call (42.5% -> 84.6%).
//  4. `register s32 g_dead30 __asm__("r30");` — want saves r27..r31 and homes
//     the two HI16 anchors in r30; the pinned-but-never-read var reserves the
//     5th callee-saved slot so the prologue (`stmw r27,0xc`, `stw r0,0x24`,
//     frame `stwu -0x20`) matches. ABLATION: dropping it = 84.6% -> 59.0%.
//
// Residual (4 words, all reload placement — NOT scheduling):
//   at instruction 9 want loads the lbl_803008B4 anchor into r30 (live across
//   the calls) while this body loads the constant 8 into r3 there, so the anchor
//   load slips one slot late to instruction 12 and into caller-saved r9; at
//   instruction 19 want loads the lbl_803008A0 anchor into r30 while this body
//   loads zero into r29 instead: the right slot but the wrong callee-saved colour.
//   (insns 14/22 differ only in that base register; the ADDR16 displacements
//   are relocation-masked, so those two are consequences of the above.)
//
// WHY STUCK: this is `reload`'s own HI16 placement + colour choice, decided
// after the front end. `cc1 -dr` proves the post-reload RTL already emits
// `lbl_803008A0`'s high before the slwi/call, so (3) is reachable from C — but
// only for the statement whose value is *cast to a pointer*. The identical
// construct for `lbl_803008B4` never hoists. Measured and all 84.6% / 156B,
// anchor still late in r9: chained assign in the call arg (U3/U6/U7), old-style
// `s32 fn_80126FF4();` (U7), `t = ctor(..); lbl = t;` (W5/Y3/Y4), comma chain
// (W8), `*(s32 *)&lbl = ..` (Y6/Y7), `extern s32 lbl[]` array-ref dest (W6),
// `(s32 *)(lbl = ..)` cast in the arg (P1/P2/P3). One-call diagnostic Y1
// (`lbl = CStruct_ctor(8)`, 152B) shows the 2-call chain is not the trigger.
//
// TRIED 2026-10-14: early `__asm__("" : : "m"(lbl_803008B4))` before the ctor
// chain — 25.6% (160B, first-miss@6), and 15.4% with g_dead30 dropped. The
// address duplicates instead of unifying (same M4/M5 failure as on A0), so the
// NOT-TRIED idea is closed. A `register`-pinned alias was ruled out without
// compiling: no free callee-saved reg exists (r30 is the prize itself), and a
// new pin would grow the stmw range and move the frame.
// ==========================================================================
void fn_800599B0(void);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_80126FF4(s32, s32);
s32 Mem_Alloc_3(s32);

extern s32 lbl_803008A0;
extern s32 lbl_803008A4;
extern s32 lbl_803008AC;
extern bool lbl_803008B4;

register s32 *sda __asm__("r30");

void fn_80059A30(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 *copy;
    s32 i;

    register s32 t __asm__("r3");

    fn_800599B0();
    sda = (s32 *)0x80300000;
    t = CStruct_ctor(CStruct_new(8));
    /* Pinning the ctor result to r3 makes the store use it directly and lets
     * the plain statements below emit want's order: r4=arg3 first, then the
     * store, then the call. Without the pin the result is copied to r0 and
     * the store sinks below the r4 staging. */
    sda[0x8B4 / 4] = t;
    fn_80126FF4(t, arg3);
    if (arg1 != 0) {
        s32 bytes = arg1 * 4;
        __asm__ volatile ("" : "+r" (sda));
        sda = (s32 *)0x80300000;
        copy = (s32 *)(sda[0x228] = (s32)Mem_Alloc_3(bytes));
        for (i = 0; i < arg1; i++) {
            copy[i] = arg0[i];
        }
    }
    lbl_803008A4 = arg1;
    lbl_803008AC = arg2;
}
