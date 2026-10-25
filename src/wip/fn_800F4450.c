// PARKED 2026-10-01: 90.59% -> 94.12% (76/81). Two REAL semantic bugs fixed
// (both invisible to any flag/pin search, because they are arithmetic, not
// scheduling):
//
//  1. SCALED-POINTER STRIDE.  The m2c draft wrote `var_r9 += 0x18` on an
//     `s32 *`, which ngccc correctly scales to 0x60 bytes/iteration.  The
//     binary advances the destination by 0x18, i.e. the source pointer is a
//     BYTE pointer (or the struct is 0x18 and the loop steps one element).
//     Fixed by declaring `var_r4` as `char *` and stepping `var_r9` through a
//     `char *` cast.  This is the same class as tools/fix_scaled_ptr.py.
//  2. LOOP COUNTER.  The m2c draft's `var_r11 = 0x30` (from a 0x54-byte / 0x18
//     tail split) produces `li r11, 0x30 / addic. r11,r11,-0x18` -> 2
//     iterations.  want is `li r11, 0x48` -> 3 iterations, and 3*0x18 = 0x48
//     is exactly the 0x48 bytes of payload the 0x54-byte block has after the
//     4-byte header and before the 3-word (0xC-byte) tail copy that follows
//     the loop.  0x48 + 0xC = 0x54.  So the counter is the payload size, not a
//     guess.
//
// The init-block shape (variant "e": a fresh `s32 *q` local per store, with
// arg0 re-declared locally as a struct whose unk0x54 is the `s32 *` the
// disassembly proves it is -- the shared Unk_C7387A53 types it `s32`, which
// forces an int<->ptr warning on every use) also matters: it beats the raw
// `(s32 *)((char *)arg0 + 0x54) + N` cast form 92.94% -> 94.12%.
//
// REMAINING RESIDUAL (5 words, one allocator coin-flip, see the diff):
//   Retail materialises the constant 1 in r10 and alternates the four base
//   reloads across r9 and r11, storing r10 at 4 of the r9 base, then zero at
//   8 of an r11 base, zero at 0xc of an r9 base, and zero at 0x10 of an r11
//   base. The build materialises the constant in r9 instead and reuses r11
//   for all four reloads, storing r9 at 4 of the first r11 base, then zero
//   at 8, 0xc, and 0x10 of the following r11 bases.
// want colours the constant 1 into r10 and ALTERNATES the four reloads
// r9/r11/r9/r11; ngccc puts the constant in r9 and reuses r11 for all four
// reloads.  Tried and measured, none better than 94.12%:
//   * four DISTINCT pointer variables q1..q4 (variant j) -> 18.29% (the
//     allocator then keeps four registers live and the whole tail shifts).
//   * a 5-word struct type with named fields instead of s32 index (m) -> 16.05%.
//   * `s32 one = 1` named local (n) -> 18.29%.
//   * store order rotated so the 1-store is written first (h) -> 91.76%.
//   * flags: -Os / -O2 / none / -fno-sched-interblock all 94.12% (flag-neutral).
// Alternation between r9 and r11 implies want has TWO reload pseudos where got
// has one; no plain-C form tried creates that split without also perturbing
// the already-exact tail.  Do NOT re-grind the loop/counter/tail -- those are
// byte-exact; only the five-store init block is open.
//
// PREVIOUS PARK NOTE (superseded, kept for history): "doloop CTR strength-
// reduction" was blamed for this function.  That diagnosis was WRONG -- the
// addic./bne bottom-test form was already being produced; the real cause was
// the 0x30-vs-0x48 counter above.  -Os is still set and is now flag-neutral
// (the score is the same with and without it).
// WIP DRAFT (concrete attempt;)
// family=m2c range=0x800F4450-0x800F45A4 size=340B
// FLAG: -Os
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_800F3A1C(s32);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 ContainsFlag(CStruct *, s32);

/* arg0's unk0x54 is a POINTER: fn_800F3A1C's result is stored there and then
 * re-loaded twelve times.  The shared Unk_C7387A53 declares it `s32`, which
 * makes every use an int<->ptr conversion; typing it here is what the
 * disassembly says and it is worth 1.2% on its own. */
typedef struct {
    char pad0x0[0x54];
    s32 *unk0x54;
} F4450_self;

void fn_800F4450(F4450_self *arg0, void *arg1, CStruct *arg2) {
    s32 *temp_r3;
    s32 *var_r9;
    s32 temp_r0;
    s32 var_r11;
    char *var_r4;

    temp_r3 = fn_800F3A1C(0x54);
    arg0->unk0x54 = temp_r3;
    *((s32 *)temp_r3) = 0;
    {
        s32 *q;
        q = arg0->unk0x54; q[1] = 1;
        q = arg0->unk0x54; q[2] = 0;
        q = arg0->unk0x54; q[3] = 0;
        q = arg0->unk0x54; q[4] = 0;
    }
    if (arg1 != NULL) {
        var_r9 = arg0->unk0x54;
        var_r4 = (char *)arg1;
        var_r11 = 0x48;
        loop: {
            ((Unk_DB0E2BAB *)var_r9)->unk0x0 = *(s32 *)(var_r4 + 0x0);
            ((Unk_DB0E2BAB *)var_r9)->unk0x4 = *(s32 *)(var_r4 + 0x4);
            ((Unk_DB0E2BAB *)var_r9)->unk0x8 = *(s32 *)(var_r4 + 0x8);
            ((Unk_DB0E2BAB *)var_r9)->unk0xC = *(s32 *)(var_r4 + 0xC);
            ((Unk_DB0E2BAB *)var_r9)->unk0x10 = *(s32 *)(var_r4 + 0x10);
            temp_r0 = *(s32 *)(var_r4 + 0x14);
            var_r4 += 0x18;
            ((Unk_DB0E2BAB *)var_r9)->unk0x14 = temp_r0;
            var_r9 = (s32 *)((char *)var_r9 + 0x18);
            var_r11 -= 0x18;
            if (var_r11 != 0) goto loop;
        }
        ((Unk_DB0E2BAB *)var_r9)->unk0x0 = *(s32 *)(var_r4 + 0x0);
        ((Unk_DB0E2BAB *)var_r9)->unk0x4 = *(s32 *)(var_r4 + 0x4);
        ((Unk_DB0E2BAB *)var_r9)->unk0x8 = *(s32 *)(var_r4 + 0x8);
    }
    if (arg2 != 0) {
        GetChecksum_2(arg2, QB_TEX_DICT, arg0->unk0x54, 0);
        *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x54) + 0x4) = ContainsFlag(arg2, QB_ADD_SUPER_SECTORS);
        *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x54) + 0x8) = ContainsFlag(arg2, QB_IS_SKY);
        *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x54) + 0xC) = ContainsFlag(arg2, QB_IS_DICTIONARY);
        *(s32 *)((char *)arg0->unk0x54 + 0x10) = ContainsFlag(arg2, QB_IS_NET);
    }
}