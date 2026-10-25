// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009DABC-0x8009DB20 (100B). Byte-identical.
#include "types.h"
extern bool lbl_80301A10;
extern s32 lbl_80301A2C;
s32 fn_8009DE98(s32);
s32 fn_8009DABC(s32 arg0) {
    if (fn_8009DE98(0) != 0) {
        lbl_80301A10 = 1;
        if (arg0 != 0) {
            fn_8009DB74();
        } else {
            lbl_80301A2C = arg0;
        }
    }
    return lbl_80301A10;
}
