// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023DDFC-0x8023DE20 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8023DDFC(Unk_31DE137E *arg0, s32 arg1) {
    register s32 var_r9 __asm__("r9");
    register void *var_r3 __asm__("r3");

    var_r9 = 0;
    __asm__ volatile("");
    var_r3 = *((void * *)&arg0->unk0x60);
loop_1:
    if ((var_r9 < arg1) && (var_r3 != NULL)) {
        var_r3 = *((void * *)&((Unk_C8FEE62D *)var_r3)->unk0x14);
        var_r9 += 1;
        goto loop_1;
    }
}
