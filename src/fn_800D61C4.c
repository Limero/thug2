// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D61C4-0x800D637C (440B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern const f32 lbl_80299B90;
extern const f32 lbl_80299B94;
extern const f32 lbl_80299B98;
extern const f32 lbl_80299B9C;

s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetVector(CStruct *, s32, void *, s32);
s32 ContainsFlag(CStruct *, s32);

typedef struct {
    char pad0x00[0x0C];
    char *p0C;
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    char pad0x20[0x1F0];
    f32 f210;
    f32 f214;
    f32 f218a;
    f32 f21C;
    f32 f220a;
    f32 f220b;
    s32 f228;
    char pad0x22C[0x14];
    f32 f240;
    f32 f244;
    f32 f248;
    s32 pad24C;
    s32 f250;
    f32 f254;
    __ps_t p258;
    __ps_t p260;
} Obj61C4;

s32 fn_800D61C4(Obj61C4 *arg0, CStruct *arg1) {
    f32 k3;
    s32 flag;

    arg0->f210 = lbl_80299B90;
    GetFloat(arg1, QB_SPEED, &arg0->f210, 0);
    arg0->f240 = arg0->f210;
    arg0->f214 = lbl_80299B94;
    GetFloat(arg1, QB_GRAVITY, &arg0->f214, 0);
    k3 = lbl_80299B98;
    {
        char *p = arg0->p0C;
        *(__ps_t *)&arg0->p258 = *(__ps_t *)(p + 88);
        *(__ps_t *)&arg0->p260 = *(__ps_t *)(p + 96);
    }
    arg0->f244 = k3;
    GetFloat(arg1, QB_COL_DIST_ABOVE, &arg0->f244, 0);
    arg0->f248 = k3;
    GetFloat(arg1, QB_COL_DIST_BELOW, &arg0->f248, 0);
    if (GetVector(arg1, QB_HEADING, &arg0->f218a, 0) != 0) {
        arg0->f228 = 1;
        arg0->f210 = arg0->f210 * arg0->f21C;
        arg0->f21C = lbl_80299B9C;
    } else {
        flag = ContainsFlag(arg1, QB_USE_CURRENT_HEADING);
        if (flag != 0) {
            char *p;
            f32 v210;
            f32 c;
            f32 t21;
            p = arg0->p0C;
            v210 = arg0->f210;
            c = lbl_80299B9C;
            *(__ps_t *)&arg0->f218a = *(__ps_t *)(p + 240);
            t21 = arg0->f21C;
            *(__ps_t *)&arg0->f220a = *(__ps_t *)(p + 248);
            arg0->f228 = 1;
            arg0->f21C = c;
            arg0->f210 = v210 * t21;
        } else {
            arg0->f228 = flag;
        }
    }
    arg0->f250 = 0;
    if (GetFloat(arg1, QB_LAND_HEIGHT, &arg0->f254, 0) != 0) {
        arg0->f250 = 1;
    }
    arg0->unk0x1C |= 0x100;
    return 1;
}
