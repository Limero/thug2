// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A7DDC-0x801A7E00 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801A7DDC(Unk_989596F9 *arg0) {
    s32 idx = arg0->unk0x630;
    u8 *p = (u8 *)((char *)arg0 + 0x5DC);

    p[idx] += 1;
    arg0->unk0x5EE += 1;
}
