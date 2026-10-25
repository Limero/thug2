// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80043AD0-0x80043B28 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8003F608(Unk_E2A1CCEB *, s32);
void fn_80050188(void *, s32);
extern char lbl_80292530[];
void fn_80043AD0(Unk_CC6723F9 *arg0, s32 arg1) {
    s32 v;
    arg0->unk0x8 = (s32)lbl_80292530;
    v = arg0->unk0x1C4;
    if (v != 0) {
        fn_80050188(v, 3);
    }
    fn_8003F608(arg0, arg1);
}
