// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058C38-0x80058CC8 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80058750(void *, s32);
void fn_80058C38(CStruct *arg0) {
    void *temp_r9;
    void *var_r31;

    if ((s32) arg0->unk0x8 != 0) {
        Mem_Free(arg0->unk0x8);
        arg0->unk0x8 = 0;
    }
    temp_r9 = arg0->unk0x4;
    if (temp_r9 != NULL) {
        var_r31 = temp_r9 + (*(s32 *)((char *)temp_r9 - 0x8) * 0xA);
        if (temp_r9 != var_r31) {
            do {
                var_r31 -= 0xA;
                fn_80058750(var_r31, 0);
            } while ( arg0->unk0x4 != var_r31);
        }
        Mem_Free2(arg0->unk0x4 - 8);
        arg0->unk0x4 = NULL;
    }
}
