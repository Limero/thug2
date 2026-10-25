// WIP DRAFT (non-matching) — best body so far
// family=m2c range=0x801F203C-0x801F2140 size=260B
// FLAG: -fno-schedule-insns -fno-schedule-insns2 -fno-sched-spec
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// === PARKED (2026-10-20) ===
// RE-TRIAGE: want_got confirms GOT hoists all constant births + both float
// loads above the first store while want interleaves stb 0x2be / lfs / hash /
// li 0xd / tail-zero / constants with the store run (53 diffs, 18.46%).
// Tried (1) statement-interleaved births in want order: collapses to 256 B
// (lmw r29 + 0x18 frame, only 3 saved regs) and 3.1% — decl-inits are what
// keep the 5-reg 0x20 frame, so size and position are mutually exclusive from
// plain C. Tried (2) volatile-qualified float externs on the decl-init body:
// byte-identical to baseline (18.46%, inert). Kept baseline as best match.
// Next lever (untried, no asm used): per-store volatile lvalue on the 0x2BE
// store only, or a float-load ordering constraint via types — scheduler, not
// allocation, is the wall (post-reload RTL already matches want order).
//
// === PARKED (2026-10-02) ===
// SCORE: 53/65 words, 18.46% masked, object .text = 260 B = EXACT size
//        (symbols.txt fn_801F203C size:0x104 == the range= marker).
//        0 inline __asm__ instructions, 0 register pins that survive,
//        object has only .text + .rela.text (no private .rodata pool).
//
// WHAT IS ALREADY BYTE-IDENTICAL (the store run + loop + frame):
//   The prologue allocates a 0x20-byte frame, saves the five callee-saved
//   registers r27-r31 at 0xc, and homes arg0 and a zero into r12 and r31;
//   the epilogue restores r27-r31, frees the frame, and returns.
//   ALL 31 field stores in exactly want's offset order (incl. the 7 adjacent
//   u8 fields at 0x2B8..0x2BE and the 0x336/0x337 pair)
//   the whole doloop is four words and fully exact: a store of r31 at
//   0x118(r9), a floating store of f13 at 0x130(r9), a 0x20 address bump of
//   r9, and the decrement-and-branch countdown; it is followed by the
//   post-loop pair that zeroes r0 and stores it at 0x2c0.
//
// WHY IT IS STUCK — 4 residual facts, all register/position ties inside ONE
// basic block (verified with `cc1 -dr` that the POST-RELOAD RTL order already
// equals want's order, so nothing above the scheduler is wrong):
//   1. Placement of 3 non-store insns in the constant block: in the want,
//      the constant block interleaves a zeroing of r10, a high-half load,
//      the 0x2be byte store, a floating load of f0, the hash high-half load
//      and a 0xd constant into r10 with the store run; it continues with a
//      zeroing of r0, a 5 into r27, another high-half load, nine more integer
//      loads, the low-half OR, the count-register setup, a floating load of
//      f13, and then the 0x2cc store, a zeroing of r31, the 0x2c4 store, the
//      r12-to-r9 copy and the 0x2d0 store. This draft instead hoists thirteen
//      integer loads plus the hash high-half/low-half pair, a high-half load
//      and the f0 and f13 floating loads above the first store, so the 0x2be
//      store lands after the f13 load, and the tail runs the 0x2cc and 0x2c4
//      stores, the r12-to-r9 copy and the 0x2d0 store.
//      i.e. GOT hoists ALL constant births + both anchor pairs above the first
//      store, and puts `li 0xd`+`mtctr` in the loop preheader.  Getting
//      `stb 0x2be` + `li 0xd` into the top block requires the constants to be
//      source STATEMENTS placed there (tried: v19/v22/v23) — but GIMPLE folds
//      the statement form back to decl-initializers and the object goes 1 word
//      short (256 B) and 4% worse.  Decl-init form gives the size + store
//      order; statement form gives the position.  They are mutually exclusive
//      from plain C.
//   2. Register colours of the call-saved constant group: want r8,r7,r6,r5,r4,r3
//      (contiguous descending) vs got r11,r10,r8,r6,r4,r3 — got skips r7 and
//      r5 (they are taken by the 0x2BE zero and by an anchor).  This is the
//      §6ds-2 "local hard-reg pool is positional" rotation.
//   3. Hard-reg pins on decl-initialiser constants are INERT (measured 8
//      single pins: all byte-identical).  Only pinning `v_zero` changed the
//      object, and for the worse (18.46 -> 12.31).  So §6cs-3's "pin one member
//      of the permuted group" does not apply to `s32 x = <const>;` — cc1
//      expands the constant into a reg of its own choosing.
//   4. `-fno-rerun-cse-after-loop` (the one flag that would explain GOT's
//      missing post-loop `li`) ICEs at flow.c:993 in this cc1; `-fno-cse-after-
//      loop` does not exist.
//
// WHAT I DID NOT TRY:
//   * A 1-instruction `__asm__("li %0,0" : "=r"(z))` opaque birth for the 0x2BE
//     zero and for the post-loop zero, to force the two missing zero births and
//     pin them at their want positions (§6y-140 / §6b "=r" li birth).  That is
//     the most promising next lever (2 emitted insns = 3% of the body, inside
//     the 30% budget).
//   * `volatile`-qualified store lvalues to freeze the store run (§6ek) — tried
//     as a whole-struct `volatile Unk_t *` and it collapses the object to
//     240 B (blocks the shared-zero reuse).  Per-store volatile on just the
//     0x2BE store was not tried.
//   * Re-deriving the struct from the promoted sibling's file-local typedefs:
//     none exists (this function has no calls, so the §6dc "search by callee
//     set" oracle is unavailable; the address-adjacent siblings
//     src/fn_801F2140.c / fn_801F2014.c are 68 B / 40 B wrappers and only
//     confirm `void *arg0` + the 0x2C0 field is an s32).
//
// MEASURED LADDER (all masked, size in brackets):
//   m2c draft as inherited ................................ 4.62% [260 B]
//   + file-local typedef, real u8/f32 widths ............. 9.23% [260 B]
//   + constants as named locals (decl-initialisers) ...... 0.00% [248 B] (1.6% masked-real)
//   + shared ctr/0x2BE variable + literal final store .... 10.77% [260 B]
//   + -fno-schedule-insns ................................ 13.85% [260 B]
//   + -fno-schedule-insns2 -fno-sched-spec .............. 18.46% [260 B]  <== kept
//   (all 20+ other project flags inert; 8 register pins inert; volatile struct
//    240 B; statement-order forms 256 B; two "5"-store permutations no-op)
//
// NOTEs that are load-bearing and easy to lose:
//   * struct pad134 is 0x184 (not 0x84): the 0x130 float and the 0x2B8 u8 run
//     are 0x184 apart; getting it wrong shifts EVERY displacement by 0x100 and
//     silently costs ~5 points.
//   * two DISTINCT extern symbols (lbl_802AE29C / lbl_802AE2A0) are required to
//     get want's TWO `lis r9,-0x7fd5` page anchors (§6an-5): one shared symbol
//     CSEs them into a single reload.
//   * the object-pointer local `self` and the loop base `sub` are TWO names for
//     the same address; collapsing them to one loses `mr r12,r3` / `mr r9,r12`.
//   * QB hash 0x54166ACD (QB_SKATE) is hand-decoded from want's
//     lis r11,0x5416 + ori r11,r11,0x6acd; kept as a bare literal on purpose
//     (§6ar-222: a QB_ macro can change codegen once pins/reassignment exist).
#include "types.h"

extern f32 lbl_802AE29C;   /* .rodata2 data:float, 0x802B0000-0x1D64 */
extern f32 lbl_802AE2A0;   /* .rodata2 data:float, 0x802B0000-0x1D60 */

typedef struct Unk_801F203C {
    s32 unk000;
    u8 unk004;
    char pad005[0x31];
    u8 unk036;
    char pad037[0x14];
    u8 unk04B;
    char pad04C[0x63];
    u8 unk0AF;
    char pad0B0[0x64];
    s32 unk114;
    s32 unk118;
    char pad11C[0x14];
    f32 unk130;
    char pad134[0x184];
    u8 unk2B8;
    u8 unk2B9;
    u8 unk2BA;
    u8 unk2BB;
    u8 unk2BC;
    u8 unk2BD;
    u8 unk2BE;
    char pad2BF[1];
    s32 unk2C0;
    s32 unk2C4;
    s32 unk2C8;
    s32 unk2CC;
    s32 unk2D0;
    s32 unk2D4;
    s32 unk2D8;
    f32 unk2DC;
    s32 unk2E0;
    s32 unk2E4;
    s32 unk2E8;
    s32 unk2EC;
    s32 unk2F0;
    s32 unk2F4;
    s32 unk2F8;
    s32 unk2FC;
    char pad300[0x28];
    s32 unk328;
    char pad32C[0xA];
    u8 unk336;
    u8 unk337;
} Unk_801F203C;

void fn_801F203C(void *arg0) {
    Unk_801F203C *self = arg0;
    Unk_801F203C *sub;
    s32 ctr = 0;
    s32 v_zero = 0;
    s32 v_five = 5;
    s32 v_64 = 0x64;
    s32 v_78 = 0x78;
    s32 v_1 = 1;
    s32 v_bb8 = 0xBB8;
    s32 v_b = 0xB;
    s32 v_168 = 0x168;
    s32 v_2 = 2;
    s32 v_3 = 3;
    s32 v_8 = 8;
    s32 lzero = 0;
    s32 v_hash = 0x54166ACD;
    f32 k2DC = lbl_802AE29C;
    f32 k130 = lbl_802AE2A0;

    self->unk2BE = ctr;
    ctr = 0xD;
    self->unk2CC = v_64;
    self->unk2C4 = v_78;
    sub = self;
    self->unk2D0 = v_1;
    self->unk2DC = k2DC;
    self->unk2E0 = v_bb8;
    self->unk2E4 = v_five;
    self->unk2E8 = v_b;
    self->unk2EC = v_168;
    self->unk2F4 = v_2;
    self->unk2F8 = v_3;
    self->unk2FC = v_8;
    self->unk2C8 = v_hash;
    self->unk337 = v_zero;
    self->unk000 = v_zero;
    self->unk004 = v_zero;
    self->unk04B = v_zero;
    self->unk0AF = v_zero;
    self->unk036 = v_zero;
    self->unk114 = v_zero;
    self->unk2BA = v_zero;
    self->unk2B9 = v_zero;
    self->unk2B8 = v_zero;
    self->unk2BB = v_zero;
    self->unk2BC = v_zero;
    self->unk2BD = v_zero;
    self->unk2D4 = v_zero;
    self->unk2D8 = v_five;
    self->unk2F0 = v_zero;
    self->unk328 = v_zero;
    self->unk336 = v_zero;
    do {
        sub->unk118 = lzero;
        sub->unk130 = k130;
        sub = (Unk_801F203C *)((char *)sub + 0x20);
    } while (ctr -= 1);
    self->unk2C0 = 0;
}