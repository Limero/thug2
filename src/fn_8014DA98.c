// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014DA98-0x8014DB38 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_802FFE7C;
extern s32 fn_8000BB70(s32 arg0, s32 arg1);
extern s32 fn_8000C394(Unk_FFAD6788 * arg0);
extern s32 Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_8014DA98(void) {
    s32 temp_r30;
    s32 temp_r31;

    temp_r30 = lbl_802FFE7C;
    temp_r31 = fn_8000BB70(temp_r30, 0);
    if ((fn_8000C394(fn_8000BB70(temp_r30, 1)) != 0) && (fn_8000C394(temp_r31) != 0)) {
        Script_RunScript(QB_ENABLE_TWO_PLAYER_OPTION, 0, 0, 0, 0);
        return;
    }
    Script_RunScript(QB_DISABLE_TWO_PLAYER_OPTION, 0, 0, 0, 0);
}
