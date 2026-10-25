// WIP DRAFT (non-matching) — hand-rebuilt from the DOL disassembly
// family=m2c range=0x800BB02C-0x800BB738 size=1804B
//
// 2026-09-27 REBUILD.  The previous body was the m2c statics-DCE husk: it
// modelled ~20 stack slots as file-scope `static s32 sp48/sp4C/sp50/spD0`, so
// ngccc proved the entire paired-single block dead and emitted 720 bytes
// against retail's 1804 (§6j-4 / trap 7).
// Semantic fixes made here (all verified against the DOL):
//   * fn_80036304 is a ONE-argument dot4 (see the promoted src/fn_80036304.c:
//     `f32 fn_80036304(CStruct *p){return x*x+y*y+z*z+w*w;}`); m2c invented a
//     TEN-argument call.  sqrtf is floorf and is CHAINED off that result
//     (recipe 23: `sqrtf(fn_80036304(...))`, r3/r4 untouched at both bl).
//   * loop strides: src 0x10 / 0x18 / 0x28 bytes (m2c had 0x10/0x18 and a
//     bogus 0x28 destination base).  Destinations are unsymboled bss at
//     0x8032E458 / 0x8032E5D8 / 0x8032E758 (m2c had 0x8037E758 for the 3rd).
//   * each loop runs count-`i` times, 1-based: entry `cmpwi n,0 / beq`, then
//     `cmpwi i,0 / addi i,-1 / bne` per pass (recipe 15, unsigned count).
//   * the 11 floats at obj+0x158 are one array `e[11]`; the cofactor block
//     writes e[0,1,2,4,5,6,8,9,10] and the three loops READ the same entries
//     as their 8 coefficients (e[0,1,2,4,5,6,8,9,10]) -- m2c modelled them as
//     unrelated `unk0x158..unk0x180` slots.
//   * file-local struct typedef with the true field types (trap 1 / §6bb-286);
//     the shared `Unk_4099A4C2` route is not used.
//
// PRECISE RESIDUAL -- unreachable opcodes, not scheduling (doc-06 M5.0h):
// 0x800BB058..0x800BB38C is a paired-single block built from the pair-product
// variants primary-opcode-4 XO5=12 with C-field 3/5/7/8/10/12/13 -- 20
// occurrences -- plus FIVE `ps_mr` (XO9=72) lane-stitches whose results are
// never read before being overwritten (0x800BB094, 0x800BB0C4, 0x800BB0D0,
// 0x800BB2E8, 0x800BB37C).  A compile probe of cc1.exe 3.9.3's whole
// `__builtin_ps_*` table (49 builtin names, 2- and 3-arg forms) emits ONLY
// XO5=25 (ps_mul), XO5=12/C=0 (ps_muls0), and the add/sub/div/merge00-11 /
// madd/msub/nmadd/nmsub/sum0/sum1/madds0/madds1/sel family; the C!=0 mul
// forms have no builtin, and 8 explicit lane-select spellings
// (merge00/01/10/11 + per-lane multiply) all fold away to nothing.  `ps_mr`
// itself ICEs (optabs.c:4116).  Dead PS values are additionally DCE'd from
// every C form (§6ax-230).  Those ~190 instructions are therefore not
// reachable from asm-free C.  The block below carries the data flow with
// `ps_mul` standing in for the C!=0 forms, which is an INFERENCE, not a match.
// Everything from 0x800BB390 on (the cofactor block + three loops, 262 of 451
// instructions) is pure scalar and IS byte-exact-eligible, but it scores at a
// shifted offset because the PS block emits a different length.
//
// MEASURED 2026-09-27 (`tools/test_wip_drafts.py --addr 0x800BB02C`, flags
// auto = `-mps-float`): DIFF, masked score 0.2-1.1%, want 1804 B (451 insns)
// vs got 1744-1760 B (436-440 insns).  Prior husk: 720 B, 1.67%.
//
// What the 3 residual clusters are, in order of cost:
//  1. PS block (0x800BB058..0x800BB38C, ~190 insns) -- unreachable opcodes,
//     see above.  Also costs 3 saved FPRs + an extra saved GPR and a 0x1A0
//     frame where want has 2 FPRs / 1 GPR and 0x110, because the unreachable
//     ops hide ~14 simultaneously-live PS values that want keeps in f0..f13.
//  2. Destination-array addresses -- FIXED 2026-10-06.  want materialises
//     each bss base as `lis r9,-0x7fc8 ; addi r9,r9,-0x1BA8` = 0x8037E458,
//     i.e. @ha/@l of the REAL symbol lbl_8037E458 (.bss:0x8037E458
//     size:0x180); the other two are lbl_8037E5D8 (size:0x180) and
//     lbl_8037E758 (size:0x20).  The earlier note mis-read the `lis`
//     immediate as 0x8034, concluded the bases were unlabelled literals
//     ("0x8032E458/0x8032E5D8/0x8032E758") and left the body emitting
//     `lis`+`ori` on a fabricated address.  The body now names the three
//     symbols, which emits the want's `lis`+`addi` pair (ADDR16_HA/LO are
//     masked in the sweep, but the link would have differed in 3 words).
//     Corroboration: lbl_8037E758's size 0x20 = two 16-byte slots, which
//     bounds loop 3 (nA4) while the other two hold up to 24 slots each.
//  3. Loop latch shape: gcc turns the three countdowns into `mtctr/bdnz`;
//     want uses `addi rN,-0x10 / cmpwi / bne`.  `-fno-strength-reduce
//     -fno-branch-count-reg` DOES fix the latch (and the `lfsx` indexed
//     source loads already match), but it removes 16 further bytes, so it
//     makes the positional score worse -- deliberately NOT stamped as a
//     `// FLAG:` line.  If a future session fixes the frame first, that flag
//     pair is the next lever (§6y-141 / §6ap-1).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
typedef float sn_ps __attribute__((mode(PS)));

extern f32 lbl_80298DD0;
extern f32 lbl_80298DD4;
extern f32 lbl_80298DD8;
extern f32 lbl_80298DDC;
extern f32 lbl_80298DE0;

/* the three destination arrays: real .bss symbols (see blocker 2 header note) */
extern u8 lbl_8037E458[];
extern u8 lbl_8037E5D8[];
extern u8 lbl_8037E758[];

typedef union { sn_ps ps; f32 f[2]; } P2;

typedef struct {
    char _000[0x20];
    P2 m20;                       /* 0x20 */
    P2 m28;                       /* 0x28 */
    char _030[0x34];
    s32 *p64;                      /* 0x64 */
    char _068[0x2C];
    u16 n94;                       /* 0x94 */
    char _096[0x2];
    s32 *p98;                      /* 0x98 */
    u16 n9C;                       /* 0x9C */
    char _09E[0x2];
    s32 *pA0;                      /* 0xA0 */
    u16 nA4;                       /* 0xA4 */
    char _0A6[0x72];
    P2 m118;                      /* 0x118 */
    P2 m120;                      /* 0x120 */
    P2 m128;                      /* 0x128 */
    P2 m130;                      /* 0x130 */
    P2 r138;                      /* 0x138: m00 m01 */
    P2 r140;                      /* 0x140: m10 m11 */
    P2 r148;                      /* 0x148: the 3-vector tail */
    f32 v150;                     /* 0x150 */
    char _154[0x4];
    f32 e[11];                     /* 0x158..0x183: inverse + loop coeffs */
    char _184[0x15];
    s8 state;                      /* 0x199 */
} BB;

/* loop-3 source element: stride 0x28, floats at 0/4/8/0xc and an INT guard
   at 0x20 (want: `lwz r0,0x20(r9)` + `cmpwi r0,0`, not a float compare). */
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    s32 _10[4];
    s32 flag;                     /* 0x20 */
    s32 _24;
} L3Ent;

f32 fn_80036304(void *arg0);
f32 sqrtf(f32 farg0);

typedef struct {
    P2 g8, g10, s18, s20, s28, s30, s38, s40, s48, s50, s58, s60,
       s68, s70, s78, s80, s88, s90, s98, sA0, sA8, sB0, sB8,
       sC0, sC8, sD0, sD8, sE0, padE8, padF0;
} FRM;

void fn_800BB02C(BB *o, f32 farg0) {
    FRM fr;
    f32 s14;
    f32 spE0;
    f32 K1 = lbl_80298DD4;
    f32 K2 = lbl_80298DD8;
    f32 K3 = lbl_80298DDC;
    f32 K4 = lbl_80298DE0;
    P2 t;
    P2 p0;
    P2 p1;
    P2 p2;
    P2 p3;
    P2 p4;
    P2 M0;
    P2 M1;
    f32 r0;
    f32 r1;
    f32 r2;
    f32 r3;
    f32 sc;
    f32 x0;
    f32 x1;
    f32 x2;
    f32 y0;
    f32 y1;
    f32 y2;
    f32 y3;
    f32 y4;
    f32 y5;
    s32 n1;
    s32 n2;
    s32 n3;
    s32 i1;
    s32 i2;
    s32 i3;
    f32 *src;
    f32 v28;
    f32 v2C;
    f32 v30;

    /* --- two-state paired-single block (see RESIDUAL above) --- */
    if (o->state <= 2) {
        P2 t0;
        P2 t2;

        fr.s98.f[0] = farg0 * lbl_80298DD0;
        fr.sA0.f[0] = farg0;
        fr.sA8.f[0] = farg0;

        fr.g8 = o->m128;
        fr.g10 = o->m130;
        M0 = o->m20;
        M1 = o->m28;
        t = fr.g8;
        p0.ps = __builtin_ps_mul(t.ps, M0.ps);
        t.ps = __builtin_ps_add(t.ps, p0.ps);
        p1.ps = __builtin_ps_mul(t.ps, M1.ps);
        t2 = fr.g10;
        t0.ps = __builtin_ps_add(t2.ps, p1.ps);
        p2.ps = __builtin_ps_mul(t0.ps, M1.ps);
        p3.ps = __builtin_ps_mul(t.ps, M0.ps);
        t0 = t;
        t0.f[0] = t.f[0];
        t0.f[1] = p1.f[1];
        p4.ps = __builtin_ps_mul(t.ps, t0.ps);
        o->m130.ps = __builtin_ps_sub(p2.ps, o->m130.ps);
        o->m128.ps = __builtin_ps_add(p3.ps, o->m128.ps);
        o->m120.ps = __builtin_ps_add(o->m120.ps, p4.ps);
        o->m118.ps = __builtin_ps_add(o->m118.ps, p4.ps);
        fr.s18 = p3;
        fr.s20 = p2;
    } else {
        P2 t0;

        fr.sB0.f[0] = farg0;
        t0 = fr.sB0;
        t = o->m128;
        t0.f[1] = t.f[1];
        t.ps = __builtin_ps_mul(t0.ps, t0.ps);
        fr.g8 = t;
        t0.ps = __builtin_ps_mul(t.ps, o->m20.ps);
        fr.g10 = t0;
        o->m130.ps = __builtin_ps_sub(t0.ps, o->m130.ps);
        o->m128.ps = __builtin_ps_add(t.ps, o->m128.ps);
    }

    /* --- the cofactor prologue: cross products into the ten pair slots --- */
    fr.s18.f[0] = o->r148.f[0] * K1;
    fr.s18.f[1] = o->r148.f[1] * K1;
    fr.s20.f[0] = o->v150 * K1;
    fr.sD8.f[0] = farg0;
    fr.s20.f[1] = K2;
    fr.s28 = o->r138;
    fr.s30 = o->r140;
    fr.s38.f[0] = fr.s18.f[1];
    fr.s38.f[1] = o->r138.f[1];
    fr.s40.f[0] = fr.s20.f[1];
    fr.s40.f[1] = K2;
    fr.sB8.f[0] = fr.g8.f[1];
    fr.sC0.f[0] = K2;
    fr.sC0.f[1] = K2;
    fr.s48 = fr.s18;
    fr.s50 = fr.s20;
    {
        P2 a0;
        P2 a1;
        P2 a2;
        P2 a3;
        P2 a4;
        P2 a5;
        P2 a6;
        P2 a7;
        P2 a8;
        P2 a9;
        P2 b0;
        P2 b1;
        P2 b2;
        P2 b3;
        f32 k2 = K2;

        a0.f[0] = fr.s48.f[0];
        a0.f[1] = fr.s30.f[0];
        a1.f[0] = fr.s30.f[0];
        a1.f[1] = k2;
        a2.f[0] = fr.s40.f[0];
        a2.f[1] = fr.s18.f[0];
        a3.f[0] = fr.s28.f[0];
        a3.f[1] = k2;
        a4.f[0] = k2;
        a4.f[1] = k2;
        a5.f[0] = fr.s18.f[0];
        a5.f[1] = fr.s20.f[0];
        a6.f[0] = fr.s30.f[0];
        a6.f[1] = k2;
        a7.f[0] = fr.s38.f[0];
        a7.f[1] = k2;
        a8.f[0] = fr.s48.f[0];
        a8.f[1] = fr.s50.f[0];
        a9.f[0] = k2;
        a9.f[1] = k2;
        b0.ps = __builtin_ps_mul(a0.ps, a2.ps);
        b1.ps = __builtin_ps_mul(a0.ps, a3.ps);
        b2.ps = __builtin_ps_mul(a0.ps, a0.ps);
        b3.ps = __builtin_ps_mul(a0.ps, a1.ps);
        a6.ps = __builtin_ps_sub(b0.ps, b1.ps);
        a7.ps = __builtin_ps_sub(b0.ps, b2.ps);
        a8.ps = __builtin_ps_add(b2.ps, b3.ps);
        a9.ps = __builtin_ps_add(b1.ps, b3.ps);
        fr.s80.ps = __builtin_ps_muls0(a4.ps, a6.ps);
        fr.s78.ps = __builtin_ps_muls0(a4.ps, a3.ps);
        fr.sC8.ps = __builtin_ps_merge00(a6.ps, a6.ps);
        fr.s70.ps = __builtin_ps_muls0(a4.ps, a2.ps);
        fr.s68.ps = __builtin_ps_muls0(a4.ps, a1.ps);
        fr.s50.ps = __builtin_ps_merge10(a8.ps, a8.ps);
        fr.s58.ps = __builtin_ps_add(fr.s78.ps, fr.s68.ps);
        fr.s60.ps = __builtin_ps_add(fr.s80.ps, fr.s70.ps);
        a9.ps = __builtin_ps_sub(fr.s50.ps, a8.ps);
        fr.s88.ps = __builtin_ps_merge10(a9.ps, a6.ps);
        fr.s90 = fr.sC8;
        fr.s48.ps = __builtin_ps_add(fr.s88.ps, fr.s58.ps);
        fr.s50.ps = __builtin_ps_add(fr.s90.ps, fr.s60.ps);
    }

    /* --- 3-vector result -> obj+0x138..0x144, then round its length --- */
    {
        P2 cst;
        P2 q0;
        P2 q1;
        P2 acc;

        fr.g8.f[0] = fr.s48.f[0];
        fr.g8.f[1] = fr.s48.f[1];
        fr.g10.f[0] = fr.s50.f[0];
        cst.f[0] = *(f32 *)0x80298CA0;
        cst.f[1] = *(f32 *)0x80298CA4;
        q0 = fr.s30;
        q0.ps = __builtin_ps_mul(fr.s90.ps, q0.ps);
        q1 = fr.s38;
        q0.ps = __builtin_ps_merge00(cst.ps, q0.ps);
        acc.ps = __builtin_ps_madd(q0.ps, fr.s28.ps, q1.ps);
        fr.sD0.ps = __builtin_ps_sum0(acc.ps, acc.ps, acc.ps);
        fr.g8.ps = __builtin_ps_muls0(fr.sD0.ps, fr.g8.ps);
        fr.g10.ps = __builtin_ps_muls0(fr.sD0.ps, fr.g10.ps);
        o->r138.ps = __builtin_ps_add(fr.g8.ps, o->r138.ps);
        o->r140.ps = __builtin_ps_add(fr.g8.ps, o->r140.ps);
    }
    s14 = fr.sB8.f[0] * K2 - fr.sD0.f[0];
    spE0 = sqrtf(fn_80036304(&o->r138));
    if (spE0 > K2) {
        fr.sE0.f[0] = K3 / spE0;
        o->r138.ps = __builtin_ps_muls0(fr.sE0.ps, o->r138.ps);
        o->r140.ps = __builtin_ps_muls0(fr.sE0.ps, o->r140.ps);
    }

    /* --- cofactor / inverse of the 3x3 built from the rotated row --- */
    r0 = o->r138.f[0];
    r1 = o->r138.f[1];
    r2 = o->r140.f[0];
    r3 = o->r140.f[1];
    sc = r1 * r1;
    sc = r0 * r0 + sc;
    sc = r2 * r2 + sc;
    sc = r3 * r3 + sc;
    if (sc > K2) {
        sc = K4 / sc;
    } else {
        sc = K2;
    }
    {
        f32 m00 = r0;
        f32 m01 = r1;
        f32 m10 = r2;
        f32 m11 = r3;
        f32 a = m00 * sc;
        f32 b = m01 * sc;
        f32 c = m10 * sc;
        f32 p;
        f32 q;
        f32 u;
        f32 v;
        f32 w;
        f32 z;

        p = m00 * a;
        q = m01 * b;
        u = m10 * c;
        v = m00 * c;
        w = m11 * c;
        z = m11 * a;
        y0 = v + z;
        y1 = m00 * b - w;
        x0 = p + q;
        y2 = m01 * c - z;
        y3 = m01 * c + z;
        x1 = p + u;
        x2 = q + u;
        y4 = v - z;
        y5 = m00 * b + w;
        o->e[1] = y1;
        o->e[2] = y0;
        o->e[6] = y2;
        o->e[10] = K3 - x0;
        o->e[0] = K3 - x2;
        o->e[5] = K3 - x1;
        o->e[4] = y5;
        o->e[8] = y4;
        o->e[9] = y3;
    }

    /* --- three fixed-size transform loops, 1-based (element 0 skipped) --- */
    n1 = o->n94;
    for (i1 = n1; i1 != 0; i1--) {
        f32 *d = (f32 *)(lbl_8037E458 + (i1 - 1) * 16);
        src = (f32 *)((char *)o->p64 + (i1 - 1) * 16);
        v28 = src[2] * o->e[8] + (src[0] * o->e[0] + src[1] * o->e[4]);
        v2C = src[2] * o->e[9] + (src[0] * o->e[1] + src[1] * o->e[5]);
        v30 = src[2] * o->e[10] + (src[0] * o->e[2] + src[1] * o->e[6]);
        d[0] = v28;
        d[1] = v2C;
        d[2] = v30;
        d[3] = src[3];
    }

    n2 = o->n9C;
    for (i2 = n2; i2 != 0; i2--) {
        f32 *d = (f32 *)(lbl_8037E5D8 + (i2 - 1) * 16);
        src = (f32 *)((char *)o->p98 + (i2 - 1) * 24);
        v28 = src[2] * o->e[8] + (src[0] * o->e[0] + src[1] * o->e[4]);
        v2C = src[2] * o->e[9] + (src[0] * o->e[1] + src[1] * o->e[5]);
        v30 = src[2] * o->e[10] + (src[0] * o->e[2] + src[1] * o->e[6]);
        d[0] = v28;
        d[1] = v2C;
        d[2] = v30;
        d[3] = src[3];
    }

    n3 = o->nA4;
    for (i3 = n3; i3 != 0; i3--) {
        f32 *d = (f32 *)(lbl_8037E758 + (i3 - 1) * 16);
        L3Ent *s = (L3Ent *)((char *)o->pA0 + (i3 - 1) * 40);

        if (s->flag != 0) {
            v28 = s->z * o->e[8] + (s->x * o->e[0] + s->y * o->e[4]);
            v2C = s->z * o->e[9] + (s->x * o->e[1] + s->y * o->e[5]);
            v30 = s->z * o->e[10] + (s->x * o->e[2] + s->y * o->e[6]);
            d[0] = v28;
            d[1] = v2C;
            d[2] = v30;
            d[3] = s->w;
        }
    }
}

// PARKED 2026-10-06: blocked on the PAIRED-SINGLE OPCODE WALL, not on the C.
// 0x800BB058..0x800BB38C (~190 of 451 instructions) is built from primary
// opcode-4 pair-product forms (XO5=12, C-field 3/5/7/8/10/12/13) plus five
// `ps_mr` lane stitches, and cc1.exe 3.9.3's `__builtin_ps_*` table has no
// builtin for the C!=0 variants (and ICEs on ps_mr -- optabs.c:4116), so those
// words are not reachable from asm-free C; the block below carries their data
// flow with `ps_mul` standing in, which is an inference, not a match.
// Everything from 0x800BB390 on (cofactor block + three walks, 262/451
// instructions) is scalar and matchable once the PS block stops shifting the
// positional score.
//
// Two non-PS defects were found and fixed in this pass (both were the body's
// fault, not the compiler's):
//   * the three destination bases were fabricated literals -- they are the
//     real .bss symbols lbl_8037E458 / lbl_8037E5D8 / lbl_8037E758, now used
//     by name (see blocker 2 in the header);
//   * loop 3's per-entry guard was read as a float (`src[8] != 0` -> `lfs` +
//     `fcmpu`) where want has `lwz r0,0x20(r9)` + `cmpwi r0,0`, so the entry
//     is now the L3Ent struct with `s32 flag` at 0x20 -- a declared-type fix,
//     not a cast.
// Residual of the still-open work: the first PS branch's frame/regalloc
// (want 0x110 frame, 2 FPRs + r30; the broken PC block forces more), the
// loop-latch shape (want `addi rN,-0x10`/`cmpwi`/`bne`, GCC gives
// mtctr/bdnz -- `-fno-strength-reduce -fno-branch-count-reg` fixes the latch
// but is not stamped because it shortens the object further), and the
// `sqrtf`-named callee at 0x80270CA4 (declared `f32` here).
// NOT re-measured this pass (no compiler available to this worker);
// re-verify with `tools/test_wip_drafts.py --addr 0x800BB02C`.
