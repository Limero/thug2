// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D6740-0x800D67D0 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern const volatile f32 lbl_80299BA8;
typedef struct D6740 {
    char pad0x0[0x140];
    f32 a140[3];
    char pad0x14C[0x14];
    f32 a160[3];
    char pad0x16C[4];
    f32 a170[3];
    char pad0x17C[4];
    f32 a180[3];
    char pad0x18C[4];
    f32 a190[3];
} D6740;
void fn_800D6740(D6740 *arg0, s32 arg1) {
    arg0->a170[arg1] = fabs(arg0->a170[arg1]);
    arg0->a160[arg1] = fabs(arg0->a160[arg1]);
    arg0->a180[arg1] = fabs(arg0->a180[arg1]);
    arg0->a190[arg1] = fabs(arg0->a190[arg1]);
    if (arg0->a140[arg1] < lbl_80299BA8) {
        arg0->a170[arg1] = -arg0->a170[arg1];
        arg0->a160[arg1] = -arg0->a160[arg1];
        arg0->a180[arg1] = -arg0->a180[arg1];
        arg0->a190[arg1] = -arg0->a190[arg1];
    }
}
