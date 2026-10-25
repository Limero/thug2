// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CD118-0x801CD16C (84B). Byte-identical.
#include "types.h"
#include "structs.h"
void memset(void *, s32, s32);
void *fn_801CD118(CStruct *arg0) {
    s32 var_ctr;

    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0x68 = 0;
    arg0->unk0x6C = 0;
    memset(arg0, 0, 0x88);
    return arg0;
}
