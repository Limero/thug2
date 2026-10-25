// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003E81C-0x8003E89C (128B). Byte-identical.
#include "types.h"
typedef struct { s32 v[14]; } Big56;
extern Big56 lbl_803003F4;
extern Big56 lbl_803645E8;
void fn_8003E81C(s32 arg0, s32 arg1) {
    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        lbl_803645E8 = lbl_803003F4;
    }
}
