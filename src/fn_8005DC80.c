// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005DC80-0x8005DCC4 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8036647C[];
void fn_8005DC80(s32 arg0, s32 arg1) {
    s32 var_ctr;
    void *var_r9;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        var_ctr = 4;
        var_r9 = (void *)lbl_8036647C;
        do {
            ((CStruct *)var_r9)->unk0x4 = 0;
            ((CStruct *)var_r9)->unk0x8 = 0;
            ((CStruct *)var_r9)->unk0xC = 0;
            var_r9 += 0x10;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
}
