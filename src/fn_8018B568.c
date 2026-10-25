// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018B568-0x8018B608 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8018B568(CStruct *arg0, s32 *arg1) {
    CStruct *var_r3;
    Unk_9994C3F5 *var_r11;
    s32 var_r9;

    arg0->unk0x10 = 0;
    var_r3 = *((void * *)&arg0->unk0x8);
    var_r11 = NULL;
    if (var_r3 != NULL) {
        do {
            if (var_r3->unk0x0 == *arg1) {
                if (var_r11 != NULL) {
                    var_r11->unk0x8 = var_r3->unk0x8;
                } else {
                    arg0->unk0x8 = var_r3->unk0x8;
                }
                if (arg0->unk0xC == (s32)var_r3) {
                    arg0->unk0xC = (s32)var_r11;
                }
                Mem_Free(var_r3);
                var_r9 = arg0->unk0x4 - 1;
                arg0->unk0x4 = var_r9;
                return;
            }
            var_r11 = var_r3;
            var_r3 = *((void * *)&var_r3->unk0x8);
        } while (var_r3 != NULL);
    }
}
