// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C3B0-0x8015C3E0 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"

extern char lbl_80305EC0[];

void IsTrue(s32, void *);

void ScriptIsCareerMode(CStruct *pParams, CScript *pScript) {
    IsTrue(*(s32 *)&lbl_80305EC0, QB_IS_CAREER);
}
