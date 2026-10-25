// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801174B4-0x80117540 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8012EFCC(Unk_FFAD6788 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8012729C(CStruct *);
bool ScriptBlock(CStruct *arg0, s32 arg1) {
    s32 sp8;

    sp8 = 0;
    if ((fn_8012729C(arg0) == 0) && (GetChecksum_2(arg0, QB_TYPE, &sp8, 0) == 0)) {
        GetChecksum_2(arg0, QB_UNTILEVENT, &sp8, 0);
    }
    fn_8012EFCC(arg1, sp8);
    return true;
}
