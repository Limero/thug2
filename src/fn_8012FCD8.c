// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012FCD8-0x8012FDC0 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 fn_8012FCD8(void *arg0) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    u8 *temp_r0_2;
    u8 *temp_r0_3;
    u8 *temp_r9;
    u8 temp_r0;

    temp_r9 = *(s32 *)((char *)arg0 + (s32)0x10);
    sp8 = 0;
    temp_r0 = *temp_r9;
    switch ((s32) temp_r0) {                        
    case 44:
        *(s32 *)((char *)arg0 + (s32)0x10) = (u8 *) (temp_r9 + 1);
        GetChecksum_2(*(s32 *)((char *)arg0 + (s32)0x18), 0, &sp8, 0);
        break;
    case 45:
        temp_r0_2 = temp_r9 + 2;
        *(s32 *)((char *)arg0 + (s32)0x10) = temp_r0_2;
        fn_8012CB2C(&spC, temp_r0_2);
        *(s32 *)((char *)arg0 + (s32)0x10) = (u8 *) (*(s32 *)((char *)arg0 + (s32)0x10) + 4);
        GetChecksum_2(*(s32 *)((char *)arg0 + (s32)0x18), spC, &sp8, 0);
        break;
    case 22:
        temp_r0_3 = temp_r9 + 1;
        *(s32 *)((char *)arg0 + (s32)0x10) = temp_r0_3;
        fn_8012CB2C(&sp10, temp_r0_3);
        *(s32 *)((char *)arg0 + (s32)0x10) = (u8 *) (*(s32 *)((char *)arg0 + (s32)0x10) + 4);
        sp8 = sp10;
        break;
    }
    return sp8;
}
