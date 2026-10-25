// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80015B38-0x80015B94 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 CARDCheck(s32);                               

// BannerExists @ 0x80015B38
s32 BannerExists(Unk_C8FEE62D *arg0) {
    s32 temp_r3;
    s32 var_r3;

    if ((s32) arg0->unk0xC != 0) {
        temp_r3 = CARDCheck(arg0->unk0x18);
        if (temp_r3 == -5) {
            arg0->unk0x10 = 1;
        }
        var_r3 = 1;
        if (temp_r3 != 0) {
            goto block_4;
        }
    } else {
block_4:
        var_r3 = 0;
    }
    return var_r3;
}
