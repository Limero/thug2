// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D8530-0x800D8610 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_80299C00;
extern f32 lbl_80299C04;

s32 GetVector(CStruct *, s32, void *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_80005C04(void *);
s32 fn_800D81F0(Unk_87C37330 *, CStruct *, s32, void *, s32);

void fn_800D8530(Unk_87C37330 *arg0, CStruct *arg1, s32 arg2, s32 arg3) {
    f32 sp8[4];
    f32 sp16[4];
    f32 *p8 = &sp8[0];

    sp8[0] = lbl_80299C00;
    p8[1] = lbl_80299C00;
    p8[2] = lbl_80299C00;
    p8[3] = lbl_80299C04;
    GetVector(arg1, 0, p8, 0);
    if (ContainsFlag(arg1, QB_FLAG_MAX_COORDS) != 0) {
        fn_80005C04(p8);
    }
    if (arg3 == 0) {
        void *p = *(void **)((char *)arg0 + 0xC);

        *(__ps_t *)&sp8[0] = __builtin_ps_add(*(__ps_t *)&sp8[0], *(__ps_t *)((char *)p + 0x58));
        *(__ps_t *)&p8[2] = __builtin_ps_add(*(__ps_t *)&p8[2], *(__ps_t *)((char *)p + 0x60));
    }
    *(__ps_t *)&sp16[0] = *(__ps_t *)&sp8[0];
    *(__ps_t *)&sp16[2] = *(__ps_t *)&p8[2];
    fn_800D81F0(arg0, arg1, arg2, sp16, 0);
}
