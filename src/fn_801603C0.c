// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801603C0-0x8016043C (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 lbl_8030191C;
extern char lbl_80305EAC[];

s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8009D374(void *, s32, s32);
void fn_80176D9C(void *);

bool ScriptBindControllerToSkater(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    void *skater;

    GetInteger(pParams, 0xB30D9965, &sp8, 1);
    GetInteger(pParams, 0xC52D1A41, &spC, 1);
    skater = *(void **)lbl_80305EAC;
    fn_8009D374(*(void **)&lbl_8030191C, spC, sp8);
    fn_80176D9C(skater);
    return true;
}
