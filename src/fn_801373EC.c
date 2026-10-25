// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801373EC-0x80137414 (40B). Byte-identical.
#include "types.h"

void fn_801373EC(void *arg0, s32 idx, s32 add) {
    register s32 *b1 asm("r11");
    register s32 *b2 asm("r3");
    register s32 off asm("r4") = idx * 4;
    b1 = (s32 *)((char *)arg0 + 0xc08);
    b2 = (s32 *)((char *)arg0 + 0x1008);
    *(s32 *)((char *)b1 + off) += 1;
    *(s32 *)((char *)b2 + off) += add;
}
