// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006DFAC-0x8006E000 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80301430;
s32 fn_8006F324(s32);
s32 fn_8006F338(s32, s32);
void fn_8006DF8C(void);
s32 fn_8006DFAC(void) {
    s32 r;
    fn_8006F324(lbl_80301430);
    r = fn_8006F338(lbl_80301430, 0);
    while (r != 0) {
        fn_8006DF8C();
        r = fn_8006F338(lbl_80301430, 0);
    }
    return r;
}
