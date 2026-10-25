// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801414F0-0x80141570 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_8029F780;
extern f32 lbl_8029F784;
static s32 ScriptInSplitScreenGame(s32 arg0, s32 arg1);

// local layout of the receiver: the float array starts at +0x2BC
struct store_s {
    char pad[0x2BC];
    f32 arr[64];
};

void fn_801414F0(s32 arg0, s32 arg1, f32 farg0) {
    volatile double _dummy;
    f32 var_f31;
    struct store_s *sp;

    sp = (struct store_s *)arg0;
    var_f31 = farg0;
    if (ScriptInSplitScreenGame(0, 0) != 0) {
        if (var_f31 > lbl_8029F780) {
            var_f31 = lbl_8029F780;
        }
        if (var_f31 < lbl_8029F784) {
            var_f31 = lbl_8029F784;
        }
    }
    sp->arr[arg1] = var_f31;
}
