// WIP DRAFT (non-matching) — PARKED 2026-08-25
// Reached 15.5%. Prologue/frame EXACT (frame 0x68, stmw r29@0x54, f31@0x60,
// &spb=sp+0x18 &spa=sp+8 via dummy-last placement; fn_80242734 is 3-arg with
// hidden arg0 passthrough — m2c dropped it). Remaining diffs: want keeps
// dx/dy/dz in SCRATCH FPRs pre-call and only stores them to sp+0x28/2c/30 for
// the post-call loop reloads; plain locals make GCC promote them to
// callee-saved f29/f30 (extra stfd, whole-frame shift), volatile forces
// store+reload pairs want doesn't have; no middle ground found (asm-escape
// barrier tried, regresses). Also want-only dead store stfs f0->0x34(sp)
// (kept via volatile sp34 here). Loop self-copy *(r+0x1c)=*(r+0x1c) modeled
// via two-pointer block. Arity: fn_80241E38(o,i)->node; fn_80240C80(n->f8)
// chained ->ret; fn_80240B2C(o,4) 2-arg called twice.
// family=m2c range=0x80242590-0x80242734 size=420B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
extern f32 lbl_802B116C;
extern f32 lbl_802B1170;
extern f32 lbl_802B1174;
extern f32 lbl_802B0544;
extern f32 lbl_802B0548;
extern f32 lbl_802B054C;
void fn_80242734(Unk_C7387A53 *, void *, void *);
void fn_80240B2C(void *, s32);
s32 fn_80241E38(void *, s32);
s32 fn_80240C80(s32);
void fn_80242590(Unk_C7387A53 *arg0) {
    f32 spa[3];
    f32 spb[3];

    volatile f32 dx;
    volatile f32 dy;
    volatile f32 dz;
    volatile f32 sp34;
    s32 i;
    s32 n;
    s32 r;
    f32 fk;
    volatile double _dummy;

    fn_80242734(arg0, spb, spa);
    dx = spb[0] - spa[0];
    dy = spb[1] - spa[1];
    dz = spb[2] - spa[2];
    sp34 = lbl_802B116C;
    ((u8 *)arg0)[3] = (u8)((s32)((dx + lbl_802B1170) / lbl_802B0544));
    ((u8 *)arg0)[4] = (u8)((s32)((dy + lbl_802B1170) / lbl_802B0548));
    ((u8 *)arg0)[5] = (u8)((s32)((dz + lbl_802B1170) / lbl_802B054C));
    fn_80240B2C(arg0, 4);
    if (*(u8 *)arg0 == 0) {
        fn_80240B2C(arg0, 4);
        *(u8 *)arg0 = 1;
    }
    for (i = 0; (u32)i < arg0->unk0x30; i++) {
        fk = lbl_802B1174;
        n = fn_80241E38(arg0, i);
        r = fn_80240C80(((Unk_1D62F22E_2 *)n)->unk0x8);
        ((Unk_0737AFB8 *)r)->unk0x18 =
            ((Unk_0737AFB8 *)r)->unk0x18 - spa[0] - dx * fk;
        ((Unk_C4D756ED *)r)->unk0x20 =
            ((Unk_C4D756ED *)r)->unk0x20 - spa[2] - dz * fk;
        {
            f32 *pa = (f32 *)(r + 0x18);
            f32 *pb = (f32 *)(r + 0x1c);
            *pb = pa[1];
        }
    }
}
// RE-TRIAGE 2026-10-12: scratch-vs-saved FPR wall stands (15.5%, prologue exact); no body change.
