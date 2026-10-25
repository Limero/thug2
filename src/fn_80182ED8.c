// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80182ED8-0x80182F54 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 Mem_Alloc_3(s32);
void *fn_80182ED8(CStruct *arg0, s32 arg1, s32 arg2) {
    s32 var_r10;
    s32 var_r11;
    s32 val;

    arg0->unk0x10 = arg2;
    arg0->unk0x8 = arg1;
    arg0->unk0x4 = Mem_Alloc_3(arg1 * 4);
    var_r11 = 0;
    if (var_r11 < arg0->unk0x8) {
        val = 0;
        var_r10 = 0;
        do {
            var_r11 += 1;
            *(s32 *)((char *)(var_r10 + arg0->unk0x4)) = val;
            var_r10 += 4;
        } while (var_r11 < arg0->unk0x8);
    }
    arg0->unk0xC = 0;
    return arg0;
}
