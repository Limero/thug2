// WIP DRAFT (non-matching) — C body hand-written from the WANT (was m2c junk)
// family=m2c range=0x80015BDC-0x80015DE4 size=520B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// STATUS 2026-10-02 (w75/0x80015BDC): DIFF 10.8% positional (m2c was 21.5%).
// The body is now instruction-for-instruction the WANT except for the
// PROLOGUE, which is 8 bytes (2 words) SHORT — see the parking note below.
// With the object shifted past those 2 missing words 89/130 want words match;
// every block, both loops, all callee arities and the whole exit tree agree.
// The positional % is depressed purely by the index shift (same situation and
// same deliberate choice as src/wip/fn_800447B4.c at 14.1% and
// src/wip/fn_800BB02C.c): length beats shape per AGENTS-recipes §6cs-1.
//
// WHAT IT IS (recovered by reading the WANT, cross-checked against the
// sibling 0x8001593C draft's findings).  A CARDProbeEx retry loop (cap
// 999999) that mounts the memory card at `chan * 0xA000 + 0x80314660` and
// records its free size, all inside a ref-counted "banner" pool object:
//   BannerCheck(0) (0x80015870) returns the pool global lbl_802FFF6C and
//     bumps the count lbl_802FFF70; it is ONE-argument (m2c's `(0, lbl)`
//     phantom is wrong — that is what desynced the whole body).
//   fn_800158D8() (0x800158D8) is the matching release, called on every exit.
//   The pool's +0x24/+0x28 flags are cleared on entry and set on the error
//     paths; 0x2C bytes total (fn_800159B4 walks +0x18/+0xC with this same
//     32-byte stride, fn_8001593C clears a record's +0xC).
//
// WHY THE SHAPE IS WHAT IT IS (all load-bearing, measured):
//   * The 0x10-byte blob at sp+8 is ONE 16-byte local with two used fields:
//     +0x8 (the pool pointer) and +0xC (lbl_80290B50, written 4x and never
//     read).  It needs TWO base registers (r26 = &st, r27 = &st.tail) because
//     the +0x8 field is reached through the nested aggregate: a single walker
//     gives r1-relative displacements and a 4-word-short object.
//   * The retry loop is a `goto` cycle (count++, then the CARDProbeEx test),
//     which is what makes ngccc ROTATE it and keep `lis 0xf / ori 0x423f`
//     inside the loop body.  A `for(;;)`/while spelling leaves it unrotated
//     and hoists the 0xF423F compare into the preheader.
//   * The loop's `-2` arm is a `goto` to a label placed AFTER the -2/-0x80/-3
//     dispatch and BEFORE the redundant `> 0` re-test: that block ORDER is
//     what puts 0x80015C90 exactly where the WANT has it.
//   * The post-loop dispatch is m2c's nested shape (`perr == -2`, then
//     `perr <= -2` reusing the flags of the first cmpwi as a bare `bgt`, then
//     `-0x80 || -3`), not a flat if-chain.
//   * CARDCheck is called ONCE and its result kept in a local: the WANT tests
//     that one value twice (`or. r3,r3,r3` then `cmpwi r3,-6`); m2c's two
//     calls would be 6 words longer.  Naming it a local is also what turns the
//     `== 0` test into `or.` instead of `cmpwi r3,0`.
//   * The probe result and the CARDMount result must be TWO variables, not
//     one: only then does ngccc leave the CARDProbeEx result in r3 (no copy)
//     and give the counter and the mount result the shared r31, which is
//     exactly the WANT's 6 callee-saved registers.
//   * Addresses are symbol references (`extern char lbl_X[]` + `(s32)lbl_X`),
//     not literals: a literal folds to `lis;ori`, the WANT uses `lis;addi`.
//
// PARKED 2026-10-02 (w75/0x80015BDC): the object is 512 B, the WANT is 520 B.
// The 8 missing bytes are two prologue copies: at 0x80015C20 the want moves
// r30 into r26 (after building r30 from r1 plus 8), and at 0x80015C24 it
// moves r11 into r27 (after building r11 from r1 plus 0xc).
// i.e. local_alloc parks each blob base in a scratch (r30, and r11 which is
// caller-saved) and reload then moves it into its callee-saved home r26/r27
// before the loop's call.  Every spelling tried emits the base straight into
// its home (1 instruction), so the rest of the function sits 2 words low and
// the positional score collapses.  This is the §6ff "object N words short on
// an otherwise byte-perfect body = a coalesced/shifted web" class (same wall
// as fn_800447B4's dropped `mr r3,r0`); §6ff's two-variable cure did NOT fire
// here because the second base's copy is a genuine reload, not a coalescer
// deletion, so both pseudos must survive to the exits.
// Tried (all length-neutral or worse): p8 as a declaration initializer vs a
// separate statement; `char *` / `s32 *` / `void *` walkers; an array blob with
// `sp8[3]`-style indexed access vs a `Blob` struct with `&st`/`&st.tail`
// pointers (byte-identical); the nested-aggregate spelling with no walkers at
// all (r1-relative, 4 words short, frame 0x30); direct-field writes through the
// aggregate instead of through the pointer (loses the base register,
// `stw r9,0x14(r1)`); two names per base with the first used before the call
// and the second at the exits (§6ff shape, coalesced away); two `register s32`
// carriers with a forced second name each (516 B but needs 7 saved registers,
// frame 0x40, and the copy lands mid-prologue); 3-way `register s32
// __asm__("rN")` pins for pC/&sp18/&sp1C (correct colours for 4 of 6, still
// 512 B); a 4th pin for the counter (508 B, cc1 drops arg0 entirely); and the
// flags -fno-thread-jumps / -fno-gcse / -fno-expensive-optimizations /
// -fno-schedule-insns / -fno-cse-follow-jumps (all DIFF, 6.9-10.8%, none 520 B;
// -fno-crossjumping / -fno-reorder-blocks do not compile under ngccc).
// Also residual (each 1-4 words, all masked-equal today but they will matter
// once the length is fixed):
//   1. local_alloc COLOUR permutation of the 6 callee-saved registers.  GOT
//      p8=r26, &sp18=r27, &sp1C=r28, pC=r29, arg0=r30, count=r31; WANT
//      p8=r26, pC=r27, arg0=r28, &sp18=r29, &sp1C=r30, count=r31.  Pinning
//      pC to r27 (3 pins) fixes 1 of the 4 and costs nothing else.
//   2. Success-path scheduling: WANT hoists `lwz r0,0x18(r1)` / `lwz r11,0x1c(r1)`
//      above the `lbl_80290B50` store, GOT keeps them after it.  Neither
//      statement order (unk0x4-then-unk0x8 vs the reverse) gets both the load
//      order and the store order the WANT wants.
//   3. p8's store is `0xc(r26)` in both, but the WANT's own base is r30 before
//      the copy pair above — i.e. residual 1 and this are the same wall.
#include "types.h"
#include "structs.h"
extern char lbl_80290B50[];
extern char lbl_80314660[];
extern void fn_8001593C(s32);
extern s32 BannerCheck(s32);
extern void fn_800158D8(void);
extern s32 CARDProbeEx(s32, s32 *, s32 *);
extern s32 CARDMount(s32, void *, void *);
extern s32 CARDCheck(s32);

/* Pool object returned by BannerCheck (0x2C bytes, ref-counted by the globals
   lbl_802FFF6C / lbl_802FFF70); +0x24/+0x28 are the two status flags. */
typedef struct { char pad0x0[0x24]; s32 f24; s32 f28; } Pool;
/* The 0x10-byte out-param blob at sp+8.  Its +0x8 slot caches the pool pointer
   and its +0xC slot takes lbl_80290B50 (written four times, never read); the
   WANT reaches them through two different bases, &st and &st.tail. */
typedef struct { s32 x0; s32 pool; } BlobTail;
typedef struct { s32 f0; BlobTail tail; void *fc; } Blob;

s32 fn_80015BDC(Unk_C8FEE62D *arg0) {
    Blob st;
    Blob *ps = &st;
    BlobTail *pt = &st.tail;
    s32 sp18;
    s32 sp1C;
    s32 count;
    s32 perr;
    s32 merr;
    s32 chk;
    Pool *pool;

    ps->fc = (void *)lbl_80290B50;
    pool = (Pool *)BannerCheck(0);
    count = 0;
    pt->pool = (s32)pool;
    pool->f24 = 0;
    ((Pool *)pt->pool)->f28 = 0;
    goto loop_test;
loop_body:
    count++;
    if (count > 0xF423F) {
        goto out;
    }
loop_test:
    perr = CARDProbeEx(arg0->unk0x18, &sp18, &sp1C);
    if (perr == -3) {
        goto out;
    }
    if (perr == -2) {
        goto set_f28;
    }
    if (perr != 0) {
        goto loop_body;
    }
out:
    if (perr == -2) {
        goto block_31;
    }
    if (perr <= -2) {
        if ((perr == -0x80) || (perr == -3)) {
            goto block_12;
        }
        goto block_31;
    }
    goto mid;
set_f28:
    ((Pool *)pt->pool)->f28 = 1;
    goto out;
mid:
    if (perr <= 0) {
    block_12:
        if (arg0->unk0xC == 0) {
            arg0->unk0x10 = arg0->unk0xC;
            arg0->unk0xC = arg0->unk0x18 * 0xA000 + (s32)lbl_80314660;
            merr = CARDMount(arg0->unk0x18, (void *)arg0->unk0xC, (void *)fn_8001593C);
            if (merr == -6) {
                if (CARDCheck(arg0->unk0x18) == -5) {
                    arg0->unk0x10 = 1;
                }
            }
            if ((merr == 0) || (merr == -6) || (merr == -0xD)) {
                chk = CARDCheck(arg0->unk0x18);
                if ((chk == 0) || (chk == -6) || (merr == -0xD)) {
                    ps->fc = (void *)lbl_80290B50;
                    arg0->unk0x4 = sp18;
                    arg0->unk0x8 = sp1C;
                    goto block_30;
                }
            }
            if (merr == -5) {
                ((Pool *)pt->pool)->f24 = 1;
                goto block_28;
            }
            if (merr == -0x80) {
                ((Pool *)pt->pool)->f24 = 1;
                goto block_28;
            }
            if (merr == -2) {
                ((Pool *)pt->pool)->f28 = 1;
                goto block_28;
            }
        block_28:
            arg0->unk0xC = 0;
            goto block_31;
        } else {
            goto block_30;
        }
    } else {
        goto block_31;
    }
block_30:
    ps->fc = (void *)lbl_80290B50;
    fn_800158D8();
    return 6;
block_31:
    ps->fc = (void *)lbl_80290B50;
    fn_800158D8();
    return 0;
}
