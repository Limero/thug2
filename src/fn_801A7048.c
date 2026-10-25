// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A7048-0x801A7094 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_801A7048(Unk_93C2DF4D *arg0, s32 arg1, s32 arg2) {
    s32 temp_r8;
    s32 temp_r9;
    s32 temp_r10;
    s32 var_r5;
    void *temp_r6;
    void *temp_r7;

    var_r5 = arg2;
    if (var_r5 == -1) {
        var_r5 = arg0->unk0x630;
    }
    temp_r8 = (arg1 >> 5) * 4;
    temp_r6 = (char *)arg0 + 0x2A4;
    temp_r10 = temp_r8 + (var_r5 << 5);
    temp_r9 = ~(1 << (arg1 & 0x1F));
    temp_r7 = (char *)arg0 + 0x564;
    *(s32 *)((char *)temp_r6 + temp_r10) &= temp_r9;
    *(s32 *)((char *)temp_r7 + temp_r8) &= temp_r9;
}