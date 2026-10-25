// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185554-0x801855A8 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void Script_RunScript(s32, s32, s32, s32, s32, s32, s32, s32);
void fn_80185554(Unk_C7387A53 *arg0) {
    s32 uninit;
    s32 temp_r11;
    s32 temp_r9;

    temp_r11 = arg0->unk0x44 + 1;
    temp_r9 = arg0->unk0x48 + 1;
    arg0->unk0x44 = temp_r11;
    arg0->unk0x48 = temp_r9;
    Script_RunScript(QB_GOALMANAGER_SHOWGOALPOINTS, 0, 0, 0, 0, uninit, temp_r9, arg0);
}
