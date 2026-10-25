// WIP DRAFT (non-matching) — hand rebuild from ps_disasm
// family=m2c range=0x801C4228-0x801C4E20 size=3064B
// extra_cflags: -mps-float
// PARKED 58.1%: exact size (3064B/766 insns) and full structure reproduced —
// all four hash-guard blocks, div-per-arm with crossjumped fdivs tails,
// camera ps_sub transform, float-returning fn_80005C28 chain
// (fn_800F078C(fn_800F0F84(...)) chained r3), three bdnz delay windows with
// correct sunk setup, volatile pair slots [stw direct + stw r31,4(r30)
// indirect mix], 4x inline 4x4 matrix multiplies with the D+(C+(A+B))
// contraction tree, psq pair copies with shared last store, negate arm with
// __builtin_ps_neg pairs + scalar fneg, copy64 with mid-derived dst pointer
// (r10), and the goto-r1/r2 merged return tail ([li r3,2][b][li r3,1]).
// REMAINING WALLS:
// 1. Matmul interleave (~200 insn positions): want schedules each element's
//    q/m load PAIRS (q,m)-first while ngccc emits (m,q)-first after elem 0;
//    register assignment matches, pure sched1 state inside the ~200-insn
//    block. Resisted: -fno-sched-spec/-interblock/-schedule-insns(ns2),
//    volatile buffers, operand-order flips (breaks fmadds encodings),
//    memory-clobber barriers between elements (fixes order but +195 insns:
//    kills arms-2/3 tail merge). Retry: find a per-element scheduling
//    barrier that does NOT split basic blocks.
// 2. Scale-block anchors mirrored: want [lis r11->CB00 first, lis r9->CB04],
//    got [r9->CB00, r11->CB04]; CB00/CB04 FPR names swapped (f12/f10);
//    [stfs maxAngle][stw 1] pair emits reversed. fr13 pin on val fixed
//    period=f11/quot=f0 parity (KEEP).
// 3. Arm-1 window holds one extra insn (&axis addi sinks into the bdnz
//    window; want keeps it post-window like arms 2/3).
// DISCOVERIES this draft (reusable):
// - ProDG cc1 DROPS stores to `volatile T *arr[n]` (qualifies the POINTEE);
//   must write `T *volatile arr[n]` to force stw+reload of out-param pairs.
// - Frame-template struct with an internal union reproduces overlapping
//   scoped buffers (axis[8] | qout@+0x20 | rot@+0x40) AND disjoint volatile
//   pair slots deterministically.
// - Duplicate the division into both if/else arms to get want's duplicated
//   [lis; lfs period; lfs const] arms + crossjump-shared fdivs/stfs.
// - `goto r1/r2` labels ordered [r2: return 2; r1: return 1;] reproduce
//   want's tail block order with the entry guard branching forward.
// - Mixed direct/indirect pair stores (`pair[0]=x` direct +
//   `pp[1]=m` via pointer var born pre-loop) reproduce want's
//   [stw r3,N(r1)][stw r31,4(r30)] mix with r30 born inside the window.
// - Stage `arg = ang * CB00` BEFORE the empty delay loop so its lis lands
//   pre-mtctr and lfs+fmuls sink INTO the window (arms 2/3 byte-exact).
// - register f32 val __asm__("fr13") pins fix scale-block FPR parity.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// scored 32.6% while git revision a117790e1 scores 58.1%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 20 distinct committed bodies.
// Re-verify with tools/score_addrs.py before editing again.
#include "types.h"
extern f32 lbl_802ACAF8;
extern f32 lbl_802ACAFC;
extern f32 lbl_802ACB00;
extern f32 lbl_802ACB04;
extern f32 lbl_802ACB08;
#include "qb_constants.h"

s32 GetFloat(s32, s32, void *, s32);
s32 ContainsFlag(s32, s32);
s32 GetChecksum_2(s32, s32, void *, s32);
s32 fn_800F0F84(s32, s32);
void fn_800F078C(s32, void *);
void *fn_80003E0C(void *, f32);
void *fn_80003EB0(void *, f32);
void *fn_80003F54(void *, f32);
f32 fn_80005C28(void *, void *, s32, s32);
extern f32 fabsf(f32);

#define MMUL(out, qq, mm, j) \
    ((out)[j] = (qq)[3] * (mm)[12 + j] + ((qq)[2] * (mm)[8 + j] + ((qq)[0] * (mm)[j] + (qq)[1] * (mm)[4 + j])))

#define MATMUL_COPY(buf, mtx) \
    { \
        f32 *qf_ = qf; \
        f32 *mf_ = mf; \
        MMUL(buf, qf_, mf_, 0); \
        MMUL(buf, qf_, mf_, 1); \
        MMUL(buf, qf_, mf_, 2); \
        MMUL(buf, qf_, mf_, 3); \
        MMUL(buf, qf_, mf_, 4); \
        MMUL(buf, qf_, mf_, 5); \
        MMUL(buf, qf_, mf_, 6); \
        MMUL(buf, qf_, mf_, 7); \
        MMUL(buf, qf_, mf_, 8); \
        MMUL(buf, qf_, mf_, 9); \
        MMUL(buf, qf_, mf_, 10); \
        MMUL(buf, qf_, mf_, 11); \
        MMUL(buf, qf_, mf_, 12); \
        MMUL(buf, qf_, mf_, 13); \
        MMUL(buf, qf_, mf_, 14); \
        MMUL(buf, qf_, mf_, 15); \
        { \
            __ps_t *s_ = (__ps_t *)(buf); \
            __ps_t *d_ = (__ps_t *)(mtx); \
            d_[0] = s_[0]; \
            d_[1] = s_[1]; \
            d_[2] = s_[2]; \
            d_[3] = s_[3]; \
            d_[4] = s_[4]; \
            d_[5] = s_[5]; \
            d_[6] = s_[6]; \
            d_[7] = s_[7]; \
        } \
    }

#define COPY64(dstp, srcp) \
    { \
        __ps_t *src_ = (__ps_t *)(srcp); \
        __ps_t *dst_ = (__ps_t *)(dstp); \
        __ps_t *mdst_ = dst_ + 4; \
        dst_[0] = src_[0]; \
        dst_[1] = src_[1]; \
        dst_[2] = src_[2]; \
        dst_[3] = src_[3]; \
        mdst_[0] = src_[4]; \
        mdst_[1] = src_[5]; \
        dst_[6] = src_[6]; \
        dst_[7] = src_[7]; \
    }

typedef struct {
    __ps_t cam[2];
    __ps_t pts[2];
    union {
        __ps_t axis[8];
        struct {
            char _p[0x20];
            volatile f32 qout[16];
        } qq;
        struct {
            char _p[0x40];
            volatile f32 rot[16];
        } rr;
    };
    f32 period;
    s32 prop_id;
    f32 ang;
    char pad1[4];
    void *volatile pair1[2];
    void *volatile pair2[2];
    void *volatile pair3[2];
} frame_t;

s32 fn_801C4228(void *arg0, s32 arg1, s32 arg2) {
    frame_t fr;

    if (arg1 != QB_ROTATE) {
        goto r2;
    }
    {
        if (GetFloat((s32)arg2, 0x79A07F3F, &fr.period, 0) != 0) {
            if ((ContainsFlag((s32)arg2, 0xD029F619) == 0) && (ContainsFlag((s32)arg2, QB_SECOND) == 0)) {
                if ((ContainsFlag((s32)arg2, 0x019176C5) != 0) || (ContainsFlag((s32)arg2, 0x4A07C332) != 0)) {
                    fr.period = fr.period / lbl_802ACAF8;
                } else {
                    fr.period = fr.period / lbl_802ACAFC;
                }
            }
            if (GetFloat((s32)arg2, 0x7323E97C, (char *)arg0 + 0x1C, 0) != 0) {
                f32 cb = lbl_802ACB00;
                register f32 val __asm__("fr13");
                val = *(f32 *)((char *)arg0 + 0x1C);
                *(f32 *)((char *)arg0 + 0x20) = fr.period;
                *(f32 *)((char *)arg0 + 0x28) = lbl_802ACB04;
                *(s32 *)((char *)arg0 + 0x2C) = 1;
                *(f32 *)((char *)arg0 + 0x24) = (val / fr.period) * cb;
                *(f32 *)((char *)arg0 + 0x1C) = fabsf(val * cb);
            }
            if (GetFloat((s32)arg2, 0x0424D9EA, (char *)arg0 + 0x30, 0) != 0) {
                f32 cb = lbl_802ACB00;
                register f32 val __asm__("fr13");
                val = *(f32 *)((char *)arg0 + 0x30);
                *(f32 *)((char *)arg0 + 0x34) = fr.period;
                *(f32 *)((char *)arg0 + 0x3C) = lbl_802ACB04;
                *(s32 *)((char *)arg0 + 0x40) = 1;
                *(f32 *)((char *)arg0 + 0x38) = (val / fr.period) * cb;
                *(f32 *)((char *)arg0 + 0x30) = fabsf(val * cb);
            }
            if (GetFloat((s32)arg2, 0x9D2D8850, (char *)arg0 + 0x44, 0) != 0) {
                f32 cb = lbl_802ACB00;
                register f32 val __asm__("fr13");
                val = *(f32 *)((char *)arg0 + 0x44);
                *(f32 *)((char *)arg0 + 0x48) = fr.period;
                *(f32 *)((char *)arg0 + 0x50) = lbl_802ACB04;
                *(s32 *)((char *)arg0 + 0x54) = 1;
                *(f32 *)((char *)arg0 + 0x4C) = (val / fr.period) * cb;
                *(f32 *)((char *)arg0 + 0x44) = fabsf(val * cb);
            }
            fr.prop_id = 0;
            if (GetChecksum_2((s32)arg2, 0x7A8017BA, &fr.prop_id, 0) != 0) {
                f32 ret;
                f32 t;
                f32 cb;
                void *objc;
                fn_800F078C(fn_800F0F84(fr.prop_id, 1), fr.cam);
                objc = *(void **)((char *)arg0 + 0xC);
                {
                    __ps_t c0 = fr.cam[0];
                    __ps_t t0 = *(__ps_t *)((char *)objc + 0x58);
                    __ps_t t1 = *(__ps_t *)((char *)objc + 0x60);
                    __ps_t c1 = fr.cam[1];
                    fr.pts[0] = c0 - t0;
                    fr.pts[1] = c1 - t1;
                }
                ret = fn_80005C28((char *)objc + 0x78, fr.pts, 2, 1);
                {
                    register f32 per __asm__("fr0");
                    per = fr.period;
                    t = ret * lbl_802ACB08;
                    *(f32 *)((char *)arg0 + 0x34) = per;
                    *(f32 *)((char *)arg0 + 0x30) = t;
                    *(f32 *)((char *)arg0 + 0x3C) = lbl_802ACB04;
                    *(s32 *)((char *)arg0 + 0x40) = 1;
                    cb = lbl_802ACB00;
                    *(f32 *)((char *)arg0 + 0x38) = (t / per) * cb;
                    *(f32 *)((char *)arg0 + 0x30) = fabsf(t * cb);
                }
            }
            {
                void *vt = *(void **)((char *)arg0 + 0x18);
                ((s32 (*)(void *, s32)) *(s32 *)((char *)vt + 0x44))(
                    (char *)arg0 + *(s16 *)((char *)vt + 0x40), 0);
            }
            goto r1;
        } else {
            if (GetFloat((s32)arg2, 0x7323E97C, &fr.ang, 0) != 0) {
                void *volatile *pp1;
                void *m;
                f32 *qf;
                f32 *mf;
                s32 delay;
                f32 arg;
                pp1 = fr.pair1;
                m = (char *)*(void **)((char *)arg0 + 0xC) + 0x78;
                arg = fr.ang * lbl_802ACB00;
                for (delay = 0; delay < 4; delay++) {
                }
                fr.pair1[0] = fn_80003E0C(fr.axis, arg);
                pp1[1] = m;
                qf = (f32 *)fr.pair1[0];
                mf = (f32 *)m;
                MATMUL_COPY(fr.rr.rot, m)
            } else if (GetFloat((s32)arg2, 0x0424D9EA, &fr.ang, 0) != 0) {
                void *volatile *pp2;
                void *m;
                f32 *qf;
                f32 *mf;
                s32 delay;
                f32 arg;
                pp2 = fr.pair2;
                m = (char *)*(void **)((char *)arg0 + 0xC) + 0x78;
                arg = fr.ang * lbl_802ACB00;
                for (delay = 0; delay < 4; delay++) {
                }
                fr.pair2[0] = fn_80003EB0(fr.cam, arg);
                pp2[1] = m;
                qf = (f32 *)fr.pair2[0];
                mf = (f32 *)m;
                MATMUL_COPY(fr.qq.qout, m)
            } else if (GetFloat((s32)arg2, 0x9D2D8850, &fr.ang, 0) != 0) {
                void *volatile *pp3;
                void *m;
                f32 *qf;
                f32 *mf;
                s32 delay;
                f32 arg;
                pp3 = fr.pair3;
                m = (char *)*(void **)((char *)arg0 + 0xC) + 0x78;
                arg = fr.ang * lbl_802ACB00;
                for (delay = 0; delay < 4; delay++) {
                }
                fr.pair3[0] = fn_80003F54(fr.cam, arg);
                pp3[1] = m;
                qf = (f32 *)fr.pair3[0];
                mf = (f32 *)m;
                MATMUL_COPY(fr.qq.qout, m)
            } else {
                goto negate;
            }
            {
                void *o58 = *(void **)((char *)arg0 + 0x58);
                COPY64((char *)o58 + 0x20, *(void **)((char *)o58 + 0xC) + 0x78)
            }
            goto r1;
        negate:
            {
                char *o;
                char *zp;
                char *zp2;
                o = *(char **)((char *)arg0 + 0xC);
                *(__ps_t *)(o + 0x98) = __builtin_ps_neg(*(__ps_t *)(o + 0x98));
                zp = o + 0x98;
                *(f32 *)(zp + 8) = -*(f32 *)(zp + 8);
                o = *(char **)((char *)arg0 + 0xC);
                *(__ps_t *)(o + 0x78) = __builtin_ps_neg(*(__ps_t *)(o + 0x78));
                zp2 = o + 0x78;
                *(f32 *)(zp2 + 8) = -*(f32 *)(zp2 + 8);
            }
            {
                void *o58 = *(void **)((char *)arg0 + 0x58);
                COPY64((char *)o58 + 0x20, *(void **)((char *)o58 + 0xC) + 0x78)
            }
            *(s32 *)((char *)(*(void **)((char *)arg0 + 0x58)) + 0x3B4) ^= 1;
            goto r1;
        }
    }
r2:
    return 2;
r1:
    return 1;
}
