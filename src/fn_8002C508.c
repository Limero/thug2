// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002C508-0x8002C570 (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8002C508(Unk_C7387A53 *);
s32 GetStructure(void *, void *);
s32 fn_80125A3C(void *, void *);
s32 Script_RunScript(void *, void *, void *, void *, void *);
bool fn_8002C508(Unk_C7387A53 *arg0) {
    s32 temp_r4;
    fn_80125A3C(QB_MOVIECAM_DEBUG, 0);
    temp_r4 = GetStructure(arg0->unk0xC, 1);
    if (temp_r4 != 0) {
        Script_RunScript(QB_CREATEFROMSTRUCTURE, temp_r4, 0, 0, 0);
    }
    return true;
}
