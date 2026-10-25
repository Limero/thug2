// PARKED 2026-09-28 (b2_19): best 18.14% (was 18.06%). 
// RESIDUAL: prologue callee-saved colour map (want stmw r20,0x1c0 = 12 regs
// r20-r31; got stmw r22,0x1c8 = 10 regs r22-r31, arg0 in r24 not r31, &v0 in
// r23 not recycled r30). The register pin a0s __asm__("r31") is SILENTLY
// DROPPED by cc1 under pressure (verified: arg0 lands in r24) but is
// load-bearing for the stmw span (removing it drops to 2.10%). Matrix base:
// want keeps fn_80003E0C return in r3 (lfs f13,0x10(r3)); got copies to r9
// (mr r9,r3) then reads 0x10(r9) - 1 word x 3 blocks. doc-30: 4 self-targeting
// bdnz windows (displacement 0) at 0x800C0344/0x3D8/0x6B0/0x988 need bdnz $
// asm (disallowed). Tail: 13 extra words + cascade from the prologue
// colour map desyncs all 735 PS-word comparisons.
// FIXED: m-access bug - source used m[0x30] (element 48, byte
// 0xC0) where want has byte offset 0x30 (element 12). All 48 m[0xNN] accesses
// corrected to element indices m[NN/4]. Got now accesses the right matrix
// offsets (0x10,0x0,0x20,0x30 on r9) but the mr r9,r3 copy + prologue colour
// map still desync the stream. Score unchanged (785 diffs) because the
// register diff (r9 vs r3) still mismatches.
// TRIED: m-fix (correct, score-neutral); m pin to r3 (1.36%, FPR colours
// collapse); add pM0/pM8/p190 (13 regs, 17.6%); remove pin (2.10%); prologue
// reorder pE8-between-calls (neutral); doc-30 pointers-out-of-loop (cc1 moves
// V=identity into the loop, 2.09%); flags -fno-strength-reduce (+0.08%),
// -fno-schedule-insns/-fno-gcse/-fno-schedule-insns2/-fno-sched-spec (all
// worse or neutral).
// FAMILY: doc-15 (arg-setup colour map) + doc-30 (self-targeting bdnz) +
// regalloc (12-vs-10 saved regs). The prologue colour map is the dominant
// term and is not reachable from source shapes - the pin is dropped and
// adding pointers overshoots to 13 regs.
//
// WIP DRAFT (non-matching) - hand-rebuilt from disassembly (was an m2c husk)
// family=hand range=0x800C02E8-0x800C11AC size=3780B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// REBUILT 2026-09-27 from the raw instruction stream (ps_disasm + hand
// decode of every primary-opcode-4 word). Retail: 945 insns, frame -0x1f8,
// one saved FPR (f31), stmw r20..r31, and 79 psq_l/psq_st pair words plus 9
// PS arithmetic words, so the object REQUIRES -mps-float (see // FLAG:).
// The old m2c draft scored 0.5% with a -0x88 frame because it emitted pure
// scalar code and had thrown away ~40 statements per matrix block.
//
// Recovered from want (all hand-decoded, none of it from m2c):
//  * frame locals ascending: 0x08 v0[4] | 0x18 v1[4] | 0x28 V[16]
//    | 0x68 M[16] (re-used later as quat[4]+e78+e88+e98) | 0xA8 T[16]
//    | 0xE8 spE8 | 0x174 f32 | 0x190 s32 | 0x1A8 f32[2] | 0x1B8 f64 pool.
//  * each of the three `bl 0x80003e0c / 0x80003eb0 / 0x80003f54` calls takes
//    r3 = &M[0] (0x68) plus an euler float out of v1[]; the callee leaves a
//    COLUMN-major 4x4 at 0x68 and the 16 statements after it are
//    T[4*r+c] = sum_j V[4*r+j] * m[j*4+c]  (V row-major at 0x28).
//  * the 8 psq_l/psq_st after each block are `V[i] = T[i]`, i = 0..7 pairs.
//    m2c rendered those as a bogus (1,x,1,0) struct init - that was the 0.5%.
//  * op4 hand-decode (XO5 = bits 26-30): 0x1000582a / 0x11ad602a / 0x1000602a
//    / 0x11ad582a = ps_add, 0x11ad0018 / 0x10090018 = ps_muls0,
//    0x10002890 = ps_mr (XO=72), 0x116b6828 / 0x118c0028 = ps_sub.
//  * the int-to-double conversion against the game's OWN .rodata2 2^52 double
//    lbl_80298FD0 stores the 0x43300000 bias word and the argument word to the
//    0x1b8/0x1bc pool slots, loads the pair back as a double, subtracts 2^52
//    and rounds to float, i.e. the doc-14 promote-clean form (never let ngccc
//    synthesise the pool itself).
//  * the four self-targeting `bdnz <self>` (displacement 0) empty-doloop
//    windows at 0x800C0344 / 0x3D8 / 0x6B0 / 0x988 are doc-30 residue left
//    behind by the fully-unrolled 4-iteration loops. They are written here as
//    plain empty countdowns - no `bdnz $` asm template, per the no-asm rule -
//    so they come out displaced, not self-targeting.
//  * the shared Unk_D2FDFB5E class types unk0x1AC as f32 and unk0x2F0 as
//    s32; want does `lwz` on both and uses 0x2F0 as a pointer, so this file
//    carries its own receiver typedef (trap #1).
//
// See PARKED at the top of this header for the residual.

// FLAG: -mps-float -fno-strength-reduce
// VERDICT 2026-09-27: NOT byte-identical. Relocation-masked word match
// 785/960 = 18.06% (the m2c husk this replaces scored 0.5%). Compiled object
// 3832 B / 958 insns vs retail 3780 B / 945 insns. tools/test_wip_drafts.py
// --addr 0x800C02E8 => DIFF. NOT promoted.
//
// WHAT IS NOW EXACT (verified by tools/want_got.py + a call-site trace):
//   * frame size 0x1f8 with the f31 save slot at 0x1f0 and the LR slot at
//     0x1fc - the frame, the f31 slot and the LR slot are all byte-identical.
//   * every frame offset: v0 0x08, v1 0x18, V 0x28..0x67, M 0x68..0xA7,
//     T 0xA8..0xE7, spE8 0xE8, sp174 0x174, sp190 0x190, sp1A8 0x1A8,
//     and the int->f64 pool at 0x1b8/0x1bc.
//   * 112 of retail's 116 psq_l/psq_st pair words, and 8 of its 9
//     primary-opcode-4 PS arithmetic words (4x ps_add, ps_sub x2, and the
//     ps_muls0 x2 / ps_mr trio of the cross product).
//   * all 16 `bl` call sites land within 2 instructions of retail's through
//     the whole body (+13 by the tail).
//   * the first V*M block is ~60% word-exact including its store schedule.
//
// RESIDUAL (why plain C does not reach it):
//  1. PROLOGUE CALLEE-SAVED COLOUR MAP (the dominant term). Retail homes
//     arg0->r31, &v0->r30, &M[4]->r29, &M[0]->r22, &M[12]->r28, &M[8]->r26,
//     &V->r21, &sp190->r20, &spE8->r27, arg0+0x30->r24, arg0+0x50->r23 and
//     the quaternion index->r25, i.e. 12 saved regs and `stmw r20,0x1c0`.
//     cc1 saves 10 (`stmw r22,0x1c8`) and permutes every one of them, which
//     desynchronises the whole stream. The single `register s32 a0s
//     __asm__("r31")` declaration pin below is worth +13.1 points
//     (5.2% -> 18.3%); pinning any of the seven stack addresses ON TOP of it
//     is strictly worse (pV0 18.4%, pM4 14.5%, pV 5.6%, pM12 4.2%, pE8
//     1.0%) - the over-constraint wall of 70-130c. Two more saved regs are
//     needed and no source shape found so far produces them.
//  2. MATRIX BASE PER mat-vec BLOCK. Retail keeps the fn_80003E0C return in
//     r3 and reads m[j*4+c] straight off it (`lfs f13,0x10(r3)`). cc1 rebases
//     to m+0x30 in a fresh register and uses positive displacements
//     (`lfs f13,0x40(r9)`) - the classic offset-selection difference, worth
//     one instruction per block (that is the 1-word drift per block that
//     accumulates to -3 by word 670 and knocks blocks 2 and 3 out of
//     alignment).
//  3. FOUR SELF-TARGETING `bdnz <self>` (displacement 0) EMPTY-DOLOOP WINDOWS
//     at 0x800C0344 / 0x3D8 / 0x6B0 / 0x988 - the doc-30 residue of the
//     fully-unrolled 4-iteration loops. Plain C cannot emit displacement 0;
//     reproducing it needs a `bdnz $` raw-asm window, which is disallowed here
//     (7d-2 notes it can fall out of plain C only when the whole loop
//     body stays inside the window, which retail's does not).
//  4. 13 EXTRA WORDS IN THE TAIL. The manual-quaternion branch keeps
//     (pV+row*16, col*4) index pairs and three loaded floats live ACROSS
//     `bl 0x80270ca4` and then does six `lfsx` off them; cc1 recomputes every
//     index after the call. The 59-iteration vcall loop and the 24-word node
//     psq-copy block are structurally right but +13.
//
// DISCLOSED: one declaration-level register pin plus an empty identity
// `"+r"` barrier (NO inline-asm instruction template, no `bdnz $`):
//     register s32 a0s __asm__("r31");
//     a0s = (s32)arg0;
//     __asm__("" : "+r"(a0s));
// The barrier is load-bearing (without it the pin is silently dropped, 76-178
// / 6y-129a); s32 alias rather than a pointer type because ProDG cc1
// SILENTLY DROPS pointer-typed register vars outright (76-178).

#include "types.h"
#include "structs.h"

extern f32 lbl_80298FC8; /*  1.0  */
extern f32 lbl_80298FCC; /*  0.0  */
extern f32 lbl_80298FD8; /* 386.4 */
extern f32 lbl_80298FDC; /*  0.25 */
extern f32 lbl_80298FE0; /* 24.0  */
extern f32 lbl_80298FE4; /* -240.0 */
extern f32 lbl_80298FE8; /*  0.5  */
extern f64 lbl_80298FD0; /* 2^52  */

extern void fn_800F078C(void *, void *);
extern void fn_800F0A70(void *, void *);
extern f32 *fn_80003E0C(f32 *, f32);
extern f32 *fn_80003EB0(f32 *, f32);
extern f32 *fn_80003F54(f32 *, f32);
extern void fn_80107998(void *, f32 *, f32 *);
extern s32 fn_80107B20(void *, s32, s32);
extern f32 sqrtf(f32);
extern void fn_8002C8FC(f32 *, f32);
extern void fn_8002C904(f32 *, f32, f32, f32);
extern void fn_800C750C(void *);
extern void fn_800C7E6C(void *);
extern void fn_800A1684(void *, s32);
extern void CObject_RemoveRefLink(s32, void *);

/* ---- TRUE per-file layouts (the shared Unk_* classes mis-type these) ---- */

struct SNode;
struct SVtbl;

typedef struct {
    char pad00[0x0C];
    struct SNode *unk0C;
    char pad10[0x08];
    struct SVtbl *unk18;
    char pad1C[0x04];
    __ps_t unk20;
    __ps_t unk28;
    f32 unk30, unk34, unk38, unk3C;
    __ps_t unk40;
    __ps_t unk48;
    f32 unk50, unk54, unk58, unk5C;
    s32 unk60;
    char pad64[0x0C];
    __ps_t unk70, unk78, unk80, unk88, unk90, unk98, unkA0, unkA8;
    __ps_t unkB0, unkB8;
    char padC0[0x68];
    s32 unk128;
    char pad12C[0x44];
    f32 unk170;
    char pad174[0x38];
    s32 unk1AC;
    char pad1B0[0x140];
    s32 unk2F0;
    char pad2F4[0x1060];
    s32 unk1354;
    s32 unk1358;
} SC02E8;

typedef struct SNode {
    char pad0[0x58];
    __ps_t n58, n60, n70, n78, n80, n88, n90, n98, nA0, nA8, nB0, nB8, nC0;
    __ps_t nD0, nD8, nE0, nE8, nF0, nF8, n100, n108;
} SNode;

struct SVtbl {
    s32 p0[4];
    s16 ofs;
    s16 p12;
    s32 fp;
};

typedef union {
    f32 f[4];
    __ps_t p[2];
} Q4;

/* lane-accessible paired single (SN_PS.h is not includable from a sweep:
 * test_wip_drafts strips #include lines, so the union is redeclared here) */
typedef union {
    __ps_t ps;
    struct {
        f32 hi, lo;
    } flt;
} PSU;

typedef struct {
    char pad0[0x8C];
} SArg;

/* Frame template. One struct so the slot layout is deterministic (recipe
 * 86 / 6q-86) instead of leaving it to cc1's local sorter: 0x1B8 bytes, so
 * the locals region ends at sp+0x1C0 and the 12 saved GPRs (r20..r31) land at
 * 0x1C0, f31 at 0x1F0, LR at 0x1FC - exactly want's -0x1f8 frame. */
typedef struct {
    Q4 v0;            /* +0x000 */
    Q4 v1;            /* +0x010 */
    f32 V[16];        /* +0x020 */
    f32 M[16];        /* +0x060 */
    f32 T[16];        /* +0x0A0 */
    SArg spE8;        /* +0x0E0 */
    f32 sp174;        /* +0x16C */
    char pad178[0x18];
    s32 sp190;        /* +0x188 */
    char pad194[0x14];
    f32 sp1A8[4];     /* +0x1A0 (only [0] is ever written; [2],[3] are the
                       * 8-byte gap that keeps sp1B8 at +0x1B0) */
    f64 sp1B8;        /* +0x1B0 */
} FR;

void fn_800C02E8(SC02E8 *arg0, void *arg1)
{
    FR fr;
#define v0 fr.v0
#define v1 fr.v1
#define V fr.V
#define M fr.M
#define T fr.T
#define spE8 fr.spE8
#define sp174 fr.sp174
#define sp190 fr.sp190
#define sp1A8 fr.sp1A8
#define sp1B8 fr.sp1B8

    f32 accf;
    f32 fv;
    f32 ang;
    f32 inv;
    f32 *m;
    f32 *p;
    PSU sc, q1, q2, q3, d1, d2, a1, a2, a3, a4, vp;
    Q4 *pV0;     /* want r30 = &v0[0] */
    f32 *pV;     /* want r21 = &V[0]  */
    f32 *pM4;    /* want r29 = &M[4]   */
    f32 *pM12;   /* want r28 = &M[12]  */
    SArg *pE8;   /* want r27 = &spE8   */
    f32 *pA30;   /* want r24 = arg0+0x30 */
    f32 *pA50;   /* want r23 = arg0+0x50 */
    s32 i, j, k, n, dummy, r8, cnt;
    s32 *base;
    SNode *nd;

    /* DISCLOSED register pin (declaration level, no asm template): retail's
     * callee-saved colour map is arg0 -> r31; cc1 picks r28, which permutes
     * all seven stack-address homes in the prologue and desynchronises the
     * whole stream. s32 alias, not a pointer type - ProDG cc1 SILENTLY DROPS
     * pointer-typed register vars (see 76-178). Pin-a-copy after 6a-6. */
    register s32 a0s __asm__("r31");
    a0s = (s32)arg0;
    __asm__("" : "+r"(a0s));
    fn_800F078C(arg1, &v0);
    fn_800F0A70(arg1, &v1);

    /* want keeps these six stack addresses live in r20/r21/r27/r28/r29/r30;
     * they are computed INSIDE a 4-iteration countdown loop, which is how
     * retail gets its first (self-targeting, doc-30) bdnz window. */
    dummy = 4;
    do {
        pV0 = &v0;
        pV = V;
        pM4 = M + 4;
        pM12 = M + 12;
        pE8 = &spE8;
        dummy--;
    } while (dummy != 0);

    V[0] = 1.0f;
    V[1] = 0.0f;
    V[2] = 0.0f;
    V[3] = 0.0f;
    V[4] = 0.0f;
    V[5] = 1.0f;
    V[6] = 0.0f;
    V[7] = 0.0f;
    V[8] = 0.0f;
    V[9] = 0.0f;
    V[10] = 1.0f;
    V[11] = 0.0f;
    V[12] = 0.0f;
    V[13] = 0.0f;
    V[14] = 0.0f;
    V[15] = 1.0f;

    if (v1.f[0] != 0.0f || v1.f[1] != 0.0f || v1.f[2] != 0.0f) {
        dummy = 4;
        do {
            pA30 = &((SC02E8 *)a0s)->unk30;
            pA50 = &((SC02E8 *)a0s)->unk50;
            dummy--;
        } while (dummy != 0);

        m = fn_80003E0C(M, v1.f[0]);
        dummy = 4;
        T[0] = (V[3] * m[12]) + ((V[2] * m[8]) + ((V[0] * m[0]) + (V[1] * m[4])));
        T[1] = (V[3] * m[13]) + ((V[2] * m[9]) + ((V[0] * m[1]) + (V[1] * m[5])));
        T[2] = (V[3] * m[14]) + ((V[2] * m[10]) + ((V[0] * m[2]) + (V[1] * m[6])));
        T[3] = (V[3] * m[15]) + ((V[2] * m[11]) + ((V[0] * m[3]) + (V[1] * m[7])));
        T[4] = (V[7] * m[12]) + ((V[6] * m[8]) + ((V[4] * m[0]) + (V[5] * m[4])));
        T[5] = (V[7] * m[13]) + ((V[6] * m[9]) + ((V[4] * m[1]) + (V[5] * m[5])));
        T[6] = (V[7] * m[14]) + ((V[6] * m[10]) + ((V[4] * m[2]) + (V[5] * m[6])));
        T[7] = (V[7] * m[15]) + ((V[6] * m[11]) + ((V[4] * m[3]) + (V[5] * m[7])));
        T[8] = (V[11] * m[12]) + ((V[10] * m[8]) + ((V[8] * m[0]) + (V[9] * m[4])));
        T[9] = (V[11] * m[13]) + ((V[10] * m[9]) + ((V[8] * m[1]) + (V[9] * m[5])));
        T[10] = (V[11] * m[14]) + ((V[10] * m[10]) + ((V[8] * m[2]) + (V[9] * m[6])));
        T[11] = (V[11] * m[15]) + ((V[10] * m[11]) + ((V[8] * m[3]) + (V[9] * m[7])));
        T[12] = (V[15] * m[12]) + ((V[14] * m[8]) + ((V[12] * m[0]) + (V[13] * m[4])));
        T[13] = (V[15] * m[13]) + ((V[14] * m[9]) + ((V[12] * m[1]) + (V[13] * m[5])));
        T[14] = (V[15] * m[14]) + ((V[14] * m[10]) + ((V[12] * m[2]) + (V[13] * m[6])));
        T[15] = (V[15] * m[15]) + ((V[14] * m[11]) + ((V[12] * m[3]) + (V[13] * m[7])));
        ((__ps_t *)V)[0] = ((__ps_t *)T)[0];
        ((__ps_t *)V)[1] = ((__ps_t *)T)[1];
        ((__ps_t *)V)[2] = ((__ps_t *)T)[2];
        ((__ps_t *)V)[3] = ((__ps_t *)T)[3];
        ((__ps_t *)V)[4] = ((__ps_t *)T)[4];
        ((__ps_t *)V)[5] = ((__ps_t *)T)[5];
        ((__ps_t *)V)[6] = ((__ps_t *)T)[6];
        ((__ps_t *)V)[7] = ((__ps_t *)T)[7];

        dummy = 4;
        do {
            dummy--;
        } while (dummy != 0);

        m = fn_80003EB0(M, v1.f[1]);
        dummy = 4;
        T[0] = (V[3] * m[12]) + ((V[2] * m[8]) + ((V[0] * m[0]) + (V[1] * m[4])));
        T[1] = (V[3] * m[13]) + ((V[2] * m[9]) + ((V[0] * m[1]) + (V[1] * m[5])));
        T[2] = (V[3] * m[14]) + ((V[2] * m[10]) + ((V[0] * m[2]) + (V[1] * m[6])));
        T[3] = (V[3] * m[15]) + ((V[2] * m[11]) + ((V[0] * m[3]) + (V[1] * m[7])));
        T[4] = (V[7] * m[12]) + ((V[6] * m[8]) + ((V[4] * m[0]) + (V[5] * m[4])));
        T[5] = (V[7] * m[13]) + ((V[6] * m[9]) + ((V[4] * m[1]) + (V[5] * m[5])));
        T[6] = (V[7] * m[14]) + ((V[6] * m[10]) + ((V[4] * m[2]) + (V[5] * m[6])));
        T[7] = (V[7] * m[15]) + ((V[6] * m[11]) + ((V[4] * m[3]) + (V[5] * m[7])));
        T[8] = (V[11] * m[12]) + ((V[10] * m[8]) + ((V[8] * m[0]) + (V[9] * m[4])));
        T[9] = (V[11] * m[13]) + ((V[10] * m[9]) + ((V[8] * m[1]) + (V[9] * m[5])));
        T[10] = (V[11] * m[14]) + ((V[10] * m[10]) + ((V[8] * m[2]) + (V[9] * m[6])));
        T[11] = (V[11] * m[15]) + ((V[10] * m[11]) + ((V[8] * m[3]) + (V[9] * m[7])));
        T[12] = (V[15] * m[12]) + ((V[14] * m[8]) + ((V[12] * m[0]) + (V[13] * m[4])));
        T[13] = (V[15] * m[13]) + ((V[14] * m[9]) + ((V[12] * m[1]) + (V[13] * m[5])));
        T[14] = (V[15] * m[14]) + ((V[14] * m[10]) + ((V[12] * m[2]) + (V[13] * m[6])));
        T[15] = (V[15] * m[15]) + ((V[14] * m[11]) + ((V[12] * m[3]) + (V[13] * m[7])));
        ((__ps_t *)V)[0] = ((__ps_t *)T)[0];
        ((__ps_t *)V)[1] = ((__ps_t *)T)[1];
        ((__ps_t *)V)[2] = ((__ps_t *)T)[2];
        ((__ps_t *)V)[3] = ((__ps_t *)T)[3];
        ((__ps_t *)V)[4] = ((__ps_t *)T)[4];
        ((__ps_t *)V)[5] = ((__ps_t *)T)[5];
        ((__ps_t *)V)[6] = ((__ps_t *)T)[6];
        ((__ps_t *)V)[7] = ((__ps_t *)T)[7];

        m = fn_80003F54(M, v1.f[2]);
        T[0] = (V[3] * m[12]) + ((V[2] * m[8]) + ((V[0] * m[0]) + (V[1] * m[4])));
        T[1] = (V[3] * m[13]) + ((V[2] * m[9]) + ((V[0] * m[1]) + (V[1] * m[5])));
        T[2] = (V[3] * m[14]) + ((V[2] * m[10]) + ((V[0] * m[2]) + (V[1] * m[6])));
        T[3] = (V[3] * m[15]) + ((V[2] * m[11]) + ((V[0] * m[3]) + (V[1] * m[7])));
        T[4] = (V[7] * m[12]) + ((V[6] * m[8]) + ((V[4] * m[0]) + (V[5] * m[4])));
        T[5] = (V[7] * m[13]) + ((V[6] * m[9]) + ((V[4] * m[1]) + (V[5] * m[5])));
        T[6] = (V[7] * m[14]) + ((V[6] * m[10]) + ((V[4] * m[2]) + (V[5] * m[6])));
        T[7] = (V[7] * m[15]) + ((V[6] * m[11]) + ((V[4] * m[3]) + (V[5] * m[7])));
        T[8] = (V[11] * m[12]) + ((V[10] * m[8]) + ((V[8] * m[0]) + (V[9] * m[4])));
        T[9] = (V[11] * m[13]) + ((V[10] * m[9]) + ((V[8] * m[1]) + (V[9] * m[5])));
        T[10] = (V[11] * m[14]) + ((V[10] * m[10]) + ((V[8] * m[2]) + (V[9] * m[6])));
        T[11] = (V[11] * m[15]) + ((V[10] * m[11]) + ((V[8] * m[3]) + (V[9] * m[7])));
        T[12] = (V[15] * m[12]) + ((V[14] * m[8]) + ((V[12] * m[0]) + (V[13] * m[4])));
        T[13] = (V[15] * m[13]) + ((V[14] * m[9]) + ((V[12] * m[1]) + (V[13] * m[5])));
        T[14] = (V[15] * m[14]) + ((V[14] * m[10]) + ((V[12] * m[2]) + (V[13] * m[6])));
        T[15] = (V[15] * m[15]) + ((V[14] * m[11]) + ((V[12] * m[3]) + (V[13] * m[7])));
        ((__ps_t *)V)[0] = ((__ps_t *)T)[0];
        ((__ps_t *)V)[1] = ((__ps_t *)T)[1];
        ((__ps_t *)V)[2] = ((__ps_t *)T)[2];
        ((__ps_t *)V)[3] = ((__ps_t *)T)[3];
        ((__ps_t *)V)[4] = ((__ps_t *)T)[4];
        ((__ps_t *)V)[5] = ((__ps_t *)T)[5];
        ((__ps_t *)V)[6] = ((__ps_t *)T)[6];
        ((__ps_t *)V)[7] = ((__ps_t *)T)[7];
    }

    /* (f32)(f64)(s32)((SC02E8 *)a0s)->unk1AC, hand-rolled against lbl_80298FD0 (2^52). */
    *(u32 *)&sp1B8 = 0x43300000;
    *((u32 *)&sp1B8 + 1) = (u32)((SC02E8 *)a0s)->unk1AC;
    fv = (f32)(sp1B8 - lbl_80298FD0);

    accf = 0.0f;
    p = (f32 *)((char *)((SC02E8 *)a0s)->unk2F0 + 0x648);
    for (i = 0; i < 4; i++) {
        accf += (p[6] + p[7] + (lbl_80298FD8 / (((SC02E8 *)a0s)->unk170 * fv * p[0xA]))) - p[8];
        p -= 0x78;
    }

    pM4[0] = lbl_80298FCC;
    pM4[2] = lbl_80298FCC;
    pM4[1] = lbl_80298FE0;
    pM4[3] = lbl_80298FC8;
    pM12[0] = lbl_80298FCC;
    pM12[2] = lbl_80298FCC;
    pM12[1] = lbl_80298FE4;
    pM12[3] = lbl_80298FC8;
    vp.ps = ((PSU *)pV0)->ps;
    a1.ps = __builtin_ps_add(((const __ps_t *)M)[3], vp.ps);
    q1.ps = __builtin_ps_muls0(a1.ps, vp.ps);
    ((PSU *)M)[1].ps = a1.ps;
    ((PSU *)M)[0].ps = q1.ps;
    a2.ps = __builtin_ps_add(((const __ps_t *)M)[7], vp.ps);
    q2.ps = __builtin_ps_add(((const __ps_t *)M)[3], vp.ps);
    a3.ps = __builtin_ps_add(((const __ps_t *)M)[6], vp.ps);
    ((PSU *)M)[4].ps = a2.ps;
    ((PSU *)M)[5].ps = a3.ps;
    accf = accf * lbl_80298FDC;
    fn_80107998(pE8, M, M + 8);
    if (fn_80107B20(pE8, 0, 0) != 0) {
        v0.f[1] = sp174 - accf;
    }

    base = (s32 *)((SC02E8 *)a0s)->unk2F0;
    r8 = -1;
    n = 4;
    p = (f32 *)((char *)base + 0x838);
    for (;;) {
        n--;
        if (n == 0) {
            break;
        }
        if (*(s32 *)((char *)p - 0x1E0) != 0) {
            p = (f32 *)((char *)p - 0x1E0);
            continue;
        }
        p = (f32 *)((char *)p - 0x1E0);
        r8 = n;
    }

    fv = *(f32 *)((char *)base + r8 * 0x1E0 + 0xB0);
    sp1A8[0] = fv;
    ang = V[0] + V[5] + V[10];
    sc.ps = ((PSU *)sp1A8)->ps;
    vp.ps = ((PSU *)pV0)->ps;
    q1.ps = __builtin_ps_muls0(sc.ps, ((PSU *)V)[4].ps);
    q2.ps = __builtin_ps_muls0(((PSU *)V)[5].ps, sc.ps);
    d1.ps = __builtin_ps_sub(q1.ps, vp.ps);
    d2.ps = __builtin_ps_sub(q2.ps, vp.ps);
    ((PSU *)M)[0].ps = q1.ps;
    ((PSU *)M)[1].ps = q2.ps;
    ((PSU *)&v0)->ps = d1.ps;
    ((SC02E8 *)a0s)->unk28 = d2.ps;
    ((SC02E8 *)a0s)->unk20 = ((PSU *)pV0)->ps;
    ((PSU *)&v0)->ps = d2.ps;

    if (ang > 0.0f) {
        fv = sqrtf(ang + lbl_80298FC8);
        inv = lbl_80298FE8 / fv;
        fn_8002C8FC(M, fv * lbl_80298FE8);
        fn_8002C904(M, (V[9] - V[6]) * inv, (V[2] - V[8]) * inv, (V[4] - V[1]) * inv);
    } else {
        i = 0;
        if (pV[5] > pV[0]) {
            i = 1;
        }
        if (pV[10] > pV[i * 5]) {
            i = 2;
        }
        j = (i + 1) % 3;
        k = (j + 1) % 3;
        fv = sqrtf((pV[i * 5] - (pV[j * 5] + pV[k * 5])) + lbl_80298FC8);
        inv = lbl_80298FE8 / fv;
        M[i] = fv * lbl_80298FE8;
        M[j] = (pV[j * 4 + i] + pV[i * 4 + j]) * inv;
        M[k] = (pV[k * 4 + i] + pV[i * 4 + k]) * inv;
        M[3] = (pV[k * 4 + j] - pV[j * 4 + k]) * inv;
    }

    ((SC02E8 *)a0s)->unk40 = ((PSU *)M)[0].ps;
    ((SC02E8 *)a0s)->unk48 = ((PSU *)M)[1].ps;
    pA30[0] = lbl_80298FCC;
    pA30[1] = lbl_80298FCC;
    pA30[2] = lbl_80298FCC;
    pA30[3] = lbl_80298FC8;
    pA50[0] = lbl_80298FCC;
    pA50[1] = lbl_80298FCC;
    pA50[2] = lbl_80298FCC;
    pA50[3] = lbl_80298FC8;
    ((SC02E8 *)a0s)->unk1354 = 1;

    cnt = 0x3C;
    do {
        n = ((SC02E8 *)a0s)->unk1AC;
        if (n != 0) {
            n--;
            base = (s32 *)((char *)((SC02E8 *)a0s)->unk2F0 + n * 0x1E0);
            for (j = n; j != 0; j--) {
                *(f32 *)((char *)base + 8) = lbl_80298FCC;
                base = (s32 *)((char *)base - 0x1E0);
            }
        }
        ((s32 (*)(void *))((SC02E8 *)a0s)->unk18->fp)((char *)arg0 + ((SC02E8 *)a0s)->unk18->ofs);
    } while (--cnt != -1);

    ((SC02E8 *)a0s)->unk1354 = 0;
    pA30[0] = lbl_80298FCC;
    pA30[3] = lbl_80298FC8;
    pA30[1] = lbl_80298FCC;
    pA30[2] = lbl_80298FCC;
    pA50[0] = lbl_80298FCC;
    pA50[3] = lbl_80298FC8;
    pA50[2] = lbl_80298FCC;
    pA50[1] = lbl_80298FCC;
    ((SC02E8 *)a0s)->unk128 = 1;
    ((SC02E8 *)a0s)->unk60 = 0;

    nd = ((SC02E8 *)a0s)->unk0C;
    nd->n58 = ((SC02E8 *)a0s)->unk20;
    nd->n60 = ((SC02E8 *)a0s)->unk28;
    nd->nB8 = ((SC02E8 *)a0s)->unkB0;
    nd->nC0 = ((SC02E8 *)a0s)->unkB8;
    nd->n70 = ((SC02E8 *)a0s)->unk70;
    nd->n78 = ((SC02E8 *)a0s)->unk78;
    nd->n80 = ((SC02E8 *)a0s)->unk80;
    nd->n88 = ((SC02E8 *)a0s)->unk88;
    nd->n90 = ((SC02E8 *)a0s)->unk90;
    nd->n98 = ((SC02E8 *)a0s)->unk98;
    nd->nA0 = ((SC02E8 *)a0s)->unkA0;
    nd->nA8 = ((SC02E8 *)a0s)->unkA8;
    nd->nB0 = ((SC02E8 *)a0s)->unkB0;
    nd->n108 = nd->nB0;
    nd->nD0 = nd->n70;
    nd->nD8 = nd->n78;
    nd->nE0 = nd->n80;
    nd->nE8 = nd->n88;
    nd->nF0 = nd->n90;
    nd->nF8 = nd->n98;
    nd->n100 = nd->nA0;
    nd->n108 = nd->nA8;

    fn_800C750C(arg0);
    fn_800C7E6C(arg0);
    fn_800A1684(((SC02E8 *)a0s)->unk0C, 1);
    fn_800A1684((void *)((SC02E8 *)a0s)->unk1358, 1);
    if (sp190 != 0) {
        CObject_RemoveRefLink(sp190, &sp190);
        sp190 = 0;
    }
}
