// WIP DRAFT (non-matching) — hand-rewritten from tools/fill_wip_drafts.py output
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 74.3243% -> 75.6757% per-object flags: -O2 -> -Os
// family=m2c range=0x8007A108-0x8007A230 size=296B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-02 (w75/0x8007A108): 3.9% DIFF -> 74.3% NEAR. 285 of the 296
// want bytes now match (verified word-by-word with tools/want_got.py); the
// object is exactly 1 WORD (4 B) SHORT of the want and the ONLY difference is
// the loop preheader. The want branches to the exit on the bound test and
// then copies the fill value into a dedicated loop register before
// materialising 1 for the latch, so the loop body stores that loop register
// to both destinations. The current output skips that copy and stores the
// shared value register to both destinations directly. Concretely the want
// orders the exit branch, then the copy of r26 to r4, then the
// materialisation of 1 in r10, then stores of r4 to 0 of r31 through 0 of
// r28 in the loop, while the output orders the exit branch, then the
// materialisation of 1 in r10, then stores of r26 to 0 of r31 through 0 of
// r28 in the loop.
//
// `li r10,1` (ngccc's loop-invariant materialisation of the literal 1 used by
// the latch's `1 << w`) IS reproduced by GOT, so the loop pass is active; it
// simply does not decide that the fill value also needs its own loop register.
// Since both stores use the SAME preheader-copied register, the want's `v` must
// be a SEPARATE web from the one that feeds the two `sv[0] = v` stores — ngccc
// merges `f = v;` copies back into one web (tried: `f = v` before the loop, at
// function entry, inside the loop body, and with loop-local pointer/value names
// — all fold to `stw r26`).  ngccc's per-phase web split (§6cw-(b)) that would
// keep them apart is not reachable from plain C here without a pin.
//
// Load-bearing choices (each is worth instructions; do not undo):
//   * NO `-Os`: measured -O2 74.3%, -Os 75.7% (but -Os also re-schedules the
//     latch's `li 1` into the body, so -O2 is the structurally correct match),
//     -O1 18.9%, -O3 74.3%.  Kept `-O2` (= project default).
//   * `volatile s32 sv[1]` for the value handed to fn_80079028.  The scalar
//     `s32 sv;` gets `&sv` HOISTED into a 7th callee-saved reg (r28): frame
//     0x30/stmw r25 instead of 0x28/stmw r26 and `mr r5,r28` at both call
//     sites instead of `addi r5,r1,8` (recipes §6al-180 / §6dn).  A
//     non-volatile `sv[1]`/`sv[2]` array does NOT fix it (still homed, 16.2%) —
//     only `volatile` does.
//   * The store `sv[0] = v;` must sit BETWEEN the two `fn_79028` calls in the
//     source: that store is what makes ngccc reload `o->dim->w`/`o->dim->h` for
//     each call's arguments instead of reusing the temps (want re-loads
//     `lbz r6,7(r11)` / `lbz r4,6(r11)` before call 1 — got reuses the regs).
//   * `(u16)(1 << o->dim->w)` must be spelled INLINE (five sites) and used TWICE
//     in the pointer math: `b = a + (((u16)(1<<w)) << 2) - 4` and
//     `c = a + ((((u16)(1<<w)) * ((u16)(1<<h) - 1)) << 2)`.  The second use is
//     the SECOND, INSTRUCTION-FREE CONSUMER the 0x80079300 write-up was looking
//     for: it forces `slw / clrlwi ..0x10 / slwi ..,2` to stay three separate
//     instructions instead of ngccc's usual single fused
//     `rlwinm rX,rX,2,0xe,0x1d` (a single-use u16 always fuses).  Confirmed:
//     with the two uses removed the step becomes one `rlwinm` and the score
//     collapses.  This is the same mechanism as 0x80079300's residual (a).
//   * `while` (NOT `if`+`do/while`): want's entry test is `cmpw r11,r29 / bge`
//     (i vs the recomputed bound), not `cmpwi rN,0 / beq`.
//   * `b = a + (((u16)(1<<w)) << 2) - 4)` needs the `-4` INSIDE, so ngccc emits
//     `slwi r30,r30,2 / addi r30,r30,-4 / add r30,r31,r30`; writing
//     `a + ((...)<<2) - 4` reassociates to `add` then `addi -4`.
//   * `fn_80079028` prototyped `(s32 *, s32, s32 *, s32)` (matches the matched
//     sibling src/fn_80079028.c); the u16 casts on args 2/4 are what give the
//     `clrlwi`s before the `bl`s.  4 args — a 3-arg prototype loses the `r6`.
//   * `Sub::off` is `s16` (`lha`), `Sub::get` is a prototyped fn-ptr (`mtlr` +
//     `blrl`), `Dim::w`/`Dim::h` are `u8` (`lbz`).
//   * `a`,`b`,`c` are BYTE (`u8 *`) pointers: the loop stores are
//     `*(s32 *)a`/`*(s32 *)c` with `a += 4`.  Element pointers delete the
//     `slwi r30,r30,2`.
//
// UPDATED 2026-10-03: attacked the single missing `mr r4,r26` with
// doc 85's alias-pin recipe and 20 variants. NOT reachable from C; recording
// the ruled-out set so the next pass does not repeat it.
//   It IS the doc-85 "two homes for one value" shape: `v` lives in r26 and the
//   loop body needs a second home.  Pinning the COPY to r4 (`register s32 fv
//   __asm__("r4")`) DOES emit the copy and DOES make the object the right
//   296 B, but it cascades the whole allocation: arg0 then takes r26 and `v`
//   r28, so every one of the 19 words that use them shifts (74.3% at the right
//   length, i.e. no gain).  Pinning the HOME instead (`v` -> r26) changes
//   nothing at all (still 292 B) because r26 is already its register - the
//   exact doc-85 trap.
//   Measured and ruled out: plain named copy `fv = v` before the loop (292 B),
//   the copy placed after the second call (292 B), copy inside the loop guard
//   (292 B), do-while shape (7 words short), `*vp` re-read in the loop (6.8%),
//   `sv[0]` round-trip (58.1%), `volatile s32` store lvalues (292 B),
//   `fv` re-tested after the loop (folded), a zero-code split-web barrier on
//   `fv` (296 B but 68.9%), and pin COMBINATIONS that hold the other homes
//   still (r27 on arg0 + r4 on the fill = 45.9%; adding r26 on `v` = 51.4%).
//   The loop register is r31/r28 in retail and got already agrees there, so the
//   only free variable is r4 -- and pinning it is precisely what cascades.
//   Conclusion: this is the doc-74-161c brittle-allocator wall, not a
//   missing-semantics one.  Leave the honest 75.3% body in place.

#include "types.h"
#include "structs.h"
// FLAG: -Os

extern void fn_80079028(s32 *, s32, s32 *, s32);

typedef struct Obj Obj;
typedef struct Sub Sub;
typedef struct Dim Dim;

struct Sub {
    u8 pad_0x158[0x158];
    s16 off;          /* +0x158, read with lha */
    u8 *(*get)(u8 *); /* +0x15C, called via mtlr/blrl */
};

struct Dim {
    u8 pad_0x6[6];
    u8 w; /* +6: log2 of the row word count */
    u8 h; /* +7: log2 of the row count      */
};

struct Obj {
    s32 pad_0x0;
    s32 pad_0x4;
    Sub *sub; /* +0x8 */
    Dim *dim; /* +0xC */
};

s32 fn_8007A108(Obj *o, s32 *vp) {
    s32 v;
    s32 i;
    u8 *a;
    u8 *b;
    u8 *c;
    volatile s32 sv[1];

    v = *vp;
    a = o->sub->get((u8 *)o + o->sub->off);
    b = a + ((((u16)(1 << o->dim->w)) << 2) - 4);
    c = a + (((((u16)(1 << o->dim->w)) * (((u16)(1 << o->dim->h)) - 1))) << 2);
    sv[0] = v;
    fn_80079028((s32 *)a, (u16)(1 << o->dim->w), sv, (u16)(1 << o->dim->h));
    sv[0] = v;
    fn_80079028((s32 *)b, (u16)(1 << o->dim->w), sv, (u16)(1 << o->dim->h));
    i = 0;
    while (i < (u16)(1 << o->dim->w)) {
        *(s32 *)a = v;
        i++;
        *(s32 *)c = v;
        a += 4;
        c += 4;
    }
    return 1;
}
