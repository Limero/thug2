// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80116790-0x80116840 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
void fn_80126FF4(void *, void *);
void fn_8012F260(void *, s32, void *, void *);
void CStruct_delete(CStruct *, s32);
bool ScriptGotoPreserveParams(CStruct *arg0, Unk_EFC8CFAD *arg1) {
    s32 spC; s32 sp8; s32 temp_r31;
    sp8 = 0;
    GetChecksum_2(arg0, 0, &sp8, 0);
    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_80126FF4(temp_r31, arg1->unk0x18);
    spC = 0;
    GetStructure_2(arg0, QB_PARAMS, &spC, 0);
    fn_80126FF4(temp_r31, spC);
    fn_8012F260(arg1, sp8, temp_r31, arg1->unk0xBC);
    if (temp_r31 != 0) { CStruct_delete(temp_r31, 3); }
    return true;
}
