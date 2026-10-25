// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D2C58-0x801D2D94 (316B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern char lbl_802AD278[];
extern f32 lbl_802AD42C;
extern f32 lbl_802AD430;
typedef union {
    __ps_t ps;
    f32 f[2];
} psu_t;
s32 fn_801D2C58(Unk_BF0EC016 *arg0) {
    Unk_7A675EAB *base;
    Unk_5E3908F1 *p24;
    Unk_548A6C04 *b1obj;
    psu_t u1;
    psu_t u2;
    psu_t u3;
    f32 d1;
    f32 d2;
    f32 d3;
    s32 result;
    Unk_548A6C04 *p3obj;
    __ps_t pa;
    __ps_t pz;
    __ps_t pb;

    base = arg0->unk0x15A0;
    p24 = (char *)base + 0x24;
    if ((arg0->unk0x320 == 0) && (base->unk0x1B8 == 0)) {
        b1obj = arg0->unk0xC;
        {
            __ps_t a = b1obj->unk0xC0;
            __ps_t z = *(__ps_t *)&lbl_802AD278;
            __ps_t sq = __builtin_ps_mul(a, a);
            __ps_t b = b1obj->unk0xB8;
            __ps_t mg = __builtin_ps_merge00(sq, z);
            __ps_t md = __builtin_ps_madd(b, b, mg);
            md = __builtin_ps_sum0(md, md, md);
            md = __builtin_ps_rsqrte(md);
            md = __builtin_ps_res(md);
            u1.ps = md;
        }
        d1 = u1.f[0];
        if (!(d1 < lbl_802AD42C)) {
            goto blk2;
        }
        __asm__ __volatile__("");
        return 1;
    }
blk2:;
    result = 0;
    __asm__("" : "+r"(result));
    if (p24->unk0x2C == 0) {
        return result;
    }
    if (arg0->unk0x374 == 0) {
        return result;
    }
    p3obj = arg0->unk0xC;
    pa = p3obj->unk0xC0;
    pz = *(__ps_t *)&lbl_802AD278;
    pb = p3obj->unk0xB8;
    {
        __ps_t sq = __builtin_ps_mul(pa, pa);
        __ps_t mg = __builtin_ps_merge00(sq, pz);
        __ps_t md = __builtin_ps_madd(pb, pb, mg);
        md = __builtin_ps_sum0(md, md, md);
        md = __builtin_ps_rsqrte(md);
        md = __builtin_ps_res(md);
        u2.ps = md;
    }
    d2 = u2.f[0];
    if (d2 < lbl_802AD42C) {
        goto set1;
    }
    if (p24->unk0x74 == 0) {
        if (p24->unk0x50 == 0) {
            goto set1;
        }
    }
    {
        __ps_t fa = p3obj->unk0xA0;
        __ps_t fb = p3obj->unk0x98;
        __ps_t fm = __builtin_ps_mul(pa, fa);
        __ps_t fh = __builtin_ps_merge00(fm, pz);
        __ps_t fi = __builtin_ps_madd(pb, fb, fh);
        fi = __builtin_ps_sum0(fi, fi, fi);
        u3.ps = fi;
    }
    d3 = u3.f[0];
    if (d3 < lbl_802AD430) {
set1:
        result = 1;
    }
    return result;
}
