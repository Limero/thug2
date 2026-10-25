// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80059F8C-0x8005A00C (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0[0x14];
    f32 unk0x14;
    s32 unk0x18;
} A80059F8C;

typedef struct {
    char pad0[0x1C];
    f32 unk0x1C;
    f32 unk0x20;
} N80059F8C;

extern void *fn_80059BB8(s32);
extern f32 lbl_802934C8;
extern f32 lbl_802934CC;
extern f32 lbl_802934D0;

void fn_80059F8C(A80059F8C *arg0, f32 farg0) {
    void **temp_r3;
    N80059F8C *temp_r3_2;
    f32 var_f0;
    volatile double _dummy;

    if (farg0 != arg0->unk0x14) {
        arg0->unk0x14 = farg0;
        temp_r3 = fn_80059BB8(arg0->unk0x18);
        if (temp_r3 != NULL) {
            temp_r3_2 = (N80059F8C *)*(s32 *)temp_r3;
            temp_r3_2->unk0x1C = farg0;
            if (farg0 != *(volatile f32 *)&lbl_802934C8) {
                var_f0 = lbl_802934CC / farg0;
            } else {
                var_f0 = lbl_802934D0;
            }
            temp_r3_2->unk0x20 = var_f0;
        }
    }
}
