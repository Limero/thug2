// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A660C-0x800A665C (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Ident: ScriptPrintEventLog — QB-hash print command. Calls GetInteger (hash
// resolve, arg0 passthrough) into sp8=0x400 backing; emits the resolved value
// into the event log at lbl_80301A78, passing `resolve == 0` as a flag and the
// pending value sp8. Returns 1 (success). The `r == 0` is want's subfic/adde.
#include "types.h"
#include "structs.h"
extern char lbl_80301A78[];
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_800A5ADC(s32, s32, s32);

bool ScriptPrintEventLog(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 r;
    sp8 = 0x400;
    r = GetInteger(pParams, 0, &sp8, 0);
    fn_800A5ADC(*(s32 *)&lbl_80301A78, r == 0, sp8);
    return true;
}