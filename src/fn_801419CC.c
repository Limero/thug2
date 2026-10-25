// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801419CC-0x80141B08 (316B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EE4;
static void *GetChecksum_3(void *arg0, u32 arg1);
static s32 fn_8014036C(s32 arg0, s32 arg1, s32 arg2);
static void fn_8019D438(void *arg0, s32 arg1);
static void fn_801C51A4(void *arg0, s32 arg1);
void fn_801419CC(Unk_C7387A53 *arg0, s32 arg1) {
    s32 temp_r29;
    Unk_31DE137E *temp_r3;

    temp_r29 = lbl_80305EE4;
    if ((arg0->unk0x2EC != arg1) && ((temp_r3 = GetChecksum_3(arg0, QB_SKATERPHYSICSCONTROL)) != NULL)) {
        arg0->unk0x2EC = arg1;
        switch (arg1) {
        case 0:
            if (fn_8014036C(QB_SCREENSHOTMODE, 0, 0) != 0) {
                fn_8019D438((void *)temp_r29, 0);
            }
            break;
        case 1:
            if (fn_8014036C(QB_SCREENSHOTMODE, 0, 0) != 0) {
                fn_8019D438((void *)temp_r29, 1);
            } else {
                temp_r3 = GetChecksum_3(arg0, QB_SKATERPHYSICSCONTROL);
                if (temp_r3->unk0x1C != 1) {
                    fn_801C51A4(temp_r3, 1);
                }
            }
            break;
        case 2:
            if ((fn_8014036C(QB_SCREENSHOTMODE, 0, 0) == 0)
                && (*(s32 *)((char *)(temp_r3 = GetChecksum_3(arg0, QB_SKATERPHYSICSCONTROL)) + (s32)0x1C) != 0)) {
                fn_801C51A4(temp_r3, 0);
            }
            break;
        }
    }
}
