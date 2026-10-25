// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D4D8-0x8002D548 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8002CDE4(s32);
void fn_8002D4D8(Unk_FFAD6788 *arg0, s32 arg1) {
    s32 var_r29;
    void **var_r31;

    var_r31 = (char *)arg0 + 4;
    var_r29 = 0x32;
    do {
        if ((s32) *(s32 *)((char *)(*((s32 *)var_r31)) + (s32)0x4) == arg1) {
            arg0->unk0xCC = (s32) (arg0->unk0xCC - 1);
            arg0->unk0xD0 = (s32) (arg0->unk0xD0 - fn_8002CDE4(*((s32 *)var_r31)));
        }
        var_r31 = (void **)((char *)var_r31 + 4);
        var_r29 -= 1;
    } while (var_r29 != 0);
}
