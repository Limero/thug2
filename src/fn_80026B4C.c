// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80026B4C-0x80026BEC (160B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void Mem_Free_3(void *);
void fn_80026B4C(Unk_57FB3CEB *arg0, s32 arg1) {
    s32 var_r29;
    s32 var_r30;
    void *temp_r11;
    Unk_F5317C5D *temp_r9;

    var_r30 = 0;
    if (var_r30 < (s16) arg0->unk0x38) {
        var_r29 = 0;
        do {
            temp_r11 = *(void **)(var_r29 + arg0->unk0x28);
            if (temp_r11 != NULL) {
                temp_r9 = ((Unk_9994C3F5 *)temp_r11)->unk0x8;
                ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + (s16)temp_r9->unk0x8, 3);
            }
            var_r30 += 1;
            var_r29 += 4;
        } while (var_r30 < (s16) arg0->unk0x38);
    }
    if ((s32) arg0->unk0x28 != 0) {
        Mem_Free_3(arg0->unk0x28);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
