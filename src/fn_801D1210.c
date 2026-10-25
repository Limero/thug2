// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D1210-0x801D1380 (368B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern const f32 lbl_802AD3D0;
extern f64 lbl_802AD3D8;
extern f32 lbl_802AD3E0;
extern s32 lbl_80303150;
// The callee's real machine interface is (r3, r4, r5, f1) -> void.  Declaring
// the float parameter in second position keeps that exact interface while
// changing the order GCC expands the argument expressions in (the same
// ABI-preserving prototype reorder used by fn_80155AA4).
extern void fn_8009F054(s32, f32, s32, s32);
extern f32 fn_8012570C(s32, s32);
extern s32 Tmr_GetTime();
extern void fn_801F1340(Unk_31DE137E *, s32);

void fn_801D1210(Unk_03AE98FA *arg0) {
    char *m1;
    char *m2;
    char *m3;
    char *m4;
    Unk_04C3523A *m5;
    Unk_4C649A8C *g1;
    Unk_5EF41E38 *g2;
    char *g3;
    char *d1;
    f32 fa;
    f32 fb;
    f32 tf1;
    s32 cvt;
    s32 z;
    u32 t268;
    u32 old264;

    if (arg0->unk0x570 != 0) {
        arg0->unk0x570 = 0;
        fn_8009F054(arg0->unk0xC, lbl_802AD3D0, QB_SKATEREXITVERTAIR, 0);
    }
    tf1 = fn_8012570C(QB_RAIL_WALK_RERAIL_TIME, 1);
    if (!(tf1 >= lbl_802AD3D8)) {
        cvt = (s32)tf1;
    } else {
        cvt = (s32)(tf1 - lbl_802AD3D8);
        cvt ^= (s32)0x80000000;
    }
    t268 = arg0->unk0x268;
    old264 = arg0->unk0x264;
    arg0->unk0x26C = cvt;
    if (t268 > old264) {
        arg0->unk0x264 = t268;
    }
    m1 = arg0->unk0x15BC;
    if ((((Unk_1D62F22E_2 *)m1)->unk0x1C == 1) && (arg0->unk0x9C == 3)) {
        g1 = m1 + 0x6C;
        if (g1->unk0x4 != 0) {
            g1->unk0x4 = 0;
            g1->unk0x8 = lbl_80303150 + Tmr_GetTime();
        }
    }
    fn_801F1340((s32)arg0->unk0x15BC, 0);
    fa = lbl_802AD3D0;
    fb = lbl_802AD3E0;
    m2 = arg0->unk0x15BC;
    ((Unk_28CB32B5 *)m2)->unk0x168 = fa;
    g2 = m2 + 0x168;
    z = 0;
    g2->unk0x4 = fb;
    g2->unk0x8 = fa;
    ((Unk_4C649A8C *)g2)->unk0xC = fb;
    m3 = arg0->unk0x15BC;
    ((Unk_E0563472 *)m3)->unk0x178 = fa;
    m3 = m3 + 0x178;
    ((Unk_E0563472 *)m3)->unk0x4 = fb;
    ((Unk_E0563472 *)m3)->unk0x8 = fa;
    ((Unk_E0563472 *)m3)->unk0xC = fb;
    m4 = arg0->unk0x15BC;
    ((Unk_AE633EE7 *)m4)->unk0x150 = fa;
    m4 = m4 + 0x150;
    ((Unk_AE633EE7 *)m4)->unk0x4 = fa;
    ((Unk_AE633EE7 *)m4)->unk0x8 = fa;
    ((Unk_AE633EE7 *)m4)->unk0xC = fb;
    m5 = arg0->unk0x15BC;
    m5->unk0x160 = z;
}
