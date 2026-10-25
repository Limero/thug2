// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80231000-0x8023104C (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80306000;
s32 fn_800145AC(void);
s32 fn_8023104C(Unk_C7387A53 *);
void fn_80231000(Unk_C7387A53 *arg0) {
    s32 temp_r28;
    s32 temp_r29;

    temp_r28 = arg0->unk0x20;
    temp_r29 = lbl_80306000;
    lbl_80306000 += fn_800145AC() - temp_r29;
    fn_8023104C(temp_r28);
}
