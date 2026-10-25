// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014004-0x80014070 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80013F94(void *, s32);
s32 fn_80014004(CStruct *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r11;
    void *var_r9;

    var_r11 = 0;
    if (var_r11 < (s32) arg0->unk0x10) {
        var_r9 = (char *)arg0 + 0x24;
        do {
            if (((s32) *(s32 *)((char *)var_r9 - 0x4) == arg1) && ((s32) ((CStruct *)var_r9)->unk0x0 == arg2)) {
                return fn_80013F94(arg0, var_r11);
            }
            var_r11 += 1;
            var_r9 += 0x10;
        } while (var_r11 < (s32) arg0->unk0x10);
    }
    return 0;
}
