// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C0A9C-0x801C0AE4 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// State init: sets arg0->unk0x20 = 1, marks a child object flag at
// unk0x7C4, and writes two float constants + 0 into the sub-object at
// arg0->unk0x9C (+0x24..0x2C).
// Suggested rename: InitSubObjectState
#include "types.h"
#include "structs.h"
extern f32 lbl_802AC608;
extern f32 lbl_802AC60C;
void fn_801C0A9C(Unk_DB0E2BAB *arg0) {
    arg0->unk0x20 = 1;
    ((Unk_298A0A9D *)arg0->unk0xAC)->unk0x7C4 = 1;
    {
        f32 temp_f0 = lbl_802AC608;
        f32 temp_f13 = lbl_802AC60C;
        *(f32 *)((char *)*((s32 * volatile *)&arg0->unk0x9C) + 0x2C) = temp_f0;
        *(f32 *)((char *)*((s32 * volatile *)&arg0->unk0x9C) + 0x28) = temp_f0;
        *(f32 *)((char *)*((s32 * volatile *)&arg0->unk0x9C) + 0x24) = temp_f13;
        *(s32 *)((char *)*((s32 * volatile *)&arg0->unk0x9C) + 0x1C) = 0;
    }
}
