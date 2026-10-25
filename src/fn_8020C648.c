// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020C648-0x8020C740 (248B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D *, u32);
extern s32 GetChecksum_2(CStruct *, u32, s32 *, s32);
extern s32 GetStructure_2(CStruct *, u32, s32 *, s32);
extern s32 CStruct_new(s32);
extern s32 fn_80126EDC(CStruct *, CStruct *);
extern void fn_802096A0(Unk_1DFFEF1A *, s32, CStruct *, CStruct *);
extern void CStruct_delete(CStruct *, s32);
bool ScriptDoNextTrick(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    register s32 var_r30 __asm__("r30");
    s32 temp_r31;

    var_r30 = 0;
    temp_r31 = GetChecksum_3(arg1->unk0xBC, QB_TRICK);
    sp8 = var_r30;
    spC = var_r30;
    GetChecksum_2(arg0, QB_SCRIPTTORUNFIRST, &sp8, 0);
    GetStructure_2(arg0, QB_PARAMS, &spC, 0);
    sp10 = var_r30;
    GetStructure_2(arg0, QB_TRICKPARAMS, &sp10, 0);
    if (sp10 != 0) {
        var_r30 = fn_80126EDC(CStruct_new(8), sp10);
        fn_802096A0(temp_r31, sp8, spC, var_r30);
        if (var_r30 != 0) {
            CStruct_delete(var_r30, 3);
        }
    } else {
        fn_802096A0(temp_r31, sp8, spC, 0);
    }
    return true;
}
