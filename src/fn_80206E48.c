// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80206E48-0x80206E7C (52B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80206E48(void *arg0) {
    s32 var_ctr;
    void *var_r9;
    volatile s16 *q;

    q = (volatile s16 *)(char *)arg0;
    var_ctr = 0x64;
    var_r9 = arg0 + 0x50;
    do {
        *(s32 *)((char *)var_r9 - 0x10) = 0;
        *(s32 *)((char *)var_r9 - 0x4) = 0;
        ((CStruct *)var_r9)->unk0x0 = 0;
        var_r9 += 0x18;
        var_ctr -= 1;
    } while (var_ctr != 0);
    q[0x99E / 2] = 0;
    q[0x99C / 2] = 0;
}
