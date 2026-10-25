// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D68B8-0x800D69A0 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8009F204(void *, void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 fn_800F0F84(s32, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_8009F27C(CStruct *, s32, s32, s32, s32);
void fn_800D68B8(Unk_7020B801 *arg0, s32 arg1) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r3;
    s32 temp_r3_2;
    temp_r3 = fn_800F0F84(arg1, 0);
    arg0->unk0x200 = arg1;
    temp_r3_2 = GetChecksum_2((CStruct *)temp_r3, QB_SPAWNOBJSCRIPT, &sp8, 0);
    if (temp_r3_2 != 0) {
        spC = 0;
        GetStructure_2((CStruct *)temp_r3, QB_PARAMS, &spC, 0);
        fn_8009F27C((CStruct *)arg0->unk0xC, sp8, spC, 0, 0);
        return;
    }
    if (GetChecksum_2((CStruct *)temp_r3, QB_UNKNOWN_0x86125749, &sp8, 0) != 0) {
        sp10 = temp_r3_2;
        GetStructure_2((CStruct *)temp_r3, QB_PARAMS, &sp10, 0);
        fn_8009F204((void *)arg0->unk0xC, (void *)sp8, (void *)sp10);
    }
}
