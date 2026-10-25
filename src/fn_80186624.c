// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80186624-0x80186818 (500B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8018B4C0(Unk_C8FEE62D * arg0, s32 *arg1, s32 *arg2);
s32 fn_80184168(Unk_9994C3F5 * arg0);
s32 fn_8018FC80(Unk_C7387A53 *);
void fn_8018ED70(Unk_C7387A53 *, void *);
s32 fn_8018EC90(Unk_C7387A53 *);
void ScriptIsHost(s32, s32);
s32 fn_8018E3B8(void *);
s32 fn_8018E3C4(Unk_C7387A53 *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_8018E24C(Unk_C7387A53 *);
void AddChecksum(CStruct *, s32, s32);
void AddString(CStruct *, s32, void *);
void AddInteger(CStruct *, s32, s32);
s32 Script_RunScript(s32, s32, s32, s32, s32);
s32 CStruct_delete(CStruct *, s32);

void fn_80186624(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 spC;
    s32 sp10;
    s32 sp8;
    s32 temp_r31;
    Unk_C7387A53 *temp_r30;

    sp8 = 0;
    while (sp8 < fn_80184168(arg0)) {
        temp_r30 = fn_8018B4C0(arg0 + 4, &sp8, &spC);
        sp10 = 0;
        fn_8018FC80(temp_r30);
        fn_8018ED70(temp_r30, &sp10);
        if ((sp10 != 0)
            && (fn_8018EC90(temp_r30) == 0)
            && (*(s32 *)(temp_r30->unk0x30) == 0)
            && ((ScriptIsHost(0, 0), (arg1 == 0)) || (fn_8018E3B8(temp_r30) != 0))
            && ((arg2 == 0) || (fn_8018E3C4(temp_r30) == 0))
            && ((arg3 == 0) || (fn_8018E3C4(temp_r30) != 0))) {
            temp_r31 = CStruct_ctor(CStruct_new(8));
            AddChecksum(temp_r31, QB_GOAL_ID, fn_8018E24C(temp_r30));
            AddChecksum(temp_r31, QB_PARENT, QB_CURRENT_MENU);
            AddString(temp_r31, QB_TEXT, sp10);
            AddChecksum(temp_r31, QB_FONT, QB_SMALL);
            AddInteger(temp_r31, QB_SCALE, 0);
            if (arg1 != 0) {
                Script_RunScript(QB_VIEW_SELECTED_GOALS_MENU_SET_EVENTS, temp_r31, 0, 0, 0);
            } else {
                Script_RunScript(QB_CHOOSE_GOALS_MENU_SET_EVENTS, temp_r31, 0, 0, 0);
            }
            if (temp_r31 != 0) {
                CStruct_delete(temp_r31, 3);
            }
        }
        sp8 += 1;
    }
}
