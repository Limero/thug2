// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234F04-0x80234F2C (40B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
extern char lbl_80305FF8[];
bool ScriptIsCustomPark(CStruct *pParams, CScript *pScript) {
    if ((s32) *(s32 *)((s32 *)((char *)(*(void * *)&lbl_80305FF8) + (s32)0x44)) != -QB_UNKNOWN_0x2BBC5D44) {
        return true;
    }
    return false;
}
