// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021D3F8-0x8021D454 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800145AC(void);
extern void fn_8013DEE0(Unk_440CB216 *, s32, s32, void *, s32, s32, s32);
void fn_8021D3F8(Unk_C7387A53 *arg0) {
    s32 sp8;

    if ((s32) arg0->unk0x24 != 0) {
        sp8 = fn_800145AC();
        fn_8013DEE0(arg0->unk0x24, 0x11, 4, &sp8, -1, 0x141E, 0);
    }
}
