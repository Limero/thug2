// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025AC04-0x8025AC18 (20B). Byte-identical.
#include "types.h"
// The want spin-waits: each loop iteration loads the status word from
// 0(r3) into r4, applies a record-form andi of 0x14, and branches back
// while the result is zero; once any of bits 0x14 is set it stores r4
// back to 0(r3) and returns. arg0 (r3) is untouched throughout.
void fn_8025AC04(s32 *arg0) {
    register u32 t __asm__("r4");
    do {
        t = *(volatile u32 *)arg0 & 0x14;
    } while (t == 0);
    *(volatile u32 *)arg0 = t;
}
