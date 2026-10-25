// PARKED 2026-10-03 (a69): DIFF 19.29% (baseline DIFF 18.78%).
// LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//     tools/test_wip_drafts.py --addr 0x80030750
//   What is already right: 0x88 frame + full prologue/epilogue (stfd f30/f31,
//   stmw r27, cr save, lmw), stack layout (msg r1+8 .. 0x37, f32 lo[10] at
//   0x38, constants in f30/f31), every call sequence, the whole eps/arg2/arg3
//   branch tree, and the *shape* of every one of the six linked-list walks
//   (`lwz 0xc(self); lwz 4(p); cmpwi -1; bne; li r,0; cmpwi; li; beq;
//   addi r,-4` + the `+4` re-shift) is instruction-for-instruction identical.
//   Remaining diff, in program order:
//     1. prologue: want `mr r29,r3; fmr f31,f1; addi r10,r29,0x18; mr r27,r6`
//        (and `mr r28,r10` later) vs got `mr r29,r3; mr r27,r6; addi r28,
//        r29,0x18; fmr f31,f1` — same 4 insns, different order/regs.
//     2. four sites where the want re-copies the link pointer into a second
//        variable before the -1 test (at 0x800307BC the copy runs from r11 to
//        r9, at 0x800308F8 and 0x80030960 from r9 to r11, and at 0x800309DC
//        from r11 to r9); ngccc deletes them (copy propagation / coalescing)
//        for the single-variable form.
//     3. msg stores: want 0x30, 0x34, 0x0C, 0x0A, 0x08 (want's 0x34 store is
//        `stb r0,4(r9)` off the &fr.f_28 register); got swaps the 0x34/0x0C
//        pair whichever source order is used.
//     4. the fn_8002DDAC call inside the arg3!=0 loop: got hoists &lo[3..5]
//        into the preheader (r28,r29,r30) and emits 3 extra `mr`s, want
//        computes them per iteration straight into r4/r5/r6.
//   Ruled out:
//     - two-variable `hold = raw; if (raw->f4 == -1) hold = NULL;` form at
//       every site: LOWERED the score to 10.2% — ngccc coalesces hold with
//       node and drops the copy, AND the added pseudos shift the whole body.
//     - msg store reordering (both orders measured): identical 19.29%.
//   Most promising next idea: the want's loop-tail `or. r30,r0,r0; bne` is
//   final.c jump_through_arith fusing `cur = X; if (X) goto top`; I forced it
//   by assigning the shift-ternary to a variable and copying it into the loop
//   variable (`nxt = nxt ? nxt-4 : NULL; cur = nxt; } while (nxt != NULL);`).
//   The same trick applied to the 4 missing `mr`s needs a second variable that
//   is still live after the -1 test, so the copy cannot be coalesced away —
//   that is what the original's local layout must have had.

// WIP DRAFT (non-matching) — hand-reconstructed from the DOL
// family=m2c range=0x80030750-0x80030A64 size=788B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

extern f32 lbl_802919E8;
extern f32 lbl_802919EC;
extern s32 lbl_80305F9C;

s32 fn_8021D358(s32, u16);
s32 fn_8022986C(void *);
s32 fn_8022A9D0(void *);
s32 fn_8021B55C(s32, s32);
void fn_80137CB4(void *);
void fn_8013DE78(void *, void *);
void fn_8002DDAC(void *, f32 *, f32 *, f32 *);

/* The list element hanging off arg0+0x18+0xC.  +0x24/+0x28 are the two
   floats this function reads and writes (lfs/stfs in the DOL), +0x4 is the
   -1 link terminator, +0xC the next link. */
typedef struct Unk_30750_node {
    char pad0x0[4];
    s32 unk0x4;
    char pad0x8[4];
    struct Unk_30750_node *unk0xC;
    char pad0x10[0x14];
    f32 unk0x24;
    f32 unk0x28;
} Unk_30750_node;

/* arg0's sub-object at +0x18 (the `addi rX, arg0, 0x18` base WANT keeps in
   r28 and reloads 0xC(r28) from in every loop). */
typedef struct Unk_30750_sub {
    char pad0x0[0x0C];
    Unk_30750_node *unk0xC;
} Unk_30750_sub;

/* Second object hanging off arg0+0x78: +0x1A is read as u16, +0x18 as s32
   and then narrowed to s8. */
typedef struct Unk_30750_b {
    char pad0x0[0x18];
    s32 unk0x18;
    char pad0x1C[0x74];
} Unk_30750_b;

/* The object arg0 itself.  unk0x78 is re-loaded from r29 in both halves of
   the arg1 block (a call sits between them, so no CSE). */
typedef struct Unk_30750_obj {
    char pad0x0[0x18];
    Unk_30750_sub unk0x18;
    char pad0x28[0x8];
    s32 unk0x30;
    char pad0x34[0x44];
    Unk_30750_b *unk0x78;
} Unk_30750_obj;

/* The 0x30-byte stack record built at r1+8: fn_80137CB4(&fr) clears it,
   fn_8013DE78(mgr, &fr) consumes it. */
typedef struct Unk_30750_msg {
    s8 f_00;
    char pad0x1[1];
    s16 f_02;
    void *f_04;
    char pad0x8[0x20];
    f32 f_28;
    s8 f_2C;
    char pad0x2D[3];
} Unk_30750_msg;

void fn_80030750(Unk_30750_obj *arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0) {
    Unk_30750_sub *self;
    Unk_30750_msg fr;
    f32 lo[10];
    Unk_30750_node *raw;
    Unk_30750_node *node;
    Unk_30750_node *nxt;
    Unk_30750_node *cur;
    Unk_30750_node *cur2;
    s32 mgr;
    s32 ent;
    s32 ent2;
    s32 isEnd;
    s32 bval;
    f32 scaled;
    f32 cst;

    self = &arg0->unk0x18;
    raw = self->unk0xC;
    isEnd = raw->unk0x4 == -1;
    node = raw;
    if (isEnd) {
        node = NULL;
    }
    cur = node ? (Unk_30750_node *)((char *)node - 4) : NULL;
    if (cur == NULL) {
        return;
    }

    node = raw;
    if (isEnd) {
        node = NULL;
    }
    cur2 = node ? (Unk_30750_node *)((char *)node - 4) : NULL;
    scaled = cur2->unk0x28 * lbl_802919E8;

    if (arg2 == 0 && fabs(scaled - farg0) < lbl_802919EC) {
        return;
    }

    if (arg1 != 0 && arg0->unk0x30 == 0) {
        mgr = lbl_80305F9C;
        ent = fn_8021D358(mgr, *(u16 *)((char *)arg0->unk0x78 + 0x1A));
        if (ent != 0 && fn_8022986C(ent) != 0) {
            ent2 = fn_8021B55C(mgr, fn_8022A9D0(ent));
            if (ent2 != 0) {
                fn_80137CB4(&fr);
                fr.f_28 = farg0;
                bval = arg0->unk0x78->unk0x18;
                fr.f_2C = (s8)bval;
                fr.f_04 = &fr.f_28;
                fr.f_02 = 8;
                fr.f_00 = 0x41;
                fn_8013DE78(ent2, &fr);
            }
        }
    }

    if (arg2 != 0) {
        if (arg3 != 0) {
            node = self->unk0xC;
            if (node->unk0x4 == -1) {
                node = NULL;
            }
            cur = node ? (Unk_30750_node *)((char *)node - 4) : NULL;
            fn_8002DDAC((char *)cur + 4, &lo[0], &lo[1], &lo[2]);
            farg0 = farg0 / (lo[2] - lo[0]);
            node = self->unk0xC;
            if (node->unk0x4 == -1) {
                node = NULL;
            }
            cur = node ? (Unk_30750_node *)((char *)node - 4) : NULL;
            if (cur == NULL) {
                return;
            }
            cst = lbl_802919E8;
            do {
                cur = (Unk_30750_node *)((char *)cur + 4);
                fn_8002DDAC(cur, &lo[3], &lo[4], &lo[5]);
                cur->unk0x24 = (lo[5] - lo[3]) * farg0 / cst;
                nxt = cur->unk0xC;
                if (nxt->unk0x4 == -1) {
                    nxt = NULL;
                }
                nxt = nxt ? (Unk_30750_node *)((char *)nxt - 4) : NULL;
                cur = nxt;
            } while (nxt != NULL);
            return;
        }
        node = self->unk0xC;
        if (node->unk0x4 == -1) {
            node = NULL;
        }
        cur = node ? (Unk_30750_node *)((char *)node - 4) : NULL;
        if (cur == NULL) {
            return;
        }
        do {
            cur = (Unk_30750_node *)((char *)cur + 4);
            nxt = cur->unk0xC;
            cur->unk0x24 = farg0 / lbl_802919E8;
            if (nxt->unk0x4 == -1) {
                nxt = NULL;
            }
            nxt = nxt ? (Unk_30750_node *)((char *)nxt - 4) : NULL;
            cur = nxt;
        } while (nxt != NULL);
        return;
    }

    node = self->unk0xC;
    if (node->unk0x4 == -1) {
        node = NULL;
    }
    cur = node ? (Unk_30750_node *)((char *)node - 4) : NULL;
    cur->unk0x28 = farg0 / lbl_802919E8;
}