// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802204B8-0x8022053C (132B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_80137CB4(Unk_9F066EC1 * arg0);
extern void fn_8013DE78(void * arg0, Unk_C71E6DE1 * arg1);

void fn_802204B8(Unk_C7387A53 *arg0) {
    u8 sp8[0x28];
    s32 sp30;
    s32 *walker;
    s32 cnt;
    s32 temp_r0;
    s32 var_r3;
    register s32 var_r4 __asm__("r4");

    cnt = 2;
    walker = (s32 *)((char *)arg0 + 0xC);
    fn_80137CB4((void *)sp8);
    sp30 = arg0->unk0x1B0;
    ((Unk_7887B1E2 *)sp8)->unk0x4 = (s32)&sp30;
    ((Unk_7887B1E2 *)sp8)->unk0x2 = 4;
    ((Unk_7887B1E2 *)sp8)->unk0x0 = 0x26;
    ((Unk_7887B1E2 *)sp8)->unk0xC = 1;
    do {
        temp_r0 = *(s32 *)walker;
        var_r4 = (s32)&sp8[0];
        walker += 1;
        __asm__ volatile("mr %0,%1" : "=r"(var_r3) : "r"(temp_r0));
        if (temp_r0 != 0) {
            fn_8013DE78(var_r3, (void *)var_r4);
        }
    } while (--cnt != 0);
}
