// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013DFE4-0x8013E034 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_8013B538(void *, u8 *, u16 *, void *, s32 *);
bool fn_8013DFE4(Unk_2D712DCE *arg0, void *arg1, void *arg2) {
    s32 sp8;
    s32 temp_r9;

    if ((s32) arg0->unk0x182C == 0) {
        return false;
    }
    temp_r9 = arg0->unk0x2274 & 0x20;
    if (temp_r9 != 0) {
        fn_8013B538(arg0, arg1, (char *)arg0 + 0x184C, arg2, &sp8);
    }
    return true;
}

