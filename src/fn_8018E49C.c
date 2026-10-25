// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E49C-0x8018E514 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_8018E49C(Unk_C7387A53 *arg0) {
    s32 spC;
    s32 sp8;
    sp8 = 0;
    GetInteger((CStruct *)arg0->unk0x20, QB_NUMBER_COLLECTED, &sp8, 0);
    GetInteger((CStruct *)arg0->unk0x20, QB_NUMBER, &spC, 1);
    return sp8 >= spC;
}
