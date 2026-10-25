// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019A3A4-0x8019A410 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_800092B0(Unk_9994C3F5 *, s32);
void fn_8019A3A4(s32 arg0, s32 arg1) {
    s32 end2;
    s32 var_r31;
    register s32 t __asm__("r0");
    register s32 a0 __asm__("r30");

    a0 = arg0;
    t = a0 + 0xC;
    if (t != 0) {
        var_r31 = a0 + 0x12C;
        if (t != var_r31) {
            end2 = t;
            do {
                var_r31 -= 0x24;
                fn_800092B0((void *)var_r31, 2);
            } while (end2 != var_r31);
        }
    }
    if (arg1 & 1) {
        Mem_Free((void *)a0);
    }
}
