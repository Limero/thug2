// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9498-0x801F9540 (168B). Byte-identical.
#include "types.h"
#include "structs.h"
extern const f32 lbl_802AE55C;
extern const f32 lbl_802AE560;
extern const f32 lbl_802AE564;
void fn_801F9498(Unk_99DF620B *arg0, Unk_2BAD2BE8 *arg1) {
    f32 temp_f12;
    u16 temp_r0;

    temp_r0 = arg0->unk0x1A;
    arg1->unk0x8 = temp_r0;
    temp_f12 = arg0->unk0x20;
    if (temp_f12 < lbl_802AE55C) {
        arg1->unk0x6 = 0;
    } else {
        arg1->unk0x6 = (u16)(s16)(temp_f12 * lbl_802AE560);
    }
    arg1->unk0x0 = (u16)(s16)(arg0->unk0x8 * lbl_802AE564);
    arg1->unk0x2 = (u16)(s16)(arg0->unk0xC * lbl_802AE564);
    arg1->unk0x4 = (u16)(s16)(arg0->unk0x10 * lbl_802AE564);
}
