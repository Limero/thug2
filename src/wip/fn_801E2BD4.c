// WIP DRAFT (non-matching) — hand-rebuilt C for fn_801E2BD4 (ProDG/ngccc)
// family=m2c range=0x801E2BD4-0x801E3128 size=1364B
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// Replaces the m2c body (which scored 0.9%).  Everything below is
// hand-decoded from the DOL; see the PARKED block for what is still missing.
//
// === PARKED (2026-10-01) ===
// score: DIFF 16.7% masked (57/341 words), object 1308 B vs want 1364 B.
// 0 emitted inline-asm instructions. No private .rodata.
//
// WHAT WAS CRACKED (all byte-proven against the want):
//  * fn_801E2BD4 is `skater-upright-sideways` matrix rotation:
//    guard `|mtx[0x24]| > 0.95f` (0x802AD7AC) -> return;
//    `v = (-mtx[0x28], 0, mtx[0x20], 0)` (a 2D "perp" of the direction),
//    a PS 4-lane dot product of (mtx[0x10..0x1C]) with v reduced by
//    ps_sum0  ==  mtx[0x10]*(-mtx[0x28]) + mtx[0x18]*mtx[0x20]
//    (a 2-D cross product), then compared against
//    +/-this->f[0x94] * 0.02f * 60.0f  (0x802AD7B4 * 0x802AD7B8).
//  * The PS head is exactly reproducible from the SN_PS.h interface:
//    `typedef float sn_ps __attribute__((mode(PS)))` +
//    ps_mul / ps_merge00 / ps_madd / ps_sum0 on sn_ps loads of the local
//    Vec4 and of mtx[0x18]/mtx[0x10], with a zero-valued constant pair at
//    0x802AD278.  ps_sum0(x,x,x) emits the want's single `ps_sum0 f13,f13,f13,f13`.
//    Reading the result back through a `union {sn_ps; struct{hi,lo};}`
//    reproduces want's `psq_st`/`lfs 0xa8(r1)`/`fmr f13,f0`.
//  * `fn_8012570C(0xABD57877, 0)` returns f32 in f1 (that is the QB hash
//    m2c emitted); 0x802AD7BC = pi/180, 0x802AD7B8 = 60.0.
//  * `fn_80003F54(Mat*,f32)` BUILDS a 4x4 rotation matrix into arg0 and
//    RETURNS it (r3 = its first arg) -> `r9 = fn_80003F54(&rot, angle)`.
//  * The 16-statement 4x4 multiply is `out[i*4+j] = SUM_k m[j*4+k]*r9[i+4k]`
//    (row-major), written out statement-by-statement; the instruction
//    sequence matches want instruction-for-instruction (only register
//    numbering differs).
//  * The two 64-byte block copies are 8 `sn_ps` element assignments each
//    (NOT `*d = *s`: under -mps-float GCC expands a struct assign with
//    lwz/stw 4-byte moves, never psq pairs — verified).
//  * The two `for (c = 4; c != 0; c--) {}` empty loops reproduce want's
//    `li r0,4; mtctr r0; bdnz .` (a branch to ITSELF) exactly; also
//    `do {} while (--c)` and `while (c) c--;` do.
//  * Frame arithmetic is confirmed: Gsave 0xb0 + 4 saved GPRs -> frame
//    0xc0, LR slot at frame+4; locals 0x08 Vec4(16), 0x18 rot(64),
//    0x58 tmp(64), 0x98/0x9C and 0xa0/0xa4 two 8-byte objects,
//    0xa8 sn_ps result.
//  * The m2c constant addresses were right; nothing to correct there.
//
// WHY IT IS STILL STUCK (4 independent walls, all register-allocation):
//  1. DEAD-STORE SURVIVAL. want keeps `stw r3,0x98(r1); stw r31,4(r29)` in
//     each branch where the SECOND word is never read again, and reloads
//     the first (`lwz r9,0x98(r1)`). GCC 2.95's DSE deletes all four stores
//     (tried: separate locals, a `struct {Mat*;Mat*;}`, an array, an
//     inlined struct-returning helper, goto vs else-if — all deleted).
//     Marking them `volatile` DOES keep the stores (and gives the right
//     frame 0xc0 and the right slots 0x98/0xa0/0xa8) but then GCC stops
//     emitting the `lwz` reload and the whole register allocation shifts:
//     that variant scores 3.5%.  So the two forms trade ~13 points each.
//  2. CALLEE-SAVED COUNT. want saves r28-r31 (arg0, arg0+0x20, &obj[0x98],
//     &mtx); this body saves 2.  Getting the 4th/5th value into a
//     callee-saved reg is a consequence of (1).
//  3. ADDRESS REMAT. want emits `addi r3,r1,0x18` AT BOTH calls to
//     fn_80003F54; with a single `Mat rot` GCC hoists `addi r30,r1,0x18`
//     and does `mr r3,r30`.  Block-scoping `rot` in each branch makes GCC
//     remat it, but then GCC allocates TWO 64-byte slots (address escapes
//     => lifetimes overlap => no stack-slot sharing), wrecking the layout.
//  4. FP COLOUR. In all 16 multiply blocks want puts the 2nd term in f13
//     and the 3rd in f12; this body gets f12/f13 swapped.  Identical
//     statement order, identical live ranges, only the local-alloc colour
//     differs.  This alone costs ~240 of the 284 multiply words.
//
// UNTRIED: `register sn_ps`/`f32 __asm__("fr12"/"fr13")` pins on ONE member
// of the f12/f13 pair for the multiply (METHOD §6fq) — 32 loads would have
// to be pinned, which likely defeats the colouring; and a full permutation
// of the 16 statement orderings (the want order is ascending 0..15, which
// is what is used, so there is nothing to permute there).
#include "dolphin/SN_PS.h"

typedef struct Mat_pairs { sn_ps p[8]; } Mat_pairs;
typedef union Mat { Mat_pairs q; f32 f[16]; } Mat;
typedef struct { f32 f[4]; } Vec4;

typedef struct Sub_801E2BD4 {
    char pad0x00[0x78];
    Mat mtx;
} Sub_801E2BD4;

typedef struct Obj_801E2BD4 {
    char pad0x00[0x0C];
    Sub_801E2BD4 *fC;
    char pad0x10[0x10];
    Mat m2;
    char pad0x50[0x44];
    f32 f94;
} Obj_801E2BD4;

typedef union PSU { sn_ps ps; struct { f32 hi, lo; } flt; } PSU;

extern f32 C_802AD7AC;
extern f32 C_802AD7B0;
extern f32 C_802AD7B4;
extern f32 C_802AD7B8;
extern f32 C_802AD7BC;
extern f32 C_802AD7C0;
extern f32 C_802AD278[2];

f32 fn_8012570C(s32, s32);
Mat *fn_80003F54(Mat *, f32);

void fn_801E2BD4(Obj_801E2BD4 *arg0) {
    Sub_801E2BD4 *r7;
    Vec4 v;
    Mat rot;
    Mat tmp;
    Mat *r9;
    Mat *p1a;
    Mat *p1b;
    Mat *p2a;
    Mat *p2b;
    f32 res;
    f32 f11;
    s32 c;
    PSU s;

    r7 = arg0->fC;
    if (fabsf(r7->mtx.f[9]) > C_802AD7AC) {
        return;
    }
    v.f[0] = -r7->mtx.f[10];
    v.f[1] = C_802AD7B0;
    v.f[2] = r7->mtx.f[8];
    v.f[3] = C_802AD7B0;
    s.ps = ps_mul(*(sn_ps *)&r7->mtx.f[6], *(sn_ps *)&v.f[2]);
    s.ps = ps_merge00(s.ps, *(sn_ps *)&C_802AD278[0]);
    s.ps = ps_madd(*(sn_ps *)&r7->mtx.f[4], *(sn_ps *)&v.f[0], s.ps);
    s.ps = ps_sum0(s.ps, s.ps, s.ps);
    res = s.flt.hi;
    f11 = arg0->f94;
    if (res > f11 * C_802AD7B4 * C_802AD7B8) {
        p1a = fn_80003F54(&rot, fn_8012570C(0xABD57877, 0) * C_802AD7BC * arg0->f94);
        p1b = &r7->mtx;
        for (c = 4; c != 0; c--) {
        }
        r9 = p1a;
    } else if (res < f11 * C_802AD7C0 * C_802AD7B8) {
        p2a = fn_80003F54(&rot, -(fn_8012570C(0xABD57877, 0) * C_802AD7BC) * arg0->f94);
        p2b = &r7->mtx;
        for (c = 4; c != 0; c--) {
        }
        r9 = p2a;
    } else {
        return;
    }
    tmp.f[0] = r9->f[0] * r7->mtx.f[0] + r9->f[1] * r7->mtx.f[4] + r9->f[2] * r7->mtx.f[8] + r9->f[3] * r7->mtx.f[12];
    tmp.f[1] = r9->f[0] * r7->mtx.f[1] + r9->f[1] * r7->mtx.f[5] + r9->f[2] * r7->mtx.f[9] + r9->f[3] * r7->mtx.f[13];
    tmp.f[2] = r9->f[0] * r7->mtx.f[2] + r9->f[1] * r7->mtx.f[6] + r9->f[2] * r7->mtx.f[10] + r9->f[3] * r7->mtx.f[14];
    tmp.f[3] = r9->f[0] * r7->mtx.f[3] + r9->f[1] * r7->mtx.f[7] + r9->f[2] * r7->mtx.f[11] + r9->f[3] * r7->mtx.f[15];
    tmp.f[4] = r9->f[4] * r7->mtx.f[0] + r9->f[5] * r7->mtx.f[4] + r9->f[6] * r7->mtx.f[8] + r9->f[7] * r7->mtx.f[12];
    tmp.f[5] = r9->f[4] * r7->mtx.f[1] + r9->f[5] * r7->mtx.f[5] + r9->f[6] * r7->mtx.f[9] + r9->f[7] * r7->mtx.f[13];
    tmp.f[6] = r9->f[4] * r7->mtx.f[2] + r9->f[5] * r7->mtx.f[6] + r9->f[6] * r7->mtx.f[10] + r9->f[7] * r7->mtx.f[14];
    tmp.f[7] = r9->f[4] * r7->mtx.f[3] + r9->f[5] * r7->mtx.f[7] + r9->f[6] * r7->mtx.f[11] + r9->f[7] * r7->mtx.f[15];
    tmp.f[8] = r9->f[8] * r7->mtx.f[0] + r9->f[9] * r7->mtx.f[4] + r9->f[10] * r7->mtx.f[8] + r9->f[11] * r7->mtx.f[12];
    tmp.f[9] = r9->f[8] * r7->mtx.f[1] + r9->f[9] * r7->mtx.f[5] + r9->f[10] * r7->mtx.f[9] + r9->f[11] * r7->mtx.f[13];
    tmp.f[10] = r9->f[8] * r7->mtx.f[2] + r9->f[9] * r7->mtx.f[6] + r9->f[10] * r7->mtx.f[10] + r9->f[11] * r7->mtx.f[14];
    tmp.f[11] = r9->f[8] * r7->mtx.f[3] + r9->f[9] * r7->mtx.f[7] + r9->f[10] * r7->mtx.f[11] + r9->f[11] * r7->mtx.f[15];
    tmp.f[12] = r9->f[12] * r7->mtx.f[0] + r9->f[13] * r7->mtx.f[4] + r9->f[14] * r7->mtx.f[8] + r9->f[15] * r7->mtx.f[12];
    tmp.f[13] = r9->f[12] * r7->mtx.f[1] + r9->f[13] * r7->mtx.f[5] + r9->f[14] * r7->mtx.f[9] + r9->f[15] * r7->mtx.f[13];
    tmp.f[14] = r9->f[12] * r7->mtx.f[2] + r9->f[13] * r7->mtx.f[6] + r9->f[14] * r7->mtx.f[10] + r9->f[15] * r7->mtx.f[14];
    tmp.f[15] = r9->f[12] * r7->mtx.f[3] + r9->f[13] * r7->mtx.f[7] + r9->f[14] * r7->mtx.f[11] + r9->f[15] * r7->mtx.f[15];
    r7->mtx.q.p[0] = tmp.q.p[0];
    r7->mtx.q.p[1] = tmp.q.p[1];
    r7->mtx.q.p[2] = tmp.q.p[2];
    r7->mtx.q.p[3] = tmp.q.p[3];
    r7->mtx.q.p[4] = tmp.q.p[4];
    r7->mtx.q.p[5] = tmp.q.p[5];
    r7->mtx.q.p[6] = tmp.q.p[6];
    r7->mtx.q.p[7] = tmp.q.p[7];
    arg0->m2.q.p[0] = r7->mtx.q.p[0];
    arg0->m2.q.p[1] = r7->mtx.q.p[1];
    arg0->m2.q.p[2] = r7->mtx.q.p[2];
    arg0->m2.q.p[3] = r7->mtx.q.p[3];
    arg0->m2.q.p[4] = r7->mtx.q.p[4];
    arg0->m2.q.p[5] = r7->mtx.q.p[5];
    arg0->m2.q.p[6] = r7->mtx.q.p[6];
    arg0->m2.q.p[7] = r7->mtx.q.p[7];
}