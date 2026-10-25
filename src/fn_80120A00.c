// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80120A00-0x80120B44 (324B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad_00[0x20];
    s32 unk_20;
    char pad_24[0x1E8];
    void *unk_20C;
    s32 pad_210;
    s32 unk_214;
    s32 pad_218;
} Unk_8038F0C0;

extern Unk_8038F0C0 lbl_8038F0C0[3];
extern f32 lbl_8029D828;
extern f32 lbl_8029D82C;
extern s32 lbl_80302F20;
extern s32 lbl_80302F2C;
extern s32 lbl_8039DAD0;
extern void AXSetVoiceState(void *, s32);
extern void AUDSimplePause(s32);
extern void fn_8011F590(void *, void *, f32, f32, f32, s32, s32);

void fn_80120A00(s32 arg0, s32 arg1) {
    s32 i;
    s32 j;
    void *p;

    if (arg1 == 1) {
        lbl_80302F20 = arg0;
        if (lbl_8039DAD0 != 0) {
            AUDSimplePause(arg0);
        }
        return;
    }

    lbl_80302F2C = arg0;
    for (i = 0; i < 3; i++) {
        if (lbl_8038F0C0[i].unk_20C != 0) {
            if (arg0 != 0) {
                if (lbl_8038F0C0[i].unk_20 == 0) {
                    lbl_8038F0C0[i].unk_20 = 1;
                    AXSetVoiceState(lbl_8038F0C0[i].unk_20C, 0);
                }
            } else if (lbl_8038F0C0[i].unk_20 != 0) {
                lbl_8038F0C0[i].unk_20 = arg0;
                AXSetVoiceState(lbl_8038F0C0[i].unk_20C, 1);
            }
        }
    }

    if (arg0 == 0) {
        return;
    }

    for (j = 0; j < 3; j++) {
        lbl_8038F0C0[j].unk_214 = 1;
        p = lbl_8038F0C0[j].unk_20C;
        if (p != 0) {
            f32 f1v = lbl_8029D828;
            __asm__("" : "+f"(f1v));
            fn_8011F590((void *)((s32)p + 0x138), p, f1v, f1v, lbl_8029D82C, 0, 0);
        }
    }
}
