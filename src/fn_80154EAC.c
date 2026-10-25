// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80154EAC-0x80154F20 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
s32 fn_80137AD4(Unk_F386DC9F *);
extern char lbl_80303448[];
s32 ScriptNumPlayersAllowed(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r3;

    sp8 = 0;
    if ((fn_80137AD4(*(s32 *)&lbl_80303448) != 1) || (GetChecksum_2(pParams, 0, &sp8, 0), var_r3 = 0, ((sp8 == QB_NUM_4) == 0))) {
        var_r3 = 1;
    }
    return var_r3;
}
