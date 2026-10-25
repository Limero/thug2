// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80163DD8-0x80163E3C (100B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
s32 fn_80198F7C(void *);
extern char lbl_80305EC0[];
bool ScriptInSlapGame(CStruct *pParams, CScript *pScript) {
    if ((fn_80198F7C(*(s32 *)&lbl_80305EC0) == QB_NETSLAP) || (fn_80198F7C(*(s32 *)&lbl_80305EC0) == QB_SLAP)) {
        return true;
    }
    return false;
}
