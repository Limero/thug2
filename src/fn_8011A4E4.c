// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A4E4-0x8011A56C (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_8029D500;
extern f32 lbl_8029D504;
typedef struct { s32 i0; char _4[0xC]; f32 f10; } SrcV;
typedef struct { f32 f0, f4, f8; s32 iC; } FlagV;
typedef struct { s32 i0; f32 f4, f8, fC, f10, f14, f18, f1C, f20, f24; s32 i28; } DstV;
void fn_8011A4E4(s32 dummy, DstV *dst, SrcV *src, FlagV *flag) {
    f32 a, b, c, d, e;
    if (flag != NULL) {
        a = flag->f0;
        c = lbl_8029D500;
        dst->f8 = a;
        b = flag->f4;
        dst->fC = b;
        d = flag->f8;
        e = (d == c) ? src->f10 : d;
        dst->f4 = e;
        dst->f18 = a;
        dst->f1C = b;
        dst->f20 = c;
        dst->f10 = a;
        dst->f14 = b;
        dst->f24 = c;
        dst->i28 = flag->iC;
    } else {
        dst->f8 = lbl_8029D504;
        dst->f4 = lbl_8029D500;
        dst->fC = lbl_8029D504;
        dst->i28 = (s32)flag;
    }
    dst->i0 = src->i0;
}
