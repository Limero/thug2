// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80032F18-0x80032FB4 (156B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80032F18(CStruct *arg0) {
    void *temp_r11;
    Unk_F5317C5D *temp_r9;
    void *var_r31;

    if ((s32) arg0->unk0x70 != 0) {
        temp_r11 = arg0->unk0x6C;
        if (temp_r11 != NULL) {
            arg0->unk0x70 = 0;
            var_r31 = temp_r11 + (*(s32 *)((char *)temp_r11 - 0x8) * 0x14);
            if (temp_r11 != var_r31) {
                do {
                    var_r31 -= 0x14;
                    temp_r9 = ((Unk_9994C3F5 *)var_r31)->unk0x8;
                    ((s32 (*)(void *, s32))temp_r9->unk0xC)(var_r31 + temp_r9->unk0x8, 0);
                } while ( arg0->unk0x6C != var_r31);
            }
            Mem_Free2(arg0->unk0x6C - 8);
            arg0->unk0x6C = NULL;
        }
    }
}
