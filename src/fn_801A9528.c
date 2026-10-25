// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A9528-0x801A9584 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_801A94E8(CStruct *);
void fn_801A9B1C(CStruct *);
void fn_801A9C1C(CStruct *, void *, s32);

// ID: sub-object reset — installs the fn_801A94E8 vtable-dispatch callback
// (state machine method, or.-null-guard + blrl tail) into arg0+8 via
// fn_801A9C1C, runs fn_801A9B1C on it, zeroes arg0->0x4, runs fn_801A9B1C
// on arg0+0x20. Suggested rename: SkaterState_SubReset.
bool fn_801A9528(CStruct *arg0) {
    CStruct *temp_r30;

    temp_r30 = (CStruct *)((char *)arg0 + 8);
    fn_801A9C1C(temp_r30, fn_801A94E8, 0);
    fn_801A9B1C(temp_r30);
    arg0->unk0x4 = 0;
    fn_801A9B1C((CStruct *)((char *)arg0 + 0x20));
    return true;
}
