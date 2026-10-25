// WIP DRAFT (non-matching) — REBUILT from disassembly 2026-10-05.
// family=m2c range=0x801D6810-0x801D7528 size=3352B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05 (isolate-801D6810): best 12.89% (tools/score_wip.py
// 0x801D6810 src/wip/fn_801D6810.c -mps-float); official verdict DIFF.
// The old m2c husk measured 8.49% but was a statics-DCE husk (1272B for a
// 3352B function) that could never be edited into a match — this body is a
// full re-decode of the retail bytes and is the one to keep.
//
// WHAT IS NOW CORRECT (vs. the m2c draft)
//   * every callee is prototyped, so the `crclr cr1eq` before each `bl` is gone
//     (ground truth: src/fn_800AA02C.c, src/fn_8014030C.c, src/fn_8014036C.c,
//     src/fn_80003E0C.c, src/fn_80004518 callers, Tmr_GetTime = 0x80124F44,
//     fn_801D7528 takes ONE arg, not two).
//   * Ctx/Actor/Phys struct offsets verified against retail: arg0+0x0C=phys,
//     +0x60/+0x68 floats, +0x314, +0x15A0 (a POINTER, loaded with lwz), +0x15BC;
//     actor +0x2C/+0x74/+0x98/+0x128/+0x194/+0x1B8; phys +0x98/+0xA0 normals,
//     +0xB8/+0xBC/+0xC0 velocity, +0x78..0xB7 the 8-vec4 matrix.
//   * the real control flow (was one giant `||` chain): see the three labels.
//   * QB constants verified: 0x13F33B41 physics_break_air_speed_scale,
//     0x848C5CD6 physics_break_air_up_scale, 0xD757F4BB Skater_Break_Vert_
//     forward_tilt, 0x9D2F8CC8 Skater_vert_push_time.
//   * rodata: 0x802AD504 = 0.0174533f (DEG2RAD), 0x802AD508 = 0.0f (the
//     normalize epsilon), 0x802AD50C = 1.0f, 0x802AD510 = 24.0f,
//     0x802AD278 = the all-zero __ps_t pair, 0x80303150 = the s32 time base.
//   * body A vs body B split: A also does the ps_rsqrte/ps_res "1/len^2" push
//     and scales phys->0xBC by QB_PHYSICS_BREAK_AIR_UP_SCALE, and arms the timer
//     at +0xFC (flag 0); B instead applies a flat 24.0f and arms +0xB4 (flag 1).
//   * the 16 output cells are a 4x4 matmul with 0x10-byte rows, accumulated
//     LEFT TO RIGHT (retail's first dot is mf0*v0 + mf1*v0x10 + mf2*v0x20 +
//     mf3*v0x30, not the right-nested m2c rendering), then copied out as eight
//     __ps_t pairs.
//   * the normalize idiom is the documented one (cf. src/fn_8000714C.c):
//     ps_mul / ps_merge00 / ps_madd / ps_sum0 / ps_rsqrte, and the pair temp is
//     written twice (8-byte psq_st of the rsqrte result, then stfs 1.0f into its
//     high lane) before one 8-byte psq_l read.
//
// RESIDUAL / WHAT I RULED OUT
//   got = 3420B vs want 3352B, and the frame is -0x180 instead of -0xe8. The
//   whole gap is FPR pressure: this body makes GCC save+restore f14..f31 (18
//   callee-saved pairs) where retail saves only f31, which costs ~144 bytes of
//   code and ~176 bytes of frame. It is not caused by variable count:
//   deleting the second normalize block drops it to -0xc0 with NO f31 save, and
//   re-adding it as 3 PS values instead of 4, or pinning a2/b2 to fr12/fr11
//   (register __ps_t __asm__("fr12") compiles and honours the pin), changes
//   nothing — so it is __builtin_ps_sum0/ps_rsqrte pseudos leaking across GCC's
//   local-alloc region, not something the C shape controls.
//   Frame layout retail wants: 0x08..0x0F + 0x10..0x17 = the fn_80003E0C scratch
//   (its & is taken by `addi r27, r1, 8`, and the SAME two slots are reused for
//   the normalize's x/y pair), 0x18..0x47 dead, 0x48..0x87 the 16 result floats,
//   0x88/0x90 the two {matrix, vec} pairs (4(r31) stores), 0x98 the ps_res result,
//   0xA0/0xA8 (body A) and 0xB0/0xB8 (body B) the four inv pairs. This body
//   reaches all of those except that the PS temps get extra homes.
//   Head-of-function register homes also differ: retail r29=arg0, r26=arg1,
//   r31=actor, r28=phys, r27=actor+0x24; this body gets r27=arg0, r26=arg1,
//   r31=actor, r29=phys, r28=actor+0x124 (arg1 and actor already match).
//   Retail keeps `actor+0x24` in r27 from the prologue and derives r9 two
//   different ways (`addi r9,r31,0x124` inside the chain, `addi r9,r27,0x100` in
//   the L_A block); I could not stop GCC from CSE-ing those into one `lwz
//   r0,0x124(r31)` + `mr r9,r0` pair.
//   NOT TRIED (would be a bulk permutation search, so out of bounds here):
//   statement-order / store-order sweeps over the 16 dot products, and
//   tools/psq-scan style reordering of the psq pair-copy runs.
//
// HANDY FACTS FOR THE NEXT ATTEMPT
//   * retail disassembly (PS-decoded) was dumped to
// <scratch> by a throwaway pd.py that reuses
//     tools/ps_diff.py's dec(); plain tools/disasm.py stalls at 0x801D68EC.
//   * the opcode-4 words in this function decode as ps_mul/ps_merge00/ps_madd/
//     ps_sum0/ps_rsqrte/ps_res via tools/ps_diff.py dec() — none of them are
//     the "xo5=6/7/8 hard wall" the older notes claim.
//   * structural skeleton (labels from retail addresses):
//       L_A  0x801D68A0  r9 = actor+0x124; if (r9->4 || arg0->0x314) goto L_B;
//                        if (arg1 == 0) return;
//       L_B  0x801D68C4  if (r9->4 || arg0->0x314) goto bodyB(0x801D6F00);
//                        else bodyA(0x801D68DC);
//       entry chain 0x801D683C..0x801D689C  -> L_A unless
//                        (actor->0x2C!=0 && fn_800AA02C(actor+0x28) >
//                         QB_SKATER_VERT_PUSH_TIME && actor->0x74==0 &&
//                         actor->0x98==0 && actor->0x1B8==0 && actor->0x194==0)
//       bodyA falls through to 0x801D74C8 (tail copy), bodyB to 0x801D7510.
//     The tail copy is eight __ps_t loads from phys+0x78..0xB0 into
//     arg0+0x20..0x58, with `addi r11,r29,0x20` created only for pair #5.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern __ps_t lbl_802AD278;
extern f32 lbl_802AD504;
extern f32 lbl_802AD508;
extern f32 lbl_802AD50C;
extern f32 lbl_802AD510;
extern s32 lbl_80303150;

s32 fn_800AA02C(void *);
s32 fn_8014036C(s32, s32, void *);
f32 fn_8014030C(s32, s32, void *);
void *fn_80003E0C(void *, f32);
void fn_80004518(s32, s32);
s32 Tmr_GetTime(void);
s32 fn_801D7528(void *);

typedef union {
    __ps_t p;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSV;

typedef struct {
    PSV a;
    PSV b;
    f32 rest[11];
} Scratch;

typedef struct {
    char pad0[0x78];
    __ps_t m0[4];
    f32 n0;
    f32 n1;
    __ps_t m1[4];
    f32 x;
    f32 y;
    f32 z;
} Phys;

typedef struct {
    char pad0[0x0C];
    Phys *phys;
    __ps_t pre[2];
    __ps_t tail[8];
    f32 f60;
    f32 f68;
    char pad1[0x2AC];
    s32 f314;
    char pad2[0x1288];
    char *f15A0;
    char *f15BC;
} Ctx;

typedef struct {
    s32 f4;
    s32 f8;
} Timer;

typedef struct {
    char pad0[0x74];
    s32 f74;
    char pad1[0x20];
    s32 f98;
    char pad2[0x88];
    s32 f128;
    char pad3[0x6C];
    s32 f194;
    char pad4[0x20];
    s32 f1B8;
} Actor;

typedef struct {
    void *m;
    void *v;
} MatPair;

#define DOT(K, C)                                                        \
    (mf[K + 0] * vv[C + 0x00] + mf[K + 1] * vv[C + 0x10] +              \
     mf[K + 2] * vv[C + 0x20] + mf[K + 3] * vv[C + 0x30])

#define MULMAT(dst, pair)                                                \
    pair.m = fn_80003E0C(&scratch, ang);                                 \
    dst = (__ps_t *)((char *)ph + 0x78);                                       \
    pair.v = dst;                                                        \
    mf = (f32 *)pair.m;                                                  \
    vv = (f32 *)pair.v;                                                  \
    res[0] = DOT(0, 0x00);                                               \
    res[1] = DOT(0, 0x04);                                               \
    res[2] = DOT(0, 0x08);                                               \
    res[3] = DOT(0, 0x0C);                                               \
    res[4] = DOT(4, 0x00);                                               \
    res[5] = DOT(4, 0x04);                                               \
    res[6] = DOT(4, 0x08);                                               \
    res[7] = DOT(4, 0x0C);                                               \
    res[8] = DOT(8, 0x00);                                               \
    res[9] = DOT(8, 0x04);                                               \
    res[10] = DOT(8, 0x08);                                              \
    res[11] = DOT(8, 0x0C);                                              \
    res[12] = DOT(12, 0x00);                                             \
    res[13] = DOT(12, 0x04);                                             \
    res[14] = DOT(12, 0x08);                                             \
    res[15] = DOT(12, 0x0C);                                             \
    dst[0] = *(__ps_t *)&res[0];                                         \
    dst[1] = *(__ps_t *)&res[2];                                         \
    dst[2] = *(__ps_t *)&res[4];                                         \
    dst[3] = *(__ps_t *)&res[6];                                         \
    dst[4] = *(__ps_t *)&res[8];                                         \
    dst[5] = *(__ps_t *)&res[10];                                        \
    dst[6] = *(__ps_t *)&res[12];                                        \
    dst[7] = *(__ps_t *)&res[14];

void fn_801D6810(Ctx *arg0, s32 arg1) {
    Scratch scratch;
    f32 res[16];
    Actor *act;
    char *act28;
    Phys *ph;
    f32 *mf;
    f32 *vv;
    __ps_t *dst;
    s32 *p;
    s32 i;
    s32 z;
    f32 ang;
    f32 eps;

    ph = arg0->phys;
    act = (Actor *)arg0->f15A0;
    act28 = (char *)act + 0x28;
    if (*(s32 *)(act28 + 4) != 0) {
        s32 tt = fn_800AA02C(act28);
        p = (s32 *)((char *)act + 0x124);
        if ((tt > fn_8014036C(QB_SKATER_VERT_PUSH_TIME, 1, ph))
            && (act->f74 == 0) && (act->f98 == 0) && (act->f1B8 == 0)
            && (act->f194 == 0)) {
            goto sel;
        }
    }
    p = (s32 *)((char *)act + 0x24 + 0x100);
    if (p[1] != 0) {
        goto sel;
    }
    if (arg0->f314 != 0) {
        goto sel;
    }
    if (arg1 == 0) {
        return;
    }
sel:
    if ((p[1] != 0) || (arg0->f314 != 0)) {
        goto bodyB;
    }
    {
        PSV sp98;
        PSV ta0;
        PSV ta8;
        PSV dot;
        MatPair pairA;
        Timer *t;

        ph = arg0->phys;
        sp98.p = (__ps_t)ph->z;
        sp98.p = __builtin_ps_mul(sp98.p, sp98.p);
        sp98.p = __builtin_ps_merge00(sp98.p, lbl_802AD278);
        dot.p = (__ps_t)ph->x;
        sp98.p = __builtin_ps_madd(dot.p, dot.p, sp98.p);
        sp98.p = __builtin_ps_sum0(sp98.p, sp98.p, sp98.p);
        sp98.p = __builtin_ps_rsqrte(sp98.p);
        sp98.p = __builtin_ps_res(sp98.p);
        {
            f32 f31 = sp98.flt.lo
                * fn_8014030C(QB_PHYSICS_BREAK_AIR_SPEED_SCALE, 1, ph);
            ph->x = -arg0->f60 * f31 + ph->x;
            ph->z = -arg0->f68 * f31 + ph->z;
            ph->y = ph->y
                * fn_8014030C(QB_PHYSICS_BREAK_AIR_UP_SCALE, 1, ph);
        }
        ang = fn_8014030C(QB_SKATER_BREAK_VERT_FORWARD_TILT, 1, ph)
            * lbl_802AD504;
        i = 4;
        do {
            i -= 1;
        } while (i != 0);
        MULMAT(dst, pairA)
        z = 0;
        t = (Timer *)((char *)arg0->f15BC + 0x3C);
        if (t->f4 != 0) {
            t->f4 = z;
            t->f8 = lbl_80303150 + Tmr_GetTime();
        }
        t = (Timer *)((char *)arg0->f15BC + 0x48);
        if (t->f4 != 0) {
            t->f4 = z;
            t->f8 = lbl_80303150 + Tmr_GetTime();
        }
        t = (Timer *)((char *)arg0->f15BC + 0x60);
        if (t->f4 != 0) {
            t->f4 = z;
            t->f8 = lbl_80303150 + Tmr_GetTime();
        }
        t = (Timer *)((char *)arg0->f15BC + 0xFC);
        if (t->f4 != 0) {
            t->f4 = z;
            t->f8 = lbl_80303150 + Tmr_GetTime();
        }
        eps = lbl_802AD508;
        scratch.a.p = (__ps_t)ph->x;
        scratch.b.p = (__ps_t)ph->z;
        dot.p = __builtin_ps_mul(scratch.b.p, scratch.b.p);
        dot.p = __builtin_ps_merge00(dot.p, lbl_802AD278);
        dot.p = __builtin_ps_madd(scratch.a.p, scratch.a.p, dot.p);
        dot.p = __builtin_ps_sum0(dot.p, dot.p, dot.p);
        if (dot.flt.lo > eps) {
            ta0.p = __builtin_ps_rsqrte(dot.p);
            ta0.flt.hi = lbl_802AD50C;
            scratch.a.flt.lo = scratch.a.flt.lo * ta0.flt.lo;
            scratch.b.p = __builtin_ps_mul(scratch.b.p, ta0.p);
        }
        ph->n0 = scratch.a.flt.lo;
        ph->n1 = scratch.b.flt.lo;
        {
            PSV a2;
            PSV b2;
            a2.p = (__ps_t)ph->n0;
            b2.p = (__ps_t)ph->n1;
            dot.p = __builtin_ps_mul(b2.p, b2.p);
            dot.p = __builtin_ps_merge00(dot.p, lbl_802AD278);
            dot.p = __builtin_ps_madd(a2.p, a2.p, dot.p);
            dot.p = __builtin_ps_sum0(dot.p, dot.p, dot.p);
            ta8.p = dot.p;
            if (dot.flt.lo > eps) {
                ta8.p = __builtin_ps_rsqrte(dot.p);
                ta8.flt.hi = lbl_802AD50C;
                ph->n0 = ta8.flt.lo * a2.flt.lo;
                b2.p = __builtin_ps_mul(b2.p, ta8.p);
                ph->n1 = b2.flt.lo;
            }
        }
        fn_80004518((s32)((char *)ph + 0x78), 2);
        goto tail;
    }
bodyB:
    if (fn_801D7528(arg0) != 0) {
        goto tail;
    }
    {
        PSV tb0;
        PSV tb8;
        PSV dot;
        MatPair pairB;
        Timer *t;

        ph = arg0->phys;
        {
            f32 s = lbl_802AD510;
            ph->x = -arg0->f60 * s + ph->x;
            ph->z = -arg0->f68 * s + ph->z;
        }
        ang = fn_8014030C(QB_SKATER_BREAK_VERT_FORWARD_TILT, 1, ph)
            * lbl_802AD504;
        i = 4;
        do {
            i -= 1;
        } while (i != 0);
        MULMAT(dst, pairB)
        z = 0;
        t = (Timer *)((char *)arg0->f15BC + 0x3C);
        if (t->f4 != 0) {
            t->f4 = z;
            t->f8 = lbl_80303150 + Tmr_GetTime();
        }
        t = (Timer *)((char *)arg0->f15BC + 0x48);
        if (t->f4 != 0) {
            t->f4 = z;
            t->f8 = lbl_80303150 + Tmr_GetTime();
        }
        t = (Timer *)((char *)arg0->f15BC + 0x60);
        if (t->f4 != 0) {
            t->f4 = z;
            t->f8 = lbl_80303150 + Tmr_GetTime();
        }
        t = (Timer *)((char *)arg0->f15BC + 0xB4);
        if (t->f4 != 1) {
            t->f4 = 1;
            t->f8 = lbl_80303150 + Tmr_GetTime();
        }
        eps = lbl_802AD508;
        scratch.a.p = (__ps_t)ph->x;
        scratch.b.p = (__ps_t)ph->z;
        dot.p = __builtin_ps_mul(scratch.b.p, scratch.b.p);
        dot.p = __builtin_ps_merge00(dot.p, lbl_802AD278);
        dot.p = __builtin_ps_madd(scratch.a.p, scratch.a.p, dot.p);
        dot.p = __builtin_ps_sum0(dot.p, dot.p, dot.p);
        if (dot.flt.lo > eps) {
            tb0.p = __builtin_ps_rsqrte(dot.p);
            tb0.flt.hi = lbl_802AD50C;
            scratch.a.flt.lo = scratch.a.flt.lo * tb0.flt.lo;
            scratch.b.p = __builtin_ps_mul(scratch.b.p, tb0.p);
        }
        ph->n0 = scratch.a.flt.lo;
        ph->n1 = scratch.b.flt.lo;
        {
            PSV a2;
            PSV b2;
            a2.p = (__ps_t)ph->n0;
            b2.p = (__ps_t)ph->n1;
            dot.p = __builtin_ps_mul(b2.p, b2.p);
            dot.p = __builtin_ps_merge00(dot.p, lbl_802AD278);
            dot.p = __builtin_ps_madd(a2.p, a2.p, dot.p);
            dot.p = __builtin_ps_sum0(dot.p, dot.p, dot.p);
            tb8.p = dot.p;
            if (dot.flt.lo > eps) {
                tb8.p = __builtin_ps_rsqrte(dot.p);
                tb8.flt.hi = lbl_802AD50C;
                ph->n0 = tb8.flt.lo * a2.flt.lo;
                b2.p = __builtin_ps_mul(b2.p, tb8.p);
                ph->n1 = b2.flt.lo;
            }
        }
        fn_80004518((s32)((char *)ph + 0x78), 2);
        return;
    }
tail:
    {
        __ps_t *s = (__ps_t *)((char *)arg0->phys + 0x78);
        __ps_t *d = arg0->tail;
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        d[4] = s[4];
        d[5] = s[5];
        d[6] = s[6];
        d[7] = s[7];
    }
}