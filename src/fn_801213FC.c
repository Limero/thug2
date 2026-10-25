// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801213FC-0x80121448 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80302F28;
extern u8 lbl_8039B8D0;
void fn_80120664(void);
bool fn_801213FC(void) {
    s32 v;
    v = (s32) (s8) lbl_8039B8D0;
    if (v > 0) {
        lbl_80302F28 = 0;
        fn_80120664();
        return true;
    }
    return false;
}
