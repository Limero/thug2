// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015594C-0x80155AA4 (344B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A7FA4[];
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 GetChecksum(CStruct *, s32);
s32 fn_800F0F84(s32, s32);
s32 GetText(CStruct *, void *, void *, s32);
void AddString(CStruct *, s32, void *);
void AddChecksum(CStruct *, s32, s32);
void fn_80127C14(CStruct *, s32, CStruct *);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);

bool ScriptAddWarpPointsToMenu(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 temp_r30;
    s32 temp_r31;
    s32 var_r28;
    u32 var_r29;

    sp8 = 0;
    GetArray(pParams, QB_NODES, &sp8, 0);
    var_r29 = 0U;
    while ((u32)var_r29 < *((u32 *)&((CStruct *)sp8)->unk0x4)) {
        var_r28 = (s32)lbl_802A7FA4;
        temp_r31 = CStruct_ctor(CStruct_new(8));
        if (GetText(fn_800F0F84(GetChecksum(sp8, var_r29), 1), QB_RESTARTNAME, &spC,
                        0) == 0) {
            spC = var_r28;
        }
        AddString(temp_r31, QB_TEXT, spC);
        AddChecksum(temp_r31, QB_PAD_CHOOSE_SCRIPT, QB_WARPSKATER);
        temp_r30 = CStruct_ctor(CStruct_new(8));
        AddChecksum(temp_r30, QB_NODENAME, GetChecksum(sp8, var_r29));
        fn_80127C14(temp_r31, QB_PAD_CHOOSE_PARAMS, temp_r30);
        Script_RunScript(QB_MAKE_TEXT_SUB_MENU_ITEM, temp_r31, 0, 0, 0);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
        var_r29 += 1;
    }
    return true;
}
