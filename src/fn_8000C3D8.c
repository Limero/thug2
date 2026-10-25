// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000C3D8-0x8000C410 (56B). Byte-identical.
#include "types.h"
#include "structs.h"

void fn_8000C3D8(Unk_76808E8C *arg0) {
    register s32 r8 asm("r8");
    register s32 r10 asm("r10");
    register s32 r9 asm("r9");
    register s32 r11 asm("r11");
    s32 v;
    s32 w;
    v = arg0->unk0xCC;
    r8 = 2;
    r10 = 1;
    r9 = 7;
    r11 = 5;
    w = v | 6;
    asm volatile("" ::: "memory");
    arg0->unk0xE0 = r8;
    asm volatile("" ::: "memory");
    arg0->unk0xC = r9;
    asm volatile("" ::: "memory");
    arg0->unk0xCC = w;
    asm volatile("" ::: "memory");
    arg0->unk0x81 = (u8)r10;
    asm volatile("" ::: "memory");
    arg0->unk0xDC = r11;
    asm volatile("" ::: "memory");
    arg0->unk0xD4 = r8;
    asm volatile("" ::: "memory");
    arg0->unk0x80 = (u8)r10;
}
