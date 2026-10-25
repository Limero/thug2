// WIP DRAFT (non-matching) — hand-rebuilt from the retail disassembly
// family=m2c range=0x800254EC-0x80025D0C size=2080B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05 (w_800254EC): 5.07% masked, official verdict DIFF.
// Object is 1736B vs the 2080B want — 86 words SHORT, so the index-aligned
// score is meaningless past the prologue. Longest byte-identical prefix is
// 4 words (stwu/mflr/stmw r21,0x13c/stw). Everything through the prologue is
// structurally right; the divergence starts at `mr r31,r3` (see residual).
//
// ESTABLISHED (do not re-derive — all verified against the retail bytes):
//  * fn_800254EC takes THREE args (r3,r4,r5); m2c's 2-arg signature put
//    arg2 in r4 and cost the whole prologue. r4 is unused.
//  * frame 0x168, stmw r21-r31 @0x13c, LR @0x16c, and NO FPR save area
//    (so this is not one of the +8-byte FPR-frame cases).
//  * local layout (declaration order = ascending offsets, g0..g2 BEFORE pt):
//      r1+0x08  Grp g0 (0x60)   r1+0x68 Grp g1   r1+0xc8 Grp g2
//      r1+0x128 Pt  pt (0x10, fn_80103678's out-param; only +0/+8 read)
//    Nd = {u16 v; f64 x@8; f64 y@0x10} is 0x18; Grp = Nd[4] = 0x60;
//    Cont = 0x14 {+4 arr, +8 count, +C rec index, +10 refcount};
//    Rec = 0x40 {+6 u16, +8 u16 cnt, +A u8 flag, +C data ptr}.
//  * the flags u16 test (`lbz 0xa; cmpwi; lwz 0xc; lhz 0; andi 0x40`) is an
//    if-converted pair of IDENTICAL arms: writing
//      `fl = rec->flag ? *(u16*)rec->data : *(u16*)rec->data;`
//    makes ngccc emit the dead `lbz/cmpwi` and then merge the arms —
//    byte-exact in isolation (recipes: if-conversion leaves the compare).
//  * the first counting loop needs TWO induction pointers, one hoisted
//    (`Rec *rp = arg0->recs;` outside) and one computed (`rq = arg0->recs + k`
//    inside). One pointer variable, or two identical expressions, or both
//    in the increment clause — all collapse to one register (`mr rX,rY` +
//    one `addi`). Only this shape gives `mr r10,r0; mr r11,r10` +
//    two `addi 0x40`.
//  * store order: `.v` fields and `.x/.y` fields both emit in SOURCE order
//    here (g0.n[3] first), not reverse.
//  * the three u16 lookups (j*8+4/5/6 as u8, j*0xA+4/6/8 as u16) reproduce
//    exactly when the Rec reads are non-CSE-able — `volatile Rec *rec` does
//    it in isolation; plain `Rec *` CSEs the flag byte into one register.
//
// RESIDUAL (86 words short + first divergence at word 4):
//  1. arg0 lands in r28, not r31 (whole-function IRA; a
//     `register Comp *a0 __asm__("r31")` pin made GCC emit an extra
//     `mr r26,r3; mr r31,r26` and did NOT fix the save area).
//  2. n8/n6 get r7/r8 instead of r8/r7.
//  3. retail REMATERIALISES pt.x/pt.y from r1+0x128/0x130 for every one of
//     the 24 double stores (load/store pairs, only f0) and stores
//     g2.n[3].x/.y TWICE (retail 0x8002597c/0x80025988) without CSE-ing.
//     Mine hoists both into f0/f13. `Pt volatile pt` forces the reloads but
//     then GCC hoists all 24 loads into f1..f31 (worse). Not reproduced.
//  4. retail keeps the record array base in r10 with the record offset in
//     r26 and re-derives `rec` as `r26+r10` five times per iteration; mine
//     materialises a single `rec` pointer (tried a `Rec *recs` local — made
//     the save area r20/r21 @0x138, i.e. worse).
//  5. retail's dead loop is `do { i--; for(k=0;k<4;k++); } while (i != -1)`
//     with the decrement hoisted (`addi r0,r9,-1` before the inner loop);
//     mine materialises k through CTR (`mtctr r31; mfctr r9`).
//  6. the search blocks re-load `cont->arr` from memory for the second
//     comparison and use `lhzx rX,rOff,rBase` indexed forms; mine folds the
//     address once (`add r11,r11,r7`) and caches the group key in a register
//     with a `clrlwi` re-truncation.
// RULED OUT: 2-arg signature, pt before g0/g1/g2, ascending store order,
// volatile pt, `Rec *recs` local, r31 register pin, whole-body duplication of
// the if-converted flag arms (the `fl` helper already removes that need).
// Next lever would be the FPR-rematerialisation puzzle (3), which needs a
// source shape that defeats GCC's alias analysis for the 24 stfd's.
#include "types.h"

typedef struct Rec {
    char pad0[0x6];
    u16 v6;
    u16 cnt;
    u8 flag;
    char padB[1];
    void *data;
    char pad10[0x30];
} Rec;

typedef struct Nd {
    u16 v;
    char pad2[6];
    f64 x;
    f64 y;
} Nd;

typedef struct Grp {
    Nd n[4];
} Grp;

typedef struct Cont {
    s32 unk0;
    Grp *arr;
    s32 cnt;
    s32 idx;
    s32 refcnt;
} Cont;

typedef struct Ctx {
    char pad0[0x88];
    s32 nrec;
    Rec *recs;
} Ctx;

typedef struct Comp {
    char pad0[0x50];
    Rec *recs;
    char pad54[0x14];
    Cont *cont;
} Comp;

typedef struct Pt {
    f64 x;
    f64 y;
} Pt;

void *fn_80025D50(Rec *);
void fn_80025DF8(Comp *);
void fn_80025D0C(Cont *, Rec *);
void *Mem_NewZero(int);
void *Mem_Alloc(s32);
void Mem_Free(void *);
void Mem_Free2(void *);
void *memset(void *, int, unsigned int);
void fn_80103678(Pt *, Rec *);

#define FLAGS_OF(r) ((r)->flag != 0 ? *(u16 *)(r)->data : *(u16 *)(r)->data)

#define SEARCH(g)                                                                \
    for (k = 0; k < nent; k++) {                                                 \
        e = arg0->cont->arr + k;                                                 \
        if (e->n[0].v == (g).n[0].v && e->n[2].v == (g).n[2].v) {                \
            e->n[1].v = (g).n[1].v;                                              \
            e->n[3].v = (g).n[3].v;                                              \
        } else if (e->n[2].v == (g).n[0].v && e->n[0].v == (g).n[2].v) {         \
            e->n[3].v = (g).n[1].v;                                              \
            e->n[1].v = (g).n[3].v;                                              \
        } else {                                                                 \
            continue;                                                            \
        }                                                                        \
        e->n[1].x = (g).n[1].x;                                                  \
        e->n[1].y = (g).n[1].y;                                                  \
        e->n[3].x = (g).n[3].x;                                                  \
        e->n[3].y = (g).n[3].y;                                                  \
    }                                                                            \
    if (k == nent) {                                                             \
        arg0->cont->arr[nent] = (g);                                             \
        nent++;                                                                  \
    }

void fn_800254EC(Comp *arg0, void *arg1, Ctx *arg2) {
    Cont *cont;
    Rec *rp;
    Rec *rq;
    Rec *recs;
    Grp *e;
    s32 n8;
    s32 n6;
    s32 total;
    s32 maxn;
    s32 bytes;
    s32 nent;
    s32 i;
    s32 j;
    s32 k;
    u16 va;
    u16 vb;
    u16 vc;
    u16 fl;
    Grp g0;
    Grp g1;
    Grp g2;
    Pt pt;

    if (arg2 != NULL) {
        arg0->recs = arg2->recs;
    }
    cont = fn_80025D50(arg0->recs);
    arg0->cont = cont;
    if (cont != NULL) {
        cont->refcnt = cont->refcnt + 1;
        fn_80025DF8(arg0);
        return;
    }
    cont = Mem_NewZero(0x14);
    arg0->cont = cont;
    n8 = 0;
    n6 = 0;
    if (arg0->recs != NULL) {
        rp = arg0->recs;
        for (k = 0; k < arg2->nrec; k++) {
            Rec *rq = arg0->recs + k;
            fl = FLAGS_OF(rq);
            if (!(fl & 0x40)) {
                n8 += rp->cnt;
                n6 += rp->v6;
            }
            rp++;
        }
    }
    total = n8 + n6;
    maxn = total - 2;
    if (maxn > 0) {
        bytes = maxn * 0x60;
        rp = (Rec *)arg0->cont;
        rq = (Rec *)Mem_Alloc(bytes);
        k = total - 3;
        if (total != 2) {
            do {
                for (i = 0; i < 4; i++) ;
                k--;
            } while (k != -1);
        }
        arg0->cont->arr = (Grp *)rq;
        memset(arg0->cont->arr, 0, bytes);
    }
    nent = 0;
    if (arg0->recs != NULL) {
        for (i = 0; i < arg2->nrec; i++) {
            Rec *rec = arg0->recs + i;
            fl = FLAGS_OF(rec);
            if (!(fl & 0x40)) {
                nent = 0;
                for (j = 0; j < rec->cnt; j++) {
                    va = rec->flag ? ((u8 *)rec->data)[j * 8 + 4] : ((u16 *)rec->data)[j * 5 + 2];
                    vb = rec->flag ? ((u8 *)rec->data)[j * 8 + 5] : ((u16 *)rec->data)[j * 5 + 3];
                    vc = rec->flag ? ((u8 *)rec->data)[j * 8 + 6] : ((u16 *)rec->data)[j * 5 + 4];
                    for (k = 0; k < 4; k++) ;
                    for (k = 0; k < 4; k++) ;
                    for (k = 0; k < 4; k++) ;
                    g0.n[3].v = vb;
                    g0.n[2].v = vb;
                    g0.n[1].v = va;
                    g0.n[0].v = va;
                    fn_80103678(&pt, rec);
                    g0.n[3].x = pt.x;
                    g0.n[3].y = pt.y;
                    g0.n[2].x = pt.x;
                    g0.n[2].y = pt.y;
                    g0.n[1].x = pt.x;
                    g0.n[1].y = pt.y;
                    g0.n[0].x = pt.x;
                    g0.n[0].y = pt.y;
                    g1.n[3].v = vc;
                    g1.n[2].v = vc;
                    g1.n[1].v = vb;
                    g1.n[0].v = vb;
                    g1.n[3].x = pt.x;
                    g1.n[3].y = pt.y;
                    g1.n[2].x = pt.x;
                    g1.n[2].y = pt.y;
                    g1.n[1].x = pt.x;
                    g1.n[1].y = pt.y;
                    g1.n[0].x = pt.x;
                    g1.n[0].y = pt.y;
                    g2.n[3].v = va;
                    g2.n[2].v = va;
                    g2.n[1].v = vc;
                    g2.n[0].v = vc;
                    g2.n[3].x = pt.x;
                    g2.n[3].y = pt.y;
                    g2.n[2].x = pt.x;
                    g2.n[2].y = pt.y;
                    g2.n[1].x = pt.x;
                    g2.n[1].y = pt.y;
                    g2.n[0].x = pt.x;
                    g2.n[0].y = pt.y;
                    arg0->cont->idx = i;
                    SEARCH(g0)
                    SEARCH(g1)
                    SEARCH(g2)
                }
            }
        }
    }
    if (nent <= maxn && nent > 0) {
        arg0->cont->cnt = nent;
        fn_80025D0C(arg0->cont, arg0->recs);
        fn_80025DF8(arg0);
        return;
    }
    if (arg0->cont->arr != NULL) {
        Mem_Free2(arg0->cont->arr);
        arg0->cont->arr = NULL;
    }
    Mem_Free(arg0->cont);
    arg0->cont = NULL;
}
