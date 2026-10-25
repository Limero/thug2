// PARKED 2026-10-03: DIFF, masked 18.18%, object 660B vs want 684B
// (6 words SHORT — per AGENTS §5 the positional pct is meaningless until the
// length matches; treat 18% as noise, not merit). Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8012A958
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/want_vs_got.py 0x8012A958
// Baseline was FAIL (`strcmp` called with s32 args, fn_80128FF4 undeclared) —
// so this is strictly an improvement, and the switch dispatch is now
// opcode-identical to the want for its first 30 instructions.
//
// WHAT IS ALREADY BYTE-EXACT (do not regress these):
//  * Prologue + both `fn_8012A8F0` calls + frame (0x28, locals t1@8 v1@c t2@10
//    v2@14, double scratch @18) — exact.
//  * The switch dispatch tree, all 30 instructions, in order. This required
//    THREE explicit empty cases the m2c draft dropped: `case 0:`, `case 8:`
//    and `case 9:` (all just `break`). Without them GCC emits only 26 insns
//    and splits the tree at 5/6 instead of 6/7. Adding them took the object
//    from 668B to exactly 684B.
//  * Case 1 and case 2's `(f32)int == f32` blocks (13 insns each) — the magic
//    int->float sequence `xoris / lis 0x4330 / stw / stw / lfd / fsub / frsp`
//    with the shared rodata double 0x4330000080000000 = 2^52+2^31 at 0x8029E658.
//  * Case 2's `t2==1` compare MUST be written `v1.f == (f32)v2.i`, not
//    `(f32)v2.i == v1.f`: the want's fcmpu operand order is REVERSED
//    (`fcmpu cr7,f12,f0` vs case 1's `fcmpu cr7,f0,f12`), and that difference
//    is the ONLY thing stopping GCC from cross-jumping the two identical
//    8-instruction tails into one shared block. Worth remembering generally:
//    a one-word operand swap is load-bearing against tail merging.
//  * float `==` materialised as a value is `fcmpu cr7; mfcr r3;
//    rlwinm r3,r3,31,31,31` on ProDG (bit 31 = cr7's SO bit — a ProDG quirk,
//    but fully deterministic). Applies to cases 2/5/6.
//  * Recipe 100 confirmed: `x == 0` folds to `xor/subfic/adde`, `x != 0`
//    stays branchy. Cases 3/4 (`strcmp(...) == 0`) and 7 (`v1.i == v2.i`)
//    now emit the want's `subfic r0,r3,0; adde r3,r0,r3` exactly.
//
// THE WANT IS SEMANTICALLY WEIRD AND THE BODY REPRODUCES THAT:
//  * `case 13` is dead. `cmpwi r0,0xd; b 0x8012ab80` jumps PAST case 7's
//    `cmpwi r0,7` onto its `bne default`, so the t2!=13 path re-tests the
//    flags of `cmpwi r0,1`/`cmpwi r0,0xd` and always returns 0; the t2==13
//    path falls through into case 5's head (13 != 5) and also returns 0.
//    Same trick on case 1 -> case 7. Hence the `goto case7` (which lands
//    after the compare) rather than a `break`.
//  * `case 1` falls through into `case 2`, `case 3` into `case 4`, and
//    `case 13` into `case 5`.
//
// REMAINING DIFF (the 6 missing words + block placement):
//  1. t2 register allocation. WANT reloads `lwz r0,0x10(r1)` inside every case
//     block; GCC hoists it into the dispatch (2 extra insns at dispatch+0x38
//     and +0x54) and copies it with `mr r9,r0` at the head of cases 1 and 13,
//     so cases 5/6/7 test `cmpwi r9,N` instead of `cmpwi r0,N`. Mine's
//     dispatch is 32 insns vs the want's 30. Unfixed: I could not find a C
//     spelling that stops the hoisting (plain scalars, and `s32 r = 0` in
//     cases 5/6, both hoist).
//  2. Cases 5/6 want `li r3,0` hoisted INSIDE the block (right after the first
//     payload `lwz`) with `bne -> epilogue`; mine materialises it in an
//     out-of-line `li r3,0; b epilogue` block, +2 words net. Writing the
//     early-0 as `s32 r = 0; ... return r;` (m2c's shape) changed nothing.
//  3. Case 2's `v1.f == v2.f` tail: WANT inlines it (9 insns at 0x8012AA98);
//     mine cross-jumps to a shared `fcmpu/mfcr/rlwinm/b` block.
//
// RULED OUT (so the next agent doesn't repeat):
//  * `strcmp` prototype variants (`int`/`s32`, `char*`/cast forms) — all
//    compile; only `== 0` yields the want's subfic/adde.
//  * `!= 0`, `? 1 : 0`, `!!x`, `u8` return, `0 != x`, `int r = ...; return r`
//    for the bool folds — every one compiles branchy. `== 0` is the only form.
//  * `s32` vs `f32` fields in the case-5/6 Vec struct (f32 is right: the want
//    uses `fcmpu cr0` + `bne`, not `cmpw`).
//  * Adding `case 11:` — not needed, the 11 gap is covered by one `b`.
//
// MOST PROMISING NEXT IDEA: the t2 hoisting (item 1) is worth one more shot
// via a struct-of-locals (`struct { s32 t; Val v; } A, B;` with `A.t`/`B.v.*`).
// A standalone probe confirmed that form still yields t@8 v@c t@10 v@14, so
// the frame is safe; struct field loads may defeat GCC's cross-block caching
// of t2 in a register and remove the `mr r9,r0` + hoisted `lwz`.
//
// WIP DRAFT (non-matching) — hand-reconstructed from the want disassembly.
// family=m2c range=0x8012A958-0x8012AC04 size=684B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
extern int strcmp(const char *, const char *);

typedef union {
    s32 i;
    f32 f;
    void *p;
} Val;

typedef struct {
    f32 x, y, z;
} Vec;

void fn_8012A8F0(void *, s32 *, s32 *);
s32 fn_80128FF4(s32);

s32 fn_8012A958(void *a, void *b) {
    s32 t1, t2;
    Val v1, v2;

    fn_8012A8F0(a, &t1, &v1.i);
    fn_8012A8F0(b, &t2, &v2.i);

    switch (t1) {
    case 0:
        break;
    case 1:
        if (t2 == 2) {
            return (f32)v1.i == v2.f;
        }
        if (t2 != 1) {
            goto case7;
        }
    case 2:
        if (t2 == 1) {
            return v1.f == (f32)v2.i;
        }
        if (t2 != 2) {
            break;
        }
        return v1.f == v2.f;
    case 3:
        if (t2 != 3) {
            goto case4;
        }
    case4:
    case 4:
        if (t2 != 4) {
            break;
        }
        return strcmp((char *)v1.p, (char *)v2.p) == 0;
    case 13:
        if (t2 != 13) {
            goto case7;
        }
    case 5:
        if (t2 != 5) {
            break;
        }
        if (((Vec *)v1.p)->y != ((Vec *)v2.p)->y) {
            return 0;
        }
        return ((Vec *)v1.p)->z == ((Vec *)v2.p)->z;
    case 6:
        if (t2 != 6) {
            break;
        }
        if (((Vec *)v1.p)->y != ((Vec *)v2.p)->y) {
            return 0;
        }
        if (((Vec *)v1.p)->z != ((Vec *)v2.p)->z) {
            return 0;
        }
        return ((Vec *)v1.p)->x == ((Vec *)v2.p)->x;
    case 7:
    case7:
        if (t2 != 7) {
            break;
        }
        return v1.i == v2.i;
    case 8:
    case 9:
        break;
    case 10:
        if (t2 != 10) {
            break;
        }
        if (v1.i != v2.i) {
            break;
        }
        return 1;
    case 12:
        if (t2 != 12) {
            break;
        }
        if (v1.i == v2.i) {
            return 1;
        }
        return fn_80128FF4(v1.i);
    }
    return 0;
}