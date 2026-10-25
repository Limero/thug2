// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F1624-0x800F164C (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800F1624(s32 arg0) {
    s32 var_ctr;
    void *var_r3;

    var_r3 = arg0 + 4;
    var_ctr = 0x4000;
    do {
        *(s16 *)((char *)var_r3 - 0x2) = 0;
        *((s16 *)&((Unk_5B449B03 *)var_r3)->unk0x0) = -1;
        var_r3 += 4;
        var_ctr -= 1;
    } while (var_ctr != 0);
}
