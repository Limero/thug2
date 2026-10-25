// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80172740-0x801727BC (124B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 fn_80172710(s32 entry);
void *fn_80172740(Unk_DB0E2BAB *arg0, s32 arg1) {
    s32 temp_r30;
    s32 temp_r3;
    s32 var_r30;
    s32 var_r31;

    temp_r30 = 1 << arg1;
    arg0->unk0x0 = arg1;
    var_r31 = temp_r30 - 1;
    temp_r3 = Mem_Alloc(temp_r30 * 0xC);
    var_r30 = temp_r3;
    if (temp_r30 != 0) {
        do {
            fn_80172710(var_r30);
            var_r30 += 0xC;
        } while (--var_r31 != -1);
    }
    arg0->unk0x4 = temp_r3;
    arg0->unk0x8 = 0;
    arg0->unk0x14 = 0;
    return arg0;
}
