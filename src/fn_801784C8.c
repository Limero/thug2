// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801784C8-0x80178520 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305F9C[];
s32 fn_8021D2C4(s32, s32);

s32 fn_801784C8(CStruct *arg0) {
    Unk_C7387A53 *temp_r3;

    temp_r3 = fn_8021D2C4(*(s32 *)&lbl_80305F9C, arg0->unk0x10);
    if (temp_r3 == NULL) {
        return 4;
    }
    temp_r3->unk0x4C = ((CStruct *)arg0->unk0x0)->unk0x4;
    return 1;
}
