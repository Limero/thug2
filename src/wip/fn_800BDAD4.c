// WIP DRAFT (non-matching) — src/wip/fn_800BDAD4.c
// family=m2c range=0x800BDAD4-0x800BDD7C size=680B
//
// PARKED 2026-10-03: DIFF 33.5% masked (57/170 words), object 676B vs
// want 680B.  Reproduce:
//   LEAF_TMPDIR=<private dir> tools/venv/bin/python tools/ps_diff.py 0x800BDAD4 680
//   (test_wip_drafts.py --addr 0x800BDAD4 only prints the DIFF bucket; ps_diff
//   prints the % and the want|got pairing.)
// Baseline this round was DIFF 22.4% / 660B.
//
// WHAT THE FUNCTION IS (hand-decoded; ps_disasm stalls on the PS words, and
// tools/ps_diff.py's dec() is the decoder that labels them correctly —
// `lis`/`ori` immediates printed by ps_disasm are sign-flipped, ignore them):
//   picks a 24-bit ARGB colour from arg0+0x114 (0/1/2), then emits translated
//   quads built from three 0x10-stride __ps_t point tables:
//     loop 1  n = arg0+0x94 : NESTED O(n^2) pairwise walk. Outer i runs
//             cnt1-1 .. 1; inner j = i..0 walks the SAME table from its base.
//             Per pass 4 pairs are stored to a __ps_t fr[4] out-block at r1+8
//             and passed to fn_8003EF4C(&fr[0], &fr[2], colour, 0, 1).
//     loop 2  n = arg0+0x9C : 0x8037E5D8 walk, f32 arg from
//             (f32*)arg0->pts1 + i*0x18 + 0x10.
//     guard   if (lbl_80301B18) { fr[0]=org[0]; fr[1]=org[1];
//             fn_8003EF54(...,0xC800C8FF,1,lbl_80298E6C); }
//     loop 4  n = arg0+0xA4 : 0x8037E758 walk BACKWARD (pointer induction,
//             ends at tbl-0x10) paired with arg0->pts2[i]. If that record's s32
//             at +0x20 != 0 it emits two fn_8003EF54 quads.
//
// FIXES LANDED THIS ROUND (all four are real semantic errors in the old body,
// +11 masked points, -20B of dead code):
//  1. THE POINT TABLES ARE PAIRS, NOT ELEMENTS. The old draft stepped
//     `pj++` / `pj--` (8 bytes); want walks 0x10 per iteration in all three
//     loops. The 8-byte step was a live BUG, not just a codegen mismatch: the
//     loop-4 end test `pj != lbl_8037E758 - 2` never matched, so the old draft
//     ran the loop with the wrong trip count. Now `pj += 2` / `pj -= 2`.
//  2. The `lbl_80301B18` guard block writes BOTH halves: it also stores
//     org[1] to fr[1] (`psq_l f0,288(arg0)` + `psq_st f0,8(r11)`). The old
//     draft only did fr[0]; that was 2 missing instructions (+1 in the -0x18
//     region) and left fr[1] as garbage for the callee.
//  3. Loop 1 reads the i-th point as an INDEXED access, not a pointer one:
//     `base[i*2]` / `base[i*2+1]` (with `pj` as the separate walking pointer).
//     That is what makes gcc emit want's `slwi r28,i,4` + `add r26,r28,r27`
//     and the mixed `psq_lx f13,r28+r27` (no displacement — psq_lx has none)
//     + `psq_l f0,8(r26)` pair. With `pi = base + i*2` and `pi[0]`/`pi[1]`
//     gcc pre-adds into ONE register and never emits the psq_lx, and gets 8
//     instead of 9 callee-saved GPRs.
//  4. Loop 2's index into pts1 is a BYTE offset (`off = i*0x18`,
//     `*(f32*)((char*)pts1 + off + 0x10)`), which is what want's `mulli r28,i,
//     0x18` in the preheader + `add r9,r28,r9` in the body needs. Counting
//     floats (`i*6`, old draft) forces an extra `slwi r,i,2` in the body.
//     Its loop test must be `while (i--)` (tests the PRE-decrement value ->
//     want's 3-word `cmpwi r,0; addi r,r,-1; bne`); `i--; while (i)` folds
//     into a 2-word `addic.`/`bne` and loses the cmpwi.
//
// STALE SCAFFOLDING REMOVED: the `register char *anchor __asm__("r23")`
// page-anchor pin (worth +6 masked points on the OLD, semantically broken
// body) is now NEUTRAL — deleting it and writing `base = lbl_8037E458;`
// gives the identical object and the same 33.5%. GCC picks r23 for the table
// address on its own. Only the `register s32 color __asm__("r25")` pin is
// still load-bearing.
//
// PRECISE RESIDUAL (re-measured on the fixed body, not inherited):
//  1. CALLEE-SAVED SET IS OFF BY ONE REGISTER. want allocates 9 GPRs,
//     r23..r31 (`stmw r23,0x2c` / `lmw r23,0x2c`). got allocates 9,
//     r22..r30 (`stmw r22,0x28`). Both sets are perfectly consecutive, they
//     just start one lower — so every `mr`/`addi`/addressing instruction in
//     the function carries the wrong register number even when the rest of
//     the instruction is right. Per-web: want r29=arg0 r25=colour r24=i-1
//     r27=base r28=i*16 r26=base+i*16 r30=pj r31=j; got r29=arg0 r25=colour
//     r22=i-1 r30=base r28=i*16 r26=base+i*16 r24=pj r31=i (j COALESCED with
//     i). arg0 and the colour are already right; the rest is shifted.
//  2. The extra web in got is a hoisted `addi r27, r1, 0x18` — gcc LIFs the
//     loop-invariant `&fr[2]` (r1+0x18) into a callee-saved register, whereas
//     want recomputes `addi r4, r1, 0x18` inside the inner loop (it recomputes
//     `addi r4, arg0+0x158` in loop 2 for the same reason, but DOES hoist
//     `addi r28, r1, 8` in loop 4). Getting rid of that one hoist would both
//     free a callee-saved GPR and make the loop-1 preheader the same length
//     as want's 5. Every C spelling tried for the callee's second argument
//     (`&fr[2]`, `fr + 2`, `fr`) leaves it hoisted — see "ruled out" below.
//  3. j is coalesced into i in loop 1, so got's inner-loop back edge is
//     `addic. r31,r31,-1` on i's own register and i is reloaded from r22,
//     whereas want keeps a distinct `mr r31, r9` (j = i) and keeps i itself
//     in a VOLATILE register (r9) across the outer loop. Forcing that with
//     `register s32 i __asm__("r9")` / `__asm__("r24")` regresses hard.
//  4. Loop 2 emits one word too many: `mr r0,r31; cmpwi r0,0; addi r31,r31,
//     -1; bne` where want has `cmpwi r30,0; addi r30,r30,-1; bne` — same
//     semantics (test the pre-decrement value), gcc just needed a copy.
//     This +1 shifts every word from 0x118 on, which is most of why the
//     positional score is stuck near a third despite the body being right.
//  5. Loop 4 is 2 words short: want forms `addi r9,r9,0x10` then
//     `psq_l 0(r9)` / `psq_st 8(r28)` for the record's +0x10 pair, got folds
//     the 0x10 into the psq_l displacement (16(r9)/24(r9)). And want keeps
//     `addi r28, r1, 8` + `mr r3, r28` for the SECOND fn_8003EF54 of the
//     iteration; got recomputes `addi r3, r1, 8` twice.
//  6. Loop-1 PS register assignment: want f12=pj[0] f11=pj[1] f13=pi[0]
//     f0=pi[1] f10=org0 f9=org1 with stores in the order 24, 8, 16, 32
//     (fr2, fr0, fr1, fr3); got reuses f0/f13 for both halves. The store
//     ORDER is reachable: `fr[0..3]` in source order scores 33.5% (best
//     measured), `fr[2],fr[3],fr[0],fr[1]` 32.9%, `fr[2],fr[0],fr[1],fr[3]`
//     32.9%.
//
// INERT: not registered in splits.txt/configure.py — never compiled, not
// counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

// FLAG: -mps-float

// 0x28-stride record behind arg0+0xA0: a 16-byte float pair at +0x10 and an
// s32 flag at +0x20 (retail reads it with lwz/cmpwi — NOT a float compare,
// which is what a bare f32* field makes gcc emit, and that fcmpu is what
// drags an f31 save into the prologue retail does not have).
typedef struct {
    char pad0x00[0x10];
    __ps_t c;
    __ps_t d;
    s32 f20;
    char pad0x24[0x4];
} P3;

// File-local layout. The shared Unk_354ED36A has these as bare s32 (0x98,
// 0xA0) and s16 (0x9C); retail needs 0x98/0xA0 as STRIDE POINTERS and 0x9C as
// unsigned (lhz). M6.89d-note: when a merged class's member type is wrong for
// this function, declare the real layout locally — do not edit the header.
typedef struct {
    char pad0x0[0x94];
    u16 cnt1;
    char pad0x96[2];
    f32 *pts1;
    u16 cnt2;
    char pad0x9E[2];
    P3 *pts2;
    u16 cnt3;
    char pad0xA6[0x6E];
    s32 kind;
    __ps_t org[2];
    char pad0x128[0x74];
    f32 f_19C;
} S;

extern f32 lbl_80298E68;
extern f32 lbl_80298E6C;
extern f32 lbl_80298E70;
extern bool lbl_80301B18;
extern __ps_t lbl_8037E458[];
extern __ps_t lbl_8037E5D8[];
extern __ps_t lbl_8037E758[];

void fn_8003EF4C(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_8003F208(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5);
void fn_8003EF54(void *arg0, s32 arg1, s32 arg2, f32 arg3);

void fn_800BDAD4(S *arg0) {
    __ps_t fr[4];
    register s32 color __asm__("r25");
    s32 i;
    s32 j;
    __ps_t *pj;
    __ps_t *base;
    s32 off;

    color = 0;
    switch (arg0->kind) {
    case 0:
        color = 0xC8FF;
        break;
    case 1:
        color = 0xC800FF;
        if (!(arg0->f_19C > lbl_80298E68)) {
            color = 0xC80000FF;
        }
        break;
    case 2:
        color = 0x640064FF;
        break;
    }

    /* pairwise segments: every (i, j<=i) pair of the 0x10-stride table */
    i = arg0->cnt1;
    if (i == 0) {
        goto skip1;
    }
    i--;
    do {
        if (i > 0) {
            base = lbl_8037E458;
            pj = base;
            j = i;
            do {
                fr[0] = base[i * 2] + arg0->org[0];
                fr[1] = base[i * 2 + 1] + arg0->org[1];
                fr[2] = pj[0] + arg0->org[0];
                fr[3] = pj[1] + arg0->org[1];
                pj += 2;
                fn_8003EF4C(&fr[0], &fr[2], color, 0, 1);
            } while (--j != 0);
        }
        i--;
    } while (i != -1);
skip1:

    i = arg0->cnt2;
    if (i == 0) {
        goto skip2;
    }
    i--;
    pj = lbl_8037E5D8 + i * 2;
    off = i * 0x18;
    do {
        fr[0] = pj[0] + arg0->org[0];
        fr[1] = pj[1] + arg0->org[1];
        fn_8003F208(&fr[0], (char *)arg0 + 0x158, 0xC, color, 1,
                    *(f32 *)((char *)arg0->pts1 + off + 0x10));
        pj -= 2;
        off -= 0x18;
    } while (i--);
skip2:

    if (lbl_80301B18 != 0) {
        fr[0] = arg0->org[0];
        fr[1] = arg0->org[1];
        fn_8003EF54(&fr[0], 0xC800C8FF, 1, lbl_80298E6C);
    }

    i = arg0->cnt3;
    if (i == 0) {
        return;
    }
    i--;
    pj = lbl_8037E758 + i * 2;
    off = i;
    do {
        if (arg0->pts2[off].f20 != 0) {
            fr[0] = pj[0] + arg0->org[0];
            fr[1] = pj[1] + arg0->org[1];
            fn_8003EF54(&fr[0], 0x64C8FF, 1, lbl_80298E70);
            fr[0] = arg0->pts2[off].c;
            fr[1] = arg0->pts2[off].d;
            fn_8003EF54(&fr[0], 0x6400C8FF, 1, lbl_80298E70);
        }
        pj -= 2;
        off--;
    } while (pj != lbl_8037E758 - 2);
}
