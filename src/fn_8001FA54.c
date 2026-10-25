// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001FA54-0x8001FAA4 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern char lbl_80300280[];
void fn_8001FA54(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;

    temp_r7 = arg4 << 8;
    temp_r6 = arg3 << 0x13;
    temp_r5 = arg2 << 0x16;
    temp_r4 = arg1 | temp_r7 | (arg0 << 0x10) | temp_r6 | temp_r5;
    (*(void (**)(s32))lbl_80300280)(temp_r4 | QB_UNKNOWN_0xF3000000);
}
