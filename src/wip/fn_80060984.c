// WIP DRAFT (non-matching) - hand-rebuilt from the DOL at 0x80060984.
// family=m2c range=0x80060984-0x80060AB4 size=304B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT THIS FUNCTION IS (recovered from the DOL, byte-proven):
//   Walk a CIRCULAR singly-linked list whose head lives at arg0->unk0x10.
//   For every node whose `unk0x0->unk0x14` is non-NULL, call the skeletal
//   ray/bone test fn_80050868 with two out-f32 slots on the stack (r1+0x18,
//   r1+0x1c); keep the node that produced the SMALLEST first out-slot (the
//   seed is the rodata float lbl_80293EE0, so the first non-NULL node always
//   wins), and remember that node's second out-slot.  Afterwards, if the
//   f32* arg5 is non-NULL, store the second out-slot through it, and return
//   the callee's s32 result (0 if the list yielded no call at all).
//
// FIXED (each verified by measurement, see MEASURED below):
//  * the callee's arg0 is NOT arg1.  Want loads the guard value out of the
//    node and calls with it live, so the guard value IS the first argument.
//    m2c passed `arg1` and made the loaded value a throwaway test - that one
//    semantic error cost the entire body shape.
//  * the walk is `while (sp10 != sp8)` over a circular list, not a
//    NULL-terminated walk; m2c's `var_cr0_eq` flag was that `!=` test.
//  * a condition-register field OTHER THAN the default is live across the
//    call: want hoists the arg5 test ABOVE the loop and re-tests it after
//    the loop.  That only falls out of `while` + a SEPARATE trailing
//    `if (arg5)`; wrapping a do-while in the same `if` collapses both tests
//    into the default field and the condition-register save disappears
//    (measured: 25.0% -> 48.7%).
//  * file-local typedefs for the node (unk0x0 = Inner*, unk0x4 = next) and
//    for arg0 (+0x10 head) replace the corpus `CStruct` guess.
//  * sp10 must be spelled `volatile`: as a plain pointer it stays in a
//    callee-saved register and the whole prologue collapses by 4 words.
//  * ...but the INITIALISER must be the statement form
//    `sp10 = 0; if (sp8) sp10 = sp8->unk0x4;`.  The ternary
//    `sp8 ? sp8->unk0x4 : 0` emits an extra branch that want does not have.
//  * the callee-argument pins are pinned as a PARTIAL group (arg1->r26,
//    arg2->r27, arg4->r29, arg5->r30; arg3 left free).  Pinning all five is
//    WORSE (51.3% vs 55.3%) because it drags the whole register-copy block
//    after the float-copy pair; leaving arg3 free keeps the arg3 copy in
//    want's position.
//
// MEASURED (tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80060984):
//   verdict NEAR, 55.3%, and the object .text is SIZE-EXACT at 304 B, equal
//   to the // range= size marker.  Prologue (0x80 frame, float saves at
//   0x60..0x78, GPR save at 0x48, link-register slot at 0x84,
//   condition-register slot at 0x44) and the whole epilogue match want word
//   for word, as do the loop body and the callee's 9-arg setup.  Local slots are exactly want's: sp8 +0x8, sp10 +0x10, sp18
//   +0x18, sp1C +0x1c.
//
// FRAME NOTE (ngccc 2.95 local-slot layout, measured here):
//   locals are allocated (a) ALL `volatile` ones first, in DECLARATION
//   ORDER, then (b) the non-volatile ones.  That is why `padA`/`padB` sit
//   between the two pointers, and why the trailing `volatile s32 padN` block
//   is what grows the frame to 0x80 / Gsave 0x48.  Seven 4-byte pads is
//   exact (6 -> 0x78, 8 -> 0x88); with no pads the whole thing is a
//   different size and the index-aligned score is meaningless.
//
// VERIFIED CLEAN despite the DIFF verdict (all four METHOD.md audit items):
//   1. object .text = 304 B == the `// range=` size marker == symbols.txt
//      `size:0x130` for fn_80060984.  No extra sections (no private .rodata).
//   2. every branch displacement equals want's decoded displacement and
//      the single call relocation targets fn_80050868 (0x80050868) - checked
//      by hand against tools/ps_disasm.py output, all 6 branch sites agree.
//   3. both extern anchors are real symbols.txt entries:
//        lbl_80293EDC = .rodata2:0x80293EDC
//        lbl_80293EE0 = .rodata2:0x80293EE0   (want builds both addresses
//        from the same page base plus low offset)
//   4. emitted inline-asm instruction count: 0.
//
// === PARKED (2026-10-01) - NEAR 55.3%, size-exact ===
//
// REMAINING BLOCKER: purely the PREHEADER BLOCK ORDER + register choice for
// the list-head value.  34 of 76 words differ, all in two places:
//
//   (a) want's preheader loads the head, sets up the float and zero seeds,
//       copies the GPR and float args into their homes, tests the head for
//       null, and stores the head slot LAST - i.e. the head pointer LIVES in
//       r10 across all the moves and its store to 8(r1) is the LAST preheader
//       step, the signature of a register-pressure SPILL of a plain local,
//       delayed by the allocator.  The build instead stores 8(r1) immediately
//       after the load (volatile-store ordering) and re-loads it before the
//       compare, so a scratch register carries it.  The same sp8 slot is
//       otherwise used identically, so this is a spill choice, not a semantic
//       difference.
//
//   (b) the callee's float-argument setup order.  Want interleaves the two
//       frame-address computations with the two float-register copies; the
//       build emits both address computations first, then both copies.
//       Pure final-scheduler ordering of an independent argument web.
//
// Both are below the level the C source can reach without either (i) giving
// up the r26..r30 colours, which is worth -7 points and reorders (a) further,
// or (ii) hand-pinning the sp8 spill target, which is what is already tried.
// Measured and rejected:
//   * partial pin sets, all 31 non-empty subsets of {r26..r30} (best = the
//     current 4-of-5 at 55.3%; pinning all five = 51.3%; pinning none =
//     48.7%).  So arg3 must stay unpinned - pinning it drags the whole
//     register-copy block after the float-copy pair.
//   * init spelling: ternary `sp8 ? sp8->unk0x4 : 0` (27.3%), if/else with an
//     explicit else (28.6%), `: sp8` (27.3%), plain `if` with no else (21.1%)
//     - all emit the extra branch or drop the lazy store the statement form has.
//   * loop shape: `while` (20.5%), rotated goto (21.8%), `if(guard){while}` +
//     trailing store (17.7%), `for(;;)` (20.5%).  Only the statement-form
//     `do/while` + separate trailing `if (arg5)` produces the hoisted test on
//     a separate condition field and therefore the condition-register save
//     that want has.
//   * source-statement order of the four initialisations: 6 permutations
//     tried, the best four all score exactly 55.3% (order-insensitive).
//   * zero-code barriers (`__asm__("")`, `__asm__ volatile("")`,
//     `__asm__("" : "+r"(v))`) before the loop, inside the loop head, and
//     after it: all INERT, 28.6% either way - they do not block the rotation
//     this loop needs.
//   * `register ListNode * volatile sp8`: INERT (48.7%, unchanged).
//   * flags: all eleven of -fno-schedule-insns / -insns2 / -gcse /
//     -sched-interblock / -sched-spec / -thread-jumps / -expensive-optimizations
//     / -strength-reduce / -branch-count-reg / -rerun-cse-after-loop are
//     inert or negative here.
// NOT TRIED: the clean allocation of the second test to its own condition
//   field suggests the original source may have had the arg5 test as a
//   separate `if` on a value the compiler could CSE - a form where the store
//   is guarded by a SECOND, redundant `if (arg5)` (so the compiler keeps two
//   tests on two fields, and the second one survives the loop).  Not measured.
// Side-by-side residual: tools/venv/bin/python tools/want_got.py 0x80060984 --file src/wip/fn_80060984.c
#include "types.h"

/* rodata seeds: want uses two separate `lis` + `lfs` pairs, so two externs */
extern f32 lbl_80293EDC;
extern f32 lbl_80293EE0;

/* callee: 7 GPR args (r3..r9) + f1/f2, s32 result in r3 */
s32 fn_80050868(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4,
                f32 *arg5, f32 *arg6, f32 farg0, f32 farg1);

/* the circular list: node->unk0x0->unk0x14 is the callee's arg0 */
typedef struct ListNode ListNode;

typedef struct {
    char pad0x0[0x10];
    ListNode *unk0x10;
} CStruct;

typedef struct {
    char pad0x0[0x14];
    s32 *unk0x14;
} Inner;

struct ListNode {
    Inner *unk0x0;
    ListNode *unk0x4;
};

s32 fn_80060984(CStruct *arg0, void *arg1, void *arg2, void *arg3, void *arg4,
                f32 *arg5, f32 farg0, f32 farg1) {
    register s32 *pa1 __asm__("r26") = arg1;
    register s32 *pa2 __asm__("r27") = arg2;
    register s32 *pa4 __asm__("r29") = arg4;
    register f32 *pa5 __asm__("r30") = arg5;
    /* want keeps arg1..arg5 in r26..r30 for the whole loop */
    /* locals in ngccc slot order: volatile block first, then the rest.
       the two pads below put sp8/sp10 at +0x8/+0x10 and sp18/sp1C at
       +0x18/+0x1c, which is what want uses. */
    ListNode * volatile sp8;
    volatile s32 padA;
    ListNode * volatile sp10;
    volatile s32 padB;
    volatile f32 sp18;
    volatile f32 sp1C;
    f32 var_f30;
    f32 var_f31;
    s32 var_r31;
    s32 *p;
    s32 temp_r3;
    volatile s32 pad0;
    volatile s32 pad1;
    volatile s32 pad2;
    volatile s32 pad3;
    volatile s32 pad4;
    volatile s32 pad5;
    volatile s32 pad6;

    var_f30 = lbl_80293EDC;
    var_r31 = 0;
    var_f31 = lbl_80293EE0;
    sp8 = arg0->unk0x10;
    sp10 = 0;
    if (sp8 != 0) {
        sp10 = sp8->unk0x4;
    }
    do {
        p = sp10->unk0x0->unk0x14;
        if (p != 0) {
            sp18 = var_f31;
            temp_r3 = fn_80050868(p, pa1, pa2, arg3, pa4, &sp18, &sp1C,
                                  farg0, farg1);
            if (var_r31 == 0 || sp18 < var_f31) {
                var_f31 = sp18;
                var_r31 = temp_r3;
                var_f30 = sp1C;
            }
        }
        sp10 = sp10->unk0x4;
    } while (sp10 != sp8);
    if (pa5 != 0) {
        *pa5 = var_f30;
    }
    return var_r31;
}
