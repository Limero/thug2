// WIP DRAFT (non-matching) -- hand-reconstructed 2026-10-05 from the retail
// bytes. Replaces the m2c bulk fill: its `0;` holes over the psq/op4 words are
// now the real SNAPS idiom (identical shape to the MATCHED twin idiom in
// src/fn_8006AC08.c), and every callee has a real prototype.
// family=m2c range=0x8006CB8C-0x8006D564 size=2520B
// extra_cflags: -mps-float -fno-schedule-insns
// INERT: not registered in splits.txt/configure.py -- never compiled.
//
// PARKED 2026-10-05 (w_8006CB8C): best 4.88% masked (was 2.54% from the m2c
// fill). `volatile double _dummy` does NOT change the frame (want 0xd8 is
// reached natively), so no +8 quirk here.
// WHAT NOW MATCHES (verified by tools/score_wip.py, 30/630 masked words):
//   * frame 0xd8, stfd f28..f31 @0xb8/0xc0/0xc8/0xd0, stw r0 @0xdc -- the
//     first 6 prologue words are byte-exact;
//   * the 16-stfs corner init at arg0+0x18..0x54 in the exact retail order;
//   * both `normalise(Vec4*)` blocks are instruction-for-instruction the
//     retail sequence (psq_l/ps_mul/ps_merge00/ps_madd/ps_sum0/ps_mr/fcmpu/
//     ble/ps_rsqrte/ps_muls0/ps_mul, including the psq_st->psq_l staging at
//     0x60/0x68 and stfs 0x64/0x6c);
//   * the `andi. fl,2 / mfcr / ... mtcrf 0x80,r / beq` CR-save idiom;
//   * 27 fn_8006FA90(&arg0->v0, i) calls, 12 s16-offset/s32-target vtable
//     dispatches, the 12 fadds corner offset pass, fn_80070B74's 13-float
//     argument mix, fn_80070BA8, fn_8006F54C.
// RESIDUAL: pure register allocation + the two hand-scheduled PS blocks.
//   1. GPR save: want `stmw r26,0xa0` (6 callee-saves: r31=arg0, r30=&arg0->v0,
//      r29=CR, r28=fl, r27=&arg0->u08, r26=&r1+0x58 -- the last two are GCC
//      loop-hoisted address computations each used exactly ONCE, at
//      0x8006D24C and 0x8006D52C). We only get 5 (stmw r27,0xa4); forcing
//      `&arg0->u08` / `&sp58` to stay in registers (register pins, explicit
//      pointer vars) did not survive GCC's rematerialisation.
//   2. Everything after the prologue is one to two FPRs/GPRs off: want keeps
//      1.0f in f8 and 0.0f in f10 for the whole body (plus a second 0.0f in
//      f28 re-read at 0x8006CE18), we get f10/f28.
//   3. The cross-product block at 0x8006CCC8-0x8006CD98 (103 instructions:
//      9 merge10/merge00 pairs, 3 ps_sub, 3 ps_mul, 4 psq staging slots at
//      r1+0x08/0x10/0x70/0x78) is semantically reconstructed but not
//      register-for-register.
//   4. The 27-call blend chain's accumulator assignment (t88/t90/t98 vs the
//      retail's self-referential `v?.ps[1] = madds*(row, v?.ps[1], t)`) is
//      guessed; the four weight slots feed each other in an order that only
//      the original source knows.
//   5. fn_80070B74's f1..f13 mix really is (v0.y, v0.x, v1.x, v1.y, p.z,
//      v1.z, v2.x, v2.y, v2.z, p.y, p.x, v3.x, v3.y) -- slot 5/10/11 hold the
//      raw point components. Unverified: this may be a struct-by-value
//      lowering rather than 13 literal arguments.
// RULED OUT: no matched twin (tools/near_twin_scan.py: no same-size match);
// global -mps-float (breaks 14 other matched fns, AGENTS-recipes M5.0);
// the `volatile double` +8 frame trick (want frame is 0xd8 = -mps-float
// native, dummy is a no-op here); -O1/-fno-caller-snoins/no-flag (2.8-3.1%);
// reading the 0.5f/0.0f rodata at each use site instead of through a local
// (this one DID help: 4.58 -> 4.88%). Store/statement permutation and
// try_variants sweeps were not run (brief forbids brute force).
// NEXT LEVER: the register-allocation items 1-2 are the whole gap between
// 4.88% and ~70%; item 3-4 need the original source's expression order.
#include "types.h"
#include "dolphin/SN_PS.h"
#include "structs.h"

/* retail rodata: 1.0f / 0.0f / 0.5f and the {0,0} pair used by ps_merge00 */
extern f32 lbl_80294BBC;
extern f32 lbl_80294BC0;
extern f32 lbl_80294BC4;
extern __ps_t lbl_80294B40;
extern s32 lbl_8030142C;

/* arg1 / arg2 and arg0+0x18..0x57 are all 16-byte Vec4s: the pairs are
 * consumed by psq_l/psq_st but initialised lane-by-lane with stfs, so both
 * views are needed (same trick as fn_8006AC08.c). */
typedef union {
    struct { f32 x, y, z, w; } f;
    __ps_t ps[2];
} Vec4;

typedef struct {
    char pad0x00[0x8];
    f32 u08, u0C, u10;          /* point added to every corner            */
    char pad0x14[0x4];
    Vec4 v0, v1, v2, v3;         /* corners; .w = 0,0,0,1 after init      */
    f32 u58, u5C, u60, u64;
    char pad0x68[0x8];
    s32 c70, c74, c78, c7C;
    char pad0x80[0x10];
    s32 u90, u94, u98, u9C;
    s32 uA0;
    f32 uA4;
    char pad0xA8[0x4];
    s32 uAC;                    /* !=0 => flag, also stored in arg1 slot  */
    void *uB0;
    s32 uB4;
} S_CB8C;

typedef struct { s16 off; char pad0x2[0x2]; s32 fn; } DispEntry;
typedef struct {
    char pad0x00[0x40];
    DispEntry e8;            /* +0x40 : set(x, y, z)                      */
    char pad0x48[0x38];
    DispEntry e16;           /* +0x80 : setindex(checksum)                 */
    DispEntry e17;           /* +0x88 : setindex(size, size)               */
} Vtbl;
typedef struct {
    char pad0x00[0x8];
    s32 u08;
    s32 u0C;
    s32 u10;
    s32 u14;
    char pad0x18[0x8];
    Vtbl *vt;                /* dispatch table @ +0x20                    */
} Obj;

void *Mem_Alloc2(s32);
void *fn_8009B9F0(void *, s32);
void *fn_8006FA90(void *, s32);
void fn_80070B40(void *, s32, s32);
void fn_80070B74(void *, s32, s32, s32, f32, f32, f32, f32, f32, f32, f32,
                 f32, f32, f32, f32, f32, f32);
void fn_80070BA8(void *);
s32 fn_8006F54C(CStruct *, s32 *, s32);

void fn_8006CB8C(S_CB8C *arg0, Vec4 *arg1, Vec4 *arg2) {
    f32 one;
    f32 zero;
    f32 X;
    f32 Y;
    f32 nX;
    f32 nY;
    SN_PS_type s1;
    SN_PS_type s2;
    SN_PS_type s3;
    SN_PS_type s4;
    __ps_t p0;
    __ps_t p1;
    __ps_t q;
    __ps_t d;
    __ps_t u;
    __ps_t w;
    __ps_t e0;
    __ps_t e1;
    __ps_t e2;
    __ps_t e3;
    Vec4 v0;
    Vec4 v1;
    Vec4 v2;
    Vec4 v3;
    Vec4 *base;
    Vec4 *row;
    __ps_t t0;
    __ps_t t1;
    __ps_t t2;
    s32 ctr;
    s32 fl;
    s32 *sp58;
    Obj *obj;
    Vtbl *vt;

    fl = 1;
    obj = (Obj *)fn_8009B9F0(Mem_Alloc2(0x54), 1);
    arg0->uB0 = obj;

    one = lbl_80294BBC;
    zero = lbl_80294BC0;

    arg0->v0.f.x = one; arg0->v0.f.y = zero;
    arg0->v0.f.z = lbl_80294BC0; arg0->v0.f.w = zero;
    arg0->v1.f.x = zero; arg0->v1.f.y = one;
    arg0->v1.f.z = lbl_80294BC0; arg0->v1.f.w = zero;
    arg0->v2.f.x = zero; arg0->v2.f.y = zero;
    arg0->v2.f.z = one; arg0->v2.f.w = zero;
    arg0->v3.f.x = zero; arg0->v3.f.y = zero;
    arg0->v3.f.z = lbl_80294BC0; arg0->v3.f.w = one;

    /* normalise arg1 in place (fn_8006AC08.c idiom) */
    p1 = arg1->ps[1];
    p0 = arg1->ps[0];
    d = __builtin_ps_mul(p1, p1);
    d = __builtin_ps_merge00(d, lbl_80294B40);
    d = __builtin_ps_madd(p0, p0, d);
    d = __builtin_ps_sum0(d, d, d);
    s1.ps = d;
    if (s1.flt.hi > zero) {
        d = __builtin_ps_rsqrte(d);
        s1.ps = d;
        s1.flt.lo = one;
        q = s1.ps;
        arg1->ps[0] = __builtin_ps_muls0(p0, d);
        arg1->ps[1] = __builtin_ps_mul(p1, q);
    }

    /* normalise arg2 in place */
    p1 = arg2->ps[1];
    p0 = arg2->ps[0];
    d = __builtin_ps_mul(p1, p1);
    d = __builtin_ps_merge00(d, lbl_80294B40);
    d = __builtin_ps_madd(p0, p0, d);
    d = __builtin_ps_sum0(d, d, d);
    s2.ps = d;
    if (s2.flt.hi > zero) {
        d = __builtin_ps_rsqrte(d);
        s2.ps = d;
        s2.flt.lo = one;
        q = s2.ps;
        arg2->ps[0] = __builtin_ps_muls0(p0, d);
        arg2->ps[1] = __builtin_ps_mul(p1, q);
    }

    /* cross(arg1, arg2) -> corner seeds */
    arg0->v0.ps[0] = arg1->ps[0];
    arg0->v0.ps[1] = arg1->ps[1];
    u = arg2->ps[0];
    w = arg2->ps[1];
    d = __builtin_ps_sub(__builtin_ps_mul(w, arg1->ps[0]),
                         __builtin_ps_mul(u, arg1->ps[1]));
    s3.ps = d;
    s3.flt.lo = one;
    e0 = s3.ps;
    e1 = __builtin_ps_mul(__builtin_ps_merge10(e0, e0),
                          __builtin_ps_merge00(arg1->ps[0], arg1->ps[1]));
    arg0->v1.ps[0] = e1;
    arg0->v1.ps[1] = e1;
    s4.ps = d;
    s4.flt.lo = one;
    e2 = s4.ps;
    e3 = __builtin_ps_mul(e1, e2);
    arg0->v2.ps[0] = e3;
    arg0->v2.ps[1] = e3;
    arg0->v3.ps[0] = e3;
    arg0->v3.ps[1] = e3;

    if (arg0->uAC != 0) {
        fl = 3;
        fn_80070B40(obj, 0, 0);
    }

    ctr = 4;
    {
        s32 *pp = (s32 *)arg0;
        do {
            pp[0x24] = pp[0x1C];
            pp++;
            ctr--;
        } while (ctr != 0);
    }

    arg0->u58 = arg0->u60;
    arg0->u5C = arg0->u64;
    ctr = 4;
    arg0->uA4 = lbl_80294BC0;
    do {
        ctr--;
    } while (ctr != 0);

    X = arg0->u58 * lbl_80294BC4;
    Y = arg0->u5C * lbl_80294BC4;
    nX = -arg0->u58 * lbl_80294BC4;
    nY = -arg0->u5C * lbl_80294BC4;

    v0.f.x = nX; v0.f.y = nY; v0.f.z = lbl_80294BC0;
    v1.f.x = X;  v1.f.y = nY; v1.f.z = lbl_80294BC0;
    v2.f.x = X;  v2.f.y = Y;  v2.f.z = lbl_80294BC0;
    v3.f.x = nX; v3.f.y = Y;  v3.f.z = lbl_80294BC0;

    /* 27 fully-unrolled fn_8006FA90(v0, i) blends of the four corners */
    base = &arg0->v0;
    row = (Vec4 *)fn_8006FA90(base, 0);
    t2 = __builtin_ps_muls0(row->ps[0], v0.ps[0]);
    row = (Vec4 *)fn_8006FA90(base, 0);
    t1 = __builtin_ps_muls0(row->ps[1], v0.ps[0]);
    row = (Vec4 *)fn_8006FA90(base, 1);
    t0 = __builtin_ps_madds1(row->ps[0], v0.ps[0], t2);
    row = (Vec4 *)fn_8006FA90(base, 0);
    v0.ps[1] = __builtin_ps_madds1(row->ps[1], v0.ps[1], t0);
    row = (Vec4 *)fn_8006FA90(base, 1);
    t2 = __builtin_ps_madds1(row->ps[1], v0.ps[1], t1);
    row = (Vec4 *)fn_8006FA90(base, 2);
    t2 = __builtin_ps_madds1(row->ps[1], v0.ps[0], t2);
    row = (Vec4 *)fn_8006FA90(base, 2);
    t1 = __builtin_ps_madds0(row->ps[0], v0.ps[0], t0);
    row = (Vec4 *)fn_8006FA90(base, 3);
    t0 = __builtin_ps_madds0(row->ps[1], v0.ps[1], t2);
    row = (Vec4 *)fn_8006FA90(base, 3);
    v0.ps[0] = __builtin_ps_madds1(row->ps[0], v0.ps[1], t1);
    row = (Vec4 *)fn_8006FA90(base, 0);
    v0.ps[1] = __builtin_ps_madds1(row->ps[1], v0.ps[1], t0);
    row = (Vec4 *)fn_8006FA90(base, 0);
    t2 = __builtin_ps_muls0(row->ps[0], v1.ps[0]);
    row = (Vec4 *)fn_8006FA90(base, 1);
    t1 = __builtin_ps_muls0(row->ps[1], v1.ps[0]);
    row = (Vec4 *)fn_8006FA90(base, 1);
    t0 = __builtin_ps_madds1(row->ps[0], v1.ps[0], t2);
    row = (Vec4 *)fn_8006FA90(base, 2);
    t2 = __builtin_ps_madds1(row->ps[1], v1.ps[1], t0);
    row = (Vec4 *)fn_8006FA90(base, 2);
    t1 = __builtin_ps_madds1(row->ps[1], v1.ps[0], t2);
    row = (Vec4 *)fn_8006FA90(base, 3);
    t0 = __builtin_ps_madds0(row->ps[0], v1.ps[1], t1);
    row = (Vec4 *)fn_8006FA90(base, 3);
    v1.ps[0] = __builtin_ps_madds0(row->ps[1], v1.ps[1], t0);
    row = (Vec4 *)fn_8006FA90(base, 0);
    v1.ps[1] = __builtin_ps_madds1(row->ps[0], v1.ps[1], t0);
    row = (Vec4 *)fn_8006FA90(base, 0);
    t2 = __builtin_ps_muls0(row->ps[0], v2.ps[0]);
    row = (Vec4 *)fn_8006FA90(base, 1);
    t1 = __builtin_ps_muls0(row->ps[1], v2.ps[0]);
    row = (Vec4 *)fn_8006FA90(base, 1);
    t0 = __builtin_ps_madds1(row->ps[0], v2.ps[0], t2);
    row = (Vec4 *)fn_8006FA90(base, 2);
    t2 = __builtin_ps_madds1(row->ps[1], v2.ps[1], t0);
    row = (Vec4 *)fn_8006FA90(base, 2);
    t1 = __builtin_ps_madds0(row->ps[0], v2.ps[1], t2);
    row = (Vec4 *)fn_8006FA90(base, 3);
    t0 = __builtin_ps_madds0(row->ps[1], v2.ps[0], t1);
    row = (Vec4 *)fn_8006FA90(base, 3);
    v2.ps[0] = __builtin_ps_madds1(row->ps[0], v2.ps[1], t0);
    row = (Vec4 *)fn_8006FA90(base, 0);
    v2.ps[1] = __builtin_ps_madds1(row->ps[1], v2.ps[1], t0);
    row = (Vec4 *)fn_8006FA90(base, 0);
    t2 = __builtin_ps_muls0(row->ps[0], v3.ps[0]);
    row = (Vec4 *)fn_8006FA90(base, 1);
    t1 = __builtin_ps_muls0(row->ps[1], v3.ps[0]);
    row = (Vec4 *)fn_8006FA90(base, 1);
    t0 = __builtin_ps_madds1(row->ps[0], v3.ps[0], t2);
    row = (Vec4 *)fn_8006FA90(base, 2);
    t2 = __builtin_ps_madds1(row->ps[1], v3.ps[1], t0);
    row = (Vec4 *)fn_8006FA90(base, 2);
    t1 = __builtin_ps_madds0(row->ps[0], v3.ps[1], t2);
    row = (Vec4 *)fn_8006FA90(base, 3);
    t0 = __builtin_ps_madds0(row->ps[1], v3.ps[0], t1);
    row = (Vec4 *)fn_8006FA90(base, 3);
    v3.ps[0] = __builtin_ps_madds1(row->ps[0], v3.ps[1], t0);
    row = (Vec4 *)fn_8006FA90(base, 3);
    v3.ps[1] = __builtin_ps_madds1(row->ps[1], v3.ps[1], t0);

    v0.f.x = v0.f.x + arg0->u08;
    v0.f.y = v0.f.y + arg0->u0C;
    v0.f.z = v0.f.z + arg0->u10;
    v1.f.x = v1.f.x + arg0->u08;
    v1.f.y = v1.f.y + arg0->u0C;
    v1.f.z = v1.f.z + arg0->u10;
    v2.f.x = v2.f.x + arg0->u08;
    v2.f.y = v2.f.y + arg0->u0C;
    v2.f.z = v2.f.z + arg0->u10;
    v3.f.x = v3.f.x + arg0->u08;
    v3.f.y = v3.f.y + arg0->u0C;
    v3.f.z = v3.f.z + arg0->u10;
    obj->u08 = arg0->uB4;
    fn_80070B74(obj, fl, 4, 4,
                v0.f.y, v0.f.x, v1.f.x, v1.f.y,
                arg0->u10, v1.f.z, v2.f.x, v2.f.y,
                v2.f.z, arg0->u0C, arg0->u08,
                v3.f.x, v3.f.y);

    vt = obj->vt;
    ((s32 (*)(void *, s32, s32))vt->e16.fn)((char *)obj + vt->e16.off, 0,
                                             arg0->u90);
    if (fl & 2) {
        vt = obj->vt;
        ((s32 (*)(void *, s32, f32, f32))vt->e17.fn)((char *)obj + vt->e17.off,
                                                      0, lbl_80294BBC, zero);
    }
    vt = obj->vt;
    ((s32 (*)(void *, s32, f32, f32, f32))vt->e8.fn)((char *)obj + vt->e8.off, 0,
                                                      v0.f.x, v0.f.y, v0.f.z);
    vt = obj->vt;
    ((s32 (*)(void *, s32, s32))vt->e16.fn)((char *)obj + vt->e16.off, 1,
                                             arg0->u94);
    if (fl & 2) {
        vt = obj->vt;
        ((s32 (*)(void *, s32, f32, f32))vt->e17.fn)((char *)obj + vt->e17.off,
                                                      1, lbl_80294BBC, zero);
    }
    vt = obj->vt;
    ((s32 (*)(void *, s32, f32, f32, f32))vt->e8.fn)((char *)obj + vt->e8.off, 1,
                                                      v1.f.x, v1.f.y, v1.f.z);
    vt = obj->vt;
    ((s32 (*)(void *, s32, s32))vt->e16.fn)((char *)obj + vt->e16.off, 2,
                                             arg0->u98);
    if (fl & 2) {
        vt = obj->vt;
        ((s32 (*)(void *, s32, f32, f32))vt->e17.fn)((char *)obj + vt->e17.off,
                                                      2, lbl_80294BBC,
                                                      lbl_80294BBC);
    }
    vt = obj->vt;
    ((s32 (*)(void *, s32, f32, f32, f32))vt->e8.fn)((char *)obj + vt->e8.off, 2,
                                                      v2.f.x, v2.f.y, v2.f.z);
    vt = obj->vt;
    ((s32 (*)(void *, s32, s32))vt->e16.fn)((char *)obj + vt->e16.off, 3,
                                             arg0->u9C);
    if (fl & 2) {
        vt = obj->vt;
        ((s32 (*)(void *, s32, f32, f32))vt->e17.fn)((char *)obj + vt->e17.off,
                                                      3, zero, lbl_80294BBC);
    }
    vt = obj->vt;
    ((s32 (*)(void *, s32, f32, f32, f32))vt->e8.fn)((char *)obj + vt->e8.off, 3,
                                                      v3.f.x, v3.f.y, v3.f.z);

    obj->u10 = arg0->uA0 & 1;
    fn_80070BA8(obj);
    sp58 = (s32 *)arg0;
    fn_8006F54C(lbl_8030142C, sp58, (s32)arg0);
}