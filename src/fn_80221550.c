// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221550-0x802215C4 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetInteger(s32 arg0, s32 arg1, void *arg2, s32 arg3);
extern void *fn_8021D358(s32 arg0, s32 arg1);
extern void fn_801276E8(s32 arg0, s32 arg1, s32 arg2);
extern char lbl_802AFE9C[];
extern s32 lbl_80305F9C;
bool ScriptGetPlayersTeam(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 temp_r29;
    void *var_r9;

    temp_r29 = lbl_80305F9C;
    GetInteger(arg0, QB_OBJID, &sp8, 0);
    var_r9 = fn_8021D358(temp_r29, ((Unk_B0EC4F37 *)&sp8)->unk0x2);
    if (var_r9 != NULL) {
        fn_801276E8(((CScript *)arg1)->unk0x18, (s32)lbl_802AFE9C,
                    ((Unk_C7387A53 *)var_r9)->unk0x34);
    }
    return true;
}
