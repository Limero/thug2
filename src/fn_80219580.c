// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80219580-0x802195B4 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Flag setter on a QB object: clears bits 2-3 of arg0->unk0x4, then sets
// bit 3 (|8) when arg1==1 (early return) or bit 2 (|4) when arg1==2.
// Suggested rename: SetModeFlags (1 -> 0x8, 2 -> 0x4)
#include "types.h"
#include "structs.h"
void fn_80219580(CStruct *arg0, s32 arg1) {
    s32 v = arg0->unk0x4 & 0xFFFFFFF3;
    arg0->unk0x4 = v;
    if (arg1 == 1) {
        arg0->unk0x4 = v | 8;
        return;
    }
    if (arg1 == 2) {
        arg0->unk0x4 = v | 4;
    }
}