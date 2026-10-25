// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005B8D4-0x8005B924 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_803CAF58;
extern f32 lbl_80293664;
void fn_8007DD50(void);
void fn_8007DCD8(f32);
void fn_8005B8D4(f32 farg0) {
    volatile double _dummy;
    if (!(farg0 <= lbl_80293664)) {
        lbl_803CAF58 = farg0;
        fn_8007DD50();
        fn_8007DCD8(farg0);
    }
}
