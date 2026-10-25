// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AB224-0x800AB348 (292B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
void GetInteger(CStruct *, s32, s32 *, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void CStruct_dtor(CStruct *);
void CStruct_new(s32);
void fn_800AB224(CScript *arg0, CStruct *arg1) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r9;
    s32 var_r9_2;

    if ((s32) arg0->unk0x38 == 0) {
        CStruct_new(8);
        arg0->unk0x38 = CStruct_ctor();
    }
    CStruct_dtor(arg0->unk0x38);
    if (GetChecksum_2(arg1, QB_EXITSCRIPT, (char *)arg0 + 0x34, 0) != 0) {
        sp8 = 0;
        if (GetStructure_2(arg1, QB_EXITPARAMS, &sp8, 0) != 0) {
            fn_80126FF4(arg0->unk0x38, sp8);
        }
    }
    spC = 0;
    GetInteger(arg1, QB_SKIPPABLE, &spC, 0);
    var_r9 = 1;
    if (spC == 0) {
        var_r9 = 0;
    }
    arg0->unk0x20 = var_r9;
    arg0->unk0x1C = ContainsFlag(arg1, QB_PLAY_HOLD);
    sp10 = 0;
    GetInteger(arg1, QB_ALLOW_PAUSE, &sp10, 0);
    var_r9_2 = 1;
    if (sp10 == 0) {
        var_r9_2 = 0;
    }
    arg0->unk0x2C = var_r9_2;
}
