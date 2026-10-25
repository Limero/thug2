// WIP DRAFT (non-matching) — hand-reconstructed 2026-09-28 from the DOL.
// family=m2c range=0x8006A6F0-0x8006A780 size=144B   (== symbols.txt size:0x90)
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// SCORE: 13.9% (24 / 36 word diffs), size-exact 144B, compiles clean
//        (needs -mps-float; the auto rule picks it up because of __ps_t).
//   tools/venv/bin/python tools/score_body.py 0x8006A6F0 src/wip/fn_8006A6F0.c
//   tools/venv/bin/python tools/want_got.py 0x8006A6F0
// (was 13.9% with the raw m2c body; 30+ variants tried, see PARKED below.
//  No inline asm anywhere in this body.)
//
// WHAT THE FUNCTION IS (fully decoded — the C below is believed CORRECT):
//   Walk a circular doubly-linked list rooted at `*(Elem **)arg0`, calling
//   fn_80069EB8(elem->unk0x0, arg1) for every elem from head->unk0x4 round
//   until the walk comes back to head (`head` is re-read from `*arg0` each
//   iteration — the callback may modify the list), then copy 16 bytes from
//   arg1 into the object at arg0+8.
//
// PROLOGUE-TO-LOOP SHAPE (0x8006A6F0..0x8006A780, 36 words): the entry block
// saves both args to callee-saved homes, loads the head, defaults the cursor
// to null, fills it from head->next when non-null, and forms the while test
// (cursor vs head).  Both values are also spilled to two frame slots, and the
// arg0+8 record address is computed HERE in the entry block (which is why the
// save set starts where it does).  The loop calls the per-element helper with
// the cursor's payload and the second arg, re-reads the head from the global
// (the callback may modify the list), advances the cursor, spills both slots
// again, and loops while cursor != head.  The tail is a plain 16-byte pair
// copy from the second arg into the arg0+8 record.
//
// The tail is a plain 16-byte pair copy emitted as pair ops (hence
// -mps-float): `dst[0] = src[0]; dst[1] = src[1];` with
// dst == (__ps_t *)((char *)arg0 + 8). Note the deliberate asymmetry —
// the first store is folded as a displacement off the arg0 home register
// while the second goes through the precomputed arg0+8 register, so that
// register is live from the ENTRY block and is the only reason the save set
// starts where it does. (Verified word-by-word with tools/ps_disasm.py.)
//
// ============================ PARKED =====================================
// BLOCKER: want keeps `cur` and `head` IN MEMORY (slots 8/0x10, reloaded
// after the call) while still using the register copies for the adjacent
// compare — i.e. plain non-volatile, NON-address-taken locals that the
// compiler always keeps in registers:
//   * with cur/head as ordinary pointer locals, the build emits the same
//     algorithm with NO stack slots at all, four saved GPRs and a 0x18
//     frame; want has three saved GPRs, slots at 8/0x10 and a 0x28 frame.
//     Every word from the prologue on is therefore shifted → 13.9-17%
//     ceiling regardless of body spelling.
//   * `volatile Elem *cur/head` DOES produce the two slots + the post-call
//     reloads, but (a) it also forces a reload for the loop test (want
//     compares the live registers) and (b) it packs the two 4-byte locals
//     at 8/0xC, not 8/0x10, and grows the body.
//   * Taking the address to force memory residency does not survive: both
//     `Elem **a = &cur; (void)a;` and a live `head == (Elem *)anchor` guard
//     are folded away by the front end, and the variable goes back to a
//     register (2.8-7.9%).
//   * A local 2-pointer array (`Elem *list[2]`) / a `for` loop / `do-while`
//     / the m2c sp8/sp10-named locals all behave identically (no slots).
//   * The 8-byte spacing of the two slots (8 and 0x10 rather than 8 and
//     0xC) suggests the two original locals were 8-aligned objects whose
//     first word is the pointer that gets stored — but no C spelling of
//     that (u64/double/union first word) was found that also keeps the
//     register compares want shows.
//   * Flags: -fno-expensive-optimizations / -fno-gcse / -fno-schedule-insns
//     / -fno-schedule-insns2 / -fno-sched-spec / -fno-caller-saves /
//     -fno-strength-reduce / -fno-rerun-cse-after-loop are ALL no-ops here.
// NEXT IDEA if this is ever re-picked: find another DOL function that
// reloads a plain (non-volatile) pointer local from 8(r1) between blocks —
// whatever C construct produced it there is the missing ingredient; this is
// very likely an inliner artifact (a `static inline` helper taking
// `Elem **` would mark the caller's local TREE_ADDRESSABLE while its body
// still compares register copies), which cannot be reproduced from a single
// function body.
#include "types.h"

typedef struct E6A6F0 { void *unk0x0; struct E6A6F0 *unk0x4; } E6A6F0;

void fn_80069EB8(void *arg0, void *arg1);

void fn_8006A6F0(void *arg0, void *arg1) {
    E6A6F0 *sp8;
    E6A6F0 *sp10;
    E6A6F0 *temp_r9;
    E6A6F0 *var_r0;
    E6A6F0 *temp_r11;
    void *temp_r0;

    temp_r9 = *(E6A6F0 **)arg0;
    var_r0 = 0;
    if (temp_r9 != 0) {
        var_r0 = temp_r9->unk0x4;
    }
    sp8 = var_r0;
    sp10 = temp_r9;
    if (var_r0 != temp_r9) {
        do {
            fn_80069EB8(sp8->unk0x0, arg1);
            temp_r0 = *(void **)arg0;
            temp_r11 = sp8->unk0x4;
            sp10 = (E6A6F0 *)temp_r0;
            sp8 = temp_r11;
        } while (temp_r11 != (E6A6F0 *)temp_r0);
    }
    *(__ps_t *)((char *)arg0 + 8) = *(__ps_t *)arg1;
    *(__ps_t *)((char *)arg0 + 0x10) = *((__ps_t *)arg1 + 1);
}
