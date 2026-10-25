// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020B134-0x8020B190 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void AddChecksum(CStruct *, s32, s32);
bool fn_8020B134(Unk_CEAF6E85 *arg0, s32 arg1, CScript *arg2) {
    s32 temp_r0;

    temp_r0 = arg0->unk0x1C10;
    if (temp_r0 == 0) {
        AddChecksum(arg2->unk0x18, QB_CURRENT_BAIL_ENDPOSE, QB_NONE);
    } else {
        AddChecksum(arg2->unk0x18, QB_CURRENT_BAIL_ENDPOSE, temp_r0);
    }
    return true;
}
