// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009FC60-0x8009FCD8 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801291FC(void *);
void fn_8009FC60(Unk_9994C3F5 *arg0, CStruct *arg1, s32 arg2) {
    s32 *temp_r3;
    s32 *var_r31;
    s32 temp_r0;
    s32 temp_r4;
    s32 var_r30;
    Unk_89391A04 *temp_r9;

    temp_r3 = fn_801291FC(arg1);
    temp_r0 = arg1->unk0x4;
    if (temp_r0 > 0) {
        var_r31 = temp_r3;
        var_r30 = temp_r0;
        do {
            temp_r9 = arg0->unk0x8;
            temp_r4 = *((s32 *)var_r31);
            var_r31 = (s32 *)((char *)var_r31 + 4);
            ((s32 (*)(void *, void *, void *))temp_r9->unk0x54)((char *)arg0 + temp_r9->unk0x50, temp_r4, arg2);
            var_r30 -= 1;
        } while (var_r30 != 0);
    }
}
