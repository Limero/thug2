// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DB3A4-0x800DB484 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80301B28;
extern s32 lbl_80301B2C;

f32 fn_8012570C(s32, s32);

typedef struct DB3A4 {
    char pad0x0[0x28];
    f32 dist;           /* 0x28 */
    char pad0x2C[0x10];
    f32 lodScale;       /* 0x3C */
    char pad0x40[0xC];
    s32 keepFlag;       /* 0x4C */
} DB3A4;

s32 fn_800DB3A4(DB3A4 *arg0, f32 *arg1) {
    volatile double _dummy;
    volatile double _dummy2;
    f32 dist;
    f32 lim2;
    f32 lim4;
    s32 keep;

    keep = 1;
    dist = arg0->dist;
    if (arg1 != NULL) {
        *arg1 = dist;
    }
    if (dist > arg0->lodScale * arg0->lodScale) {
        keep = 0;
    } else {
        lim2 = fn_8012570C(QB_ANIMLODINTERLEAVE2, 0);
        lim4 = fn_8012570C(QB_ANIMLODINTERLEAVE4, 0);
        lim2 = lim2 * lim2;
        lim4 = lim4 * lim4;
        if (dist > lim4) {
            if ((++lbl_80301B2C & 3) != 0) {
                keep = 0;
            }
        } else if (dist > lim2) {
            if ((++lbl_80301B28 & 1) != 0) {
                keep = 0;
            }
        }
    }
    if (arg0->keepFlag != 0) {
        keep = 1;
    }
    return keep;
}
