// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80152704-0x801527D8 (212B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_8009F3D0(Unk_C8FEE62D *, void *, CStruct *);
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 GetStructure_2(CStruct *, void *, s32 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 fn_801746A4(Unk_C7387A53 *, void *);
bool ScriptMakeSkaterGosub(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    Unk_31DE137E *var_r3;

    sp8 = 0;
    GetStructure_2(arg0, QB_PARAMS, &sp8, 0);
    spC = 0;
    GetChecksum_2(arg0, 0, &spC, 0);
    if ((arg1 == NULL) || (var_r3 = arg1->unk0xBC, ((var_r3 == NULL) != 0)) || ((s32) var_r3->unk0x1C != QB_OBJECT_TYPE_SKATER)) {
        temp_r30 = lbl_80305EAC;
        sp10 = 0;
        GetInteger(arg0, QB_SKATER, &sp10, 0);
        var_r3 = fn_801746A4(temp_r30, sp10);
    }
    if (var_r3 != NULL) {
        fn_8009F3D0(var_r3, spC, sp8);
    }
    return true;
}
