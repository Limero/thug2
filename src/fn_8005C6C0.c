// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005C6C0-0x8005C6E8 (40B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8005C6C0(CStruct *arg0, s32 arg1) {
    if (arg1 != 0) {
        arg0->unk0x4 = (s32) (arg0->unk0x4 | 0x10000);
        return;
    }
    arg0->unk0x4 = (s32) (arg0->unk0x4 & QB_UNKNOWN_0xFFFEFFFF);
}
