// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80130C6C-0x80130CB8 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Timer setter: unk0x9C = 0, unk0xA4 = 2, and unk0xA0 = arg1 / lbl_8029E768.
// Suggested rename: SetTimerDuration
#include "types.h"
#include "structs.h"
extern f32 lbl_8029E768;
void fn_80130C6C(Unk_FFAD6788 *arg0, u32 arg1) {
    arg0->unk0x9C = 0;
    arg0->unk0xA4 = 2;
    *((f32 *)&arg0->unk0xA0) = (f32)arg1 / lbl_8029E768;
}