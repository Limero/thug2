// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80114208-0x80114258 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
void fn_8009DABC(s32);
// ScriptStartupCaptureDevice @ 0x80114208
void ScriptStartupCaptureDevice(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetInteger(pParams, QB_ALLOC_BUFFER, &sp8, 0);
    fn_8009DABC(sp8 != 0);
}
