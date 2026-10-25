// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006E270-0x8006E2FC (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8006E000(s32, s32);
void fn_8006F324(s32);
float fn_800144C8(void);
s32 fn_8006F338(s32, s32);
extern f32 lbl_80294BDC;
extern s32 lbl_80300460;
extern s32 lbl_80301430;
s32 fn_8006E270(s32 arg0) {
    s32 temp;
    s32 r;

    if ((lbl_80300460 == 0) && (lbl_80301430 != 0)) {
        temp = (s32)(fn_800144C8() * lbl_80294BDC);
        fn_8006F324(lbl_80301430);
        while ((r = fn_8006F338(lbl_80301430, 0)) != 0) {
            fn_8006E000(r, temp);
        }
        __asm__("" : "+r"(r));
        return r;
    }
    return arg0;
}
