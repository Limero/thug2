// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024FD90-0x8024FE30 (160B). Byte-identical.
// extra_cflags: -fno-schedule-insns -fno-schedule-insns2
#include "types.h"
#include "structs.h"
#define DCB(x) __asm__ __volatile__("dcbst 0, %0" :: "r"(x))

register u32 g_a1 __asm__("r4");
register u32 g_a2 __asm__("r5");

void fn_8024FD90(Unk_5B449B03 *arg0, u32 arg1, u32 arg2) {
    register u32 h __asm__("r6");
    register u32 prod __asm__("r7");
    register u32 stride __asm__("r8");
    register u32 acc __asm__("r9");
    register u32 p __asm__("r10");
    register u32 t __asm__("r11");
    g_a1 = arg1;
    g_a2 = arg2;
    g_a2 <<= 4;
    h = arg0->unk0x4;
    prod = g_a2 * h;
    p = *((u32 *)&arg0->unk0x8);
    g_a1 <<= 6;
    stride = h << 2;
    p += g_a1;
    p += prod;
    DCB(p);
    t = p + 0x20;
    DCB(t);
    p += stride;
    DCB(p);
    t = p + 0x20;
    DCB(t);
    p += stride;
    DCB(p);
    g_a2 >>= 1;
    t = p + 0x20;
    h >>= 1;
    DCB(t);
    acc = g_a2 * h;
    p += stride;
    stride = h << 2;
    DCB(p);
    t = p + 0x20;
    DCB(t);
    t = *((u32 *)&arg0->unk0xC);
    g_a1 >>= 1;
    acc += g_a1;
    h = *((u32 *)&arg0->unk0x10);
    t += acc;
    DCB(t);
    t += stride;
    h += acc;
    DCB(t);
    DCB(h);
    h += stride;
    DCB(h);
}
