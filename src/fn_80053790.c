// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80053790-0x800537D8 (72B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_80364BF8[];
s32 fn_80053BB0(s32, s32, s32);
s32 fn_80053790(s32 arg0) {
    s32 sp8;
    CScript *temp_r3;

    sp8 = arg0;
    temp_r3 = fn_80053BB0((s32)lbl_80364BF8, &sp8, 1);
    if (temp_r3 != NULL) {
        return temp_r3->unk0x18;
    }
    return 0;
}
