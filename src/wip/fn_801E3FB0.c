// WIP DRAFT (non-matching) — hand-rebuilt from disasm (group E)
// PARKED: ~18% - PS-saturated vec-math rebuild; all opcodes decoded
// and emittable (ps_muls0/ps_add/ps_sub/ps_mr/ps_res via __ps_t builtins,
// -mps-float), semantics fully reconstructed (scale two obj+0x408/0x410 pairs
// by lbl_802AD808, add into objC->0x58/0x60 pairs, quad-copy sum pair to
// obj+0x230/238/240/248 [0x238/0x248 reload fr.b], hash delta into obj->0x244,
// two fn_801EC684 guards, diff/lerp via fn_80005A90, tail fn_80005854).
// Tried: separate-union + frame-template struct layouts, fr11/fr12 register
// pins (backfired, §74-146), double sc.p read for the ps_mr copy, memory
// clobbers for load order, volatile limit-load against hoisting, compare
// polarity flips (< > <=). Remaining walls: (a) GCC splits my locals into
// slots below &fr so r30 homes &fr.c not &fr (want: addi r30,r1,8 + 8(r30)
// reloads); (b) psq_l scheduling order in prologue block; (c) fcmpu operand
// order at the lane-limit test always emits swapped+ble vs want's bgt;
// (d) got 440B vs want 456B - four insns still unaccounted (likely exact
// spill/lr-slot interplay). Retry hints: pin ONLY via file-scope tricks,
// investigate want's li r4,1 placement before stfs, count anonymous PS conv
// temps.
// family=m2c range=0x801E3FB0-0x801E4178 size=456B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 14.9% ([7]asc->14.9%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 fn_8014030C(s32, s32, Unk_FFAD6788 *);
extern s32 fn_801EC684(Unk_E2C810EF *, s32, s32);
extern void fn_80005A90(Unk_C1F9F519 *, Unk_C1F9F519 *);
extern void fn_80005854(void *, void *);
extern f32 lbl_802AD808;
extern char lbl_802AD80C[];

s32 fn_801E3FB0(Unk_913806C4 *arg0) {
    struct fractx {
        __ps_t a;
        __ps_t b;
        __ps_t c;
        __ps_t d;
        __ps_t e;
        __ps_t f;
        union { __ps_t p; f32 v[2]; } sc;
    } fr;
    __ps_t sa;
    __ps_t sb;
    __ps_t t1;
    __ps_t t2;
    Unk_DF2324A8 *objC;

    fr.sc.v[0] = lbl_802AD808;
    sa = fr.sc.p;
    __asm__ volatile("" ::: "memory");
    t1 = arg0->unk0x408;
    t2 = arg0->unk0x410;
    sb = fr.sc.p;
    objC = arg0->unk0xC;
    t1 = __builtin_ps_muls0(t1, sb);
    t2 = __builtin_ps_muls0(t2, sb);
    fr.c = t1;
    fr.d = t2;
    sa = __builtin_ps_add(objC->unk0x58, t1);
    sb = __builtin_ps_add(objC->unk0x60, t2);
    fr.a = sa;
    fr.b = sb;
    arg0->unk0x240 = sa;
    arg0->unk0x230 = sa;
    arg0->unk0x238 = fr.b;
    arg0->unk0x248 = fr.b;
    *((f32 *)&((Unk_39999125 *)arg0)->unk0x244) += fn_8014030C(QB_SKATER_DEFAULT_HEAD_HEIGHT, 1, (s32)objC);
    if (fn_801EC684(arg0, 0x10, 0) == 0) {
        return 0;
    }
    *(__ps_t *)&fr = arg0->unk0x148;
    fr.a = arg0->unk0x150;
    fr.sc.p = fr.a;
    if (*(volatile f32 *)&lbl_802AD80C < fr.sc.v[1]) {
        return 0;
    }
    t1 = arg0->unk0x240;
    t2 = arg0->unk0x248;
    sa = arg0->unk0x138;
    sb = arg0->unk0x140;
    fr.c = __builtin_ps_sub(sa, t1);
    fr.d = __builtin_ps_sub(sb, t2);
    fn_80005A90(&fr.c, &fr);
    t1 = fr.c;
    t2 = fr.d;
    objC = arg0->unk0xC;
    arg0->unk0x230 = objC->unk0x58;
    arg0->unk0x238 = objC->unk0x60;
    sa = __builtin_ps_add(objC->unk0x58, t1);
    sb = __builtin_ps_add(objC->unk0x60, t2);
    arg0->unk0x240 = sa;
    arg0->unk0x248 = sb;
    fr.e = sa;
    fr.f = sb;
    if (fn_801EC684(arg0, 0x10, 0) != 0) {
        sa = __builtin_ps_add(arg0->unk0x138, arg0->unk0x148);
        sb = __builtin_ps_add(arg0->unk0x140, arg0->unk0x150);
        fr.e = sa;
        fr.f = sb;
        objC = arg0->unk0xC;
        objC->unk0x58 = sa;
        sb = fr.f;
    } else {
        objC = arg0->unk0xC;
        objC->unk0x58 = sa;
        sa = arg0->unk0x240;
        sb = arg0->unk0x248;
    }
    objC->unk0x60 = sb;
    fn_80005854((void *)((char *)objC + 0xB8), &fr);
    return 1;
}
