// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800422E8-0x8004238C (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct TextFlags422E8 {
    signed char b0;
    signed char b1;
    signed char b2;
    signed char b3;
} TextFlags422E8;

typedef struct TextObj422E8 {
    char pad0[8];
    s32 vtable;
    char padC[0x184];
    s32 f190;
    s32 f194;
    s32 f198;
    char pad19C[0xC];
    s32 f1A8;
    s32 f1AC;
    char pad1B0[8];
    TextFlags422E8 flags;
    s32 f1BC;
    s32 f1C0;
    char pad1C4[4];
    f32 f1C8;
    f32 f1CC;
} TextObj422E8;

void *fn_8003F360(void *);
void fn_80043800(void *, s32, s32);
void fn_8009E274(void *, s32);
extern char lbl_80292598[];
extern f32 lbl_8029249C;

void *fn_800422E8(TextObj422E8 *arg0) {
    f32 temp_f0;
    TextFlags422E8 *temp_r11;
    s32 zero;

    zero = 0;
    fn_8003F360(arg0);
    temp_r11 = (TextFlags422E8 *)((char *)arg0 + 0x1B8);
    arg0->flags.b0 = (s8)zero;
    arg0->vtable = (s32)lbl_80292598;
    temp_r11->b2 = (s8)zero;
    temp_r11->b3 = -128;
    temp_r11->b1 = (s8)zero;
    arg0->f194 = zero;
    arg0->f198 = zero;
    arg0->f190 = zero;
    arg0->f1A8 = zero;
    arg0->f1AC = zero;
    fn_80043800(arg0, 1, 0);
    arg0->f1C0 = zero;
    temp_f0 = lbl_8029249C;
    arg0->f1BC = zero;
    arg0->f1C8 = temp_f0;
    arg0->f1CC = temp_f0;
    fn_8009E274(arg0, QB_TEXTELEMENT);
    return arg0;
}
