// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001F200-0x8001F250 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "types.h"
extern char lbl_80300278[];
void fn_8001F200(f32 arg0, f32 arg1) {
    volatile double _dummy;   /* issue-01: forces retail's +8 FPR frame */
    (*(void (**)(f32, f32))(s32)lbl_80300278)(arg0, arg1);
    (*(void (**)(f32))(s32)lbl_80300278)(arg1);
}
