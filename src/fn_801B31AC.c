// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B31AC-0x801B3220 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void Script_RunScript(s32, s32, s32, s32, s32);

void fn_801B31AC(Unk_C7387A53 *arg0) {
    s32 temp_r9;

    Script_RunScript(QB_PED_INITIALIZE_MOVEMENT, 0, arg0->unk0xC, 0, 0);
    temp_r9 = arg0->unk0x30;
    if ((temp_r9 == QB_GENERIC_MOVE_UPDATE) || (temp_r9 == -QB_UNKNOWN_0x59CE169C)) {
        arg0->unk0x24 = (s32) (arg0->unk0x24 | 2);
    }
}
