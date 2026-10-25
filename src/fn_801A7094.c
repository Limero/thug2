// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A7094-0x801A70D8 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_801A7094(Unk_93C2DF4D *arg0, s32 arg1, s32 arg2)
{
    s32 temp_r9;
    s32 var_r5;
    s32 val;
    s32 mask;
    void *temp_r11;

    var_r5 = arg2;
    if (var_r5 == -1) {
        var_r5 = arg0->unk0x630;
    }
    temp_r11 = (char *)arg0 + 0x2A4;
    temp_r9 = ((arg1 >> 5) * 4) + (var_r5 << 5);
    val = *(s32 *)((char *)temp_r11 + temp_r9);
    mask = 1 << (arg1 & 0x1F);
    return (val & mask) != 0;
}
