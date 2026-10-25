// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023DDA8-0x8023DDCC (36B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8023DDA8(Unk_31DE137E *arg0) {
    s32 var_r3;
    Unk_C8FEE62D *temp_r9;

    var_r3 = 0;
    temp_r9 = *((void * *)&arg0->unk0x60);
    while (temp_r9 != NULL) {
        temp_r9 = *((void * *)&temp_r9->unk0x14);
        var_r3 += 1;
    }
    return var_r3;
}
