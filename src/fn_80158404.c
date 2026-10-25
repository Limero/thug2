// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80158404-0x801584BC (184B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EFC;
void fn_80126FF4(Unk_80577C09 *, CStruct *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_801A5C04(Unk_9994C3F5 *);
s32 fn_801A5C40(s32, s32);

bool ScriptGetSkaterProfileInfoByName(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 profs;
    s32 n;
    s32 node;
    s32 var_r30;

    var_r30 = 0;
    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    profs = lbl_80305EFC;
    n = fn_801A5C04(profs);
    while (var_r30 < n) {
        node = fn_801A5C40(profs, var_r30) + 0x6C;
        GetChecksum_2(node, QB_NAME, &spC, 1);
        if (spC == sp8) {
            fn_80126FF4(pScript->unk0x18, node);
            return true;
        }
        var_r30 += 1;
    }
    return false;
}
