// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010198C-0x801019C4 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: table-entry field reader. Resolves a table object via
// arg0+0x8, then indexes its entry array (stride 0xA or 8 depending on the
// +0xA flag) by arg1 and returns the u16 field at +2. Likely a script
// property/table accessor (game-db / object-def table).
#include "types.h"
#include "structs.h"
u16 fn_8010198C(Unk_9994C3F5 *arg0, s32 arg1) {
    Unk_6E48A312 *temp_r11;
    
    temp_r11 = arg0->unk0x8;
    if ((s32) temp_r11->unk0xA == 0) {
        return *(u16 *)((char *)((arg1 * 0xA) + temp_r11->unk0xC) + 0x2);
    }
    return *(u16 *)((char *)((arg1 * 8) + temp_r11->unk0xC) + 0x2);
}
