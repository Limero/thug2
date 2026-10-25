// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80201C80-0x80201CCC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_802010FC(Unk_BC7B49A5 *);
void fn_80201C80(Unk_E0930646 *arg0, s32 arg1, s32 arg2) {
    if ((fn_802010FC(arg0) != 0) && (arg2 != (s32) arg0->unk0xA20)) {
        arg0->unk0xA1C = arg1;
    }
}
