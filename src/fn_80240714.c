// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80240714-0x80240744 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802406A4(s32);
void fn_80240714(CStruct *arg0) {
    s32 temp_r9;

    temp_r9 = arg0->unk0x8 & 0x100;
    if (temp_r9 == 0) {
        fn_802406A4(arg0->unk0x34);
    }
}
