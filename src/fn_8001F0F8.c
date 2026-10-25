// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001F0F8-0x8001F164 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80300278[];
void fn_8001F0F8(s32 arg0, f64 dval, f32 farg1, f32 farg2) {
    volatile double _dummy1;
    volatile double _dummy2;

    ((void (*)(s32, f64))*(void (**)(s32, f64))lbl_80300278)(arg0, dval);
    ((void (*)(f32))*(void (**)(f32))lbl_80300278)(farg1);
    ((void (*)(f32))*(void (**)(f32))lbl_80300278)(farg2);
}
