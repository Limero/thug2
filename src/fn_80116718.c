// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80116718-0x80116790 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_8012F260(Unk_15EF4A35 *, s32, Unk_C8FEE62D *, CStruct *);
bool ScriptGoto(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 spC;
    s32 sp8;

    sp8 = 0;
    GetChecksum_2(arg0, 0, &sp8, 0);
    spC = 0;
    GetStructure_2(arg0, QB_PARAMS, &spC, 0);
    fn_8012F260(arg1, sp8, spC, arg1->unk0xBC);
    return true;
}
