// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015D258-0x8015D2C0 (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 GetInteger(CStruct * arg0, s32 hash, s32 * out, s32 flag);
extern s32 fn_801746A4(Unk_C7387A53 * obj, s32 idx);
extern s32 fn_80174AB8(void * obj, s32 idx);
extern s32 fn_80143258(s32 a, s32 b);
bool ScriptUpdateSkaterStats(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;

    GetInteger(pParams, QB_PLAYER, &sp8, 1);
    temp_r29 = fn_801746A4(*(s32 *)&lbl_80305EAC, sp8);
    fn_80143258(temp_r29, fn_80174AB8(*(s32 *)&lbl_80305EAC, sp8));
    return true;
}
