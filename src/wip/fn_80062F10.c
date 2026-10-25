// WIP DRAFT (non-matching) — hand-rewritten from the want disassembly.
// family=m2c range=0x80062F10-0x800636F4 size=2020B
// extra_cflags: -mps-float
//
// PARKED 2026-10-04 at **DIFF 44.4 %** (222/500 words match after relocation
// masking; was 82/505 = 16.2 % when this round started).  Object is now
// **2000 B = 5 words SHORT of the 2020 B want** (it was 2180 B = 40 words
// LONG).  Everything semantic in this function is believed fixed; the residual
// is (a) a 5-word length deficit concentrated in the three outer-loop latches
// and (b) the callee-saved colour map.
//
// ------------------------------------------------------------------
// FINDINGS (all measured on this body, private LEAF_TMPDIR)
// ------------------------------------------------------------------
// 1. **THE VERTEX SHIFT LOOP WAS A SELF-ASSIGNMENT** — m2c/the previous round
//    wrote `f124[3*(j-1)*f84 + 3i] = f124[3*(j-1)*f84 + 3i]` (same index both
//    sides), which cc1 DCEs, so a whole 26-word loop vanished from the object.
//    Retail (0x80063348-0x800633A4) copies from `3*j` DOWN into `3*(j-1)`, and
//    the loop variable runs `for (j = n2 - 1; j > 0; j--)` with the guard
//    `j-1 > 0` (`addic. r3,r3,-1; bgt`).  With the real indices the loop
//    reappears and matches retail instruction for instruction.
// 2. **RETAIL'S THREE-COMPONENT RUNS ARE "LOAD ALL, THEN STORE ALL"**, and that
//    single fact is what makes the base/stride loads land where they do.  A
//    `f32` store is a hard alias barrier in this cc1, so a statement-interleaved
//    run (`f[A] = f[B]; f[A+2] = f[B+2]; f[A+1] = f[B+1];`) re-reads
//    `o->f84`/`o->f124` (and recomputes `k*f84`) **once per statement**: 6
//    reload groups where retail has 2.  Spelling the run as three loads into
//    temporaries followed by the three stores drops retail's count exactly, and
//    the destination addresses must also be materialised before the first store
//    (`f32 *d = &o->f124[…]; d[0]=c0; d[2]=c2; d[1]=c1;`), otherwise the 2nd and
//    3rd stores re-read `o->f124`.  Measured: 2348 B -> 2260 B (all groups) ->
//    2060 B (also materialising the `1024.0f` fill address) -> 1984 B.
//    *Counter-intuitively* the three **store** statements want the plain
//    subscript form `o->f124[i*3+2] = t2;` (not `d[2] = t2;`): the subscript
//    form alone took 44.4 % -> the pointer form 38.8 %.  Keep both spellings.
// 3. **The index must read `o->f94`, not a saved local `n`.**  Retail reloads
//    `o->f94` inside every one of these loops and computes `3*f94` with the
//    `slwi/add` 3x trick there; a local `n = o->f94 - 1` gets `3*n` hoisted
//    into a long-lived register instead (one extra callee-saved reg, +3 words
//    per group).  `o->f94--;` in place + `o->f94 * 3` in the indices measured
//    2072 B -> 1984 B and +26 matched words.  (Read literally the two are the
//    same value — `o->f94` has just been stored — so this is a codegen oracle,
//    not a semantics change.)
// 4. **`Geo`'s two float fields are `f[1]` and `f[5]`, not `f[4]` and `f[20]`.**
//    Retail touches `r1+0xC` and `r1+0x1C` = `g+4`, `g+0x14`, and the four
//    `psq_st`s land at `g+0/8/0x10/0x18`, i.e. `p[i]` is at 8*i (packed
//    `f[2i],f[2i+1]`) and the two scalars are the *second halves* of `p[0]` and
//    `p[2]`.  Fixing the subscripts moved `fA8`+`fB0`'s neighbours and was
//    needed for the `+8` frame shift below.
// 5. **`Geo *gp = &g;` is load-bearing *now* (it was a measured negative on the
// earlier body).** Retail keeps `&g` in r31 (`mr r31, r3` after the
//    `addi r3,r1,8`) and uses it for the `psq_st` and the `fn_80107D7C` /
//    `fn_80107B20` args; the local reproduces that: 111 -> 139 matched words.
// 6. **The object-pair `+1`/`+2` ORDER INVERTS.**  Retail emits
//    `lfsx …0 / lfs …+8 / lfs …+4 / stfsx …0 / stfs +8 / stfs +4`, i.e. source
//    order 0,2,1.  Writing 0,1,2 in the source makes cc1 emit 0,2,1 here
//    (register-pressure/order artefact) — swapping to 0,1,2 gained 10 matched
//    words (139 -> 149).  Same for the `1024.0f` fill triple.
// 7. **`char padB4[8]` at the end of `Geo`** (+5 words).  Retail's `stmw r25`
//    base is `0xec`, ours `0xe4`: retail's `fctiwz` double slot is at `r1+0xE0`,
//    ours at `r1+0xD8`.  8 bytes of tail padding (after `fB0`, so `fA8` is
//    unmoved) moves it.  `padB4[4]` is inert, `[12]` == `[8]`.
// 8. **A named temp for the `3 * i` factor (§6fr).**  `bi = 3 * i;` hoisted to
//    function scope, before the shift loop, turns the shift loop's `12*i`
//    strength reduction into retail's `3*i` element index: 154 -> 159 matched
//    words.  The *same* temp used in the tail triple HURTS (222 -> 194): there
//    retail strength-reduces to `12*i` and the temp blocks it.
//
// NEGATIVE RESULTS (all measured on this body):
//   `-fstrict-aliasing` / `-fno-strict-aliasing` / `-fargument-noalias*`
//   / `-fforce-mem` / `-fsched-spec-load*` / `-frerun-cse-after-loop`
//   / `-fexpensive-optimizations`  — all produce a BYTE-IDENTICAL 2000 B object
//   (this ngccc accepts the options but ignores them; only `-fschedule-insns2`
//   is live and it is on by default).  `-fno-schedule-insns2` 40.8 %,
//   `-Os` 6.7 %.
//   `o->f94 * 3` inside the `n = o->f94 - 1` / `*e = o->f100[n]` form: 12.7 %
//   (kept the local).  `continue;` at the end of each swap-remove body: inert
//   (byte-identical).  Outer loop with the increments as body statements
//   instead of the `for`-increment clause: 11.9 % (cc1 rotates it differently).
//   `Geo` accessed through `gp` everywhere EXCEPT the `fA8` out-param block:
//   byte-identical.  Using the function-scope `bi` in the tail triple: 38.8 %.
//
// REMAINING BLOCKER:
//   * **length**: 5 words short.  4 of them are the three outer-loop latches —
//     retail saves `i-1` -> r27 and `e-0x30` -> r26 in the preheader and then
//     does `mr r31,r26 / mr r29,r27 / lwz r0,0x94(r30) / addi r29,1 /
//     addi r31,0x30` in the latch, while cc1 here saves the *post*-increment
//     `i+1`/`e+0x30` at the loop TOP (`addi r27,r28,1 / addi r26,r31,0x30`)
//     and restores those, leaving the latch 4 words shorter.  Every spelling
//     tried (`for`-increment clause, explicit body increments, `continue`)
//     picks the same shape; it looks like a register-allocation consequence of
//     retail's two extra long-lived values, not a different source.
//   * **colour**: with the length fixed the callee-saved map is off by two
//     (retail r25-r31 vs got r24-r29 for the loop-carried values), so most of
//     the loops mismatch on register numbers alone even though the instruction
//     sequences are now identical (verified word-by-word for the first
//     swap-remove inner loop, the shift loop and the tail triple).
#include "types.h"
#ifndef __SN__
typedef double __ps_t;
#endif

typedef struct Unk_Obj Unk_Obj;

typedef struct {
    f32 v[6];
    char pad18[0x10];
    f32 t;
    f32 lim;
} Elem;

typedef struct { __ps_t p[2]; } Pairs;

typedef union {
    __ps_t p[4];
    f32 f[8];
} GeoTop;

typedef struct {
    GeoTop t;
    char pad20[0x88];
    s32 fA8;
    s32 fAC;
    s32 fB0;
    char padB4[8];
} Geo;

struct Unk_Obj {
    char pad0[0x8];
    void **vt;
    char padC[0x1C];
    volatile Pairs bb;
    Pairs bb2;
    char pad48[0x10];
    s32 m12[3];
    f32 f64;
    char pad68[0x10];
    f32 f78;
    f32 f7C;
    s32 f80;
    s32 f84;
    char pad88[0xC];
    s32 f94;
    char pad98[0x5C];
    f32 fF4;
    char padF8[0x8];
    Elem *f100;
    char pad104[0x4];
    s32 f108;
    char pad10C[0x18];
    f32 *f124;
    char pad128[0x8];
    s32 f130;
    char pad134[0x18];
    s32 f14C;
    char pad150[0x8];
    s32 f158;
    s32 f15C;
    char pad160[0x4];
    s32 f164;
    s32 f168;
};

extern s32 lbl_80300E00;
extern f32 lbl_803CAF38;

s32 fn_8009F498(void *);
void fn_800636F4(void *);
void fn_80064540(void *);
s32 fn_8005DE90(void *);
s32 fn_800557B8(s32 *, f32);
void fn_800639E8(void *);
void fn_801309EC(void *);
void fn_8010794C(void *);
s32 fn_80107B20(void *, s32, s32);
f32 fn_80107D7C(void *);
void fn_8009DFC0(void *, s32 *);
s32 fn_80064294(void *);

#define GETN(o) ({ void **t_ = (o)->vt; \
                   ((s32 (*)(void *))t_[7])((char *)(o) + (signed short)((s16 *)t_)[6]); })

void fn_80062F10(Unk_Obj *o, s32 arg1, f32 dt) {
    Elem *e;
    s32 i, j, k, n, n2, lim, bi;
    Geo g;

    if ((o->f130 != 0 && o->f94 == 0) || (o->f80 != 0 && fn_8009F498((void *)o->f80) == 0)) {
        if (o != NULL) {
            void **t = o->vt;
            void (*fp)(void *, s32) = (void (*)(void *, s32))t[3];
            fp((char *)o + (signed short)((s16 *)t)[4], 3);
        }
    } else if (arg1 == 0 && o->f158 != 0) {
        fn_800636F4(o);
        fn_80064540(o);
        o->f15C = 1;
        if (lbl_80300E00 == 1 && fn_8005DE90(0) != 0 && o->f168 != 0 &&
            fn_800557B8(o->m12, o->f64) != 0) {
            o->f15C = arg1;
            if (o->f78 == 0.0f) {
                for (i = 0, e = o->f100; i < o->f94; i++, e++) {
                    e->t = e->t + dt;
                    if (e->t > e->lim) {
                        o->f94--;
                        *e = o->f100[o->f94];
                        j = 0;
                        k = 0;
                        while (j < GETN(o)) {
                            {
                                f32 *d = &o->f124[k * o->f84 + i * 3];
                                f32 c0 = o->f124[k * o->f84 + o->f94 * 3 + 0];
                                f32 c1 = o->f124[k * o->f84 + o->f94 * 3 + 1];
                                f32 c2 = o->f124[k * o->f84 + o->f94 * 3 + 2];
                                d[0] = c0;
                                d[1] = c1;
                                d[2] = c2;
                            }
                            {
                                f32 *z = &o->f124[k * o->f84 + o->f94 * 3];
                                z[0] = 1024.0f;
                                z[1] = 1024.0f;
                                z[2] = 1024.0f;
                            }
                            j++;
                            k += 3;
                        }
                    }
                }
                return;
            }
        }
        {
            f32 sc = o->f78;
            if (sc != 0.0f) {
                s32 w;
                o->f7C = o->f7C + dt;
                w = (s32)(o->f7C * sc);
                if (w != 0) {
                    o->f7C = o->f7C - w / sc;
                    fn_800639E8(o);
                }
            }
        }
        if (o->f108 != 0) {
            fn_801309EC((void *)o->f108);
        }
        if (o->f14C != 0 && dt != 0.0f) {
            if (o->f164 != 0) {
                Geo *gp = &g;
                fn_8010794C(gp);
                gp->t.p[0] = o->bb.p[0];
                gp->t.p[2] = o->bb.p[0];
                gp->t.p[1] = o->bb.p[1];
                gp->t.p[3] = o->bb.p[1];
                gp->t.f[1] = gp->t.f[1] + 1.0f;
                gp->t.f[5] = gp->t.f[5] - 4800.0f;
                if (fn_80107B20(gp, 0, 0) != 0) {
                    o->fF4 = 2.0f * fn_80107D7C(gp);
                }
                if (gp->fA8 != 0) {
                    fn_8009DFC0((void *)gp->fA8, &gp->fA8);
                    gp->fA8 = 0;
                }
            }
            {
                f32 sc2 = dt * lbl_803CAF38;
                for (i = 0, e = o->f100; i < o->f94; i++, e++) {
                    e->t = e->t + dt;
                    e->v[0] = sc2 * e->v[3] + e->v[0];
                    e->v[1] = sc2 * e->v[4] + e->v[1];
                    e->v[2] = sc2 * e->v[5] + e->v[2];
                    {
                        void **t = o->vt;
                        s32 (*fp)(void *) = (s32 (*)(void *))t[7];
                        n2 = fp((char *)o + (signed short)((s16 *)t)[6]);
                    }
                    bi = 3 * i;
                    for (j = n2 - 1; j > 0; j--) {
                        s32 b = 3 * j;
                        s32 b3 = b - 3;
                        {
                            f32 *d = &o->f124[b3 * o->f84 + bi];
                            f32 c0 = o->f124[b * o->f84 + bi + 0];
                            f32 c1 = o->f124[b * o->f84 + bi + 1];
                            f32 c2 = o->f124[b * o->f84 + bi + 2];
                            d[0] = c0;
                            d[1] = c1;
                            d[2] = c2;
                        }
                    }
                    {
                        f32 t2 = sc2 * e->v[2] + o->f124[i * 3 + 2];
                        f32 t1 = sc2 * e->v[1] + o->f124[i * 3 + 1];
                        f32 t0 = sc2 * e->v[0] + o->f124[i * 3 + 0];
                        o->f124[i * 3 + 2] = t2;
                        o->f124[i * 3 + 1] = t1;
                        o->f124[i * 3 + 0] = t0;
                    }
                }
            }
            for (i = 0, e = o->f100; i < o->f94; i++, e++) {
                if (e->t > e->lim) {
                    o->f94--;
                    *e = o->f100[o->f94];
                    j = 0;
                    k = 0;
                    while (j < GETN(o)) {
                            {
                                f32 *d = &o->f124[k * o->f84 + i * 3];
                                f32 c0 = o->f124[k * o->f84 + o->f94 * 3 + 0];
                                f32 c1 = o->f124[k * o->f84 + o->f94 * 3 + 1];
                                f32 c2 = o->f124[k * o->f84 + o->f94 * 3 + 2];
                                d[0] = c0;
                                d[1] = c1;
                                d[2] = c2;
                            }
                            {
                                f32 *z = &o->f124[k * o->f84 + o->f94 * 3];
                                z[0] = 1024.0f;
                                z[1] = 1024.0f;
                                z[2] = 1024.0f;
                            }
                        j++;
                        k += 3;
                    }
                }
            }
            lim = fn_80064294(o);
            for (i = 0, e = o->f100; i < o->f94; i++, e++) {
                if (lim < o->f94) {
                    o->f94--;
                    *e = o->f100[o->f94];
                    j = 0;
                    k = 0;
                    while (j < GETN(o)) {
                            {
                                f32 *d = &o->f124[k * o->f84 + i * 3];
                                f32 c0 = o->f124[k * o->f84 + o->f94 * 3 + 0];
                                f32 c1 = o->f124[k * o->f84 + o->f94 * 3 + 1];
                                f32 c2 = o->f124[k * o->f84 + o->f94 * 3 + 2];
                                d[0] = c0;
                                d[1] = c1;
                                d[2] = c2;
                            }
                            {
                                f32 *z = &o->f124[k * o->f84 + o->f94 * 3];
                                z[0] = 1024.0f;
                                z[1] = 1024.0f;
                                z[2] = 1024.0f;
                            }
                        j++;
                        k += 3;
                    }
                }
            }
            o->bb2.p[1] = o->bb.p[1];
            o->bb2.p[0] = o->bb.p[0];
        }
    }
}
