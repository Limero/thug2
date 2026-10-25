// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007D4E0-0x8007D584 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_8037B614[];
extern const f32 lbl_80295E5C;
extern const f32 lbl_80295E60;
extern const f32 lbl_80295E64;
void GX_Project(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void GX_GetProjectionv(f32 *);
void GX_GetViewportv(f32 *);
f32 fn_8007D4E0(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    f32 sp8[8];
    f32 sp28[6];
    f32 k1, k2;

    GX_GetProjectionv(&sp8[0]);
    GX_GetViewportv(&sp28[0]);
    GX_Project(arg1[0], arg1[1], arg1[2], lbl_8037B614, &sp8[0], &sp28[0], arg2, arg3, arg4);
    k1 = lbl_80295E5C;
    k2 = lbl_80295E60;
    *arg2 *= k1;
    *arg3 *= k2;
    return lbl_80295E64;
}
