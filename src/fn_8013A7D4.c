// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013A7D4-0x8013A8D0 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8013A7D4(Unk_DB0E2BAB *arg0) {
    s32 temp_r0;
    s32 temp_r9;
    u16 *temp_r8;
    u16 temp_r9_2;
    u32 temp_r0_2;
    Unk_A99C4F7E *temp_r11;
    Unk_BDBFA817 *temp_r11_2;
    Unk_BDBFA817 *temp_r11_3;
    register Unk_BDBFA817 *temp_r10_2 __asm__("r10");
    s32 *p;

    arg0->unk0x8 = 2;
    if (arg0->unk0x14 & 1) {
        return 4;
    }
    temp_r8 = *((u16 * *)&arg0->unk0x0);
    temp_r9 = arg0->unk0x9C;
    p = (s32 *)((char *)arg0 + (s32)0x1C);
    p[temp_r9] = (s32) *temp_r8;
    arg0->unk0x9C = (s32) (temp_r9 + 1);
    temp_r11 = *((void * *)&arg0->unk0x10);
    temp_r0 = temp_r11->unk0x4930;
    if (temp_r0 != 0) {
        temp_r9_2 = *temp_r8;
        if (temp_r9_2 < (u32)temp_r0) {
            if ((u32)(temp_r0 - temp_r9_2) > 0x1388U) {
                goto block_13;
            }
            goto block_10;
        }
        if ((s32)temp_r9_2 == temp_r0) {
            temp_r11_2 = *((void * *)&arg0->unk0xC);
            temp_r11_2->unk0x1800 = (s32) (temp_r11_2->unk0x1800 + 1);
            return 0;
        }
        temp_r0_2 = temp_r9_2 - temp_r0;
        if (temp_r0_2 > 1U) {
            if (temp_r0_2 > 0x1388U) {
block_10:
                temp_r11_3 = *((void * *)&arg0->unk0xC);
                temp_r11_3->unk0x17FC = (s32) (temp_r11_3->unk0x17FC + 1);
                temp_r10_2 = *((void * *)&arg0->unk0xC);
                temp_r10_2->unk0x17F8 = (s32) (temp_r10_2->unk0x17F8 - 1);
                arg0->unk0x14 = (s32) (arg0->unk0x14 | 2);
                goto ret;
            }
            temp_r10_2 = *((void * *)&arg0->unk0xC);
            temp_r10_2->unk0x17F8 =
                (s32) (temp_r10_2->unk0x17F8 + (temp_r0_2 - 1));
            temp_r11 = *((void * *)&arg0->unk0x10);
        } else {
            goto block_13;
        }
    } else {
        goto store;
    }
store:
    temp_r11->unk0x4930 = (s32) *temp_r8;
    goto ret;
block_13:
    temp_r11->unk0x4930 = (s32) temp_r9_2;
ret:
    return 1;
}
