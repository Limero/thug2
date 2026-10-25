// WIP DRAFT (non-matching) — family=hand range=0x80242F80-0x802431F0 size=624B
// PARKED 2026-10-15: re-verified 10.26% size-exact (140 diffs, all register/frame).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// === PARKED 2026-10-06 ===========================================
// Semantics: nested "find the arg2-th child" walk over arg1 entries.
//   k=0
//   for i in [0,arg1->n):
//       e = fn_80241E38(arg1, i); fn_80238964();
//       t = fn_80236EF4(e->w8, 0);
//       if (t->w8 & 0x80) {                 // leaf entry
//           if (k == arg2) { copy e's 12 bytes to *arg0; return; }
//           k++;
//       } else {                             // branch entry: walk children
//           for j in [0,t->m):
//               c = fn_80241E38(t, j);
//               if (k == arg2) { build sp8 from c + byte sums from e/c; *arg0 = sp8; return; }
//               k++;
//       }
//   *arg0 = sp8 (uninitialised fallthrough); return;
// Node layout (16 B): {u8 b0,b1,b2,b3; u32 w4; u32 w8}.  arg1 = {u32 w0; u16 h4; ...; u32 n@0x30}.
// t = {u32 w0; u16 h4; u32 w8@8; ...; u32 m@0x30}.  Result = 12 B (word0 = the byte tuple,
// word4/word8 copied from c).
//
// --- WHAT WAS FIXED THIS ROUND (both real, both verified) -------------------
// 1) The previous body's sp8 byte writes were 8 BYTES TOO HIGH. The original
//    writes four bytes at the base of the result buffer; sp8's base is the
//    buffer start, so those are sp8[0..3]. The old body wrote sp8[8..0xB]
//    (one slot too high) — the "sp8" in the old draft was declared `u8[12]`
//    but indexed as if its base were 8 bytes lower. Fixed by modelling sp8
//    as the real 12-byte Node so the byte writes land in word 0 and the
//    word4/word8 stores copy the child entry. (Offset-fixing the old u8[12]
//    body in place gives the same semantics and the same 14.79% score.)
// 2) The old body compiled to 568B, 56B (14 words) SHORT of the 624B function.
//    Per AGENTS §6cs-1/§6es the index-aligned score of a short object is
//    meaningless - that stale "13.5% / NEAR ~71%" header line was measured on
//    the short object.  This body is 624B EXACT (control flow reproduces both
//    of want's store blocks), so the honest number is the one below.
//
// --- CURRENT STATE ----------------------------------------------------------
// Object .text = 624B = symbols.txt size.  want_got: 140/156 words differ,
// 10.26% (tools/score_addrs.py / test_wip_drafts.py: 9.9%).  The old 568B body
// scores 14.79% but cannot ever match (size short).
// Every one of the 140 diffs is REGISTER/FRAME, not shape - the operation
// stream is structurally identical:
//   original prologue saves 11 registers with a larger frame;
//   this build saves 9 with a smaller frame.
// The original keeps the match index in a callee-saved register and
// materialises the THREE stack-buffer base pointers into callee-saved regs
// inside the child loop (result buffer, first temp, second temp), then stores
// the temp copies through them, while the byte reads use direct stack
// displacements. The got body uses direct stack displacements for everything
// (only one base pointer survives), so the whole function is off by 2 saved
// registers and every operand index shifts. That is the entire residual.
//
// --- LEVERS TRIED (all measured; none moves the register count) -------------
//  * typed Node/sp18/sp20 structs instead of m2c `*(s32*)((char*)x+off)` casts
//    (done - this is the body below);
//  * reordering the byte assignments to want's store order b3,b0,b2,b1: 10.26;
//  * explicit `u8 *p18 = sp18; u8 *p20 = sp20;` pointer locals used for the
//    temp stores: 10.90% (still 9 saved regs);
//  * declaring sp18/sp20 inside the inner-loop block (GCC hoists): no change;
//  * splitting the end-block into 6 field stores: 5.77%.
// The old o0/o1/o2+goto shape compiles 56B shorter because cc1 merges the two
// identical store blocks that want keeps distinct.
// Nothing left that is not source-guessing at the allocator - park and move on.
//
// Arity ground truths (from the callee prologues / call-site registers):
//   fn_80241E38(ptr, s32) -> ptr          (r3/r4 in, r3 out)
//   fn_80236EF4(ptr, s32) -> ptr          (r3/r4 in, r3 out)
//   fn_80238964() 0-arg global getter, result DISCARDED here.
#include "types.h"

typedef struct {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    u32 w4;
    u32 w8;
} Node;

typedef struct {
    u32 w0;
    u16 h4;
    u8 _p[0x2A];
    u32 n;
} List;

typedef struct {
    u32 w0;
    u16 h4;
    u8 _p2[2];
    u32 w8;
    u8 _p3[0x24];
    u32 m;
} Type;

void *fn_80241E38(void *arg0, s32 arg1);
void *fn_80238964(void);
void *fn_80236EF4(void *arg0, s32 arg1);

void *fn_80242F80(Node *arg0, List *arg1, s32 arg2) {
    Node sp8;
    u8 sp18[6];
    u8 sp20[6];
    u32 i;
    u32 j;
    u32 k;
    Node *e;
    Node *c;
    Type *t;

    k = 0;
    for (i = 0; i < arg1->n; i++) {
        e = fn_80241E38(arg1, i);
        fn_80238964();
        t = fn_80236EF4((void *)e->w8, 0);
        if (t->w8 & 0x80) {
            if (k == (u32)arg2) {
                *arg0 = *e;
                return arg0;
            }
            k++;
        } else {
            for (j = 0; j < t->m; j++) {
                c = fn_80241E38(t, j);
                if (k == (u32)arg2) {
                    *(u32 *)&sp18[0] = arg1->w0;
                    *(u16 *)&sp18[4] = arg1->h4;
                    *(u32 *)&sp20[0] = t->w0;
                    *(u16 *)&sp20[4] = t->h4;
                    sp8 = *c;
                    sp8.b0 = e->b0;
                    sp8.b1 = e->b1 + c->b1;
                    sp8.b2 = e->b2;
                    sp8.b3 = e->b3 + c->b3;
                    switch (e->b3) {
                    case 0:
                        sp8.b0 = e->b0 + c->b0;
                        sp8.b2 = e->b2 + c->b2;
                        break;
                    case 1:
                        sp8.b0 = e->b0 + c->b2;
                        sp8.b2 = e->b2 + sp18[3] - c->b0 - sp20[3];
                        break;
                    case 2:
                        sp8.b0 = e->b0 + sp18[3] - c->b0 - sp20[3];
                        sp8.b2 = e->b2 + sp18[5] - c->b2 - sp20[5];
                        break;
                    case 3:
                        sp8.b0 = e->b0 + sp18[5] - c->b2 - sp20[5];
                        sp8.b2 = e->b2 + c->b0;
                        break;
                    }
                    *arg0 = sp8;
                    return arg0;
                }
                k++;
            }
        }
    }
    *arg0 = sp8;
    return arg0;
}
