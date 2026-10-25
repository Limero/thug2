// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80184D74-0x80184EB0 (316B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A94A8[];
s32 fn_8018EC08(void);
s32 fn_8018E24C(Unk_C7387A53 *);
s32 CStruct_new(s32);
void fn_8018EC38(Unk_C7387A53 *);
void CStruct_delete(CStruct *, s32);
s32 fn_80127848(CStruct *, void *, s32);
s32 CStruct_ctor(s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_8018BFAC(Unk_C7387A53 *);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_801317C0(s32);
void fn_801843AC(s32, s32);
s32 GoalManager_GetGoal(s32, s32, s32);
void fn_80184D74(Unk_C7387A53 *arg0) {
    s32 temp_r31;
    void *temp_r30;
    Unk_5BE2D2B7 *temp_r9;
    Unk_E71E4713 *temp_r9_2;

    if ((s32) arg0->unk0x38 != 0) {
        temp_r30 = GoalManager_GetGoal(arg0, arg0->unk0x38, 1);
        fn_8018EC08();
        fn_801843AC(arg0, 0);
        fn_801317C0(QB_SK3_KILLSKATER);
        fn_801317C0(QB_SK3_KILLSKATER_FINISH);
        Script_RunScript(QB_KILL_BLUR, 0, 0, 0, 0);
        temp_r9 = ((Unk_C8FEE62D *)temp_r30)->unk0x14;
        if ((temp_r9->unk0xAC(temp_r30 + temp_r9->unk0xA8) == 0) || (ContainsFlag(fn_8018BFAC(temp_r30), QB_DONT_KILL_TRIGGER_ON_SUCCESS) != 0)) {

temp_r31 = CStruct_ctor(CStruct_new(8));
            fn_80127848(temp_r31, lbl_802A94A8, fn_8018E24C(temp_r30));
            Script_RunScript(QB_GOALMANAGER_RESETGOALTRIGGER, temp_r31, 0, 0, 0);
            if (temp_r31 != 0) {
                CStruct_delete(temp_r31, 3);
            }
        }
        temp_r9_2 = ((Unk_C8FEE62D *)temp_r30)->unk0x14;
        ((s32 (*)(void *))temp_r9_2->unk0x64)(temp_r30 + temp_r9_2->unk0x60);
        fn_8018EC38(temp_r30);
    }
}
