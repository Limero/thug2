// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022C458-0x8022C648 (496B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_8022AE98(void *);
void *fn_8022B75C(void *, s32);
s32 fn_802195BC(Unk_C7387A53 *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void fn_80009C00(CStruct *);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
s32 Mth_Rnd(s32);
void fn_80127E70(s32, s32, s32, s32);
void AddComponent(CStruct *, s32, s32, void *);
void AddInteger(CStruct *, s32, s32);

bool ScriptChooseServer(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r31;
    register s32 var_r30 __asm__("r30");
    Unk_C7387A53 *temp_r29;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r31_2;
    Unk_FFAD6788 *temp_r28;

    temp_r28 = lbl_80305F9C;
    GetChecksum_2(pParams, QB_ID, &sp8, 0);
    var_r31 = 0;
    var_r30 = 0;
    fn_8022AE98(temp_r28);
    temp_r29 = fn_8022B75C(temp_r28, sp8);
    if (fn_802195BC(temp_r28) == 0) {
        if (((s32) temp_r29->unk0x34 >= (s32) temp_r29->unk0x38)) {
            var_r31 = 1;
            var_r30 = QB_NET_REASON_FULL;
        }
    } else if ((fn_802195BC(temp_r28) == 1) && ((s32) temp_r29->unk0x3C >= (s32) temp_r29->unk0x40)) {
        var_r31 = 1;
        var_r30 = QB_NET_REASON_FULL_OBSERVERS;
    }
    if (var_r31 != 0) {
        temp_r31 = CStruct_ctor(CStruct_new(8));
        AddChecksum((var_r31 = temp_r31), QB_REASON, var_r30);
        AddChecksum(var_r31, QB_JUST_DIALOG, 0);
        fn_80009C00(temp_r28->unk0xF0);
        Script_RunScript(QB_CREATEJOINREFUSEDDIALOG, var_r31, 0, 0, 0);
        if (var_r31 != 0) {
            CStruct_delete(var_r31, 3);
        }
    } else {
        temp_r31_2 = CStruct_ctor(CStruct_new(8));
        if (temp_r29->unk0x98 == 0) {
            temp_r30 = Mth_Rnd(0x7FFF);
            fn_80127E70(temp_r31_2, QB_COOKIE, 0xD, temp_r30 * Mth_Rnd(0x7FFF));
        }
        fn_80127E70(temp_r31_2, 0, 1, temp_r29->unk0x2C);
        AddComponent(temp_r31_2, 0, 3, 0);
        AddInteger(temp_r31_2, QB_MAXPLAYERS, temp_r29->unk0x38);
        Script_RunScript(QB_NET_CHOSEN_JOIN_SERVER, temp_r31_2, 0, 0, 0);
        if (temp_r31_2 != 0) {
            CStruct_delete(temp_r31_2, 3);
        }
    }
    return true;
}
