// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80191508-0x80191618 (272B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_80190ACC(void *, s32 *, s32, s32, void *, s32);
s32 fn_80191FD4(s32 *);
void fn_80191C50(void *);
void fn_80191050(CStruct *, s32, s32, s32, s32);

void fn_80191508(CStruct *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    register s32 var_r28 __asm__("r28");
    s32 temp_r29;
    s32 temp_r8;

    if (arg0->unk0x4 == 0) {
        temp_r29 = ContainsFlag(fn_80191FD4(arg0), QB_NO_STREAM);
        if (temp_r29 == 0) {
            sp8 = -1;
            var_r28 = 0;
            __asm__("" : "+r"(var_r28));
            GetInteger(arg1, QB_CAM_ANIM_INDEX, &sp8, 0);
            spC = temp_r29;
            GetString(arg1, QB_SPEAKER_NAME, &spC, 0);
            temp_r8 = ContainsFlag(arg1, QB_LAST_ANIM);
            if (fn_80190ACC(arg0, &sp10, sp8, 0, spC, temp_r8) != 0) {
                var_r28 = 1;
            }
            if (sp10 != 0) {
                fn_80191C50(arg0);
                *(volatile s32 *)&sp14 = temp_r29;
                GetChecksum_2(arg1, QB_SPEAKER_OBJ_ID, &sp14, 0);
                fn_80191050(arg0, sp10, 0, sp14, var_r28);
            }
        }
    }
}
