// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009A484-0x8009A4D8 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80297610[];
void fn_8009A658(void *);
void *fn_8009A484(char *arg0, s32 arg1, f32 farg0) {
    *(s32 *)(arg0 + 0x10) = (s32)lbl_80297610;
    *(f32 *)(arg0 + 0x8) = farg0;
    *(s32 *)(arg0 + 0x0) = 0;
    *(s32 *)(arg0 + 0x4) = arg1;
    if (arg1 == 0) {
        fn_8009A658(arg0);
    }
    return arg0;
}
