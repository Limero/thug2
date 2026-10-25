// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B05B8-0x801B063C (132B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_801B01C0(CStruct *, s32);
void fn_801B05B8(Unk_9994C3F5 *arg0, s32 arg1) {
    void *temp_r9;
    void *var_r31;

    temp_r9 = arg0->unk0x8;
    if (temp_r9 != NULL) {
        var_r31 = temp_r9 + (*(s32 *)((char *)temp_r9 - 0x8) * 0x14);
        if (temp_r9 != var_r31) {
            do {
                var_r31 -= 0x14;
                fn_801B01C0(var_r31, 0);
            } while ( arg0->unk0x8 != var_r31);
        }
        Mem_Free2(arg0->unk0x8 - 8);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
