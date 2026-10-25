// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D3A4-0x8002D418 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8002D3A4(Unk_FFAD6788 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_r0;
    s32 var_r3;
    u32 temp_r9;

    switch (arg4) {                                 
    case 2:
        var_r3 = 8;
        var_r0 = 8;
        break;
    case 3:
        var_r3 = 0x10;
        var_r0 = 0x10;
        break;
    case 4:
        var_r3 = 0x14;
        var_r0 = 0x10;
        break;
    default:
        var_r3 = 0;
        var_r0 = 0;
        break;
    }
    temp_r9 = arg0->unk0xD4;
    return (((u32) ((arg2 * var_r3) + (arg3 * var_r0)) / temp_r9) + 1) * temp_r9;
}
