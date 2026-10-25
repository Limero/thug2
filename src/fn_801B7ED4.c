// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B7ED4-0x801B7F60 (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void *GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);

void fn_801B7ED4(Unk_C7387A53 *arg0, s32 arg1) {
    s32 var_r0;
    s32 var_r9;
    Unk_3BD30EA5 *temp_r3;
    Unk_31DE137E *temp_r3_2;

    temp_r3 = GetChecksum_3(arg0->unk0xC, QB_SKATERLOOPINGSOUND);
    if (temp_r3 != NULL) {
        var_r0 = temp_r3->unk0x54;
        var_r9 = temp_r3->unk0xE0;
        if (var_r0 != arg1) {
            var_r9 |= 1;
        }

        temp_r3->unk0xE0 = (var_r9 != 0) ? 1 : 0;
        temp_r3->unk0x54 = arg1;
    }
    temp_r3_2 = GetChecksum_3(arg0->unk0xC, QB_SKATERSOUND);
    if (temp_r3_2 != NULL) {
        temp_r3_2->unk0x1C = arg1;
    }
}
