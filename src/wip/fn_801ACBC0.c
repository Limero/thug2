// WIP DRAFT (non-matching) — hand-rebuilt from the PS disassembly.
// family=m2c range=0x801ACBC0-0x801ACF84 size=964B
// extra_cflags: -mps-float -fno-schedule-insns
//
// PARKED 2026-10-05 (w-0x801ACBC0/rebuilt): DIFF 10.46% (956B object vs 964B
// want; was DIFF 0.83% / 1072B from the m2c husk). The whole function is now
// reconstructed SEMANTICALLY and structurally right — 14/241 words match from
// word 0 and 200+/241 match under LCS alignment: frame 0x188, stmw r18 0x130 /
// 14 callee-saved GPRs, stfd+lfd f28..f31 @0x168/0x170/0x178/0x180, LR 0x18c,
// slot order s0@0x08 / C@0x28 / D@0x38 / s1@0x48 / o0@0x68 / o1@0x78 /
// d@0x88 / out@0x98 / mat@0xC0 / ts@0x100 / tt@0x104 / sq@0x108, Elem stride
// 0x60 with a@0x08 / b@0x18 / v@0x28 / p48@0x48 / flags@0x50 / id@0x54, the
// whole psq_l/ps_sub/ps_mul/ps_merge00/ps_madd/ps_sum0 distance block (14
// words) byte-for-byte, the `ok`-flag li/andi/li/cmpwi idiom, and the
// fn_800EA994 7-arg form (r3..r8 + f1; the 8-arg m2c proto was wrong).
//
// Residual (all regalloc/scheduling, no semantic content left):
//  (a) LENGTH 956B vs 964B. WANT's copy block materialises BOTH &s0 and &D
//      into registers (`addi r9,r1,8; mr r3,r9` and `addi r27,r1,0x38;
//      mr r6,r27`, 4 words); ngccc emits one-shot `addi r3,r1,8` +
//      `addi r6,r1,0x38` (2). WANT also does `fmr f30,f1` before the six
//      snap fsub/fadds and `fmuls f30,f30,f30` after them (2 words); ngccc
//      keeps `snap` in f1 and does a single `fmuls f28,f1,f1` (1).
//  (b) PARAM-HOME COLOUR in the entry block: WANT arg4->r31, arg1->r30,
//      arg2->r29, &C->r28, &D->r27 (later recycled to &mat / &e->v / &o->v);
//      ours is the same five-register SET rotated one slot (arg4->r27,
//      arg2->r28, arg1->r29, &C->r30, &mat->r31). Same count, wrong
//      allocation ORDER — the documented §6r/169 param-home wall.
//  (c) FPR COLOUR: WANT f28=lbl_802ABBF8(0.25), f29=best(1e14), f30=snap*snap,
//      f31=dist; ours f28=snap*snap, f29=scale, f30=best.
//  (d) SNAP-PADDING BLOCK: WANT interleaves the six `fsubs/fadds` with the
//      seven `stfs` and with the `lis` remats; ngccc emits all six arithmetic
//      ops first and all seven stores after.
//  (e) BOUNDS CHECKS: WANT builds its two bases lazily and interleaved
//      (`addi r11,r30,0x18` before check1, `addi r9,r30,8` between check1 and
//      check2) and reads the +0 element of each Vec off r30 directly
//      (0x18(r30)/8(r30)); named `pa`/`pb` locals DO make ngccc create both
//      bases, but it creates them together, up-front, in the opposite order.
//  (f) TAIL COPY: WANT loads out.w (r1+0xb8) between the first psq pair
//      load and store; ours emits it after the third pair.
//
// Measured and rejected (all <= the kept 10.46%): plain -mps-float 7.17%;
// -fno-sched-spec / -fno-schedule-insns2 / -fno-gcse / -fno-thread-jumps /
// -fno-cse-follow-jumps / -fno-cse-skip-blocks / -fno-rerun-cse-after-loop /
// -ffixed-r31 / -fno-expensive-optimizations 2.9-7.2% (some are invalid options
// for cc1 2.95: -fno-reorder-blocks, -fno-crossjumping, -fno-tree-loop-optimize,
// -fmove-vregs). Body variants: no named &C/&D 6.4%; both named 8.9%; named
// &s0 (ps0) 5.9%; pa/pb assigned inside the check1 arm 10.46% (tie); using
// `e->a` direct for check2 while pa covers checks 4/6 10.46% (tie).
// LOAD-BEARING findings for anyone continuing:
//  * `pe = &e->v; po = &o->v;` as real locals (they must survive the
//    fn_801AE688 call) is what buys the 14th callee-saved GPR; without them
//    the stmw is `r19,0x134` and the frame layout below 0x130 shifts.
//  * `scale = lbl_802ABBF8;` as a pre-loop local is what buys the 4th saved
//    FPR (f28..f31); using the extern directly makes ngccc remat `lis+lfs`
//    inside the divide and save only f29..f31.
//  * 16-byte copies must be spelled member-wise (`s.p0.xy.ps = a->xy.ps;`) —
//    `s.p0 = *a` compiles to four lwz/stw pairs, never psq.
//  * the magic compared at +0x54 is 0xF5B17B09 (lis -0xa4f / ori 0x7b09), not
//    the m2c `-QB_UNKNOWN_0x0A4E84F7`.
//  * fn_801AAE94 takes FOUR `f32 *` and the four locals are 16-byte vectors
//    (r3=r1+8, r4=r1+0x18, r5=r1+0x28, r6=r1+0x38), so `s0` is really a Seg
//    {*arg1, *arg2} and `s1` is {e->v, e->p48->v}.
//  * lbl_802ABB78 is read as an 8-byte paired-single constant (zeros) for the
//    ps_merge00 in the dot product, exactly like the sibling
//    src/wip/fn_80006C64.c does with lbl_8028FD98.
#include "types.h"
#include "qb_constants.h"

typedef union {
    __ps_t ps;
    struct {
        f32 hi, lo;
    } flt;
} PSV;

typedef struct {
    PSV xy, zw;
} Vec;

typedef struct {
    Vec p0, p1;
} Seg;

typedef struct Elem {
    char pad0x00[8];
    Vec a;
    Vec b;
    Vec v;
    char pad0x38[0x10];
    struct Elem *p48;
    struct Elem *p4c;
    u32 flags;
    u32 id;
    char pad0x58[8];
} Elem;

typedef struct {
    char pad0x00[0x48];
    Elem *first;
    s32 pad0x4C;
    s32 n;
} List;

typedef struct {
    __ps_t m[8];
} Mat;

typedef struct {
    PSV p0, p1, p2, p3;
    f32 w;
} Out;

extern f32 lbl_802ABBF0;
extern f32 lbl_802ABBF4;
extern f32 lbl_802ABBF8;
extern __ps_t lbl_802ABB78;

#define MAGIC 0xF5B17B09

void fn_800063B4(void *p);
void fn_801AAE94(f32 *a, f32 *b, f32 *c, f32 *d);
f32 fn_8012570C(s32 a, s32 b);
s32 fn_800E9D30(Elem *o, s32 i);
s32 fn_80006C64(Seg *s0, Seg *s1, Vec *o0, Vec *o1, f32 *ts, f32 *tt, s32 clamp);
void fn_801AE688(Mat *out, void *a1, Elem *a2);
s32 fn_800EA994(void *a0, Vec *a1, Vec *a2, Mat *a3, void *a4, void *a5, f32 a6);

s32 fn_801ACBC0(List *arg0, Vec *arg1, Vec *arg2, void *arg3, Out *arg4, Elem **arg5) {
    Seg s0;
    Vec C;
    Vec D;
    Seg s1;
    Vec o0;
    Vec o1;
    Vec d;
    Out out;
    Mat mat;
    f32 ts, tt;
    PSV sq;
    Vec *pc = &C;
    Vec *pd = &D;
    Vec *pe, *po, *pa, *pb;
    Elem *e, *o;
    s32 i, ok, r;
    f32 snap, snap2, dist, best, scale;
    __ps_t z, t;

    *arg5 = NULL;
    fn_800063B4(&s0);
    s0.p0.xy.ps = arg1->xy.ps;
    s0.p0.zw.ps = arg1->zw.ps;
    s0.p1.xy.ps = arg2->xy.ps;
    s0.p1.zw.ps = arg2->zw.ps;
    fn_801AAE94((f32 *)&s0.p0, (f32 *)&s0.p1, (f32 *)pc, (f32 *)pd);
    snap = fn_8012570C(QB_CLIMB_MAX_SNAP, 0);
    C.xy.flt.hi -= snap;
    C.xy.flt.lo -= snap;
    C.zw.flt.hi -= snap;
    C.zw.flt.lo = lbl_802ABBF0;
    D.xy.flt.hi += snap;
    D.xy.flt.lo += snap;
    D.zw.flt.hi += snap;
    D.zw.flt.lo = lbl_802ABBF0;
    snap2 = snap * snap;
    best = lbl_802ABBF4;
    scale = lbl_802ABBF8;

    for (i = 0; i < arg0->n; i++) {
        e = arg0->first + i;
        ok = 1;
        if (!(e->flags & 0x20)) {
            ok = 0;
        }
        if (ok && fn_800E9D30(e, 2) != 0 && e->p48 != NULL) {
            pa = &e->a;
            pb = &e->b;
            if (!(C.xy.flt.hi > pb->xy.flt.hi)) {
                if (!(D.xy.flt.hi < pa->xy.flt.hi)) {
                    if (!(C.zw.flt.hi > pb->zw.flt.hi)) {
                        if (!(D.zw.flt.hi < pa->zw.flt.hi)) {
                            if (!(C.xy.flt.lo > pb->xy.flt.lo)) {
                                if (!(D.xy.flt.lo < pa->xy.flt.lo)) {
                                    fn_800063B4(&s1);
                                    s1.p0.xy.ps = e->v.xy.ps;
                                    s1.p0.zw.ps = e->v.zw.ps;
                                    o = e->p48;
                                    s1.p1.xy.ps = o->v.xy.ps;
                                    s1.p1.zw.ps = o->v.zw.ps;
                                    if (fn_80006C64(&s0, &s1, &o0, &o1, &ts, &tt, 1) != 0) {
                                        d.zw.ps = o1.zw.ps - o0.zw.ps;
                                        d.xy.ps = o1.xy.ps - o0.xy.ps;
                                        z = lbl_802ABB78;
                                        t = d.zw.ps * d.zw.ps;
                                        t = __builtin_ps_merge00(t, z);
                                        t = __builtin_ps_madd(d.xy.ps, d.xy.ps, t);
                                        sq.ps = __builtin_ps_sum0(t, t, t);
                                        dist = sq.flt.hi;
                                        if (e->id == MAGIC || e->p48->id == MAGIC) {
                                            dist /= scale;
                                        }
                                        if (!(dist > snap2)) {
                                            if (!(dist > best)) {
                                                o = e->p48;
                                                pe = &e->v;
                                                po = &o->v;
                                                if (e->v.xy.flt.lo < o->v.xy.flt.lo) {
                                                    fn_801AE688(&mat, arg0, e);
                                                    r = fn_800EA994(arg3, pe, po, &mat, &o1, &out, tt);
                                                    if (r != 1) {
                                                        continue;
                                                    }
                                                    *arg5 = e;
                                                } else {
                                                    fn_801AE688(&mat, arg0, o);
                                                    r = fn_800EA994(arg3, po, pe, &mat, &o1, &out, lbl_802ABBF0 - tt);
                                                    if (r != 1) {
                                                        continue;
                                                    }
                                                    *arg5 = e->p48;
                                                }
                                                best = dist;
                                                arg4->p0.ps = out.p0.ps;
                                                arg4->p1.ps = out.p1.ps;
                                                arg4->p2.ps = out.p2.ps;
                                                arg4->p3.ps = out.p3.ps;
                                                arg4->w = out.w;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return (*arg5 != 0);
}