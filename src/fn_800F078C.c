// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F078C-0x800F0838 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029B304;
extern f32 lbl_8029B308;
s32 GetVector(CStruct *arg0, s32 arg1, CStruct *arg2, s32 arg3);
typedef struct { f32 x, y, z, w; } V4;
void fn_800F078C(CStruct *arg0, V4 *arg1) {
    V4 sp8;
    V4 *p;
    f32 a, b;
    if (GetVector(arg0, QB_POS, (CStruct *)arg1, 0) == 0) {
        if (GetVector(arg0, QB_POSITION, (CStruct *)arg1, 0) != 0) {
            arg1->z = -arg1->z;
        } else {
            a = lbl_8029B304;
            p = &sp8;
            b = lbl_8029B308;
            sp8.x = a;
            p->w = b;
            p->y = a;
            p->z = a;
            ((__ps_t *)arg1)[1] = ((__ps_t *)p)[1];
            ((__ps_t *)arg1)[0] = ((__ps_t *)&sp8)[0];
        }
    }
}
