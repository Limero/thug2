// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FFE40-0x800FFE78 (56B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_800FFE40(Unk_377B7C81 *arg0, void *arg1) {
    u16 flg = arg0->unk0x4;
    arg0->unk0x8 = (s32)arg1;
    arg0->unk0x4 = flg | 0xC000;
    arg0->unk0xA0 = ((Unk_BE223D5D *)arg1)->unk0x10;
    arg0->unk0xA8 = ((Unk_BE223D5D *)arg1)->unk0x18;
    arg1 = (char *)arg1 + (s32)0x10;
    arg0->unk0xB0 = ((Unk_BE223D5D *)arg1)->unk0x10;
    arg0->unk0xB8 = ((Unk_BE223D5D *)arg1)->unk0x18;
}