// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009A524-0x8009A574 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8009A6C0(void *);
void fn_8009A658(void *);
void fn_8009A524(char *arg0, f32 farg0) {
    if (*(f32 *)(arg0 + 0x8) != farg0) {
        s32 t = *(s32 *)(arg0 + 0x4);
        *(f32 *)(arg0 + 0x8) = farg0;
        if (t == 0) {
            fn_8009A6C0(arg0);
            fn_8009A658(arg0);
        }
    }
}
