// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005B5FC-0x8005B65C (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct S5B5FC {
    char pad0[4];
    f32 unk4;
    f32 unk8;
} S5B5FC;
void fn_8005B68C(S5B5FC *);
bool fn_8005B5FC(S5B5FC *arg0, f32 farg0, f32 farg1) {
    f32 temp_f0;

    arg0->unk8 = farg0;
    temp_f0 = arg0->unk4;
    if (temp_f0 < farg0) {
        temp_f0 = temp_f0 + farg1;
        arg0->unk4 = temp_f0;
        if (temp_f0 > farg0) {
            arg0->unk4 = farg0;
        }
    } else if (temp_f0 > farg0) {
        temp_f0 = temp_f0 - farg1;
        arg0->unk4 = temp_f0;
        if (temp_f0 < farg0) {
            arg0->unk4 = farg0;
        }
    }
    fn_8005B68C(arg0);
    return true;
}
