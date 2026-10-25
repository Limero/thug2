// WIP DRAFT (non-matching) — fn_80070138 @ 0x80070138 (216 B), ProDG/ngccc.
// Constructor-style field init: 8 float loads out of .rodata2, one rodata
// pointer, and 21 integer/byte stores, all through a COPY of the parameter
// (`mr r9, r3` — every store is `disp(r9)`, r3 is dead after the copy).
//
// family=m2c range=0x80070138-0x80070210 size=216B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Body is parked at DIFF 46.3% (25/54 words; NEAR threshold is >50%).
// 216B object, size-exact. See the PARKED block at the bottom.
#include "types.h"
extern f32 lbl_80294D4C;   // 2000.0f  @ 0x80294D4C
extern f32 lbl_80294D50;   //  100.0f  @ 0x80294D50
extern f32 lbl_80294D54;   //    0.0f  @ 0x80294D54  (stored to 0x0C/0x18/0x3C)
extern f32 lbl_80294D58;   //   16.0f  @ 0x80294D58
extern f32 lbl_80294D5C;   //  500.0f  @ 0x80294D5C
extern f32 lbl_80294D60;   //    4.0f  @ 0x80294D60
extern char lbl_80294D90[];          // 0x2FC-byte table @ 0x80294D90

// File-local view of the init'd object.  The corpus type (Unk_78674569, all
// s32, minimum size 4) is WRONG here and cost ~30 instructions: want has
// `stb` at 0x10-0x17, 0x24-0x27 and 0x40-0x43 and `stfs` at 0x00/0x08/0x0C/
// 0x18/0x20/0x30/0x38/0x3C, so every member needs its true width.
typedef struct {
    f32 unk0x00;
    s32 unk0x04;
    f32 unk0x08;
    f32 unk0x0C;
    u8 unk0x10;
    u8 unk0x11;
    u8 unk0x12;
    u8 unk0x13;
    u8 unk0x14;
    u8 unk0x15;
    u8 unk0x16;
    u8 unk0x17;
    f32 unk0x18;
    s32 unk0x1C;
    f32 unk0x20;
    u8 unk0x24;
    u8 unk0x25;
    u8 unk0x26;
    u8 unk0x27;
    char pad0x28[4];
    s32 unk0x2C;
    f32 unk0x30;
    s32 unk0x34;
    f32 unk0x38;
    f32 unk0x3C;
    u8 unk0x40;
    u8 unk0x41;
    u8 unk0x42;
    u8 unk0x43;
    char pad0x44[0x14];
    s32 unk0x58;
    s32 unk0x5C;
} Unk_80070138;

// The r9 pin is load-bearing: want's only r3 reference is the `mr r9, r3` at
// 0x8007015C and all 30 stores are `disp(r9)`.  Without the pin GCC coalesces
// the local back onto r3 and every store mismatches.  The pin adds no frame in
// this statement order (in the m2c/interleaved order it costs a 16B frame).
void fn_80070138(Unk_80070138 *p) {
    register Unk_80070138 *arg0 __asm__("r9") = p;
    arg0->unk0x5C = (s32)lbl_80294D90;
    arg0->unk0x00 = lbl_80294D4C;
    arg0->unk0x08 = lbl_80294D50;
    arg0->unk0x0C = lbl_80294D54;
    arg0->unk0x18 = lbl_80294D54;
    arg0->unk0x20 = lbl_80294D58;
    arg0->unk0x30 = lbl_80294D5C;
    arg0->unk0x38 = lbl_80294D60;
    arg0->unk0x3C = lbl_80294D54;
    arg0->unk0x04 = 0x28;
    arg0->unk0x10 = 0;
    arg0->unk0x11 = 0;
    arg0->unk0x12 = 0;
    arg0->unk0x13 = 0;
    arg0->unk0x14 = 0xFF;
    arg0->unk0x15 = 0xFF;
    arg0->unk0x16 = 0xFF;
    arg0->unk0x17 = 0xFF;
    arg0->unk0x1C = 8;
    arg0->unk0x24 = 0x80;
    arg0->unk0x25 = 0x80;
    arg0->unk0x26 = 0x80;
    arg0->unk0x27 = 0x80;
    arg0->unk0x34 = 0xFE;
    arg0->unk0x40 = 0x80;
    arg0->unk0x41 = 0x80;
    arg0->unk0x42 = 0x80;
    arg0->unk0x43 = 0x80;
    arg0->unk0x58 = 1;
    arg0->unk0x2C = 0;
}

// === PARKED (2026-10-01) — NEAR 46.3%, object 216B = want 216B ===
// Raised from DIFF 1.85% to NEAR 46.3% (25/54 words), size-exact throughout.
//
// Load-bearing fixes, in order of value:
//  1. True member widths in a file-local typedef (~30 insns).  The corpus
//     Unk_78674569 is all-s32/min-size-4, so m2c's `*(s32*)(arg0+0x13)` and
//     `unk0x24 = 0x80` compiled to `stw` and added a `stfd/lwz` int-conversion
//     dance plus an 8-byte frame.  Want's store widths (stb x21, stfs x8,
//     stw x9) pin the types exactly.
//  2. Store-group statement order: pointer store first, then the 8 float
//     stores contiguous and ascending by offset, then the integer stores
//     ascending with unk0x2C last (+~20 words).  Two independent pieces of
//     want evidence fix this order:
//       - the seven `lis` HI16 anchors sit at the block top in STRICTLY
//         ascending rodata order (4D4C,4D50,4D54,4D58,4D5C,4D60,4D90), and
//         ProDG/GCC emits those in pre-sched2 instruction order => the six
//         float statements must be contiguous and offset-ascending, with the
//         pointer statement first (it is not hoisted: `lis r11`@0x80070154 +
//         `addi`@0x8007017C are split, i.e. inline, unlike the six floats);
//       - want's `li` sequence is 0x80, 0, 0xFF, 0x28, 8, 0xFE, 1, 0 — the
//         constant for unk0x2C is emitted LAST, so that store is last.
//     Contiguity is load-bearing: interleaving the integer stores into the
//     float run collapses the HI16 block (only 2 of 7 stay at the top) and
//     the score falls back to 0-2%.
//  3. `register Unk_80070138 *arg0 __asm__("r9") = p;` (+30 words).  Zero
//     emitted asm; it is what produces `mr r9, r3` at 0x8007015C.
//
// Residual 29 words, all in the two things this compiler will not yield:
//  a. Store-block interleave (~17 words).  want's block is ascending by offset
//     (0x5C,0x00,0x04,0x08,0x13,0x17,0x1C,0x20,...,0x58,0x2C) whereas got's is
//     grouped [all floats][all ints].  Got's two subsequences (floats and ints
//     separately) already match want's exactly, so the original interleaved
//     the integer statements among the float ones — but that is the same edit
//     that destroys the HI16 block.  Tried and measured: fully ascending
//     (1.85%), ptr-first fully ascending (1.85%), early-ints-before-floats
//     (0.00%), m2c/emission order (0.00%, plus a 16B frame from the pin).
//  b. Register colours + the first `lfs` hoist (~12 words).  want allocates the
//     HI16s r10,r8,r9,r7,r6,r5,r11 and pulls `lfs f0`(4D54, 3 uses) to the
//     front of the load block; got allocates r9,r10,r8,r7,r6,r5,r11 and keeps
//     the loads in statement order.  These come off reload's pseudo order and
//     sched2's successor-count priority, not from anything expressible in C.
//
// Untried: `-fno-sched-interblock` / `-fno-sched-spec` / `-fno-strength-reduce`
// on this body (only -fno-schedule-insns2, -fno-schedule-insns, -fno-gcse and
// -fno-regmove were measured; the last three are neutral-or-worse).  Also
// untried: making the pinned local a different type from the parameter
// (`char *`/`void *` alias) in case the surviving `mr` implies the original
// copied through a differently-typed pointer.
