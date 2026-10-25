// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009A898-0x8009A8CC (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GX_SetScissor(s32, s32, s32, s32);
void fn_8009A898(Unk_C7387A53 *arg0) {
    Unk_5B449B03 *temp_r9;

    temp_r9 = (Unk_5B449B03 *) arg0->unk0xC;
    GX_SetScissor(temp_r9->unk0x0, temp_r9->unk0x2, temp_r9->unk0x4, temp_r9->unk0x6);
}
