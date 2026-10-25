// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057D90-0x80057DE8 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_8005F1F0(s32);
void fn_80057D90(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 var_r0;
    Unk_897A0ACF *temp_r9;

    temp_r9 = arg0->unk0x14;
    if (temp_r9 != NULL) {
        if (arg1 != 0) {
            var_r0 = temp_r9->unk0x4 & QB_UNKNOWN_0xFFFFFFFB;
        } else {
            var_r0 = temp_r9->unk0x4 | 4;
        }
        temp_r9->unk0x4 = var_r0;
    }
    if ((s32) arg0->unk0x10 != 0) {
        fn_8005F1F0(arg0->unk0x10);
    }
}
