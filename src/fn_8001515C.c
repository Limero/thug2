// range 0x8001515C-0x8001517C (0x20). Byte-identical.
// Identification: toggle-and-clear — flips the low bit of lbl_802FFF20
// (xori 1) and zeroes lbl_802FFF14. A pair of state/augment globals.
// Suggested rename: Fn_8001515C_ToggleFlagAndReset.
#include "types.h"
extern char lbl_802FFF20[];
extern char lbl_802FFF14[];
void fn_8001515C(void) {
    *(s32 *)lbl_802FFF20 ^= 1;
    *(s32 *)lbl_802FFF14 = 0;
}