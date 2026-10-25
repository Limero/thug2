// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B91DC-0x801B92C4 (232B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_800F0598(s32);
extern s32 fn_800F0610(void *, s32);
extern s32 fn_800F0F84(s32, s32);
extern void fn_800F0838(void *, Unk_9994C3F5 *);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern void fn_801B3220(Unk_C7387A53 *, s32 *, s32 *, Unk_C8FEE62D *);
bool fn_801B91DC(Unk_A9157FE7 *arg0) {
    s32 sp8;
    s32 count;
    s32 var_r29;
    s32 var_r31;

    if (arg0->unk0x24 & 4) {
        arg0->unk0x24 = (arg0->unk0x24 & QB_UNKNOWN_0xFFFFFFFB) | 0x80;
        count = fn_800F0598(arg0->unk0x5C);
        if (count > 1) {
            for (var_r29 = 0; var_r29 < count; var_r29++) {
                var_r31 = fn_800F0610(arg0->unk0x5C, var_r29);
                if ((GetChecksum_2(fn_800F0F84(var_r31, 1), QB_SKATEACTION, &sp8, 0) != 0)
                    && (sp8 == (s32)QB_GRIND_BAIL)) {
                    arg0->unk0x60 = var_r31;
                    fn_800F0838(var_r31, (char *)arg0 + 0x88);
                    break;
                }
            }
        }
        fn_801B3220(arg0, QB_STATE_BAILGRIND, QB_SKATERPED_STATETABLE, 0);
        return true;
    }
    return false;
}
