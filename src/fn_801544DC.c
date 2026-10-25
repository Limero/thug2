// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801544DC-0x80154524 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305DE8;

s32 fn_80128E34(CStruct * arg0, void * arg1, void *arg2, s32 arg3);

bool ScriptLastBroadcastedOmnigonWas(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    fn_80128E34(pParams, QB_CHEAT_FLAG, &sp8, 1);
    return lbl_80305DE8 == sp8;
}
