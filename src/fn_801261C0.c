// Promoted from src/wip (m2c draft hand-refined to exact match via promoted sibling fn_801FC44C idiom).
// range 0x801261C0-0x80126230 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80303264[];
extern bool lbl_8030326C[];
extern s32 lbl_80303274;
extern void fn_80012098(s32 arg0, s32 arg1);
void fn_801261C0(void) {
    s32 v = lbl_80303264[lbl_80303274];
    if (v != 0) {
        if (lbl_8030326C[lbl_80303274] != 0) {
            fn_80012098(v, 3);
        }
        lbl_80303264[lbl_80303274] = 0;
    }
}
