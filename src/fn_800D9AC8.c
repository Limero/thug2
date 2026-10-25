// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D9AC8-0x800D9B38 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800D9960(CScript *, s32);
void fn_800D9AC8(Unk_31DE137E *arg0) {
    s32 i;
    for (i = 0; i <= 2; i++) {
        if ((arg0->unk0x1C >> i) & 1) {
            if (fn_800D9960(arg0, i) != 0) {
                arg0->unk0x1C &= ~(1 << i);
            }
        }
    }
}
