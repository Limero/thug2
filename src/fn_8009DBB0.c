// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009DBB0-0x8009DBF8 (72B). Byte-identical.
#include "types.h"
extern s32 lbl_80301A34;
s32 fn_8009DEA8(void);
bool fn_8009DBB0(s32 arg0) {
    if (fn_8009DEA8() != 0) {
        lbl_80301A34 = arg0;
        return true;
    }
    return false;
}
