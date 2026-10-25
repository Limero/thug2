// WIP DRAFT (non-matching) — C body hand-reconstructed from the retail bytes.
// family=m2c range=0x800EAD24-0x800EB040 size=796B
// extra_cflags: -mps-float
// FLAG: -fno-schedule-insns2
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05 (ps-recon-17%): 17.1% masked, object size EXACT (796 B).
//
// What this body is: the previous draft was m2c garbage (it declared every
// stack slot `s32`, lost the three `fn_801AE5A4` results and every paired-single
// op, and scored 2.0%). Retail is a PS-vector ladder update: three
// `fn_801AE5A4(&pair, ctrl, vec)` transforms into 16-byte stack vectors, two
// `1/sqrt(len^2)` normalisations built from ps_mul/ps_merge00/ps_madd/ps_sum0/
// ps_rsqrte/ps_res, then per-axis muls0/add/sub. This C reproduces all of that
// (hence `-mps-float`, the `S_EAD24` layout with __ps_t pairs at +0x28/+0x50,
// and the 8-byte `V8` union slots for the "stored as a pair, read as f32"
// constants). Local-slot map now matches retail exactly: 12 volatile `__ps_t`
// at 0x08..0x67, 4 f32 at 0x68..0x74, 4 V8 at 0x78..0x90.
//
// Residual (all prologue + FPR-colouring, see below):
//  (1) frame is 0xB8, want 0xC8. Retail's save area starts at 0xAC; mine at
//      0xA4. Retail has 20 unused bytes (0x98..0xAB) after the last local that
//      ngccc does not reproduce: every extra-local shape was tried (extra
//      volatile __ps_t / volatile V8 / volatile f32 / unused V8 / struct-wrapped
//      V8 / extra pointers / SN_PS_type tail) and each either vanishes or
//      lands BEFORE the 4-byte group and pushes sp68 off 0x68.
//  (2) retail saves TWO FPRs (stfd f30,0xb8 + stfd f31,0xc0) and one is
//      lbl_8029AC4C (0.0f) loaded ONCE at 0x800EADF4 and then reused for five
//      compares/stores across four calls. ngccc rematerialises the global into
//      a volatile FPR (f8/f12) instead of hoisting it into f30, so the frame
//      and the whole prologue+epilogue shift by 0x10.
//  (3) the `mr r5,r0 ; cmpwi r0,0 ; bne ; lwz r5,0x4c(r9)` NULL-select (r0
//      holds the loaded value, r5 the outgoing arg register): every C spelling
//      tried collapses it to `lwz r5,... ; cmpwi r5,0` (no `mr`).
//  (4) PS block: retail opens with a provably-dead `psq_l f0,0x28(r1)` and
//      stores 0x10 TWICE (`a[1] = b[1]` emitted twice). Reachable only if
//      there is a hidden extra volatile local / duplicate assignment; ngccc
//      drops both. That is a 4-word offset for the whole PS block.
//  (5) the two normalisations: retail reuses the SAME ps_mul result in f12 for
//      both and re-loads only the {0,0} pair; this source writes the chain out
//      twice so cc1 re-loads b[0]/b[1] instead of keeping them in f12/f13.
//
// Ruled out: twin transfer (twin_scan/near_twin_scan find no byte- or ±4-word
// twin), `1/sqrtf()` spelling (need explicit __builtin_ps_* — confirmed: plain
// sqrtf would call the libm), store-order/permutation sweeps, extra flags
// (measured: none 16.1%, -fno-schedule-insns 13.6%, -fno-schedule-insns2 17.1%,
// both 8.5%).
#include "types.h"
#include "dolphin/SN_PS.h"
#include "qb_constants.h"
#include "structs.h"

extern __ps_t lbl_8029ABB0;
extern f32 lbl_8029AC4C;
extern f32 lbl_8029AC50;

/* arg0 layout recovered from retail: __ps_t pairs at +0x28 and +0x50 (read
 * with psq_l/ps_muls0), an s32 script state at +0x80 that is LATER read back
 * as part of the +0x50..+0x5F pair arithmetic, and a f32 "speed" at +0x7BC. */
typedef struct {
    char pad0[0x28];
    __ps_t v28[2];
    char pad1[0x50 - 0x38];
    __ps_t v50[2];
    char pad2[0x80 - 0x60];
    s32 st80;
    char pad3[4];
    f32 f88;
    char pad4[0xA0 - 0x8C];
    f32 fA0;
    char pad5[0x7BC - 0xA4];
    f32 f7BC;
    char pad6[0x1830 - 0x7C0];
    Unk_C7387A53 *p1830;
    char padx[4];
    CStruct *p1838;
    void *p183C;
    char pad7[0x19B8 - 0x1840];
    f32 f19B8;
} S_EAD24;

/* a slot written as a pair (psq_st) but read back as a scalar (lfs) */
typedef union { f32 f; __ps_t p; } V8;

CStruct *GetStructure(s32, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
void fn_801AE5A4(__ps_t *, CStruct *, Unk_C7387A53 *);
void fn_800EB040(void *);
void fn_800EB268(void *);
f32 cosf(f32);

void fn_800EAD24(S_EAD24 *arg0) {
    /* two named pointers into `a` so ngccc keeps a base address live in r29
     * and r30 (`addi r30,r1,8 ; mr r29,r30 ; psq_l ..,8(r29/r30)`) */
    volatile __ps_t *ap;
    volatile __ps_t *aq;
    volatile __ps_t a[2];
    volatile __ps_t b[2];
    volatile __ps_t c[2];
    volatile __ps_t d[2];
    volatile __ps_t e[2];
    volatile __ps_t g[2];
    f32 sp68;
    f32 sp6C;
    f32 sp70;
    f32 sp74;
    V8 sp78;
    V8 sp80;
    V8 sp88;
    V8 sp90;
    f32 f31;
    f32 f10;
    f32 f12;
    f32 f11;
    f32 f0;
    f32 f1;
    f32 var_f13;
    s32 up;
    s32 st;
    Unk_C7387A53 *p;
    Unk_C7387A53 *q;
    Unk_C7387A53 *r;
    __ps_t sq;
    __ps_t t;
    __ps_t t2;

    ap = a;
    aq = a;
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_LADDER_MOVE_SPEED, &sp68, 1);
    f31 = sp68;
    f31 = f31 * arg0->fA0;
    f1 = *(f32 *)((char *)arg0->p183C + 0x290);
    f31 = f31 * cosf(f1);
    arg0->f7BC = f31;
    f31 = f31 * arg0->f88;

    p = arg0->p1830;
    q = p->unk0x48;
    r = q;
    if (q == 0) {
        r = p->unk0x4C;
    }
    fn_801AE5A4((__ps_t *)&b[0], arg0->p1838, r);
    fn_801AE5A4((__ps_t *)&c[0], arg0->p1838, arg0->p1830);

    c[0] = b[0];
    a[0] = c[1];
    a[1] = b[1];
    sq = __builtin_ps_mul(ap[1], b[1]);
    t = __builtin_ps_merge00(sq, lbl_8029ABB0);
    t = __builtin_ps_madd(b[0], b[0], t);
    t = __builtin_ps_sum0(t, t, t);
    sp78.p = __builtin_ps_res(__builtin_ps_rsqrte(t));

    f10 = arg0->f19B8;
    f11 = sp78.f;
    f11 = f31 / f11;
    arg0->f19B8 = f10 + f11;
    up = (f11 > lbl_8029AC4C);

    t2 = __builtin_ps_merge00(sq, lbl_8029ABB0);
    t2 = __builtin_ps_madd(b[0], b[0], t2);
    t2 = __builtin_ps_sum0(t2, t2, t2);
    sp80.p = __builtin_ps_res(__builtin_ps_rsqrte(t2));
    f31 = sp80.f;

    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_LADDER_BOTTOM_OFFSET_UP, &sp6C, 1);
    if (arg0->f19B8 < (sp6C / f31)) {
        fn_800EB040(arg0);
        return;
    }
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_LADDER_TOP_OFFSET_UP, &sp70, 1);
    if (arg0->f19B8 > ((f31 - sp70) / f31)) {
        fn_800EB268(arg0);
        return;
    }
    f12 = arg0->f19B8;
    var_f13 = (f12 > lbl_8029AC50) ? lbl_8029AC50 : f12;
    f0 = (var_f13 < lbl_8029AC4C) ? lbl_8029AC4C : var_f13;
    arg0->f19B8 = f0;
    if ((f0 == lbl_8029AC4C) || (f0 == lbl_8029AC50)) {
        arg0->f7BC = lbl_8029AC4C;
        st = QB_LADDER;
    } else if (up != 0) {
        st = QB_LADDERMOVEUP;
    } else {
        st = QB_LADDERMOVEDOWN;
    }
    arg0->st80 = st;

    fn_801AE5A4((__ps_t *)&d[0], arg0->p1838, arg0->p1830);
    sp88.f = arg0->f19B8;
    e[1] = __builtin_ps_muls0(aq[1], sp88.p);
    e[0] = __builtin_ps_muls0(a[0], sp88.p);
    c[0] = __builtin_ps_add(d[0], e[0]);
    c[1] = __builtin_ps_add(d[1], e[1]);

    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_LADDER_CLIMB_OFFSET, &sp74, 1);
    sp90.f = sp74;
    g[0] = __builtin_ps_muls0(arg0->v50[0], sp90.p);
    g[1] = __builtin_ps_muls0(arg0->v50[1], sp90.p);
    arg0->v28[0] = __builtin_ps_sub(c[0], g[0]);
    arg0->v28[1] = __builtin_ps_sub(c[1], g[1]);
    arg0->f7BC = __builtin_fabsf(arg0->f7BC);
    b[0] = arg0->v28[0];
    b[1] = arg0->v28[1];
}

// Retail behavior summary, keyed by address:
// The prologue at 0x800EAD24 reserves 0xC8 bytes of frame, saves the link
// register, and spills float registers f30 and f31 at frame offsets 0xB8 and
// 0xC0. At 0x800EAD34 it saves integer registers from r29 at 0xAC, stores
// the link value at 0xCC, copies the first argument into r31, and zeroes r4.
// 800EAD44: GetStructure(QB_WALK_PARAMETERS,0)
// 800EAD50: GetFloat(...,QB_LADDER_MOVE_SPEED,&sp68,1)
// 800EAD64: f31 = sp68*fA0*cosf(*(f32*)(p183C+0x290)); arg0->f7BC = f31
// 800EAD88: f31 *= f88 ; fn_801AE5A4(&b,ctrl,p->unk0x48?:p->unk0x4C)
// 800EADAC: fn_801AE5A4(&c,ctrl,p1830)
// 800EADC8: c[0]=b[0]; a[0]=c[1]; a[1]=b[1]; a[1]=b[1]   (0x18 prologue of PS ops)
// 800EAE08: sq=ps_mul(a[1],a[1]); t=ps_merge00(sq,{0,0}); t=ps_madd(b[0],b[0],t)
// 800EAE1C: t=ps_sum0(t,t,t); sp78=ps_res(ps_rsqrte(t))
// 800EAE2C: f11=f31/sp78.lo ; arg0->f19B8 += f11 ; up=(f11>0.0f)
// 800EAE4C: sp80=ps_res(ps_rsqrte(ps_sum0(ps_madd(b[0],b[0],ps_merge00(sq,{0,0})))))
// 800EAE68: f31=sp80.lo
// 800EAE70: if (arg0->f19B8 < sp6C/f31) { fn_800EB040(arg0); return; }
// 800EAEB8: if (arg0->f19B8 > (f31-sp70)/f31) { fn_800EB268(arg0); return; }
// 800EAEF0: clamp to [0,1]; pick QB_LADDER / QB_LADDERMOVEUP / QB_LADDERMOVEDOWN
// 800EAF58: arg0->st80 = state
// 800EAF5C: fn_801AE5A4(&d,ctrl,p1830) ; sp88 = arg0->f19B8
// 800EAF90: e[1]=ps_muls0(a[1],sp88) ; e[0]=ps_muls0(a[0],sp88)
// 800EAFA4: c[0]=ps_add(d[0],e[0]) ; c[1]=ps_add(d[1],e[1])
// 800EAFCC: GetFloat(...,QB_LADDER_CLIMB_OFFSET,&sp74,1) ; sp90 = sp74
// 800EAFF4: g[0]=ps_muls0(arg0+0x50,sp90) ; g[1]=ps_muls0(arg0+0x58,sp90)
// 800EB004: arg0+0x28=ps_sub(c[0],g[0]) ; arg0+0x30=ps_sub(c[1],g[1])
// 800EB010: arg0->f7BC = fabsf(arg0->f7BC)
// 800EB01C: b[0]=arg0+0x28 ; b[1]=arg0+0x30   (dead volatile pair stores)