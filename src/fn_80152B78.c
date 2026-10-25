// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80152B78-0x80152C00 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 GetChecksum_4(CStruct *, void *, void *, void *);
s32 fn_801317C0(void *);
s32 fn_8013183C(void *);
extern char lbl_802A7D78[];
extern char lbl_802A7DA0[];
bool ScriptKillSpawnedScript(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r3;

    sp8 = 0;
    temp_r3 = GetChecksum_4(pParams, (s32)lbl_802A7DA0, &sp8, NULL);
    if (temp_r3 != 0) {
        fn_801317C0(sp8);
    } else {
        spC = temp_r3;
        if (GetChecksum_4(pParams, (s32)lbl_802A7D78, &spC, 0) != 0) {
            fn_8013183C(spC);
        }
    }
    return true;
}
