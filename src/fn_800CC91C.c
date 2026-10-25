// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC91C-0x800CC9A8 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "types.h"
#include "qb_constants.h"

typedef struct S_800CC91C {
    char _pad04[0x04];
    s32 unk04;              /* QB_SOUND ("Sound") */
    char _pad08[0x10];
    s32 unk18;              /* (s32)lbl_80299658 */
    char _pad1C[0x84];
    f32 fA0;
    f32 fA4;
    f32 fA8;
    f32 fAC;
    f32 fB0;
    f32 fB4;
    f32 fB8;
    f32 fBC;
    s32 unkC0;
    s32 unkC4;
} S_800CC91C;

typedef struct S_800CC91C_A {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
} S_800CC91C_A;

extern f32 lbl_8029961C;
extern f32 lbl_80299620;
extern char lbl_80299658[];
void *fn_8009F53C(void *);

void *fn_800CC91C(S_800CC91C *arg0) {
    f32 temp_f0;
    f32 temp_f13;
    S_800CC91C_A *temp_r9;
    S_800CC91C_A *temp_r11;

    fn_8009F53C(arg0);
    arg0->unk18 = (s32)lbl_80299658;
    arg0->unk04 = QB_SOUND;
    temp_f13 = lbl_80299620;
    temp_f0 = lbl_8029961C;
    temp_r9 = (S_800CC91C_A *)((char *)arg0 + 0xA0);
    arg0->unkC0 = 0;
    temp_r11 = (S_800CC91C_A *)((char *)arg0 + 0xB0);
    arg0->unkC4 = 0;
    arg0->fA0 = temp_f0;
    temp_r9->f4 = temp_f0;
    temp_r9->f8 = temp_f0;
    temp_r9->fC = temp_f13;
    arg0->fB0 = temp_f0;
    temp_r11->f4 = temp_f0;
    temp_r11->f8 = temp_f0;
    temp_r11->fC = temp_f13;
    return arg0;
}
