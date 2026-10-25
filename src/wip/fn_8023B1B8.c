// RE-TRIAGED 2026-10-13: still 58.9% NEAR (sweep), 424/428B.
// family=hand range=0x8023B1B8-0x8023B364 size=428B
// Load-schedule + regalloc wall (field-load order, loop-counter regs per header).
// No new lever; body unchanged.
// UPDATED 2026-10-04 (bf): 57.9% -> **59.4%** by ONE semantic fix —
// `temp_r4pin` is the +0x18 u32 byte-swap web and must be declared **u32**,
// not s32. With `s32` the macro's `>> 0x18` becomes a SIGNED shift and ngccc
// emits `srawi r9,r4,0x18` where want has `srwi r9,r4,0x18`; every other
// instruction of that 8-insn web is already correct, so the whole web shifts
// and cascades through the register allocation.
//
// The rest is a load-schedule + regalloc wall and is NOT solved:
//  * want loads the five u16 fields in the order +6, +0x10, +4, +8, +0xA,
//    +0x12 (with +0x18 first); the draft reads them +0x18, +0x10, +4, +8,
//    +0xA, +6, +0x12 and cc1 preserves that order.  Reordering the reads to
//    match want's *load* order scores 55.7% (with pins) / 41.5% (without) —
//    the pin web then permutes.
//  * the +0x12 loop's read order is the mirror image: want loads +0x2C
//    BEFORE +0x2A, the draft loads +0x2A first.
//  * want's second loop uses a DIFFERENT counter register (r7) and a
//    different pointer register (`mr r3,r31` copy, r3 advanced) from the first
//    loop (r27 / r31).  Forcing two separate C counters + a separate pointer
//    variable drops the object to 408 B (want 428 B) and the score to 56.9%.
//  * dropping the `q` r12 pin = 44.3%, pinning temp_r4pin to r0 = 38.7%,
//    reordering only the +6/+0x10 pair = 55.7%.
// Object is 424 B vs want 428 B (1 word short); frame, prologue
// (`stwu r1,-0x20 / stmw r27,0xc / li r3,1 / li r30,0` — a true leaf, no LR
// save), the +0x3C94 u32 web, the +0x18 u32 web, both loop bodies' arithmetic
// and the epilogue all match.
//
// PARKED 2026-10-01: 52.8% -> 57.9% via the doc-75 reload/arg pin lever,
// found by tools/reload_pin_sweep.py (the first corpus sweep of that lever):
//
//      register u32 temp_r4pin __asm__("r4");
//      temp_r4pin = ((Unk_C7125B80 *)q)->unk0x18;
//      ... ((Unk_C7125B80 *)q)->unk0x18 = SWAP32(temp_r4pin);
//
// The swap-temp web is retyped onto a pinned r4.  Pinning the arg0/temp_r7 web
// to r3 or r4 gives 56.6%, temp_r5->r5 55.7%, temp_r3->r3 54.7%.  The pin has
// to cover the WHOLE web (declaration + both uses); renaming only the
// assignment leaves the store on the old variable and scores nothing.
//
#include "types.h"
#include "structs.h"
#define SWAP32(x) (((x) >> 0x18) | (((x) >> 8) & 0xFF00) | (((x) << 8) & 0xFF0000) | ((x) << 0x18))
#define SWAP16(x) (u16)(((x) >> 8) | ((x) << 8))

void fn_8023B1B8(Unk_E4EF6F7F *arg0) {
    register char *q __asm__("r12");
    char *w;
    s32 i;
    u32 temp_r10;
    register u32 temp_r4pin __asm__("r4");
    u32 tw_a;
    u32 tw_b;
    u32 tw_c;
    u16 temp_r11;
    u16 temp_r3;
    u16 temp_r5;
    u16 temp_r6;
    u16 temp_r7;
    u16 temp_r8;
    u16 th_a;

    i = 0;
    temp_r10 = arg0->unk0x13C94;
    w = (char *)arg0 + 0x14A14;
    q = (char *)arg0 + 0x13C94;
    arg0->unk0x13C94 = SWAP32(temp_r10);
    temp_r4pin = ((Unk_C7125B80 *)q)->unk0x18;
    temp_r11 = ((Unk_C7125B80 *)q)->unk0x10;
    temp_r3 = ((Unk_C7125B80 *)q)->unk0x4;
    temp_r5 = ((Unk_C7125B80 *)q)->unk0x8;
    temp_r7 = ((Unk_C7125B80 *)q)->unk0xA;
    temp_r6 = ((Unk_C7125B80 *)q)->unk0x6;
    temp_r8 = ((Unk_C7125B80 *)q)->unk0x12;
    ((Unk_C7125B80 *)q)->unk0x4 = SWAP16(temp_r3);
    ((Unk_C7125B80 *)q)->unk0x6 = SWAP16(temp_r6);
    ((Unk_C7125B80 *)q)->unk0x8 = SWAP16(temp_r5);
    ((Unk_C7125B80 *)q)->unk0xA = SWAP16(temp_r7);
    ((Unk_C7125B80 *)q)->unk0x12 = SWAP16(temp_r8);
    ((Unk_C7125B80 *)q)->unk0x18 = SWAP32(temp_r4pin);
    ((Unk_C7125B80 *)q)->unk0x10 = SWAP16(temp_r11);
    for (i = 0; i < ((Unk_C7125B80 *)q)->unk0x10; i++) {
        tw_a = ((Unk_F50EB36F *)w)->unk0x0;
        tw_b = ((Unk_F50EB36F *)w)->unk0x4;
        ((Unk_F50EB36F *)w)->unk0x0 = SWAP32(tw_a);
        ((Unk_F50EB36F *)w)->unk0x4 = SWAP32(tw_b);
        w += 8;
    }
    for (i = 0; i < ((Unk_C7125B80 *)q)->unk0x12; i++) {
        th_a = ((Unk_F50EB36F *)w)->unk0x2A;
        tw_c = ((Unk_F50EB36F *)w)->unk0x2C;
        ((Unk_F50EB36F *)w)->unk0x2A = SWAP16(th_a);
        ((Unk_F50EB36F *)w)->unk0x2C = SWAP32(tw_c);
        w += 0x30;
    }
}
