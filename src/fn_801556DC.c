// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801556DC-0x8015594C (624B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A7FA4[];
extern char lbl_802A7F98[];
extern char lbl_802A7FB4[];
s32 fn_800A9E0C(s32, s32, s32);
s32 fn_800F0F84(s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_80128C20(CStruct *, void *, void *, s32);
void AddString(CStruct *, s32, void *);
void AddChecksum(CStruct *, s32, s32);
void fn_80127C14(CStruct *, s32, CStruct *);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_8012772C(CStruct *, s32, f32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);

bool ScriptAddRestartsToMenu(CStruct *pParams, CScript *pScript) {
    f32 spC;
    s32 sp8;
    s32 temp_r30;
    s32 temp_r31;
    s32 var_r25;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;

    var_r25 = (s32)lbl_802A7FA4;
    var_r28 = 0;
    var_r27 = 0;
    var_r29 = 0x1E240;
loop_1:
    var_r28 = fn_800A9E0C(0, 0, var_r28);
    if (var_r28 != 0) {
        if (fn_80128C20(fn_800F0F84(var_r28, 1), (s32)lbl_802A7F98, &sp8, 0) == 0) {
            sp8 = var_r25;
        }
        temp_r31 = CStruct_ctor(CStruct_new(8));
        AddString(temp_r31, QB_TEXT, sp8);
        AddChecksum(temp_r31, QB_ID, var_r29);
        AddChecksum(temp_r31, QB_NO_BG, QB_NO_BG);
        AddChecksum(temp_r31, QB_CENTERED, QB_CENTERED);
        AddChecksum(temp_r31, QB_PAD_CHOOSE_SCRIPT, QB_SKIP_TO_SELECTED_RESTART);
        AddChecksum((temp_r30 = CStruct_ctor(CStruct_new(8))), QB_NODE_NAME, var_r28);
        fn_80127C14(temp_r31, QB_PAD_CHOOSE_PARAMS, temp_r30);
        GetFloat(pParams, QB_INITIAL_SCALE, &spC, 1);
        fn_8012772C(temp_r31, QB_SCALE, spC);
        Script_RunScript(QB_THEME_MENU_ADD_ITEM, temp_r31, 0, 0, 0);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
        if (temp_r30 != 0) {
            CStruct_delete(temp_r30, 3);
        }
        var_r29 += 1;
        var_r27 += 1;
        goto loop_1;
    }
    if (var_r27 == 0) {
        AddString(
            (temp_r31 = CStruct_ctor(CStruct_new(8))), QB_TEXT, (s32)lbl_802A7FB4);
        AddChecksum(temp_r31, QB_ID, 0x1E240);
        AddChecksum(temp_r31, QB_NO_BG, QB_NO_BG);
        AddChecksum(temp_r31, QB_CENTERED, QB_CENTERED);
        AddChecksum(temp_r31, QB_PAD_CHOOSE_SCRIPT, QB_SKIP_TO_SELECTED_RESTART);
        Script_RunScript(QB_THEME_MENU_ADD_ITEM, temp_r31, 0, 0, 0);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
    return true;
}
