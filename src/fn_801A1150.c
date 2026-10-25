// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A1150-0x801A11D0 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "structs.h"
extern f32 lbl_802AB17C;
extern f32 lbl_802AB180;
extern f32 lbl_802AB184;
extern void fn_8002DEAC(Unk_DB0E2BAB *, s32, f32, f32, f32, f32);
void fn_801A1150(Unk_C7387A53 *arg0, f32 *arg1, s32 arg2, s32 arg3) {
    arg0->unk0x3C = (s32)arg1;
    if (arg3 == 0) {
        fn_8002DEAC((char *)arg0 + (s32)0x40, 0,
                    lbl_802AB17C, *arg1,
                    lbl_802AB17C, lbl_802AB180);
    } else {
        fn_8002DEAC((char *)arg0 + (s32)0x40, 0,
                    *arg1 - lbl_802AB184,
                    lbl_802AB17C,
                    lbl_802AB17C, lbl_802AB180);
    }
}
