// UPDATED 2026-09-13 (c): extended flag matrix (recipe 49) found `-fno-schedule-insns2` -> 30.77% to 46.15%.
// WIP DRAFT (non-matching) — hand-rebuilt from disasm, SNAPS paired-single body.
// family=m2c range=0x801CE3E4-0x801CE4E8 size=260B
// PS ops needed: ps_mul/merge00/madd/sum0 + ps_mr(xo10=72) x2 + ps_muls0 x3,
// all emittable (__builtin_ps_* / inline-asm ps_mr, see sibling fn_8015E868).
// FLAG: -mps-float -fno-schedule-insns2
// PARKED: SNAPS paired-single body fully reconstructed (__ps_t + __builtin_ps_*
// + asm ps_mr); stack layout pinned (sp8@8/hole@C/pair@10/scale@18/tail@20,
// frame 0x30 GPR-only). Remaining ~10 word diffs are all FPR-role coloring +
// small block-order artifacts in the two muls0/mr webs — the exact wall that
// parked the zone sibling fn_8015E868 at 83.6% (doc 06 M5.0o). Resisted:
// decl-order permutations, web reordering, frN pins (call-result caveat
// §6ae-9), volatile staging, natural/inverted compare polarity.
// (ps_diff 30.8% raw / cascaded; structure aligned)
#include "types.h"
#include "structs.h"
extern f32 lbl_802AD308;
extern f32 lbl_802AD30C;
extern f32 lbl_802AD310;
extern char lbl_802AD278[];
s32 GetFloat(CStruct *, void *, f32 *, s32);
f32 sqrtf(f32);

s32 fn_801CE3E4(Unk_C7387A53 *arg0, CStruct *arg1) {
    f32 sp8;
    char _c[4];
    f32 v10;
    f32 v14;
    f32 v18;
    f32 v1C;
    f32 v20;
    f32 v24;
    Unk_130D31C8 *o1;
    Unk_073F5245 *o2;
    __ps_t hi, k, lo, pair;
    f32 speed;
    f32 thr;

    __asm__("" : : "m"(sp8), "m"(_c[0]), "m"(v10), "m"(v14), "m"(v18), "m"(v1C), "m"(v20), "m"(v24));

    sp8 = lbl_802AD308;
    GetFloat(arg1, 0, &sp8, 0);
    o1 = *((void * *)&arg0->unk0xC);
    hi = o1->unk0xC0;
    k = *(__ps_t *)&lbl_802AD278[0];
    hi = hi * hi;
    lo = o1->unk0xB8;
    thr = lbl_802AD30C;
    hi = __builtin_ps_merge00(hi, k);
    lo = __builtin_ps_madd(lo, lo, hi);
    lo = __builtin_ps_sum0(lo, lo, lo);
    *(__ps_t *)&v10 = lo;
    speed = *(volatile f32 *)&v10;
    if (speed < thr) {
        __ps_t pa = o1->unk0xA0;
        __ps_t pb = o1->unk0x98;
        o1->unk0xC0 = pa;
        o1->unk0xB8 = pb;
    } else {
        __ps_t lo2;
        __ps_t hi2;
        __ps_t pr2;
        f32 dt = sqrtf(speed);
        f32 mx = lbl_802AD310;
        lo2 = o1->unk0xB8;
        hi2 = o1->unk0xC0;
        v18 = mx / dt;
        pair = *(__ps_t *)&v18;
        __asm__("ps_mr %0, %1" : "=&f"(pr2) : "f"(pair));
        hi2 = __builtin_ps_muls0(hi2, pr2);
        lo2 = __builtin_ps_muls0(lo2, pr2);
        o1->unk0xC0 = hi2;
        o1->unk0xB8 = lo2;
    }
    v20 = sp8;
    o2 = *((void * *)&arg0->unk0xC);
    {
        __ps_t o184 = o2->unk0xB8;
        __ps_t q = *(__ps_t *)&v20;
        __ps_t o192 = o2->unk0xC0;
        __ps_t mr;
        __asm__("ps_mr %0, %1" : "=&f"(mr) : "f"(q));
        o184 = __builtin_ps_muls0(o184, mr);
        o192 = __builtin_ps_muls0(o192, mr);
        o2->unk0xB8 = o184;
        o2->unk0xC0 = o192;
    }
    return 1;
}
