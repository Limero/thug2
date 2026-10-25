// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023DA64-0x8023DB08 (164B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_8023DA18(Unk_9D3CA704 * arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4);
void fn_8023DA64(Unk_71EAD930 *arg0, Unk_F96D0DC8 *arg1) {
    u8 sp8;
    u8 sp9;
    u8 spA;
    u8 spB;
    u8 temp_r0;
    u8 temp_z;

    temp_r0 = arg0->unk0x4C;
    if ((s32)temp_r0 == 0) {
        arg1->unk0x0 = temp_r0;
        arg1->unk0x1 = temp_r0;
        arg1->unk0x2 = temp_r0;
        arg1->unk0x3 = temp_r0;
        arg1->unk0x4 = temp_r0;
        arg1->unk0x5 = temp_r0;
        return;
    }
    fn_8023DA18(arg0, &sp8, &sp9, &spA, &spB);
    arg1->unk0x3 = (u8)((s32)(spA - sp8) + 1);
    arg1->unk0x5 = (u8)((s32)(spB - sp9) + 1);
    arg1->unk0x4 = (u8)((temp_z = 0U), 1U);
    arg1->unk0x0 = sp8;
    arg1->unk0x2 = sp9;
    arg1->unk0x1 = temp_z;
}
