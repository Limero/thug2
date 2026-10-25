// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80230BC4-0x80230BEC (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80230BC4(void *arg0) {
    s32 var_ctr;
    void *var_r3;

    var_r3 = arg0;
    var_ctr = 0x12;
    do {
        if ((s32) ((Unk_FFAD6788 *)var_r3)->unk0xC0 != 0) {
            ((Unk_FFAD6788 *)var_r3)->unk0xBC = 0;
        }
        var_r3 += 0x28;
        var_ctr -= 1;
    } while (var_ctr != 0);
}
