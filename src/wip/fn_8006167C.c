// WIP DRAFT (non-matching) — hand-rebuilt 2026-09-26, best body 75.6% (10/41 words).
//
// STRUCTURE (established from WANT; the whole loop body, both booleans, the
// call setup and the epilogue are byte-exact):
//   circular-list walk. `h = arg0->unk0x10` is the head; the walk starts at
//   `node = h ? h->unk0x4 : 0` and stops when `node == h`. Per iteration the
//   callee argument is `**(s32 *)node` (two dependent lwz), and the two
//   booleans are materialised SEPARATELY and merged with `or`:
//   `acc = (acc != 0) | (t != 0);` -> [cmpwi][li 1][bne][li 0] twice, then
//   `or` (no mfcr — each cmpwi is consumed by its own branch immediately).
// THE TWO STACK SLOTS ARE LOAD-BEARING: want keeps the head in a slot at r1+8
// and the current node in a slot at r1+0x10, reloading BOTH every iteration
// (`lwz r9,8(r1)` in the latch, `lwz r11,0x10(r1)` at the body top and again
// after the call). Model them as a frame struct of `volatile s32` members —
//   struct { volatile s32 sp8; s32 padC; volatile s32 sp10; } fr;
// The explicit `padC` is what produces want's 0x28 frame: the 8-byte gap
// between the two slots pushes the stmw span to r29-r31 at 0x1c. Without the
// pad both slots pack at +8/+0xC and the frame is 0x20 (v1 = 35.0%). Keeping
// `head` in a plain register instead of the slot costs another 7 words — the
// slot must be the ONLY copy (v2 = 42.5% -> v3 = 75.6%).
// The `fr.sp10 = node` store belongs INSIDE the loop TEST block, so the comma
// condition `(fr.sp10 = node, node != fr.sp8)` is what reproduces it.
//
// PARKED 2026-09-26 on 10 words in two register/order groups (doc-15/33 class,
// no breakthrough — do not re-run the ladder):
//   A. Prologue scratch: want holds `h` in r9 (`lwz r9,0x10(r3) / stw r9,8(r1)
//      / cmpwi r9,0 / li r0,0 / lwz r0,4(r9)`), cc1 picks r11 in every C
//      spelling. A 1-instruction cascade over 5 words.
//   B. Latch block: want is [lwz r11,0x10(r1)][or][lwz r9,8(r1)][lwz r0,4(r11)]
//      [cmpw r0,r9][stw r0,0x10(r1)][bne] — the compare lands BEFORE the slot
//      store; got always emits the store first and folds the sp8 load into r0.
//   Levers tried, all 75.6% or worse:
//     condition-order forms: `node != (fr.sp10 = node, fr.sp8)`,
//       `(fr.sp10 = node, 1) && (node != fr.sp8)`, `for(;;){fr.sp10=node; if
//       (node==fr.sp8) break; ...}` — ALL 75.6% (identical 10 diffs);
//       `fr.sp10 != node || (fr.sp10 = node, node != fr.sp8)` = 20.0%.
//     flags: -fno-sched-spec / -fno-sched-interblock / -fno-gcse = 75.6% no-ops,
//       -fno-schedule-insns2 70.7%, -fno-schedule-insns 31.0%.
//   Both residuals are per-block register/issue choices inside one basic block,
//   not source-reachable — the shape is right, the colouring is not.
//   The latch pair follows from the volatile slots: the two slot accesses keep
//   source order, so the head load can only lead the node-slot store if the
//   head read is the FIRST operand of the loop condition and the store sits in
//   the right-hand operand; every comma spelling evaluated so far puts the
//   store first (`... = node, node != fr.sp8`). A condition written as
//   `fr.sp8 != (...)` still emits store-then-load because the assignment is
//   evaluated before the comparison. That ordering constraint is what pins the
//   r9/r11 split too (want's r9 carries the head).
// TRIED 2026-10-14: hard r9 pin on h (`register s32 h9 __asm__("r9")`) ->
// 26.8% (160B, frame breaks — a caller-saved pin perturbs global alloc, not
// just the prologue); prologue init reorder (`acc = 0` before `h = ...`) ->
// 75.6% byte-identical (the r11 pick is alloc-order, not birth-order).
// family=m2c range=0x8006167C-0x80061720 size=164B
#include "types.h"
#include "structs.h"

s32 fn_8005F8AC(s32, s32, s32);

s32 fn_8006167C(CStruct *arg0, s32 arg1, s32 arg2) {
    struct {
        volatile s32 sp8;
        s32 padC;
        volatile s32 sp10;
    } fr;
    s32 h;
    s32 node;
    s32 acc;
    s32 t;

    h = arg0->unk0x10;
    acc = 0;
    fr.sp8 = h;
    node = (h != 0) ? *(s32 *)((char *)h + 4) : 0;
    while ((fr.sp10 = node, node != fr.sp8)) {
        t = fn_8005F8AC(*(s32 *)*(s32 *)fr.sp10, arg1, arg2);
        acc = (acc != 0) | (t != 0);
        node = *(s32 *)((char *)fr.sp10 + 4);
    }
    return acc;
}
