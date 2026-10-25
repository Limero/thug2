// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80096D38-0x80096E4C (276B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8037B5E8[];
extern char lbl_8037B644[];
void fn_8001D424(void *);
void PSMTX_MultVec(s32, void *, void *);

typedef struct { f32 x, y, z, r; } Sph;
typedef struct { char pad0[0x130]; f32 a, b, c, d, e, g; } Bounds;

s32 fn_80092DD4(Sph *, s32);

s32 fn_80096D38(Sph *arg0) {
    f32 sp8[3];
    f32 sp18[3];
    Bounds *bd;
    f32 temp_f12, temp_f13, temp_f12_2, temp_f13_2;
    f32 xx, yy, zz;

    fn_8001D424(sp8);
    fn_8001D424(sp18);
    sp8[0] = arg0->x;
    sp8[1] = arg0->y;
    sp8[2] = arg0->z;
    PSMTX_MultVec((s32)lbl_8037B644, sp8, sp18);
    bd = (Bounds *)lbl_8037B5E8;
    xx = sp18[0];
    yy = sp18[1];
    zz = sp18[2];

    if (arg0->r < (zz - bd->e)) return 1;
    if (arg0->r < (bd->g - zz)) return 1;
    if ((temp_f12 = bd->b * zz, temp_f13 = bd->d * yy, arg0->r < (temp_f12 + temp_f13))) return 1;
    if (arg0->r < (temp_f12 - temp_f13)) return 1;
    if ((temp_f13_2 = bd->a * zz, temp_f12_2 = bd->c * xx, arg0->r < (temp_f13_2 - temp_f12_2))) return 1;
    if (!(arg0->r < (temp_f13_2 + temp_f12_2))) {
        __asm__ __volatile__("");
    } else {
        return 1;
    }

    if (fn_80092DD4(arg0, 1) != 0) {
        return 2;
    }
    return 0;
}
