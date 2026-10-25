// WIP DRAFT (non-matching, PARKED) — hand reconstruction of the want bytes.
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 2.1053% -> 2.3684% `volatile` keyword(s) removed from the body
// family=m2c range=0x8008279C-0x80082D8C size=1520B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// ---------------------------------------------------------------------------
// PARKED 2026-10-04.  Best measured body below (tools/want_got.py, base flags
// -O2 -G0 -mcpu=750 -fno-common -mps-float): 2.48 %, object 1292 B vs want
// 1520 B (57 words short).  Baseline m2c draft was DIFF 1.3 % / 1420 B.
//
// WHAT THIS IS.  The m2c body was thrown away and the function re-derived from
// the want bytes; this body is SEMANTICALLY COMPLETE and structurally faithful
// (see "recovered semantics" below) — it is not an obfuscated guess any more.
// fn_8008279C pops three 0x18-byte vertices off the byte queue at
// lbl_8029653C, builds edge/edge/cross vectors, and either appends the three
// originals to *arg0 (small triangles) or pushes the four-sub-triangle
// refinement (12 vertices, big triangles).
//
// RECOVERED SEMANTICS (all verified against the want, see scratch tools):
//  * Vertex = 24 B:  {x,y} {z,w} pair-pair | s32 colour | u16 nidx | u16 tidx.
//    The queue chunk size is 0x18 (fn_8006BC90 -> memcpy with queue->size).
//  * Pop order:  &v3 (0x38) first, then &v2 (0x20), then &v1 (0x08).  p2=&v2 and
//    p3=&v3 are address-taken block locals at 0xc8/0xcc (the want reloads them).
//  * e0 = v2-v1, e1 = v3-v1, e2 = e0 x e1, each stored as 4 f32 with w = 1.0f
//    (lbl_80296534) at 0x50 / 0x60 / 0x70.  Scalar fsubs/fmsubs + stfs, but the
//    dot product then reads them back as __ps_t pairs (psq_l 112/120(r1)).
//  * The "area" is the house dot idiom on the {n.z,n.w}/{n.x,n.y} pairs:
//        dot = merge00(mul(n.p1,n.p1), zero@0x802964D8);
//        dot = madd(n.p0, n.p0, dot);
//        dot = sum0(dot, dot, dot);            -> stored 8 B at 0xd0
//    and only dot.flt.hi is used:  `if (dot.flt.hi > lbl_8030143C /*82944.0f*/)`
//    -> 12 pushes, else 3 appends.  (The four words ps_mul/ps_merge00/ps_madd/
//    ps_sum0 are byte-identical to fn_800A1230 / fn_800A11D8 / fn_800B090C.)
//  * Big branch: o0 = mid(v1,v2), o1 = mid(v2,v3), o2 = mid(v1,v3).  Each is
//    FIRST a full 0x18 copy of v1 (psq_l/psq_st of the pair-pair, lwz/stw colour,
//    lhz/sth nidx, lhz/sth tidx) and then has its x/y/z, its four colour BYTES
//    and its nidx/tidx overwritten.  midpoints are (b-a)*0.5f + a; the colour is
//    a + ((b-a)>>1) per unsigned byte; nidx/tidx use the same form on s16 casts.
//  * Push order (= the four sub-triangles): v1,o0,o2, o0,v2,o1, o0,o1,o2,
//    o2,o1,v3.  Small branch: an inlined append helper runs three times and
//    re-reads *arg0 each time (hence lwz r30,0(r30) three times).
//
// WHY IT STILL DOES NOT MATCH (blockers, in order of cost):
//  1. (30 words, >50 % of the gap) The want rematerialises the QUEUE GLOBAL's
//     address at all 15 call sites:
//         lis r6,0x8029 ; addi r6,r6,0x653c ; lwz r3,0(r6) ; bl
//     ngccc instead folds @l into the displacement and hoists the `lis` word
//     into a saved register (r31) for the whole function:
//         lis r31,X@ha ; lwz r3,X@l(r31) ; bl
//     Every source spelling tried (plain extern, extern array + [0], volatile
//     global, volatile/plain/register pointer to the global, address passed to
//     an inlined helper taking `s32 *`, struct-member double indirection) folds;
//     no flag changes it (probe: -fno-gcse/-fno-schedule-insns2/-fno-thread-jumps/
//     -fno-branch-probabilities/-fno-defer-pop/-fno-caller-saves all identical).
//     Evidence that this is register-pressure-driven and not a spelling: in the
//     want ALL 18 GPRs are live in the colour-lerp block (r14..r31 all appear),
//     so no register is spare to home the address; our block leaves r31 spare.
//     It is therefore downstream of blocker 2.
//  2. (10 words) The want masks every colour byte with `clrlwi rD,rS,0x18`
//     (= `(u8)x`) right after the `lbz`, 12 sites, CSE'd to 10.  We could not
//     find a spelling that keeps those masks: `((const u8*)&a->col)[k]` and a
//     `union {s32 c; struct{u8 b[4];}}` both fold (GCC knows lbz is already
//     zero-extended); an `s8` member instead produces `extsb` (wrong value
//     range).  The masks are only visible if GCC cannot range-analyse the byte,
//     i.e. the original colour bytes were probably not read as a plain `u8`
//     field of a stack local.
//  3. Frame: want frame 0x168 with stmw r14 at 0xf0 and SIX saved FPRs
//     (f26-f31); ours is 0x160 with stmw at 0xe0 and SEVEN (f25-f31).  Under the
//     closed form frame = Gsave + 72 + 8*nFPR that means we need 24 more bytes
//     of locals (q1/q2 at 0xdc/0xe0 are not homed by our body, and 0xe4..0xef
//     is dead in the want) and one fewer live FPR.  12 of those 24 bytes are
//     exactly the q1/q2 homes, so getting blocker 2 right likely fixes part of
//     this too.
//  4. Two cosmetic shape deltas remain: the want keeps `&v1` in r29 from before
//     the pops (`addi r29,r1,8 ; ... ; mr r4,r29`), ours rematerialises
//     `addi r4,r1,8`; and the want's `lfs f0,0xd0(r1) ; fmr f13,f0 ; fcmpu cr0`
//     has no `fmr` in ours.
//
// DIAGNOSTIC TRAP for blocker 1 (worth knowing before you re-measure it): the
// folded form prints as `lis r30,X@ha ; lwz r3,0(r30)` because ngccc leaves the
// low half in an R_PPC_ADDR16_LO relocation on the displacement field, so the
// field itself reads 0.  `lwz rX,0(rY)` therefore does NOT by itself prove the
// address was materialised - the tell is the accompanying `addi rY,rY,X@l`.
// Conversely a want that shows `lis + lwz X@l(rY)` with no addi IS the folded
// (hoistable) form, and 15 use sites will be homed in one saved register.
//
// LEVER THAT DID PAY (kept): declaring the copy DESTINATION's __ps_t pair
// members `volatile` (WVtx) reproduces retail's NON-CSE'd psq_l/psq_st pair-copy
// block - 3 x (psq_l+psq_st) per pair instead of 1 load + 3 stores - which is
// docs/parkings/81-*.md generalised from a volatile source to a volatile
// destination.  Worth +12 words.  Also worth keeping: a `goto` web for the
// small-triangle branch pins the block order so the push block falls through
// and the append block is the `ble` target (2.48 % vs 1.86 % for the same body
// written as if/else).
// ---------------------------------------------------------------------------
#include "types.h"
#include "dolphin/SN_PS.h"

typedef union {
    struct {
        f32 x, y, z, w;
    } f;
    struct {
        __ps_t p0, p1;
    } p;
} Vec4;

typedef union {
    struct {
        f32 x, y, z, w;
    } f;
    struct {
        __ps_t p0, p1;
    } p;
} WVec4;

typedef struct {
    Vec4 pos;
    s32 col;
    u16 n;
    u16 t;
} Vtx;

typedef struct {
    WVec4 pos;
    s32 col;
    u16 n;
    u16 t;
} WVtx;

extern s32 lbl_8029653C;
extern __ps_t lbl_802964D8;
extern f32 lbl_80296534;
extern f32 lbl_80296538;
extern s32 lbl_80366DDC;
extern f32 lbl_8030143C;
extern void fn_8006BC90(s32, void *);
extern void fn_8006BCDC(s32, void *);

static inline f32 mid3(f32 a, f32 b) {
    return (b - a) * 0.5f + a;
}

static inline u8 mid8(u8 a, u8 b) {
    return a + ((b - a) >> 1);
}

static inline u16 mid16(u16 a, u16 b) {
    return a + (((s16)b - (s16)a) >> 1);
}

static inline void append_vtx(Vtx **list, Vtx *v) {
    Vtx *p;

    p = *list;
    p->pos.p.p0 = v->pos.p.p0;
    p->pos.p.p1 = v->pos.p.p1;
    p->col = v->col;
    p->n = v->n;
    p->t = v->t;
    *list = p + 1;
}

#define MID_COL(dst, a, b)                                                     \
    do {                                                                       \
        ((u8 *)&(dst)->col)[0] = mid8(((const u8 *)&(a)->col)[0],              \
                                      ((const u8 *)&(b)->col)[0]);             \
        ((u8 *)&(dst)->col)[1] = mid8(((const u8 *)&(a)->col)[1],              \
                                      ((const u8 *)&(b)->col)[1]);             \
        ((u8 *)&(dst)->col)[2] = mid8(((const u8 *)&(a)->col)[2],              \
                                      ((const u8 *)&(b)->col)[2]);             \
        ((u8 *)&(dst)->col)[3] = mid8(((const u8 *)&(a)->col)[3],              \
                                      ((const u8 *)&(b)->col)[3]);             \
    } while (0)

s32 fn_8008279C(Vtx **arg0) {
    Vtx v1, v2, v3;
    Vec4 e0, e1, e2;
    WVtx o0, o1, o2;
    Vtx *p2, *p3;
    SN_PS_type dot;
    WVtx *q0, *q1, *q2;

    if (lbl_80366DDC == 0) {
        return 0;
    }
    p2 = &v2;
    p3 = &v3;
    fn_8006BCDC(lbl_8029653C, &v3);
    fn_8006BCDC(lbl_8029653C, p2);
    fn_8006BCDC(lbl_8029653C, &v1);

    e0.f.x = v2.pos.f.x - v1.pos.f.x;
    e0.f.y = v2.pos.f.y - v1.pos.f.y;
    e0.f.z = v2.pos.f.z - v1.pos.f.z;
    e0.f.w = lbl_80296534;
    e1.f.x = v3.pos.f.x - v1.pos.f.x;
    e1.f.y = v3.pos.f.y - v1.pos.f.y;
    e1.f.z = v3.pos.f.z - v1.pos.f.z;
    e1.f.w = lbl_80296534;
    e2.f.x = e0.f.y * e1.f.z - e0.f.z * e1.f.y;
    e2.f.y = e0.f.z * e1.f.x - e0.f.x * e1.f.z;
    e2.f.z = e0.f.x * e1.f.y - e0.f.y * e1.f.x;
    e2.f.w = lbl_80296534;

    dot.ps = __builtin_ps_mul(e2.p.p1, e2.p.p1);
    dot.ps = __builtin_ps_merge00(dot.ps, lbl_802964D8);
    dot.ps = __builtin_ps_madd(e2.p.p0, e2.p.p0, dot.ps);
    dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);

    if (dot.flt.hi <= lbl_8030143C) {
        goto small;
    }
        q0 = &o0;
        q1 = &o1;
        q2 = &o2;

        o0.pos.p.p0 = v1.pos.p.p0;
        o0.pos.p.p1 = v1.pos.p.p1;
        o1.pos.p.p0 = v1.pos.p.p0;
        o1.pos.p.p1 = v1.pos.p.p1;
        o2.pos.p.p0 = v1.pos.p.p0;
        o2.pos.p.p1 = v1.pos.p.p1;
        o0.col = v1.col;
        o0.n = v1.n;
        o0.t = v1.t;
        o1.col = v1.col;
        o1.n = v1.n;
        o1.t = v1.t;
        o2.col = v1.col;
        o2.n = v1.n;
        o2.t = v1.t;

        o0.pos.f.x = mid3(v1.pos.f.x, v2.pos.f.x);
        o0.pos.f.y = mid3(v1.pos.f.y, v2.pos.f.y);
        o0.pos.f.z = mid3(v1.pos.f.z, v2.pos.f.z);
        o1.pos.f.x = mid3(v2.pos.f.x, v3.pos.f.x);
        o1.pos.f.y = mid3(v2.pos.f.y, v3.pos.f.y);
        o1.pos.f.z = mid3(v2.pos.f.z, v3.pos.f.z);
        o2.pos.f.x = mid3(v3.pos.f.x, v1.pos.f.x);
        o2.pos.f.y = mid3(v3.pos.f.y, v1.pos.f.y);
        o2.pos.f.z = mid3(v3.pos.f.z, v1.pos.f.z);

        MID_COL(&o0, &v1, &v2);
        MID_COL(&o1, &v2, &v3);
        MID_COL(&o2, &v1, &v3);

        o0.n = mid16(v1.n, v2.n);
        o0.t = mid16(v1.t, v2.t);
        o1.n = mid16(v2.n, v3.n);
        o1.t = mid16(v2.t, v3.t);
        o2.n = mid16(v1.n, v3.n);
        o2.t = mid16(v1.t, v3.t);

        fn_8006BC90(lbl_8029653C, &v1);
        fn_8006BC90(lbl_8029653C, q0);
        fn_8006BC90(lbl_8029653C, q2);
        fn_8006BC90(lbl_8029653C, q0);
        fn_8006BC90(lbl_8029653C, p2);
        fn_8006BC90(lbl_8029653C, q1);
        fn_8006BC90(lbl_8029653C, q0);
        fn_8006BC90(lbl_8029653C, q1);
        fn_8006BC90(lbl_8029653C, q2);
        fn_8006BC90(lbl_8029653C, q2);
        fn_8006BC90(lbl_8029653C, q1);
        fn_8006BC90(lbl_8029653C, p3);
    return 1;

small:
    append_vtx(arg0, &v1);
    append_vtx(arg0, &v2);
    append_vtx(arg0, &v3);
    return 1;
}
