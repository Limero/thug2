// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015B4DC-0x8015B528 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
extern char lbl_80305EAC[];
s32 ScriptSpinTapsAreOn(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r3;
    s32 temp_r4;

    sp8 = 0;
    GetInteger(pParams, 0, &sp8, 0);
    temp_r3 = *(s32 *)&lbl_80305EAC + 0x3AC;
    temp_r4 = sp8 * 0x10;
    return *(s32 *)((char *)temp_r3 + temp_r4);
}
