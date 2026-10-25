// WIP DRAFT — hand-written from disasm 2026-10-09.
// family=hand range=0x8025F298-0x8025F340 size=168B
// INERT: not registered in splits.txt/configure.py — never compiled.
//
// Arena carve + clear (twin of fn_8025F340, which is byte-EXACT with the same
// source shape): lo = OSGetArenaLo(); lbl_803CAB64 = lo;
// OSSetArenaLo(lo + 0x8000); then 0x8000 bytes cleared as a byte-stride loop
// with 4-byte stores (`for (i = 0; i < 0x8000; i += 4) *(u32 *)((u8 *)lbl +
// i) = 0;` — same loop mwcc emits here: li r0,0x400 + stwx/addi r5,r5,4).
//
// PARKED (2026-10-09): 164B vs 168B — everything matches except a single
// `mr r4,r3` + store position that the reference has in the prologue:
//   The reference copies the arena pointer from r3 to r4, builds the rounded
//   address in r3 with an addis of 1 off the r4 copy, stores r4 to the
//   arena-low symbol through r13, then completes the addition with an addi of
//   -0x8000; the draft instead stores r3 to that symbol directly and performs
//   the same addis of 1 and addi of -0x8000 on r3 itself.
// i.e. the reference keeps the arena pointer alive for the store while the
// 0x8000 (two-instruction addis+addi) is materialised in r3, and mwcc here
// emits the store first and reuses r3 for the sum. Tried and all 41/42:
// store-then-call (u32*/u8*/int locals, 0x2000-element form), call-then-store
// (forces r31 + 0x20 frame), assignment-as-expression inside the call,
// explicit `end` temp, integer-pointer arithmetic. Frame, carve, and the whole
// 8x-unrolled clear loop match byte-for-byte — the residual is this one insn.
//
// ADDENDUM 2026-10-09 (same session, exhaustive): 9 more shapes (two-variable
// lo/p, void*, u32, s32, s8/u8 round-trips, split decl+assign, base copy) plus
// 7 mwcc versions (1.2.5n/1.2.5/1.3/1.3.2/1.3.2r/2.5/2.6) and 10 flag sets
// (-O1..-O4,s,-schedule off,-opt off,-inline off/noauto) — EVERY build is
// 164B with the same missing `mr`. mwcc here simply does not copy the call
// result into a second register for the store; the reference build did. This
// is a compiler-behaviour gap, not a source-shape gap: park until a compiler
// patch/target is found (only the 4B `mr` + store slot differ).
// mwcc region (GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *lbl_803CAB64;
void *OSGetArenaLo(void);
void OSSetArenaLo(void *addr);

void fn_8025F298(void) {
    u32 *lo;
    u32 i;

    lo = OSGetArenaLo();
    lbl_803CAB64 = lo;
    OSSetArenaLo((char *)lo + 0x8000);

    for (i = 0; i < 0x8000; i += 4) {
        *(u32 *)((u8 *)lbl_803CAB64 + i) = 0;
    }
}
