// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018B9D4-0x8018BA34 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
s32 fn_8018B6B8(void);
void fn_8018B9D4(Unk_C7387A53 *arg0, s32 arg1) {
    CStruct *temp_r3;
    s32 *temp_r9;

    temp_r9 = arg0->unk0x30;
    if ((s32) *((s32 *)temp_r9) == 0) {
        *((s32 *)temp_r9) = arg1;
        return;
    }
    Mem_Alloc2(0xC);
    temp_r3 = fn_8018B6B8();
    temp_r3->unk0x0 = arg1;
    temp_r3->unk0x4 = (s32 *) arg0->unk0x30;
    arg0->unk0x30 = temp_r3;
}
