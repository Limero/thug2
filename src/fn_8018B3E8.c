// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018B3E8-0x8018B46C (132B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void *fn_8018B3D4(CStruct *);
bool fn_8018B3E8(CStruct *arg0, s32 *arg1, s32 arg2) {
    CStruct *temp_r3;
    s32 var_r9;

    temp_r3 = fn_8018B3D4(Mem_Alloc2(0xC));
    temp_r3->unk0x4 = arg2;
    temp_r3->unk0x0 = *arg1;
    if (arg0->unk0x8 == NULL) {
        arg0->unk0x8 = (s32)temp_r3;
    } else {
        *(s32 *)(arg0->unk0xC + (s32)0x8) = (s32)temp_r3;
    }
    var_r9 = arg0->unk0x4;
    arg0->unk0x10 = 0;
    arg0->unk0xC = (s32)temp_r3;
    arg0->unk0x4 = var_r9 + 1;
    return true;
}
