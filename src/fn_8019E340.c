// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019E340-0x8019E3E8 (168B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EE4;
s32 fn_80128E94(CStruct *, void *, void *, s32);
s32 GetChecksum(CStruct *, s32);
bool ScriptSetMenuPadMappings(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 hash1;
    s32 hash2;
    s32 hash3;
    s32 val;
    s32 i;
    s32 walker;

    s32 var_r0;

    fn_80128E94(pParams, 0, &sp8, 1);
    i = 0;
    hash1 = QB_INACTIVE;
    hash2 = QB_ACTIVE;
    hash3 = QB_USE_AS_FIRST;
    walker = lbl_80305EE4 + 0x64;
    do {
        val = GetChecksum(sp8, i);
        var_r0 = 0;
        if (val == hash1) {
        } else if (val == hash2) {
            var_r0 = 1;
        } else if (val == hash3) {
            var_r0 = 2;
        }
        *(s32 *)walker = var_r0;
        i++;
        walker += 0xC;
    } while (i <= 1);
    return true;
}
