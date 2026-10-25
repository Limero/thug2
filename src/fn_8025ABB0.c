// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025ABB0-0x8025ABC4 (20B). Byte-identical.
#include "types.h"
// WANT: lis r4,-0x7fd0; ori r4,r4,0x89cc; li r5,0; stw r5,0(r4); blr
// (store 0 to *(u32*)0x803089CC — full 32-bit address materialization
// into r4 BEFORE the zero, zero carried in r5).
void Vtable0x80308A40_m16(void) {
    register s32 p __asm__("r4");
    register s32 z __asm__("r5");
    p = (s32)0x803089CC;
    __asm__ volatile("li %0,0" : "=r"(z));
    *(s32 *)p = z;
}
