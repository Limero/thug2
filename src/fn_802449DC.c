// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802449DC-0x80244A20 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802449DC(Unk_F96D0DC8 *arg0, u8 arg1, u8 arg2) {
    if (arg1 < (u8) arg0->unk0x7) {
        arg0->unk0x7 = arg1;
    }
    if (arg1 > (u8) arg0->unk0x9) {
        arg0->unk0x9 = arg1;
    }
    if (arg2 < (u8) arg0->unk0x8) {
        arg0->unk0x8 = arg2;
    }
    if (arg2 > (u8) arg0->unk0xA) {
        arg0->unk0xA = arg2;
    }
}
