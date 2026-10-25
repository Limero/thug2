// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FE60C-0x801FE6E8 (220B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AE88C;
extern s32 lbl_80305EAC;
f32 fn_8012570C(s32 arg0, s32 arg1);
f32 fn_800144C8(void);
void fn_8009F010(s32 arg0, s32 arg1, s32 arg2);
void fn_801FE60C(Unk_C8FEE62D *arg0) {
    volatile double _dummy;
    f32 temp_f31;
    f32 var_f0;
    s32 state = arg0->unk0x1C;
    if (state == 1) {
        s32 t = *(s32 *)(arg0->unk0x28 + (s32)0x1C);
        switch (t) {
        case 2:
        case 3:
        case 4:
            temp_f31 = fn_8012570C(QB_HANG_RUN_TIMER_SPEED_ADJUSTMENT, 0);
            var_f0 = *((f32 *)&arg0->unk0x20) - (temp_f31 * fn_800144C8());
            break;
        default:
            var_f0 = *((f32 *)&arg0->unk0x20) - fn_800144C8();
            break;
        }
merge:
        *((f32 *)&arg0->unk0x20) = var_f0;
        if (*((volatile f32 *)&arg0->unk0x20) < *(volatile f32 *)&lbl_802AE88C) {
            arg0->unk0x1C = 3;
            fn_8009F010(arg0->unk0xC, QB_RUNTIMERUP, 0);
        }
    } else if (state == 3) {
        fn_8009F010(arg0->unk0xC, QB_RUNTIMERUP, 0);
    }
}
