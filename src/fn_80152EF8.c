// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80152EF8-0x80152F48 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddChecksum(CStruct *, void *, void *);
extern s32 lbl_80300460;
s32 ScriptGameIsPaused(CStruct *pParams, CScript *pScript) {
    s32 var_r3;

    var_r3 = 0;
    if (lbl_80300460 != 0) {
        AddChecksum(pParams, QB_GAME_IS_PAUSED, QB_GAME_IS_PAUSED);
        var_r3 = 1;
    }
    return var_r3;
}
