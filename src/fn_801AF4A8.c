// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AF4A8-0x801AF5DC (308B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801AED60(Unk_C7387A53 *);
s32 Game_GetGoalManager();
s32 fn_80184F88(Unk_C7387A53 *);
void fn_8018505C(s32, s32);
s32 fn_801AED20(Unk_C7387A53 *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddInteger(CStruct *, s32, s32);
s32 fn_801AED74(s32);
void AddString(CStruct *, s32, void *);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_801AED28(Unk_C7387A53 *);
void fn_801AED54(Unk_C7387A53 *);
void fn_801AF4A8(CStruct *arg0) {
    s32 temp_r31;
    s32 var_r28;
    s8 var_r29;
    Unk_C7387A53 *var_r30;
    register void *var_r9 __asm__("r9");

    var_r9 = *((void * *)&arg0->unk0x10);
    var_r28 = 0;
    if (((CStruct *)var_r9)->unk0x4 == -1) {
        var_r9 = NULL;
    }
    var_r29 = 0;
    var_r30 = var_r9;
    if (var_r30 != NULL) {
        do {
            if (fn_801AED60(var_r30) != 0) {
                if (fn_80184F88(temp_r31 = Game_GetGoalManager()) != 0) {
                    fn_8018505C(temp_r31, var_r28);
                }
                if (fn_801AED20(var_r30) == 0) {
                    var_r29 += 1;
                    temp_r31 = CStruct_ctor(CStruct_new(8));
                    if (var_r29 > 1) {
                        AddInteger(temp_r31, QB_MULTIPLE_NEW_GAPS, var_r29);
                    }
                    AddString(temp_r31, QB_GAP_TEXT, fn_801AED74(var_r30));
                    Script_RunScript(QB_GOT_GAP_FOR_FIRST_TIME, temp_r31, 0, 0, 0);
                    if (temp_r31 != 0) {
                        CStruct_delete(temp_r31, 3);
                    }
                }
                fn_801AED28(var_r30);
            }
            fn_801AED54(var_r30);
            var_r9 = *((void * *)&var_r30->unk0xC);
            if (((CStruct *)var_r9)->unk0x4 == -1) {
                var_r9 = NULL;
            }
            var_r28 += 1;
            var_r30 = var_r9;
        } while (var_r30 != NULL);
    }
}
