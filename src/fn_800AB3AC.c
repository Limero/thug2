// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AB3AC-0x800AB3D8 (44B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800AB3AC(Unk_C7387A53 *arg0, s32 arg1) {
    if (arg1 == 0) {
        arg0->unk0x24 = 1;
    }
    if ((s32) arg0->unk0x20 != 0) {
        arg0->unk0x24 = 1;
    }
    return arg0->unk0x24;
}
