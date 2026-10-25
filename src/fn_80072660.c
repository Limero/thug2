// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80072660-0x80072688 (40B). Byte-identical.
#include "types.h"

extern char lbl_80301600[];

typedef union {
    u32 raw;
    struct { u32 a : 8; u32 b : 8; u32 c : 8; u32 d : 8; } f;
} PackedColor;

void fn_80072660(void *arg0, u32 *arg1) {
    u8 *base = (u8 *)&lbl_80301600;
    PackedColor pc;
    register u32 raw asm("r0") = *arg1;
    register u32 r11v asm("r11");
    register u32 r10v asm("r10");
    pc.raw = raw;
    r10v = pc.f.a;
    raw = pc.f.b;
    r11v = pc.f.c;
    base[8] = r10v;
    base[9] = raw;
    base[0xa] = r11v;
}
