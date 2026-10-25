// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80045170-0x80045218 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Unk_80045170_Sub {
    char pad0x0[0x3C];
    f32 f_0x3C;
} Unk_80045170_Sub;

typedef struct Unk_80045170 {
    char pad0x0[0xC];
    s32 flags;
    char pad0x10[0x78];
    Unk_80045170_Sub sub_0x88;
    char pad0xC8[0x8];
    Unk_80045170_Sub sub_0xD0;
    char pad0x110[0x88];
    void *unk_0x198;
} Unk_80045170;

extern f32 lbl_80292648;
extern f32 lbl_8029264C;
extern f32 lbl_80292650;
void fn_8005E910(void *o, f32 a0);

void fn_80045170(Unk_80045170 *arg0, s32 arg1, f32 farg0) {
    volatile double _dummy;
    f32 temp_f31;
    f32 t;
    Unk_80045170_Sub *temp_r11;
    Unk_80045170_Sub *temp_r30;

    t = farg0 * lbl_80292648;
    temp_f31 = t / lbl_8029264C;
    temp_f31 = temp_f31 + lbl_80292650;
    temp_r11 = &arg0->sub_0xD0;
    if (temp_r11->f_0x3C != temp_f31) {
        temp_r11->f_0x3C = temp_f31;
        arg0->flags |= 0x400;
    }
    if (arg1 != 0) {
        temp_r30 = &arg0->sub_0x88;
        if (temp_r30->f_0x3C != temp_f31) {
            fn_8005E910(arg0->unk_0x198, temp_f31);
            temp_r30->f_0x3C = temp_f31;
            arg0->flags |= 0x400;
        }
    }
}
