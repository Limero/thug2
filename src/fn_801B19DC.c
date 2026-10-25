// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B19DC-0x801B1BE8 (524B). Byte-identical.
// extra_cflags: -mps-float -fno-schedule-insns
#include "types.h"
#include "structs.h"

extern f32 lbl_802ABED0;
extern f32 lbl_802ABED4;
extern f32 lbl_802ABED8;
extern char lbl_802ABE50[];
extern s32 lbl_80305EAC;
s32 fn_801745B4(s32);
f32 fn_80005C28(void *, s32, s32, s32);

typedef union { __ps_t p; f32 w[2]; } S;

f32 fn_801B19DC(Unk_C7387A53 *arg0) {
    volatile S V[14];
    register __ps_t tc __asm__("fr0");
    __ps_t v98;
    register __ps_t vA0 __asm__("fr12");
    volatile __ps_t *pv;
    Unk_556F3429 *obj;
    s32 r3v;
    f32 th;
    f32 c8;
    f32 d1;
    f32 d2;
    f32 magx;
    __ps_t k;
    __ps_t s;
    register __ps_t mag __asm__("fr13");
    __ps_t nv;
    register __ps_t t2 __asm__("fr0");
    register __ps_t m2 __asm__("fr12");
    register __ps_t a __asm__("fr13");
    register __ps_t b __asm__("fr11");
    register __ps_t cc __asm__("fr12");
    __ps_t dd;
    __ps_t e;
    __ps_t f;
    __ps_t g;
    __ps_t h;
    __ps_t j;
    __ps_t n;
    register __ps_t j2 __asm__("fr12");
    register __ps_t e2 __asm__("fr10");
    register __ps_t u11 __asm__("fr11");
    register __ps_t v12 __asm__("fr12");
    register __ps_t w9 __asm__("fr9");
    register __ps_t x10 __asm__("fr10");
    register __ps_t y13 __asm__("fr13");
    register __ps_t z0 __asm__("fr0");
    __ps_t p10;
    __ps_t q9;
    __ps_t sq11;
    __ps_t sq13;
    __ps_t k7;
    __ps_t mg12;
    __ps_t mz0;
    __ps_t acc12;
    __ps_t acc0;
    __ps_t sum12;
    __ps_t sum0;

    obj = (void *)fn_801745B4(lbl_80305EAC);
    th = lbl_802ABED0;
    pv = &V[0].p;
    v98 = obj->unk0x98;
    V[0].p = v98;
    vA0 = obj->unk0xA0;
    pv[1] = vA0;
    V[0].w[1] = th;
    tc = pv[1];
    k = *(volatile __ps_t *)&lbl_802ABE50[0];
    __asm__ __volatile__("ps_mul %0, %0, %0" : "+f"(tc));
    s = V[0].p;
    __asm__ __volatile__("ps_merge00 %0, %0, %1" : "+f"(tc) : "f"(k));
    __asm__ __volatile__("ps_madd %0, %1, %1, %0" : "+f"(tc) : "f"(s));
    __asm__ __volatile__("ps_sum0 %0, %0, %0, %0" : "+f"(tc));
    __asm__("ps_mr %0, %1" : "=f"(mag) : "f"(tc));
    __asm__("" : "=f"(magx) : "f"(mag));
    if (magx > th) {
        mag = __builtin_ps_rsqrte(tc);
        nv = __builtin_ps_muls0(s, mag);
        V[10].p = mag;
        V[0].p = nv;
        V[10].w[1] = *(volatile f32 *)&lbl_802ABED4;
        t2 = pv[1];
        m2 = *(volatile __ps_t *)&V[10].p;
        __asm__ __volatile__("ps_mul %0, %0, %1" : "+f"(t2) : "f"(m2));
        pv[1] = t2;
    }
    V[2].w[0] = th;
    c8 = lbl_802ABED4;
    {
        volatile S *q = &V[2];
        q[1].w[1] = th;
        q[0].w[1] = c8;
        q[1].w[0] = th;
    }
    a = pv[1];
    b = V[0].p;
    cc = V[2].p;
    dd = V[3].p;
    e = __builtin_ps_merge10(b, a);
    e = __builtin_ps_mul(e, cc);
    r3v = arg0->unk0xC;
    k7 = *(__ps_t *)&lbl_802ABE50[0];
    f = __builtin_ps_merge10(cc, dd);
    f = __builtin_ps_mul(b, f);
    g = __builtin_ps_merge00(cc, dd);
    h = __builtin_ps_merge00(a, b);
    h = __builtin_ps_mul(h, g);
    f = __builtin_ps_sub(f, e);
    j = __builtin_ps_merge00(f, f);
    V[11].p = j;
    V[11].w[1] = c8;
    n = __builtin_ps_merge10(h, h);
    h = __builtin_ps_sub(h, n);
    j2 = V[11].p;
    f = __builtin_ps_merge10(f, h);
    V[0].p = f;
    __asm__("ps_mr %0, %1" : "=f"(e2) : "f"(j2));
    V[4].p = f;
    V[5].p = e2;
    pv[1] = e2;
    u11 = *((volatile __ps_t *)&((Unk_DF2324A8 *)r3v)->unk0x58);
    v12 = *((volatile __ps_t *)&((Unk_DF2324A8 *)r3v)->unk0x60);
    w9 = V[0].p;
    v12 = __builtin_ps_add(v12, e2);
    u11 = __builtin_ps_add(u11, w9);
    __asm__ __volatile__("" : "+f"(v12), "+f"(u11));
    V[9].p = v12;
    V[8].p = u11;
    V[4].p = u11;
    V[5].p = v12;
    x10 = pv[1];
    y13 = *((volatile __ps_t *)&((Unk_DF2324A8 *)r3v)->unk0x58);
    z0 = *((volatile __ps_t *)&((Unk_DF2324A8 *)r3v)->unk0x60);
    y13 = __builtin_ps_sub(y13, w9);
    z0 = __builtin_ps_sub(z0, x10);
    __asm__ __volatile__("" : "+f"(z0), "+f"(y13));
    V[8].p = y13;
    V[6].p = y13;
    V[9].p = z0;
    V[7].p = z0;
    p10 = obj->unk0x58;
    q9 = obj->unk0x60;
    u11 = __builtin_ps_sub(u11, p10);
    y13 = __builtin_ps_sub(y13, p10);
    v12 = __builtin_ps_sub(v12, q9);
    sq11 = __builtin_ps_mul(u11, u11);
    sq13 = __builtin_ps_mul(y13, y13);
    z0 = __builtin_ps_sub(z0, q9);
    mg12 = __builtin_ps_merge00(v12, k7);
    mz0 = __builtin_ps_merge00(z0, k7);
    acc12 = __builtin_ps_madds0(mg12, mg12, sq11);
    acc0 = __builtin_ps_madds0(mz0, mz0, sq13);
    sum12 = __builtin_ps_sum0(acc12, acc12, acc12);
    V[12].p = sum12;
    sum0 = __builtin_ps_sum0(acc0, acc0, acc0);
    V[13].p = sum0;
    {
        register f32 s68 __asm__("fr0");
        register f32 s70 __asm__("fr12");
        register f32 d1r __asm__("fr13");
        register f32 d2r __asm__("fr0");
        s68 = V[12].w[0];
        s70 = V[13].w[0];
        __asm__ __volatile__("fmr %0, %1" : "=f"(d1r) : "f"(s68));
        __asm__ __volatile__("fmr %0, %1" : "=f"(d2r) : "f"(s70));
        d1 = d1r;
        d2 = d2r;
    }
    if (d1 < d2) {
        V[0].w[0] = -V[0].w[0];
        ((volatile S *)pv)[1].w[0] = -((volatile S *)pv)[1].w[0];
    }
    return fn_80005C28(r3v + 0xD0, (s32)&V[0].p, 2, 1) * lbl_802ABED8;
}
