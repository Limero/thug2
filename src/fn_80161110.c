// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80161110-0x80161158 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8009F498(void *);

bool ScriptCompositeObjectExists(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    return fn_8009F498(sp8) != 0;
}
