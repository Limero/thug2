// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005FA1C-0x8005FA80 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80293EAC;
extern f32 lbl_80293EB0;
extern f32 lbl_80293EB4;
extern f32 lbl_80293EB8;
void fn_8005FA1C(void *arg0, void *arg1) {
    f32 a;
    f32 b;
    f32 c;

    if (*(s32 *)((char *)arg1 + 8) > 0) {
        a = lbl_80293EAC;
        b = lbl_80293EB0;
        c = lbl_80293EB4;
        *(f32 *)((char *)arg0 + 0) = a;
        *(f32 *)((char *)arg0 + 8) = a;
        *(f32 *)((char *)arg0 + 0xC) = c;
        *(f32 *)((char *)arg0 + 4) = b;
    } else {
        a = lbl_80293EAC;
        b = lbl_80293EB0;
        c = lbl_80293EB8;
        *(f32 *)((char *)arg0 + 0) = a;
        *(f32 *)((char *)arg0 + 8) = a;
        *(f32 *)((char *)arg0 + 0xC) = c;
        *(f32 *)((char *)arg0 + 4) = b;
        __asm__ __volatile__("" ::: "memory");
    }
}
