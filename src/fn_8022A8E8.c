// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022A8E8-0x8022A964 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_8013FA3C(s32, s32);

void fn_8022A8E8(CScript *arg0, s32 arg1) {
    volatile s32 sp8;
    register s32 a1 __asm__("r4");
    register s32 p10 __asm__("r10");
    register s32 one __asm__("r11");
    s32 temp_r9;

    a1 = arg1;
    if (arg0->unk0x1DC == a1) {
        p10 = arg0->unk0x1C;
        if (p10 != NULL) {
            temp_r9 = *(s32 *)((char *)(void *)p10 + (s32)0x68);
            sp8 = 2;
            one = 1;
            temp_r9 = (s32) (temp_r9 & QB_UNKNOWN_0xFFFFFFFD);
            *(s32 *)((char *)(void *)p10 + (s32)0x68) = temp_r9;
            sp8 = one;
            temp_r9 = arg0->unk0x1C;
            *(s32 *)((char *)(void *)temp_r9 + (s32)0x68) = (s32) (*(s32 *)((char *)(void *)temp_r9 + (s32)0x68) | 1);
            fn_8013FA3C(arg0->unk0x1C, a1);
        }
        arg0->unk0x1DC = 0;
    }
}
