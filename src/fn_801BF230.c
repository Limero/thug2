// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BF230-0x801BF2AC (124B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802AC4FC;
extern f32 lbl_802AC500;
void fn_801BF230(Unk_FFAD6788 *arg0) {
    f32 temp_f11;
    f32 temp_f0;

    temp_f11 = *((f32 *)&arg0->unk0xD4);
    if (temp_f11 > lbl_802AC4FC) {
        *((f32 *)&arg0->unk0xD4) = temp_f11 - lbl_802AC500;
        *((f32 *)&arg0->unk0xD0) = *((f32 *)&arg0->unk0xD0) + *((f32 *)&arg0->unk0xD8);
    } else {
        *((f32 *)&arg0->unk0xD4) = lbl_802AC4FC;
    }
    temp_f0 = *((f32 *)&arg0->unk0xE0);
    if (temp_f0 > lbl_802AC4FC) {
        *((f32 *)&arg0->unk0xE0) = temp_f0 - lbl_802AC500;
        *((f32 *)&arg0->unk0xDC) = *((f32 *)&arg0->unk0xDC) + *((f32 *)&arg0->unk0xE4);
    } else {
        *((f32 *)&arg0->unk0xE0) = lbl_802AC4FC;
    }
}
