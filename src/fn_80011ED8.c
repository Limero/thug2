// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80011ED8-0x80011EFC (36B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80011ED8(Unk_C7387A53 *arg0) {
    s32 *temp_r9;

    temp_r9 = arg0->unk0x3C;
    *((s32 *)temp_r9) = arg0->unk0x84;
    arg0->unk0x84 = temp_r9;
    arg0->unk0x3C = (s32 *)(temp_r9 + arg0->unk0x38);
}
