// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023EE14-0x8023EEF4 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_ctor(void *);
void AddChecksum(CStruct *, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_8023EE14(Unk_C7387A53 *arg0) {
    volatile s32 sp8;
    s32 temp_r0;

    CStruct_ctor(&sp8);
    temp_r0 = arg0->unk0x74;
    if (temp_r0 == 3) {
        AddChecksum(&sp8, QB_MODE, QB_GAP_ADJUST);
    } else if (temp_r0 == 2) {
        AddChecksum(&sp8, QB_MODE, QB_GAP_REGULAR);
    } else if (temp_r0 == 6) {
        AddChecksum(&sp8, QB_MODE, QB_RAIL_PLACEMENT);
    } else {
        AddChecksum(&sp8, QB_MODE, QB_REGULAR);
    }
    Script_RunScript(QB_PARKED_SET_HELPER_TEXT_MODE, &sp8, 0, 0, 0);
    CStruct_delete(&sp8, 2);
}
