// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015EDF0-0x8015EE80 (144B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern char lbl_802A8248[];
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80174AB8(void *, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void fn_80127D38(CStruct *, void *, s32);
s32 ScriptGetPlayerAppearance(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;
    s32 temp_r31;
    s32 var_r3;

    sp8 = 0;
    GetInteger(pParams, QB_PLAYER, &sp8, 0);
    temp_r31 = fn_80174AB8(lbl_80305EAC, sp8) + 0x5C;
    var_r3 = 0;
    if (temp_r31 != 0) {
        temp_r30 = CStruct_ctor(CStruct_new(8));
        fn_80126FF4(temp_r30, temp_r31);
        fn_80127D38(pScript->unk0x18, (s32)lbl_802A8248, temp_r30);
        var_r3 = 1;
    }
    return var_r3;
}
