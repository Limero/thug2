// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80154490-0x801544DC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 *lbl_80305EAC;

s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
void fn_80199490(CStruct * arg0, s32 arg1);

bool ScriptGameFlow(CStruct *pParams, CScript *pScript) {
    s32 sp8 = 0;

    GetChecksum_2(pParams, 0, &sp8, 0);
    fn_80199490(((Unk_40426380 *)lbl_80305EAC)->unk0x398, sp8);
    return true;
}
