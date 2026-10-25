// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A80B0-0x801A80DC (44B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AB9F8[];
void fn_801A80B0(s32 arg0, s32 arg1) {
    register s32 o __asm__("r11");

    o = arg0;
    ((Unk_C8FEE62D *)o)->unk0x8 = 0;
    ((Unk_C8FEE62D *)o)->unk0x14 = (s32)lbl_802AB9F8;
    ((Unk_C8FEE62D *)o)->unk0x18 = arg1;
    ((Unk_C8FEE62D *)o)->unk0xC = o;
    ((Unk_C8FEE62D *)o)->unk0x10 = o;
    ((Unk_C8FEE62D *)o)->unk0x4 = o;
}
