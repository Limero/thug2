// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801539C8-0x80153A20 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_8021FA48(Unk_26CD8A51 *, s32);

bool ScriptDisconnectFromInternet(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 ctx;

    ctx = lbl_80305F9C;
    sp8 = 0;
    GetChecksum_2(pParams, QB_CALLBACK, &sp8, 0);
    fn_8021FA48(ctx, sp8);
    return true;
}
