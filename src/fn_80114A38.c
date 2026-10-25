// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80114A38-0x80114ADC (164B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029D1C0;
s32 fn_801270B4(CStruct *, void *);
s32 AddInteger(CStruct *, void *, void *);
s32 GetFloat(CStruct *, void *, f32 *, void *);
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
bool ScriptCastToInteger(CStruct *pParams, CScript *pScript) {
    f32 spC;
    s32 sp8;

    sp8 = 0;
    if (GetChecksum_2(pParams, 0, &sp8, 0) != 0) {
        spC = lbl_8029D1C0;
        if (GetFloat(pScript->unk0x18, sp8, &spC, 0) != 0) {
            fn_801270B4(pScript->unk0x18, sp8);
            AddInteger(pScript->unk0x18, sp8, (s32) spC);
            return true;
        }
    }
    return false;
}
