// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80134B00-0x80134BB8 (184B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_80012224(s32 arg0, void *arg1);

void fn_80134B00(CStruct *arg0, s32 *arg1) {
    s32 temp_r0;
    u32 temp_r8;
    void *temp_r9;
    CStruct *var_r4;
    Unk_9994C3F5 *var_r10;

    temp_r8 = *((u32 *)&arg0->unk0x4);
    if (temp_r8 != 0) {
        var_r10 = NULL;
        var_r4 = (void *)((char *)temp_r8 + ((*arg1 & ((1 << arg0->unk0x0) - 1)) * 12));
        if (var_r4 != NULL) {
            do {
                temp_r9 = *((void * *)&var_r4->unk0x8);
                if ((var_r4->unk0x0 == *arg1) && (var_r4->unk0x4 != 0)) {
                    if (var_r10 != NULL) {
                        *((void * *)&var_r10->unk0x8) = temp_r9;
                        fn_80012224(0, var_r4);
                    } else {
                        var_r4->unk0x0 = 0;
                        var_r4->unk0x4 = 0;
                    }
                    arg0->unk0x8 = arg0->unk0x8 - 1;
                    return;
                }
                var_r10 = var_r4;
                var_r4 = temp_r9;
            } while (var_r4 != NULL);
        }
    }
}
