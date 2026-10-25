// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FE804-0x801FE888 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A78;
extern f32 lbl_802AE8A0;
extern s32 fn_80131A24(s32 arg0);
extern void fn_800A54AC(Unk_AD65BA9A * arg0, void * arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6);
void fn_801FE804(Unk_31DE137E *arg0) {
    Unk_9D99273B *temp_r11;

    if (fn_80131A24(((Unk_C7387A53 *)arg0->unk0xC)->unk0x2E8 + QB_RUNTIMERCONTROLLER) != 0) {
        temp_r11 = arg0->unk0xC;
        fn_800A54AC(lbl_80301A78, QB_HIDERUNTIMER, temp_r11->unk0x2E8 + QB_RUNTIMERCONTROLLER, temp_r11->unk0x18, 0, 0, lbl_802AE8A0);
    }
    arg0->unk0x1C = 0;
}
