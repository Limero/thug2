// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80114388-0x80114408 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: ScriptGetCaptureAttribute (QB script command, 0x80 bytes,
// registered in the script-command registry as "GetCaptureAttribute").
// Wraps the registered command-name lookup + attribute fetch helpers
// (fn_8009DC9C / fn_8009DE3C).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8009DC9C(void *);
void fn_8009DE3C(s32, s32 *, s32 *);
void AddInteger(CStruct *, s32, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);

bool ScriptGetCaptureAttribute(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;

    if (GetChecksum_2(pParams, 0, &sp8, 0) != 0) {
        fn_8009DE3C(fn_8009DC9C(sp8), &spC, &sp10);
        AddInteger(pScript->unk0x18, QB_ARG0, spC);
        AddInteger(pScript->unk0x18, QB_ARG1, sp10);
    }
    return true;
}
