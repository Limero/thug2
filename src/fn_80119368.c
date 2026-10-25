// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119368-0x80119398 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE50[];

bool ScriptIsPS2(CStruct *pParams, CScript *pScript) {
    s32 temp_r0;

    temp_r0 = *(s32 *)&lbl_802FFE50;
    if (temp_r0 == 1) {
        goto block_5;
    }
    if (temp_r0 == 2) {
        goto block_5;
    }
    if (temp_r0 == 3) {
        goto block_5;
    }
    goto block_8;
block_5:
    return true;
block_8:
    return false;
}