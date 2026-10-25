// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80206E24-0x80206E48 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80206E24(Unk_90685748 *arg0) {
    s32 *var_r3;
    s32 var_ctr;

    var_ctr = 0xA;
    arg0->unk0x1248 = 0;
    var_r3 = (char *)arg0 + 0x1270;
    do {
        *((s32 *)var_r3) = 0;
        var_r3 = (s32 *)((char *)var_r3 - 4);
        var_ctr -= 1;
    } while (var_ctr != 0);
}
