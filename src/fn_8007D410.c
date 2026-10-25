// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007D410-0x8007D448 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8007D410(Unk_31DE137E *arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        arg0->unk0x1C = (s32) (arg0->unk0x1C | (2 << arg1));
        return;
    }
    arg0->unk0x1C = (s32) (arg0->unk0x1C & ~(2 << arg1));
}
