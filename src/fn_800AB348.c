// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AB348-0x800AB3A8 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddInteger(s32, s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_800AB348(Unk_C7387A53 *arg0) {
    s32 temp_r30;
    temp_r30 = CStruct_ctor(CStruct_new(8));
    AddInteger(temp_r30, QB_SKIPPABLE, arg0->unk0x20);
    AddInteger(temp_r30, QB_ALLOW_PAUSE, arg0->unk0x2C);
    return temp_r30;
}
