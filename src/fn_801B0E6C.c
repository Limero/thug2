// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0E6C-0x801B0EF8 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_801B0A04(Unk_C8FEE62D *, s32);
void fn_801B0E6C(CStruct *arg0, s32 arg1) {
    void *temp_r9;
    void *var_r31;

    temp_r9 = arg0->unk0xC;
    if (temp_r9 != NULL) {
        var_r31 = temp_r9 + (*(s32 *)((char *)temp_r9 - 0x8) << 5);
        if (temp_r9 != var_r31) {
            do {
                var_r31 -= 0x20;
                fn_801B0A04(var_r31, 0);
            } while ( arg0->unk0xC != var_r31);
        }
        Mem_Free2(arg0->unk0xC - 8);
    }
    Mem_Free(arg0->unk0x8);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
