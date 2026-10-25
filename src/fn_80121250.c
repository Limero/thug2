// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80121250-0x80121314 (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8038F0C0[];
extern s32 lbl_80302F2C;
extern s32 lbl_8039B8C0[];
extern void AXSetVoiceState(s32, s32);
extern void fn_80120F20(s32, f32, f32);
extern s32 fn_801210B4(f32, s32);
bool fn_80121250(s32 arg0, f32 farg0, f32 farg1, f32 farg2) {
    volatile double _dummy;
    volatile double _dummy1;
    volatile double _dummy2;
    s32 temp_r10;
    s32 v;
    char *base;
    char *p1;
    char *p2;

    base = lbl_8038F0C0;
    temp_r10 = arg0 * 0x21C;
    p1 = base + 0x20C;
    lbl_8039B8C0[arg0] = 0;
    v = *(s32 *)(p1 + temp_r10);
    if (v != 0) {
        p2 = base + 0x218;
        *(s32 *)(p2 + temp_r10) = 0;
        if (lbl_80302F2C == 0) {
            AXSetVoiceState(v, 1);
        }
        fn_80120F20(arg0, farg0, farg1);
        fn_801210B4(farg2, arg0);
        return true;
    }
    return false;
}
