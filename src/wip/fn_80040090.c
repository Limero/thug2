// PARKED 2026-10-05 (w2_80040090): NEAR **93.83%** (20/324 words masked-differ,
// object size exactly 1296B = the symbol size, so the size gate PASSES).
// Reproduce: LEAF_TMPDIR=<scratch> \
//   tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80040090
//   tools/venv/bin/python tools/score_wip.py 0x80040090 src/wip/fn_80040090.c
// Up from the previous 79.01% parked state.  Four fixes, all measured:
//
//  1. EVERY callee needs a real prototype (from the previous round; the m2c
//     draft called ~20 unprototyped functions, so ngccc emitted `crclr cr1eq`
//     before each `bl` -- 7.4% -> 77.8% on its own).  Arity was read off each
//     callee's retail prologue / the sibling src/wip/CScreenElement_SetMorph.c.
//  2. The stack frame is fully decoded and reproduced: want frame 0xa8, local
//     area 0x08..0x8b.  Six 0x10 aggregates (Pair 0x08, V4 0x18, V4 0x28,
//     Pair 0x38, Ref 0x48, Ref6 0x58..0x6f) then seven scalars
//     (Just 0x70/0x74, 0x78, 0x7c, 0x80, 0x84, 0x88).
//     MEASURED RULE (verified with a synthetic probe, not guessed):
//     ngccc slots AGGREGATES first, in declaration order, each rounded up to a
//     multiple of 8; address-taken SCALARS next, in the order their address is
//     first TAKEN (== statement order), NOT declaration order -- swapping the
//     declarations of two scalars produces byte-identical output.
//     That is why the rgba temp (0x68) and the QB_PARENT out-param (0x6c) must
//     live INSIDE the 0x58 aggregate (`Ref6 sp58` members .e/.f): as separate
//     scalars their slots land at 0x78/0x68 and everything from 0x68 on shifts.
//
//  3. QB_JUST (79.0 -> 91.1 on its own).  NEW RECIPE, worth remembering:
//     **a duplicate `li` for two adjacent zero stores only happens when the
//     zeros come from a DECLARATOR INITIALISER, never from assignment
//     statements.**  Measured on a probe: `just[0]=0; just[1]=0;` (also as
//     `s32[2]`, `struct{s32,s32;}`, union-member writes, two separate scalars,
//     and every `volatile` spelling) ALL fold to a single `li r0,0` feeding
//     both `stw`, while `Just just = { { 0, 0 } };` emits `li r9,0` +
//     `li r10,0` into two different registers -- exactly want
//     (0x80040268 `li r9,0`, 0x80040270 `li r10,0`, `stw r9,0x70(r1)`,
//     `stw r10,0x74(r1)`).  Two constraints: (a) the initialiser must be in a
//     NESTED BLOCK -- at function scope GCC expands it into the ENTRY block and
//     the stores land next to the prologue; (b) the pair is written as integer
//     zeros but read as floats, so the declared type is a `union` whose first
//     member is the `s32` struct (that takes the initialiser) and whose second
//     member is the `f32` struct (that is what every use site reads, no casts).
//
//  4. QB_PARENT zero stores: give the aggregate a NAMED POINTER and write the
//     fields through it (`Ref6 *p58 = &sp58; p58->a = 0; p58->b = 0; ...`).
//     GCC's `combine` then rewrites the two `stw r27,0x5c(r1)/0x60(r1)` into
//     `stw r27,4(r30)/8(r30)` off the pointer's register.  Without the pointer
//     want's `4(r30)`/`8(r30)` form is unreachable.
//
//  5. QB_FLIP_H / QB_FLIP_V: write the flag update as a store in BOTH arms
//     (`*(s32*)(arg0+0xC) = *(s32*)(arg0+0xC) | 0x02000000;`) instead of
//     through a temp.  The two identical arm tails then get merged by
//     cross-jumping, which lands the single `stw r0,0xc(r31)` BEFORE the next
//     call's `lis r4` -- want's order.  With the temp variable ngccc hoists the
//     `lis` above the store (doc 15 family).  91.7 -> 93.8 together with #6.
//
//  6. QB_ROT_ANGLE: `f32 b = lbl_80292328;` inside the arm makes the divisor a
//     register (one `lfs`, reused by both `fdivs`), and hoisting the flag store
//     `|= 0x400` to the TOP of the arm's statement list re-aligns the block.
//     Both are load-bearing for the SIZE GATE: this cluster is exactly one word
//     SHORTER than want once the divisor is registerised, which is what pays for
//     the +1 word the QB_JUST declarator costs.  Fixing either alone gives
//     1292B or 1300B and the score collapses to ~14%.
//
// RESIDUAL (20 words), two clusters:
//
//  A. QB_ROT_ANGLE block, 12 words (0x80040314..0x8004034C, 15 words long,
//     count-exact).  want holds the angle in f13, PI in f12 and 180.0f in f11
//     -- each loaded ONCE and live across the whole block -- and still
//     duplicates the arithmetic (`fmr f0,f13` + 2x fmuls + 2x fdivs).
//     got reloads PI for the second chain and therefore needs 4 `lfs` + 2 `lis`
//     where want has 3 `lfs` + 2 `lis` + 1 `fmr`; the chain order also differs.
//     This is a genuine ngccc/ProDG 3.9.3 codegen wall, and the earlier round's
//     "not reachable from plain C" conclusion is now mechanistically explained:
//     GCC 2.95 tree-level CSE has exactly two reachable states here --
//       (a) constants as non-address-taken `f32` locals  => the CSE tracks the
//           DECLs across the flag store, so the WHOLE expression folds: one
//           `fmuls` + one `fdivs`, 13 words, -4 (measured; this is what the
//           previous round's "`extern const f32`" spelling also did); or
//       (b) constants as plain `extern f32`  => the flag store may alias the
//           globals, so both constants are RELOADED for the second chain:
//           17 words, +2 (measured, the 91.05% state).
//     "loads CSE'd but arithmetic duplicated" needs the two expressions in two
//     basic blocks (GCC 2.95 does not propagate expression CSE across blocks;
//     only register equivalences), which requires a branch want does not have.
//     VERIFIED AND RULED OUT here: nested `{ }` and `do{}while(0)` around the
//     second store (both flattened to one block, full CSE); a `volatile` flag
//     store and `__asm__ __volatile__("" ::: "memory")` (neither defeats the
//     tree CSE when the operands are locals -- y1/y4/y5 probes); an asymmetric
//     pair `sp7C*a/b` vs `vv*a/b` with `vv` a promoted local (tree CSE substitutes
//     the local's value and folds anyway); making BOTH constants locals;
//     making the MULTIPLIER the local instead of the divisor (1292B, -1);
//     `extern const f32` on either/both; `-fno-expensive-optimizations`,
//     `-fno-gcse`, `-fno-cse-follow-jumps`, `-fno-thread-jumps`, `-O1`,
//     `-fno-schedule-insns`, `-fno-schedule-insns2` (all re-measured on the
//     current body, none better than the flagless default).  The three statement
//     orderings that keep the size gate were all measured (flag first 93.8%,
//     flag last 93.5%, flag between 92.9%).
//
//  B. QB_PARENT, 8 words (0x800401D8..0x80040200).  Pure ngccc scheduling:
//     want's `addi r30, r1, 0x58` (the `&sp58` web) and its `li r27, 0` are
//     both materialised AFTER the ResolveComplexID / GetElement_2 calls -- want
//     even leaves the pre-call slot at 0x800401D8 EMPTY.  got hoists the `addi`
//     into that empty pre-call slot of the *ResolveComplexID* call (3 slots
//     earlier than want) and the `li r27,0` into the pre-call slot of
//     GetElement_2 instead of the post-call slot.  The one-word shift is why 6
//     of the 8 diffs are "wrong but self-consistent" instructions; the same
//     shift is what `br_targets.py` reports as its 2 branch differences (the
//     `beq` moves from 0x800401E0 to 0x800401E4, SAME target 0x80040268).
//     RULED OUT: doc 88's two-register-webs recipe (`Ref6 *p58` + `q58 = p58`
//     as the first statement) -- it makes ngccc allocate a THIRD saved register
//     for the pointer, grows the frame and drops the body to 3.1%/1300B;
//     `p58` at function scope (same failure, r28/r30 swap);
//     `p58 = (Ref6 *)((char *)&sp48 + 0x10)` and a `char *` bridge to create a
//     dependency that would block the hoist (combine normalises it straight back
//     to `addi r1+0x58` and the scheduler still hoists);
//     `register Ref6 *p58 __asm__("r30")` (1248B, frame collapse);
//     declaration/assignment moved after GetElement_2, `sp58.p` first, pointer
//     used for only the zero stores, `sp58.a/b = 0` swapped, or the zero stores
//     via `(char *)p58 + 4`.
//
// NOT a size problem, not a prototype/typing problem, not a reloc problem any
// more: the whole instruction stream is 1:1 and in order with want from
// 0x80040090 to 0x800401D4, from 0x80040204 to 0x80040310 (except the 2 known
// cluster-B words), and from 0x80040350 to 0x8004059C.  The three
// `extern f32 lbl_802923xx` loads are correctly emitted as
// `lis r9,0` + `lfs f0,0(r9)` (R_PPC_ADDR16_HA/LO -- the linker fills
// 0x8029/0x2320 and the LINKED bytes are identical); `score_wip.py` masks the
// `lis` top half AND the `lfs` displacement, so they are not residual.  A raw
// `*(f32 *)0x80292320` literal was measured earlier and forces lis+ori+lfs
// (3 words), blowing the size gate -- the symbol form is correct.
// WIP DRAFT (non-matching) -- INERT: not registered in splits.txt/configure.py.
// family=m2c range=0x80040090-0x800405A0 size=1296B
#include "types.h"
#include "qb_constants.h"

// want 0x08 (12B, slot rounded to 0x10): out-param of fn_80125000/GetPair,
// whose floats are read at +4/+8.
typedef struct { u32 u; f32 x; f32 y; } Pair;
// want 0x18 and 0x28 (0x10): GetVector out-params (4 floats).
typedef struct { f32 x, y, z, w; } V4;
// want 0x48 (0x10): GetElement_2 out-param, later released.
typedef struct { void *p; s32 a; s32 b; s32 c; } Ref;
// want 0x58..0x6f (0x14, slot rounded to 0x18).  Members .p/.a/.b are the
// add-ref link struct; .e is the rgba temp (want slot 0x68) and .f is the
// QB_PARENT out-param (want slot 0x6c).
typedef struct { void *p; s32 a; s32 b; s32 c; s32 e; s32 f; } Ref6;
// want 0x70 (0x8): the QB_JUST out-param pair.  Written as integer zeros
// (`stw r9,0x70(r1)` / `stw r10,0x74(r1)`) and read back as floats, so the
// punned pair is declared as a union -- the integer member takes the
// initialiser and the float member is what every use site reads.
typedef union {
    struct { s32 x, y; } i;
    struct { f32 x, y; } f;
} Just;

extern f32 lbl_8029231C;
extern f32 lbl_80292320;
extern f32 lbl_80292324;
extern f32 lbl_80292328;

void fn_80125000(void *);
s32 GetPair(void *, s32, Pair *, s32);
s32 GetVector(void *, s32, V4 *, s32);
s32 GetFloat(void *, s32, f32 *, s32);
s32 GetInteger(void *, s32, s32 *, s32);
s32 GetChecksum_2(void *, s32, s32 *, s32);
s32 ContainsFlag(void *, s32);
s32 ResolveComplexID(void *, void *, s32, void *);
s32 GetElement_2(void *, void *, s32, s32);
void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);
void fn_8004AEF4(void *, void *, void *, s32);
void CScreenElement_SetPos(void *, s32, f32, f32);
void fn_8003F80C(void *, void *, s32);
void fn_8003F93C(void *, s32, f32, f32);
s32 CScreenElement_resolve_just(void *, void *, s32, f32 *, f32 *);
void fn_8003F9C0(void *, f32, f32);
s32 CScreenElement_resolve_rgba(void *, void *, s32, s32 *);
void CScreenElement_SetRGBA(void *, s32 *, s32);
void fn_8003FDDC(void *, f32);
void fn_8003FDF0(void *, s32);
void SetChecksumTag(void *, s32, s32);
void RemoveFlagTag(void *, s32);
void fn_8009E6D8(void *, void *);

void CScreenElement_SetProperties(void *arg0, void *arg1) {
    Pair sp8;
    V4 sp18;
    V4 sp28;
    Pair sp38;
    Ref sp48;
    Ref6 sp58;
    s32 sp78;
    f32 sp7C;
    f32 sp80;
    s32 sp84;
    s32 sp88;
    s32 temp_r26;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;

    temp_r26 = *(s32 *)((char *)arg0 + 0x10);
    fn_80125000(&sp8);
    if (GetPair(arg1, QB_POS, &sp8, 0) != 0) {
        CScreenElement_SetPos(arg0, 1, sp8.x, sp8.y);
    } else if (GetVector(arg1, QB_POS, &sp18, 0) != 0) {
        CScreenElement_SetPos(arg0, 1, sp18.x, sp18.y);
    }
    if (GetVector(arg1, QB_POS3D, &sp28, 0) != 0) {
        sp28.w = lbl_8029231C;
        fn_8003F80C(arg0, &sp28, 1);
    }
    if (ContainsFlag(arg1, QB_NO3DSCALING) != 0) {
        *(s32 *)((char *)arg0 + 0xC) |= 0x800000;
    }
    fn_80125000(&sp38);
    if (GetPair(arg1, QB_DIMS, &sp38, 0) != 0) {
        fn_8003F93C(arg0, 1, sp38.x, sp38.y);
    }
    if (ResolveComplexID(temp_r26, arg1, QB_PARENT, &sp58.f) != 0) {
        Ref6 *p58 = &sp58;
        GetElement_2(&sp48, temp_r26, sp58.f, 0);
        p58->a = 0;
        p58->b = 0;
        p58->p = arg0;
        if (arg0 != NULL) {
            CObject_AddRefLink(arg0, p58);
        }
        fn_8004AEF4(temp_r26, &sp48, p58, 1);
        if (sp58.p != NULL) {
            CObject_RemoveRefLink(sp58.p, &sp58);
            sp58.p = NULL;
        }
        if (sp48.p != NULL) {
            CObject_RemoveRefLink(sp48.p, &sp48);
            sp48.p = NULL;
        }
    }
    {
        Just just = { { 0, 0 } };
        if (CScreenElement_resolve_just(arg0, arg1, QB_JUST, &just.f.x, &just.f.y) != 0) {
            fn_8003F9C0(arg0, just.f.x, just.f.y);
        }
    }
    if (CScreenElement_resolve_rgba(arg0, arg1, QB_RGBA, &sp78) != 0) {
        sp58.e = sp78;
        CScreenElement_SetRGBA(arg0, &sp58.e, 1);
    }
    sp7C = lbl_80292320;
    if (GetFloat(arg1, QB_ROT_ANGLE, &sp7C, 0) != 0) {
        f32 b = lbl_80292328;
        *(s32 *)((char *)arg0 + 0xC) |= 0x400;
        *(f32 *)((char *)arg0 + 0x10C) = (sp7C * lbl_80292324) / b;
        *(f32 *)((char *)arg0 + 0xC4) = (sp7C * lbl_80292324) / b;
    }
    if (ContainsFlag(arg1, QB_PRESERVE_LOCAL_ORIENTATION) != 0) {
        *(s32 *)((char *)arg0 + 0xC) |= 0x01000000;
    }
    if (ContainsFlag(arg1, QB_FLIP_H) != 0) {
        *(s32 *)((char *)arg0 + 0xC) = *(s32 *)((char *)arg0 + 0xC) | 0x02000000;
    } else {
        *(s32 *)((char *)arg0 + 0xC) = *(s32 *)((char *)arg0 + 0xC) & 0xFDFFFFFF;
    }
    if (ContainsFlag(arg1, QB_FLIP_V) != 0) {
        *(s32 *)((char *)arg0 + 0xC) = *(s32 *)((char *)arg0 + 0xC) | 0x04000000;
    } else {
        *(s32 *)((char *)arg0 + 0xC) = *(s32 *)((char *)arg0 + 0xC) & 0xFBFFFFFF;
    }
    if (GetFloat(arg1, QB_Z_PRIORITY, &sp80, 0) != 0) {
        fn_8003FDDC(arg0, sp80);
    }
    if (ContainsFlag(arg1, QB_NOT_FOCUSABLE) != 0) {
        SetChecksumTag(arg0, 0, QB_TAG_NOT_FOCUSABLE);
    } else if (ContainsFlag(arg1, QB_FOCUSABLE) != 0) {
        RemoveFlagTag(arg0, QB_TAG_NOT_FOCUSABLE);
    }
    if (GetChecksum_2(arg1, QB_LOCAL_ID, &sp84, 0) != 0) {
        SetChecksumTag(arg0, QB_TAG_LOCAL_ID, sp84);
    }
    if (ContainsFlag(arg1, QB_UNPAUSE) != 0) {
        fn_8003FDF0(arg0, 0);
    }
    if (ContainsFlag(arg1, QB_BLOCK_EVENTS) != 0) {
        var_r0_3 = *(s32 *)((char *)arg0 + 0xC) | 0x200000;
    } else if (ContainsFlag(arg1, QB_UNBLOCK_EVENTS) != 0) {
        var_r0_3 = *(s32 *)((char *)arg0 + 0xC) & 0xFFDFFFFF;
    } else {
        goto block_45;
    }
    *(s32 *)((char *)arg0 + 0xC) = var_r0_3;
block_45:
    if (ContainsFlag(arg1, QB_HIDE) != 0) {
        var_r0_4 = *(s32 *)((char *)arg0 + 0xC) | 0x400000;
    } else if (ContainsFlag(arg1, QB_UNHIDE) != 0) {
        var_r0_4 = (*(s32 *)((char *)arg0 + 0xC) & 0xFFBFFFFF) | 0x1000;
    } else {
        goto block_50;
    }
    *(s32 *)((char *)arg0 + 0xC) = var_r0_4;
block_50:
    if ((GetInteger(arg1, QB_PRIORITY, &sp88, 0) != 0) && (sp88 > 0)) {
        *(s32 *)((char *)arg0 + 0x18C) = sp88;
        *(s32 *)((char *)arg0 + 0xC) |= 0x10000000;
    }
    fn_8009E6D8(arg0, arg1);
}