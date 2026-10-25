// WIP DRAFT — fn_800414B0  (GetListAndFindWindowElement-like list walk)
// family=m2c range=0x800414B0-0x80041564 size=180B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// === PARKED (2026-10-01) ===
// Score: DIFF, object .text = 156 B vs want 180 B (39 words, 6 words short);
// 38/45 masked words differ.  Best of ~25 measured C shapes.
//
// WHAT IS ALREADY RIGHT (verified by hand against the want):
//   * callee audit: fn_80041460(&out, obj) 2-arg (r3,r4) — reads obj->0x58,
//     writes out[0]/out[4]/out[8]=0; CObject_RemoveRefLink(node,&out) 2-arg.
//   * both callees prototyped (kills the m2c crclr); no dead args needed.
//   * locals: one 3-pointer struct at r1+8 (fn_80041460 writes +0/+4/+8).
//   * the QB hash is QB_WINDOWELEMENT 0xA13ADBB7 (re-decoded from lis/ori).
//   * dead `mr r3,r31` before `cmpw` at the loop top REPRODUCES verbatim.
//   * loop body = [QB check; fn_80041460; reload; null test; RemoveRefLink;
//     sp8.f0=0], one peeled copy of the tail before the loop, one shared
//     compare driving both the exit `beq` and the latch back-edge.
//   * got matches want word-for-word over the whole loop-B block.
//
// THE RESIDUAL — all 6 missing words come from ONE cause:
//   want keeps `cmpwi cr4, r31,0` live in the CALLEE-SAVED cr4 across the
//   `bl CObject_RemoveRefLink`, which forces the whole doc-28 CR-save pair
//   (`mfcr r12`+`stw r12,0x1c(r1)` / `lwz r12`+`mtcrf 8,r12`), the 4th saved
//   GPR (r28 = the NULL constant), the 0x30 frame, and the address hoist of
//   &sp8 into r29 with its copy into the first call-argument register:
//   the want saves the condition-register field around the call (a
//   move-from-condition-register into r12 at 0x800414B8 with its store to
//   0x1c(r1) at 0x800414C4, both absent here), re-tests the pre-peel compare
//   with a branch on that saved field at 0x800414F8 targeting 0x80041544
//   across the call, hoists the stack-address computation plus its argument
//   copy at 0x800414CC and 0x800414D0 (both absent here), materialises the
//   NULL constant in r28 rather than r29 (zeroing r28 at 0x80041500 and
//   storing it at 0x8004153C), and restores the field after the call with a
//   load at 0x8004154C and a move-to-condition-register-field at 0x80041558
//   (both absent here).
//   Mechanism: this is docs/parkings/72 (redundant flag-reusing branch) fused
//   with docs/parkings/28 (CR-save).  In plain C the peel's second test of
//   `temp_r31 != NULL` is provably redundant (a local's value cannot change
//   across a call), so GCC's dom/jump-threading deletes the branch; with the
//   branch gone, nothing needs the compare kept across the call, so the CC
//   pseudo lands in volatile cr0 and the mfcr/mtcrf pair, the 4th saved GPR
//   and the bigger frame all disappear.  fn_8011A95C (src/fn_8011A95C.c) is
//   the same phenomenon working: there GCC *hoists* a loop-invariant
//   `out != NULL` into the preheader, keeps it in cr4, and then reuses the
//   live flag for a second branch 20 insns later across a `bl`.
//   Here the tested value genuinely changes every iteration, so there is
//   nothing invariant to hoist.
//
// MEASURED AND INERT (diffs/size unchanged from the parked body):
//   ~25 shapes: [A,B] vs [B,A] body order, while / do-while / for(;;),
//   break / return NULL / goto out, `if (cur) {...} while (cur)` double guard,
//   explicit peel vs implicit, `while (cur)` vs `!= NULL`, decl-order swap
//   (node before struct), pointer vs s32 loop var, `register` + `__asm__("r31")`
//   pin, volatile struct, named zero constant, 12- vs 16-byte struct,
//   zero-code "+r" and "memory" barriers before the loop and before the null
//   test, and flags -fno-schedule-insns / -fno-schedule-insns2 / -fno-gcse /
//   -fno-thread-jumps / -fexpensive-optimizations / -mps-float.
//   The [A,B] order DOES trigger GCC's rtl-loop.c pre-rotation (it hoists the
//   latch block into the preheader — exactly want's peel) but 2.95 then drops
//   the preheader's `bl fn_80041460` and leaves r31 undefined: a genuine
//   ngccc 2.95.3 loop-rotate miscompile, 116 B / 132 B output.
//
// NOT TRIED: a 4-instruction `mfcr`/`mtcrf` asm wedge for the CR-save pair
// (plus one `beq`) — deliberately left alone because it is a fake-the-
// compiler escape hatch, and 5 of the 6 missing words (including the frame
// size and the r28/r29 allocation) would still be unsourced.
//
#include "types.h"
#include "qb_constants.h"

// The container fn_80041460 fills: f0 = obj->0x58, f4 = f8 = 0.
typedef struct Unk_LinkList {
    void *unk0x0;
    void *unk0x4;
    void *unk0x8;
} Unk_LinkList;

// Object whose +0x58 seeds the list (typed as a pointer, not the corpus s32).
typedef struct Unk_ObjA {
    char pad0x0[0x58];
    void *unk0x58;
} Unk_ObjA;

// List node; +0x1C is the QB hash compared against QB_WINDOWELEMENT.
typedef struct Unk_Node {
    char pad0x0[0x1C];
    s32 unk0x1C;
} Unk_Node;

void fn_80041460(Unk_LinkList *out, void *obj);
void CObject_RemoveRefLink(Unk_Node *node, Unk_LinkList *list);

void *fn_800414B0(Unk_ObjA *arg0) {
    Unk_LinkList sp8;
    Unk_Node *temp_r31;

    fn_80041460(&sp8, arg0);
    temp_r31 = sp8.unk0x0;
    if (temp_r31 != NULL) {
        CObject_RemoveRefLink(temp_r31, &sp8);
        sp8.unk0x0 = NULL;
        do {
            if (temp_r31->unk0x1C == QB_WINDOWELEMENT)
                return temp_r31;
            fn_80041460(&sp8, temp_r31);
            temp_r31 = sp8.unk0x0;
            if (temp_r31 == NULL)
                break;
            CObject_RemoveRefLink(temp_r31, &sp8);
            sp8.unk0x0 = NULL;
        } while (temp_r31 != NULL);
    }
    return NULL;
}
