// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C70A4-0x800C7234 (400B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern char lbl_80298F18[];   /* PS pair (0,0) — merge00 const */
extern f32 lbl_80299174;   /* 1.0f */
extern f32 lbl_80299178;   /* 0.01f */
extern f32 lbl_8029917C;   /* 0.0f */

void fn_800C70A4(Unk_5C12F2FE *obj) {
    s32 *u = (s32 *)obj;
    f32 *f = (f32 *)obj;
    int n;
    int a;
    n = u[0x64 / 4];
    u[0x64 / 4] = 0;
    if (u[0x328 / 4] != 0)
        return;
    a = u[0x120 / 4];
    if (u[0x334 / 4] != 0) {
        if (a != 0)
            return;
    }
    if ((u32)(a + u[0x68 / 4]) <= 2)
        return;
    if (a != 0) {
        if (a != u[0x1AC / 4])
            return;
    }
    {
        f32 one = lbl_80299174;
        __ps_t A = obj->unk0xB8;
        __ps_t B = obj->unk0xB0;
        __ps_t t = __builtin_ps_mul(A, A);
        SN_PS_type dot;
        f32 x;
        t = __builtin_ps_merge00(t, *(__ps_t *)&lbl_80298F18);
        dot.ps = __builtin_ps_madd(B, B, t);
        dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
        x = dot.flt.hi;
        if (x > one)
            return;
        {
            f32 z = lbl_80299178;
            __ps_t C = obj->unk0xC8;
            __ps_t D = obj->unk0xC0;
            __ps_t t2 = __builtin_ps_mul(C, C);
            SN_PS_type dot2;
            f32 x2;
            t2 = __builtin_ps_merge00(t2, *(__ps_t *)&lbl_80298F18);
            dot2.ps = __builtin_ps_madd(D, D, t2);
            dot2.ps = __builtin_ps_sum0(dot2.ps, dot2.ps, dot2.ps);
            x2 = dot2.flt.hi;
            if (x2 > z * z)
                return;
        }
        {
            f32 zero = lbl_8029917C;
            if (f[0x134 / 4] > zero)
                return;
            u[0x64 / 4] = n + 1;
            if (n + 1 <= 2)
                return;
            {
                f32 *q1;
                f32 *q2;
                f32 *q3;
                f32 *q4;
                f[0x30 / 4] = zero;
                q1 = &f[0x30 / 4];
                q1[1] = zero;
                q3 = &f[0x138 / 4];
                q1[2] = zero;
                q4 = &f[0x148 / 4];
                q1[3] = one;
                q2 = &f[0x50 / 4];
                f[0x50 / 4] = zero;
                q2[1] = zero;
                q2[2] = zero;
                q2[3] = one;
                f[0x138 / 4] = zero;
                q3[1] = zero;
                q3[2] = zero;
                q3[3] = one;
                f[0x148 / 4] = zero;
                q4[1] = zero;
                q4[2] = zero;
                q4[3] = one;
            }
            {
                int cnt = u[0x1AC / 4];
                f32 fill;
                if (cnt-- != 0) {
                    int a16 = cnt * 16;
                    int b;
                    int k;
                    fill = zero;
                    __asm__("" : "+f"(fill));
                    b = a16 - cnt;
                    k = b * 32;
                    do {
                        char *base = *((char *volatile *)&obj->unk0x2F0);
                        *(f32 *)((char *)(k + (s32)base) + 0xA4) = fill;
                        k -= 480;
                    } while (cnt-- != 0);
                }
            }
            u[0x60 / 4] = 0;
        }
    }
}
