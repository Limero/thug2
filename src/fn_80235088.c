// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80235088-0x802350D0 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_802403A0(s32);
extern char lbl_802B0A3C[];
// ScriptExitParkEdTestPlay @ 0x80235088
bool ScriptExitParkEdTestPlay(CStruct *pParams, CScript *pScript) {
    Script_RunScript(QB_PARKED_TESTPLAY_CLEANUP, 0, 0, 0, 0);
    fn_802403A0(lbl_802B0A3C);
    return true;
}
