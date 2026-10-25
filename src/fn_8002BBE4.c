// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002BBE4-0x8002BC78 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_80125A3C(void *, s32);
bool fn_8002BBE4(Unk_C7387A53 *arg0, Unk_9994C3F5 *arg1) {
    s32 temp_r9;
    s32 var_r0;

    fn_80125A3C(QB_MOVIECAM_DEBUG, 0);
    temp_r9 = arg0->unk0xC;
    if (temp_r9 == QB_UNKNOWN_0x4E917BDA) {
        var_r0 = QB_CUTKEY_BO_LEVELEVENT_580_SAFE;
        goto block_4;
    }
    if (temp_r9 == QB_UNKNOWN_0x208D7A0D) {
        var_r0 = QB_CUTKEY_BO_LEVELEVENT_591_SAFE;
block_4:
        arg0->unk0xC = var_r0;
    }
    Script_RunScript(arg0->unk0xC, 0, arg1, 0, 0);
    return true;
}
