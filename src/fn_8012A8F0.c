// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012A8F0-0x8012A958 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80125480(s32);
void fn_8012A8F0(Unk_5B449B03 *arg0, s32 *arg1, s32 *arg2) {
    s32 temp_r0;
    Unk_1D62F22E *temp_r3;

    *arg2 = *((s32 *)&arg0->unk0x8);
    temp_r0 = arg0->unk0x0 & 0x7F;
    *arg1 = temp_r0;
    if (temp_r0 == 0xD) {
        temp_r3 = fn_80125480(*arg2);
        if (temp_r3 != NULL) {
            *arg2 = temp_r3->unk0xC;
            *arg1 = (s32) temp_r3->unk0x2;
        }
    }
}
