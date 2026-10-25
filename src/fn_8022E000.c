// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022E000-0x8022E028 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8022E000(CStruct *arg0, CStruct *arg1) {
    arg1->unk0x4 = (s32) (arg1->unk0x4 | 8);
    arg1->unk0x8 = (void *) arg0->unk0x8;
    arg0->unk0x8 = arg1;
    arg0->unk0x0 = (s32) (arg0->unk0x0 | 8);
}
