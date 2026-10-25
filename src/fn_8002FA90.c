// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002FA90-0x8002FB00 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80031CEC(Unk_132A52FF *, s32);
s32 fn_800CC2D4(void *);
void fn_8002F1C4(Unk_C7387A53 *);
void fn_8002F7D4(Unk_C101CE15 *);
void fn_8002F9C4(s32);
s32 fn_8002FA90(Unk_FFAD6788 *arg0, s32 arg1, s32 arg2) {
    fn_8002F7D4(arg0);
    fn_8002F9C4(arg0);
    fn_8002F1C4(arg0);
    if ((arg2 != 0) && (fn_800CC2D4(arg0->unk0x7C) != 0)) {
        return fn_80031CEC(arg0, arg1);
    }
    return 0;
}
