// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800103C4-0x80010400 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800103C4(s32 arg0, s32 arg1) {
    s32 var_ctr;
    s32 var_r3;
    void *var_r9;

    var_r3 = arg0 + 0x204;
    var_ctr = 7;
    var_r9 = arg0 + 0x20C;
loop_1:
    if (((s32) ((CStruct *)var_r9)->unk0x84 == 0) || ((s32) ((CStruct *)var_r9)->unk0x0 != arg1)) {
        var_r3 += 0x90;
        var_r9 += 0x90;
        var_ctr -= 1;
        if (var_ctr == 0) {
            return 0;
        }
        goto loop_1;
    }
    return var_r3;
}
