// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026E5B8-0x8026E5DC (36B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
// Thin wrapper: forwards the r13-addressed global lbl_803CA420 to
// fn_8026E5AC. Suggested rename: Call8026E5AC_WithGlobal (unnamed global)
#include "types.h"
extern s32 lbl_803CA420;
void fn_8026E5AC(s32);
void fn_8026E5B8(void) {
    fn_8026E5AC(lbl_803CA420);
}
