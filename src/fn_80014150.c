// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014150-0x80014248 (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    f32 f00;
    f32 f04;
    f64 f08;
    s32 f10[4];
    u64 f20;
    u64 f28;
    s32 f30;
} Unk_Timer;

extern Unk_Timer lbl_803142B8;
extern Unk_Timer lbl_803142F0;
extern u64 lbl_802FFF38;
extern volatile u64 lbl_802FFF58;

void fn_80014150(void) {
    s32 i;

    lbl_803142B8.f00 = 0.01666666f;
    lbl_803142B8.f04 = 1.0f / 60.0f;
    lbl_803142B8.f08 = 0.01666666f;
    for (i = 0; i < 4; i++) {
        lbl_803142B8.f10[i] = 1;
    }
    lbl_803142B8.f20 = 0;
    lbl_803142B8.f28 = 0;
    lbl_803142B8.f30 = 0;
    lbl_803142F0 = lbl_803142B8;
    lbl_802FFF58 = 0;
    lbl_802FFF38 = 0;
}
