// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C58C-0x8009C5F0 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8009C58C(Unk_C7387A53 *arg0, f32 f1, f32 f2, f32 f3) {
    s32 i = 0;
    if (i < arg0->unk0x40) {
        s32 off = 0;
        do {
            *(f32 *)(off + arg0->unk0x28) += f1;
            *(f32 *)(off + arg0->unk0x28 + 4) += f2;
            *(f32 *)(off + arg0->unk0x28 + 8) += f3;
            i += 1;
            off += 0xC;
        } while (i < arg0->unk0x40);
    }
}
