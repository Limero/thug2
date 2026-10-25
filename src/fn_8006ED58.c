// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006ED58-0x8006EDD4 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8006ED28(void *);
void *fn_8006ED58(Unk_DB0E2BAB *arg0, s32 arg1) {
    u32 temp_r30;
    s32 temp_r3;
    char *var_r30;
    u32 var_r31;

    temp_r30 = 1 << arg1;
    arg0->unk0x0 = arg1;
    var_r31 = temp_r30 - 1;
    temp_r3 = Mem_Alloc(temp_r30 * 0xC);
    var_r30 = (char *)temp_r3;
    if (temp_r30 != 0) {
        do {
            fn_8006ED28(var_r30);
            var_r30 += 0xC;
        } while (var_r31-- != 0);
    }
    arg0->unk0x4 = temp_r3;
    arg0->unk0x8 = 0;
    arg0->unk0x14 = 0;
    return arg0;
}
