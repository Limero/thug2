// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9900-0x801A99B0 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80305F1C[];
extern s32 fn_801A8A38(s32, s32);
extern s32 Game_GetGoalManager(void);
extern void fn_80187B84(s32, s32);
bool fn_801A9900(Unk_03123917 *arg0, s32 arg1) {
    s32 *temp_r28;
    s32 *var_r9;
    s32 temp_r0;
    u32 var_r11;
    u32 var_r31;
    u32 temp_r9;
    u32 off;

    var_r31 = arg0->unk0x804;
    if (var_r31 > 0x200U) {
        var_r31 = 0x200;
    }
    arg1 = fn_801A8A38(*(s32 *)&lbl_80305F1C, arg1);
    if (arg1 == 0) {
        return false;
    }
    var_r11 = 0U;
    temp_r28 = (s32 *)((char *)arg0 + 4);
    if (var_r11 < var_r31) {
        var_r9 = temp_r28;
        do {
            temp_r0 = *var_r9;
            var_r9 += 1;
            if (temp_r0 == arg1) {
                return false;
            }
            var_r11 += 1;
        } while (var_r11 < var_r31);
    }
    fn_80187B84(Game_GetGoalManager(), arg1);
    temp_r9 = arg0->unk0x804;
    off = (temp_r9 * 4) & 0x7FC;
    temp_r9 += 1;
    *(s32 *)((char *)temp_r28 + off) = arg1;
    arg0->unk0x804 = temp_r9;
    return false;
}
