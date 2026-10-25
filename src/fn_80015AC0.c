// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80015AC0-0x80015B38 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80015BDC(Unk_C8FEE62D *);
s32 CARDFormat(s32);
s32 fn_80015AC0(Unk_C8FEE62D *arg0) {
    s32 temp_r3;
    s32 var_r3;

    if ((s32) arg0->unk0xC != 0) {
        temp_r3 = CARDFormat(arg0->unk0x18);
        if (temp_r3 != 0) {
            if ((s32) arg0->unk0xC != 0) {
                arg0->unk0xC = 0;
            }
            fn_80015BDC(arg0);
            arg0->unk0x10 = 1;
        }
        var_r3 = 1;
        if (temp_r3 != 0) {
            goto block_6;
        }
    } else {
block_6:
        var_r3 = 0;
    }
    return var_r3;
}
