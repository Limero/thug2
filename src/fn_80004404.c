// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80004404-0x80004518 (276B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    f32 m00;
    f32 m01;
    f32 m02;
    f32 m03;
    f32 m10;
    f32 m11;
    f32 m12;
    f32 m13;
    f32 m20;
    f32 m21;
    f32 m22;
    f32 m23;
    f32 m30;
    f32 m31;
    f32 m32;
    f32 m33;
} Matrix44;

extern f32 lbl_8028FC94;
extern f32 lbl_8028FC98;
extern f32 lbl_8028FC9C;
f32 sinf(f32);
f32 cosf(f32);

void *fn_80004404(Matrix44 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    volatile double frame_pad[5];
    f32 temp_f0;
    f32 temp_f13;
    f32 temp_f1;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;

    temp_f13 = lbl_8028FC98;
    temp_f0 = lbl_8028FC94;
    temp_f29 = farg0 * temp_f13;
    arg0->m00 = temp_f0;
    arg0->m01 = temp_f0;
    arg0->m02 = temp_f0;
    arg0->m03 = temp_f0;
    arg0->m10 = temp_f0;
    arg0->m11 = temp_f0;
    arg0->m12 = temp_f0;
    arg0->m13 = temp_f0;
    arg0->m20 = temp_f0;
    arg0->m21 = temp_f0;
    arg0->m22 = temp_f0;
    arg0->m23 = temp_f0;
    arg0->m30 = temp_f0;
    arg0->m31 = temp_f0;
    arg0->m32 = temp_f0;
    arg0->m33 = temp_f0;
    temp_f31 = cosf(temp_f29);
    temp_f28 = farg1 * (temp_f31 / sinf(temp_f29));
    temp_f31_2 = cosf(temp_f29);
    temp_f1 = sinf(temp_f29);
    temp_f30 = farg3 / (farg3 - farg2);
    arg0->m00 = temp_f28;
    arg0->m23 = lbl_8028FC9C;
    arg0->m22 = temp_f30;
    arg0->m11 = temp_f31_2 / temp_f1;
    arg0->m32 = -temp_f30 * farg2;
    return arg0;
}
