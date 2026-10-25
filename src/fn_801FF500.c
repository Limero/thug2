// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FF500-0x801FF54C (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802AEA54;
void fn_801FF500(Unk_C7387A53 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    f32 k = lbl_802AEA54;
    arg0->unk0x20 = 1;
    *((f32 *)&arg0->unk0x38) = farg0;
    *((f32 *)&arg0->unk0x34) = farg1;
    if (farg2 > k) {
        *((f32 *)&arg0->unk0x40) = ((farg0 - *((f32 *)&arg0->unk0x2C)) / farg2);
        *((f32 *)&arg0->unk0x3C) = ((farg1 - *((f32 *)&arg0->unk0x28)) / farg2);
    }
    *((f32 *)&arg0->unk0x44) = farg2;
    *((f32 *)&arg0->unk0x24) = farg3;
}
