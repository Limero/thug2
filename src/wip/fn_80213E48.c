// PARKED 62.5%: PS scheduler/FPR-coloring wall (doc-06 tail-scheduler family).
// family=m2c range=0x80213E48-0x80213FA8 size=352B
// Structure fully decoded & semantically correct: 3× chained
// GetFloat(GetStructure(H,0), hash, &out, 1) script calls, then two
// ps_sub pairs + two ps_add pairs over {arg0->0xC}+0x58/0x60 pair fields,
// results stored via psq_st into out-param blocks, then
// fn_80007264(&sp8,&spA,&spB); fn_80105CE8(arg0+0x858, &sp8);
// *(u32*)lbl_80302BD8 = walker.
// Tried: frame-template struct (frame+stmw span EXACT), 4×__ps_t locals
// (+0x20 gap exact), FPR birth-order permutations (cA/f31v/f29v/X/f10v),
// staged &outA/&outB pointer temps (explodes allocation to stmw r28),
// psq_st pair source-order permutations, blk2 rotate-right store run,
// split/two-step float assignments, named vs nested PS operands.
// Residual: every variant shifts FPR colors by one ({f31,f30,f29} web)
// and/or reorders the three outgoing-address addis (want r4,r5,r3 vs got
// r3,r4,r5) plus psq_l/psq_st interleave in both batches.
// FLAG: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AF69C;
extern f32 lbl_802AF6A0;
extern s32 lbl_80302BD8;
extern s32 GetStructure(s32 hash, s32 flag);
extern s32 GetFloat(CStruct * arg0, s32 hash, f32 * out, s32 flag);
extern s32 fn_80007264(void *, void *, void *);
extern void fn_80105CE8(Unk_5CB48605 *, void *);

void fn_80213E48(Unk_C7387A53 *arg0) {
    struct {
        s32 sp8[8];
        s32 outA[4];
        f32 blk1[4];
        s32 outB[4];
        f32 blk2[4];
        f32 sp68;
        f32 sp6C;
        f32 sp70;
    } fr;
    f32 cA;
    f32 f31v;
    f32 f29v;
    f32 X;
    f32 f10v;
    char *walker;
    Unk_0B6E8BDA *r9p;
    __ps_t s1;
    __ps_t s2;
    __ps_t s3;
    __ps_t s4;

    walker = (char *)arg0 + 0x858;
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_FEELER_LENGTH, &fr.sp68, 1);
    cA = lbl_802AF69C;
    f31v = fr.sp68 + cA;
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_WALKER_HEIGHT, &fr.sp6C, 1);
    f29v = fr.sp6C + cA;
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_SNAP_DOWN_HEIGHT, &fr.sp70, 1);
    f10v = lbl_802AF6A0;
    X = fr.sp70 + cA;

    fr.blk1[0] = f31v;
    fr.blk1[1] = X;
    fr.blk1[2] = f31v;
    fr.blk1[3] = f10v;
    r9p = *((char * *)&arg0->unk0xC);
    s1 = __builtin_ps_sub(r9p->unk0x58, *(__ps_t *)&fr.blk1[0]);
    fr.blk2[1] = f29v;
    s2 = __builtin_ps_sub(r9p->unk0x60, *(__ps_t *)&fr.blk1[2]);
    fr.blk2[2] = f31v;
    fr.blk2[3] = f10v;
    fr.blk2[0] = f31v;
    *(__ps_t *)&fr.outA[2] = s2;
    *(__ps_t *)&fr.outA[0] = s1;
    s3 = __builtin_ps_add(r9p->unk0x60, *(__ps_t *)&fr.blk2[2]);
    *(__ps_t *)&fr.outB[2] = s3;
    s4 = __builtin_ps_add(r9p->unk0x58, *(__ps_t *)&fr.blk2[0]);
    *(__ps_t *)&fr.outB[0] = s4;
    fn_80007264(fr.sp8, fr.outA, fr.outB);
    fn_80105CE8((s32)walker, fr.sp8);
    lbl_80302BD8 = (s32)walker;
}
