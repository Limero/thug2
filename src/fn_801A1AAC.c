// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A1AAC-0x801A1B2C (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "structs.h"
extern f32 lbl_802AB1B4;
extern f32 lbl_802AB1B8;
extern f32 lbl_802AB1BC;
extern void fn_8002DEAC(Unk_DB0E2BAB *, s32, f32, f32, f32, f32);
void fn_801A1AAC(Unk_C7387A53 *arg0, f32 *arg1, s32 arg2, s32 arg3) {
    *(s32 *)((char *)arg0 + 0x70) = (s32)arg1;
    if (arg3 == 0) {
        fn_8002DEAC((char *)arg0 + (s32)0x74, 0,
                    lbl_802AB1B4, *arg1,
                    lbl_802AB1B4, lbl_802AB1B8);
    } else {
        fn_8002DEAC((char *)arg0 + (s32)0x74, 0,
                    *arg1 - lbl_802AB1BC,
                    lbl_802AB1B4,
                    lbl_802AB1B4, lbl_802AB1B8);
    }
}
