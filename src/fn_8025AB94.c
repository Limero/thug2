// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025AB94-0x8025ABB0 (28B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// IDENTIFIED (2026-09-01): named Vtable0x80308A40_m15 (vtable slot 15 of
// the 0x80308A40 object) — GX FIFO/CP register poke (writes 3 then
// 0x4CC8 to 0xCC003024) inside an infinite loop (b back to fn start;
// never returns). Match notes: for(;;) loop (else GCC emits a trailing
// blr), memory barrier between the constant assigns and stores, and
// v2/v1 assignment order (r3 4CC8 before r4 3).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void Vtable0x80308A40_m15(void) {
    register char *p __asm__("r5");
    register s32 v1 __asm__("r4");
    register s32 v2 __asm__("r3");
    for (;;) {
        p = (char *)QB_UNKNOWN_0xCC000000;
        v2 = 0x4CC8;
        v1 = 3;
        __asm__ volatile("" : : : "memory");
        *((u32 volatile *)&((Unk_8588B1A5 *)p)->unk0x3024) = v1;
        *((u32 volatile *)&((Unk_8588B1A5 *)p)->unk0x3024) = v2;
        __asm__ volatile("nop");
    }
}
