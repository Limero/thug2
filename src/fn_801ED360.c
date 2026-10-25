// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801ED360-0x801ED494 (308B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AD920;
extern s32 fn_801ED494(Unk_FF487DD2 * arg0);
extern s32 Script_RunScript(s32 a, s32 b, s32 c, s32 d, s32 e);
void fn_801ED360(Unk_56FA3D0E *arg0) {
    s32 var_r11;
    CScript *temp_r11;
    s32 temp_r9;

    if ((arg0->unk0x1554 == 0) && (arg0->unk0x348 != 0) && (*(s32 *)(arg0->unk0x15BC + (s32)0xA0) == 0)) {
        temp_r11 = (void *)arg0->unk0x15CC;
        if ((temp_r11->unk0x20 == 0) && (temp_r11->unk0x1C == 0) && (*((f32 *)&temp_r11->unk0x28) == lbl_802AD920)) {
            temp_r9 = arg0->unk0x1550;
            if (temp_r9 != 0) {
                arg0->unk0x1550 = temp_r9 - 1;
                return;
            }
            if ((arg0->unk0x34C > 0) && (fn_801ED494(arg0) != 0) && (arg0->unk0x1550 == 0)) {
                arg0->unk0x1550 = 0x1E;
                var_r11 = 0;
                temp_r9 = ((Unk_C7387A53 *)arg0->unk0x15C4)->unk0x38;
                if (((Unk_E06AC104 *)temp_r9)->unk0x188 == 0) {
                    var_r11 = ((((Unk_E06AC104 *)temp_r9)->unk0x20 ^ 1) == 0);
                }
                if (var_r11 != 0) {
                    Script_RunScript(QB_WALK_MAYBE_THROW_PROJECTILE, 0, arg0->unk0xC, 0, 0);
                    return;
                }
                Script_RunScript(QB_SKATE_MAYBE_THROW_PROJECTILE, 0, arg0->unk0xC, 0, 0);
            }
        }
    }
}
