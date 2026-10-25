// WIP DRAFT (non-matching) — C body rewritten by hand (w75/0x801396A4)
// family=m2c range=0x801396A4-0x80139790 size=236B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Semantics (established from the want, not from m2c):
//   255-iteration loop over an array of 0x18-byte elements.  A 3-word stack
//   object at r1+8 holds a "vtable" slot (+8, lbl_8029F350) and a "current"
//   cursor slot (+4).  Per element: publish the element in the cursor slot,
//   walk node->fC->f4 (with the `node->f4 == -1 => NULL` end-of-list
//   sentinel), republish the child in the cursor slot, and call the node's
//   virtual at +0x14 with (this + vtbl->f8, 3).
#include "types.h"

extern char lbl_8029F350[];

typedef struct Node {
    char pad0x0[4];
    s32 f4;
    char pad0x8[4];
    s32 fC;
} Node;

typedef struct Elem {
    char pad0x0[0xC];
    s32 fC;
} Elem;

typedef struct Vt {
    char pad0x0[8];
    s16 f8;
    char pad0xA[2];
    s32 fC;
} Vt;

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
} Ctx;

void fn_801396A4(Elem *arg0) {
    Ctx sp8;
    Ctx *ctx;
    s32 i;
    Node *cur;
    Node *nx;
    Node *nxt;
    Node *elem;
    Vt *vt;

    for (i = 0; i <= 0xFE; i++) {
        ctx = &sp8;
        ctx->f8 = (s32)lbl_8029F350;
        elem = (Node *)((i * 0x18) + (s32)arg0);
        cur = (Node *)elem->fC;
        ctx->f4 = (s32)elem;
        if (cur->f4 == -1) {
            cur = NULL;
        }
        ctx->f4 = (s32)cur;
        if (cur == NULL) {
            nxt = NULL;
        } else {
            nxt = (Node *)cur->f4;
        }
        if (nxt != 0) {
            cur = nxt;
            do {
                nx = (*(Node **)((char *)ctx + 4))->fC;
                if (nx->f4 == -1) {
                    nx = NULL;
                }
                ctx->f4 = (s32)nx;
                if (nx == NULL) {
                    nxt = NULL;
                } else {
                    nxt = (Node *)nx->f4;
                }
                if (cur != NULL) {
                    vt = (Vt *)cur->fC;
                    ((s32 (*)(void *, s16))vt->fC)((char *)cur + vt->f8, 3);
                }
                cur = nxt;
            } while (cur != NULL);
        }
        ctx->f8 = (s32)lbl_8029F350;
    }
}

// PARKED 2026-10-02 (w75/0x801396A4): 69.5% NEAR (was 18.6% DIFF), size exact.
// Cracked this pass (all pure C, no flags needed, no asm):
//   * ctx address ASSIGNED INSIDE the for-body (`ctx = &sp8;` as the first
//     statement) instead of before the loop.  That is what creates want's
//     6th callee-saved register: `addi r30,r1,8 | lis/addi r27 | mr r28,r30 |
//     mr r26,r3` prologue with the `8(r28)`/`4(r28)` preheader stores and the
//     `stmw r26,0x18(r1)`/`lmw r26,0x18(r1)` span (51.7% the moment this one
//     line changed; 18.6% before).
//   * `elem = (i * 0x18) + arg0` (mulli-result first) gives want's
//     `add r9,r9,r26` operand order; `(char *)arg0 + i*0x18` gives the
//     mirrored `add r9,r26,r9`.
//   * vtable `+8` field typed `s16` (not s32) -> want's `lha r3,8(r9)`;
//     `(char *)this + vt->f8` then folds to the `lha`+`add` this-adjust.
//   * callee signature `((s32 (*)(void *, s16))vt->fC)(base, 3)` supplies the
//     missing 2nd argument `li r4,3` (the m2c draft passed one arg).
//   * `cur = elem->fC` BEFORE `ctx->f4 = elem` restores want's store-then-load
//     order in the preheader (69.5%; the load-first order let the scheduler
//     hoist `lwz r11,0xc(r9)` above the store = 66.1%).
//   * loop shape: `if (nxt) { cur = nxt; do {...} while (cur); }` keeps BOTH
//     the preheader guard AND the bottom latch test (want tests the phi twice:
//     `or. r10,r11,r11; beq` in the preheader, `or. r10,r31,r31; bne` at the
//     latch).  Guard-on-cur + latch-on-cur MERGES into a top-tested while
//     loop (32%); guard-on-nxt loses the fused copy.
// Tried and rejected (all <= current): guard/latch on 4 variable pairings
// (32.2 / 66.1 / 69.5 / 55.0), plain do-while 33.9, goto form 37.3, for-form
// 35.6, `while(1)+break` 32.2, house `goto check` hybrid 37.3, two-distinct
// `nxt` temps 69.5 (no gain), self-assigning select 23.7, s32-typed walkers
// (compile), arg0 as s32/void*, `&arg0[i]`, decl-order shuffles (69.5),
// no `elem`/`vt` temps (16.7), volatile ctx/slot 66-69.5, and flags
// (-fno-schedule-insns 49.2, -fno-sched-interblock/-fno-sched-spec 61.0,
// -fno-gcse 6.8, -fno-schedule-insns2/-fno-thread-jumps/-fno-peephole 69.5,
// i<0xFF 69.5, u32 i 67.8) — DEFAULT FLAGS WIN.
// Residual (18 words): (1) the loop variable `cur` and the child `nx` are
// allocated r11/r9 instead of want's r10/r11 — want's `cur` reuses the dead
// outer-counter register r10, which needs the preheader phi copy to land in a
// FRESH pseudo (want copies r11->r10 at the guard); every variant that made
// them distinct pseudos (extra loop var `p`, preheader `nxt0`) still let
// ngccc pick r11, i.e. it inherits r11 from the preheader's `cur`.  (2) want's
// preheader null-select is the doc-42 double-branch diamond with dest==base
// (`cmpwi r11,0; bne Lload; li r11,0; b Lend; Lload: lwz r11,4(r11)`) while
// ngccc always emits branch-over-load into a fresh reg here.  (3) 2-word
// `li r31,0` / `cmpwi cr7` swap at the loop head.
// Applies to: the 0x8013A5xx/0x801399xx ctx-cursor family and doc-42 members.