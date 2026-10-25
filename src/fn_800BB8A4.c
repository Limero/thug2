// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BB8A4-0x800BB9BC (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "dolphin/SN_PS.h"

typedef struct {
    char pad0x0[0x5C];
    f32 unk0x5C;
    f32 unk0x60;
    char pad0x64[0x98];
    s32 unk0xFC;
    __ps_t v4a[2];
    f32 unk0x110;
    __ps_t v4b[2];
    __ps_t v4c[2];
    char pad0x138[0x10];
    __ps_t v4d[2];
    char pad0x158[0x41];
    s8 unk0x199;
} S_BB8A4;

extern char lbl_80298CA0[];
extern f32 lbl_80298DEC;
extern f32 lbl_80298DF0;

void fn_800BA678(S_BB8A4 *);

void fn_800BB8A4(S_BB8A4 *arg0) {
    SN_PS_type ta, tb, tc;
    __ps_t z1, a1, b1, c1, g1, u1, t1, z2, h1, i1, d1, j1;
    f32 x1, x2, x3, lim1, lim2;
    register f32 lim3 __asm__("fr12");
    s32 b9;

    if ((s8)arg0->unk0x199 <= 2) {
        return;
    }

    a1 = arg0->v4c[1];
    z1 = *(__ps_t *)lbl_80298CA0;
    b1 = arg0->v4c[0];
    a1 = a1 * a1;
    lim1 = arg0->unk0x5C;
    t1 = __builtin_ps_merge00(a1, z1);
    t1 = b1 * b1 + t1;
    ta.ps = __builtin_ps_sum0(t1, t1, t1);
    x1 = ta.flt.hi;
    if (x1 > lim1) {
        return;
    }

    c1 = arg0->v4d[1];
    g1 = arg0->v4d[0];
    c1 = c1 * c1;
    lim2 = arg0->unk0x60;
    c1 = __builtin_ps_merge00(c1, z1);
    g1 = __builtin_ps_madd(g1, g1, c1);
    tb.ps = __builtin_ps_sum0(g1, g1, g1);
    x2 = tb.flt.hi;
    if (x2 > lim2) {
        return;
    }

    fn_800BA678(arg0);

    b9 = 1;
    if (!(arg0->unk0xFC & 1)) {
        b9 = 0;
    }
    if (b9 == 0) {
        return;
    }

    j1 = arg0->v4b[0];
    h1 = arg0->v4a[0];
    i1 = arg0->v4a[1];
    d1 = arg0->v4b[1];
    h1 = h1 - j1;
    z2 = *(__ps_t *)lbl_80298CA0;
    h1 = h1 * h1;
    lim3 = lbl_80298DEC;
    i1 = i1 - d1;
    i1 = __builtin_ps_merge00(i1, z2);
    u1 = __builtin_ps_madds0(i1, i1, h1);
    tc.ps = __builtin_ps_sum0(u1, u1, u1);
    x3 = tc.flt.hi;
    if (x3 < lim3) {
        return;
    }

    arg0->unk0x110 = lbl_80298DF0;
}
