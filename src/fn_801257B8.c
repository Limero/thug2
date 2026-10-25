// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801257B8-0x80125814 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
// Script_GetInteger @ 0x801257B8
s32 Script_GetInteger(s32 arg0) {
    Unk_5AA7B5D7 *temp_r3;
    u8 temp_r0;

    temp_r3 = fn_80125480();
    if (temp_r3 == NULL) {
        goto ret0;
    }
    temp_r0 = *(u8 *)((char *)temp_r3 + 2);
    if (temp_r0 == 1) {
        goto case1;
    }
    if (temp_r0 != 2) {
        goto ret0;
    }
case2:
    return (s32)(*((f32 *)&temp_r3->unk0xC));
case1:
    return temp_r3->unk0xC;
ret0:
    return 0;
}
