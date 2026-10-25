// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013B6F4-0x8013B76C (120B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8013B6F4(Unk_C7387A53 *arg0, s32 arg1) {
    s32 addr;
    register s32 *walk __asm__("r10");
    s32 v;
    s32 sum;
    s32 cnt;
    s32 i;

    addr = (s32)arg0 + 4;
    __asm__("mr %0, %1" : "=r"(walk) : "r"(addr));
    *(s32 *)(addr + (*((u32 *)&arg0->unk0x2C) << 2)) = arg1;
    sum = 0;
    cnt = 0;
    *((u32 *)&arg0->unk0x2C) = (*((u32 *)&arg0->unk0x2C) + 1) % 10;
    i = 0xA;
    do {
        v = *(walk++);
        if (v != 0) {
            sum += v;
            cnt += 1;
        }
    } while (--i != 0);
    if (cnt > 0) {
        *(s32 *)arg0 = sum / cnt;
    }
}
