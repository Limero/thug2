// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009951C-0x8009955C (64B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8009951C(Unk_1C4D340C *arg0) {
    u16 temp_r3;

    temp_r3 = arg0->unk0x5C;
    if ((s32) temp_r3 != 0) {
        arg0->unk0x58 = Mem_Alloc(temp_r3 * 4);
    }
}
