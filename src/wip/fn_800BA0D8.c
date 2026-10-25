// WIP DRAFT (non-matching) — hand-rebuilt from the DOL disassembly 2026-09-27
// family=m2c range=0x800BA0D8-0x800BA59C size=1220B
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled into
// the DOL, not counted in objdiff progress. activate via tools/wip.py.
//
// fn_800BA0D8 — the skater "composite xform" update. Retail 1220 B / 305 insns
// (symbols.txt size:0x4C4 = 0x800BA0D8..0x800BA598). Structure recovered from
// the DOL:
//   * prologue stwu -0x168; mfcr+mtcrf CR save at 0x124; f29/f30/f31 at
//     0x150/0x158/0x160; ONE stmw at 0x128; LR at 0x16c. NOTE the single
//     `stmw r22,0x128(r1)` / `lmw r22,0x128(r1)` pair saves+restores the WHOLE
//     r22..r31 block (10 words, 0x128..0x14F) — it is not a one-register save.
//   * guard self->unk0x114 == 2 -> epilogue, emitted BEFORE the time fetch.
//   * integrate unk0x19C, then unk0x110, by the frame delta. The unk0x110
//     underflow path is an s16-offset vtable dispatch: lwz node+8(vt),
//     lha 0x38(vt), lwz 0x3C(vt), add, mtlr+blrl.
//   * unk0x114 == 0 -> 8 PS pairs self+0x158.. -> node+0xD0 and return.
//   * main path: a 0..4-iteration probe loop (fn_8010794C / fn_80107B20 /
//     fn_800BB02C / fn_800BCE9C) building a 4-pair transform block in the
//     r1+8 local, plus a two-component paired-single normalize on a hit.
//   * tail: three scalar cross-product rows packed into two pairs, 2x ps_re,
//     re-broadcast into node+0x58/0x60, 8-pair block copies to node+0x78 and
//     node+0xD0, node+0xB8/0xC0 from self+0x128/0x130, then fn_800BDAD4
//     behind lbl_80301B14.
//
// ---------------------------------------------------------------------------
// FILE-LOCAL TYPEDEFS ARE LOAD-BEARING (AGENTS.md trap 1 / M6.89d-note).
// The shared class Unk_EA9C57B9 types 0xB8/0xBC/0xC0/0xC4/0x110/0x158..0x180/
// 0x19C as `s32` (a corpus-wide majority vote) and 0xA4 as `s32`; this
// function loads/stores every one of them with lfs/stfs, and 0xA4 with lhz.
// With the shared class the whole float tail becomes fctiwz/stw pairs and the
// lhz becomes a lwz, which changes the object size and every frame offset.
// BA0D8_S is this function's real layout; BA0D8_N is the child node and
// BA0D8_M the 0x100-byte r1+8 local block. Also note the 0x158.. region is
// 8 PAIRS but the transform tail reads individual LANES of them (0x158/0x15C
// are the two halves of pair 0), so it needs both views — `lf = (f32 *)&...`.
//
// ---------------------------------------------------------------------------
// PARKED 2026-10-03: NOT byte-identical. 71/296 words (24.0%)
//   under tools/ps_diff.py; object 1184 B vs retail 1220 B; compiles clean.
//   Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/ps_diff.py 0x800BA0D8
//   (test_wip_drafts.py reports DIFF for every PS draft — it applies no psq
//   masking and ignores the -mps-float FLAG line; use ps_diff.py. The
//   24.9% quoted by the 2026-09-27 round was the same scorer on a body with a
//   WRONG-OPCODE stand-in for 4 words, see the correction below.)
//
// *** CORRECTION TO THE 2026-09-27 PARK REASON — there is no "ps_re wall". ***
//   The four words 0x10E06890 (want+0x17C), 0x10003890 (+0x1B4),
//   0x11600090 (+0x388) and 0x11803890 (+0x39C) were decoded as A-form
//   xo5=8/frC=2 => "ps_re" and the round concluded byte-exact was unreachable.
//   They are **X-form ps_mr pair moves** (XO10 = frC<<5 | xo5 = 2<<5|8 = 72).
//   ps_re is XO10 = 683; `(w >> 1) & 0x3FF` is 72 for all four, so they are
//   not ps_re. Decoded form (tools/ps_diff.py is right, the round's note was
//   wrong):  ps_mr f7,f13 / ps_mr f0,f7 / ps_mr f11,f0 / ps_mr f12,f7.
//   Semantic proof, not just a bit-slice: each one is a *broadcast* — the
//   source FPR is in ps0 mode (a scalar written by a store and read back as a
//   pair), and every consumer is a multiply or add on that same register: the
//   first broadcast scales one pair twice by the reciprocal of f30, and the
//   second broadcast scales another pair twice by the reciprocal of
//   f30*0.5f*f30 (offsets 232(r1) at +0x17C and 240(r1) at +0x1B4).
//     +0x388 ps_mr f11,f0 / +0x39C ps_mr f12,f7 are the same two broadcasts
//            for the tail's two packed cross-product rows.
//   ps_mr is trivially emittable (docs/parkings/06 M5.0q; byte-exact
//   src/fn_801B19DC.c is full of them). The C is therefore a plain
//   assignment, `BCAST(x) == (x)`, which is what this file now does. Any
//   other draft parked on "ps_re is not emittable" is parked for no reason
//   and should be re-audited with the two-form decoder (06 M5.0q).
//
// MEASURED (ps_diff, body semantics held constant):
//   RECIP = __builtin_ps_div({1,1}, x)  59/295  20.0%  1180 B  (wrong opcode)
//   BCAST, do{}while(hit)               71/296  24.0%  1184 B  <- kept
//   BCAST, for(;;) + trailing break      59/295  20.0%  1180 B
//   BCAST, three duplicated loop tails   59/295  20.0%  1180 B
//   (the old 24.9%/1208 B figure = RECIP + three duplicated tails; its extra
//    bytes came from the 4 wrong-opcode ps_divs + the rodata-pair address,
//    i.e. it was size-gaming, not a better body.)
//
// RESIDUAL (in attack order):
//  (1) TWO ps_mr COPIES THAT THIS BUILD ELIMINATES. want needs f7 to hold
//      bcast(fr.e0) for two ps_muls0 and f0 to hold bcast(fr.e2) for two
//      more, so it materialises each broadcast once into a long-lived
//      register (the psq_l itself lands in f13/f7, then ps_mr moves it).
//      This build front-end CSEs each pair away: it psq_l's straight into
//      f8/f9 and uses those for both consumers, so it emits **zero** ps_mr
//      (verified by dumping the .o's .text — grep ps_mr returns nothing).
//      Splitting the C into two variables does not help; the fix has to be
//      an FPR pin (recipe 67: `register __ps_t u0 __asm__("fr7")`), untried.
//  (2) OBJECT IS 9 WORDS SHORT (1184 vs 1220). Six of the missing words are
//      the two ps_mr above plus want's two redundant scalar `fmr` copies at
//      the end of the normalize block (want loads the scalar at 0xf8(r1),
//      copies it across FPRs and issues a negative-multiply-add into f7, then
//      loads the scalar at 0x100(r1), copies it and divides f7 by it to form
//      f31, where this build loads directly into f1/f0 — pure FPR
//      allocator tie-break, not expressible in C).
//  (3) LOOP PLACEMENT. want: pre-loop falls straight into the body
//      (+0x158), latch `cmpwi r27,4` at +0x2B4 and the back edge
//      `bne cr4,+0x158` at +0x300 (cr4 was set at +0x2A0, reused across the
//      RemoveRefLink call). Every C spelling tried — `for(;;)`, `for(;;)`
//      with a trailing `if (hit==0) break;`, duplicated tails, and
//      `do{}while(hit)` — makes GCC emit the latch block BEFORE the body and
//      branch into the body from the pre-loop instead, so everything after
//      the loop is offset. This is block placement, not loop semantics.
//  (4) CHILD-NODE REGISTER (want+0xA8 on). want reloads self->unk0x0C three
//      times (r3 for the vcall, r11 for the 0x58/0x60 stores, r9 for the
//      0x78/0xD0 copies); this build CSEs one value into a single reg.
//  (5) PAGE ANCHORS. want keeps 0x802A0000 in r22 all body long AND
//      rematerialises copies in r9 (prologue compares) and r24 (the 0.5f
//      reload). This build emits `lis`+`lis`+`addi` for the same page twice
//      and never hoists; the two `register s32 pg22/pg24 __asm__("r22"/
//      "r24")` pins in this file do not fix it.
//  (6) The 8-pair block copies keep f0 here, alternate f0/f7/f13 in want, and
//      `&fr` is hoisted into r30 for both loop calls where want remats it
//      with `addi r3,1,8` for fn_8010794C and keeps the saved copy (r26) for
//      fn_80107B20. Both are downstream of (1)/(3).
//
#include "types.h"

extern __ps_t lbl_80298CA0;    /* epsilon vector table, 0x3C */
extern f32 lbl_80298D88;       /* 0.0f */
extern f32 lbl_80298D8C;       /* 0.5f */
extern f32 lbl_80298D90;       /* 6.0f */
extern bool lbl_80301B14;

/* the vtable slot this function dispatches through: s16 this-offset at
 * +0x38, function pointer at +0x3C (lha + lwz + add + mtlr/blrl). */
typedef struct BA0D8_VT {
    char pad0x00[0x38];
    s16 unk0x38;
    void (*unk0x3C)(void *);
} BA0D8_VT;

/* the child transform node hanging off self->unk0x0C */
typedef struct BA0D8_N {
    char pad0x00[0x08];
    BA0D8_VT *unk0x08;
    char pad0x0C[0x4C];
    __ps_t unk0x58;
    __ps_t unk0x60;
    char pad0x68[0x10];
    __ps_t unk0x78;
    __ps_t unk0x80;
    __ps_t unk0x88;
    __ps_t unk0x90;
    __ps_t unk0x98;
    __ps_t unk0xA0;
    __ps_t unk0xA8;
    __ps_t unk0xB0;
    __ps_t unk0xB8;
    __ps_t unk0xC0;
    char pad0xC8[0x08];
    __ps_t unk0xD0;
    __ps_t unk0xD8;
    __ps_t unk0xE0;
    __ps_t unk0xE8;
    __ps_t unk0xF0;
    __ps_t unk0xF8;
    __ps_t unk0x100;
    __ps_t unk0x108;
} BA0D8_N;

/* this function's real `self` layout — see the header note */
typedef struct BA0D8_S {
    char pad0x00[0x0C];
    BA0D8_N *unk0x0C;
    char pad0x10[0x10];
    __ps_t unk0x20;
    __ps_t unk0x28;
    char pad0x30[0x74];
    u16 unk0xA4;
    char pad0xA6[0x12];
    f32 unk0xB8;
    f32 unk0xBC;
    f32 unk0xC0;
    f32 unk0xC4;
    char pad0xC8[0x34];
    s32 unk0xFC;
    char pad0x100[0x10];
    f32 unk0x110;
    s32 unk0x114;
    __ps_t unk0x118;
    __ps_t unk0x120;
    __ps_t unk0x128;
    __ps_t unk0x130;
    char pad0x138[0x20];
    __ps_t unk0x158;
    __ps_t unk0x160;
    __ps_t unk0x168;
    __ps_t unk0x170;
    __ps_t unk0x178;
    __ps_t unk0x180;
    __ps_t unk0x188;
    __ps_t unk0x190;
    char pad0x198[0x04];
    f32 unk0x19C;
} BA0D8_S;

/* The 0x100-byte local block at r1+8. fn_8010794C / fn_80107B20 /
 * fn_800BCE9C all take its address, which is what keeps the otherwise-dead
 * v0..v3 pair stores alive. r0..r3 are the four cross-product scalars the
 * tail materialises as two pairs. */
typedef struct BA0D8_M {
    __ps_t p0;                 /* +0x00  r1+0x08 */
    __ps_t p1;                 /* +0x08  r1+0x10 */
    __ps_t p2;                 /* +0x10  r1+0x18 */
    __ps_t p3;                 /* +0x18  r1+0x20 */
    f32 r0;                    /* +0x20  r1+0x28 */
    f32 r1;
    f32 r2;                    /* +0x28  r1+0x30 */
    f32 r3;
    char pad0x30[0x50];
    f32 f80;                   /* +0x80  r1+0x88 */
    char pad0x84[0x24];
    void *obj;                 /* +0xA8  r1+0xB0 */
    void *lnk4;                /* +0xAC  r1+0xB4 */
    void *lnk8;                /* +0xB0  r1+0xB8 */
    char pad0xB4[0x0C];
    __ps_t v0;                 /* +0xC0  r1+0xC8 */
    __ps_t v1;                 /* +0xC8  r1+0xD0 */
    __ps_t v2;                 /* +0xD0  r1+0xD8 */
    __ps_t v3;                 /* +0xD8  r1+0xE0 */
    f32 e0;                    /* +0xE0  r1+0xE8 */
    f32 e1;
    f32 e2;                    /* +0xE8  r1+0xF0 */
    f32 e3;
    __ps_t w0;                 /* +0xF0  r1+0xF8 */
    __ps_t w1;                 /* +0xF8  r1+0x100 */
} BA0D8_M;

void CObject_RemoveRefLink(void *, void *);
f32 fn_800144C8(void);
void *fn_8010794C(void *);
s32 fn_80107B20(void *, s32, s32);
void fn_800BA9C8(BA0D8_S *);
void fn_800BA704(BA0D8_S *);
void fn_800BA678(BA0D8_S *);
void fn_800BB02C(BA0D8_S *, f32);
void fn_800BCE9C(BA0D8_S *, void *);
s32 fn_800BB9BC(BA0D8_S *);
void fn_800BBFF8(BA0D8_S *);
void fn_800BC968(BA0D8_S *);
void fn_800BB738(BA0D8_S *);
void fn_800BB8A4(BA0D8_S *);
void fn_800BDAD4(BA0D8_S *);

/* CORRECTION 2026-10-03: the four XO10=72 words this draft used
 * to blame on ps_re are plain X-form pair moves, i.e. a broadcast of a
 * ps0-mode scalar FPR into a pair — NOT a reciprocal. Raw words at +0x17C,
 * +0x1B4, +0x388 and +0x39C move the broadcast value into its consumer
 * register (the first fed from the pair loaded at 232(r1), i.e. the stored
 * f30; the tail two feed the cross-product rows at r1+0x28 and r1+0x30).
 * ps_re is XO10=683; these decode to XO10=72 exactly, and every downstream
 * user is a ps_muls0/ps_add whose frB/frC is the moved register, which is the
 * broadcast shape. ngccc emits ps_mr natively (docs/parkings/06 M5.0q,
 * byte-exact src/fn_801B19DC.c), so the whole "opcode wall" that parked this
 * function did not exist — the source just assigns the pair. */
#define BCAST(x) (x)

void fn_800BA0D8(BA0D8_S *arg0) {
    BA0D8_M fr;
    BA0D8_M *sp;
    BA0D8_N *nd;
    BA0D8_N *nd2;
    BA0D8_VT *vt;
    __ps_t q0, q1, q2, q3, q4, q5, q6;
    __ps_t u0, u1, u2;
    f32 f30, f31;
    f32 t0, t1, t2;
    f32 c29;
    f32 *lf;
    void *ep;                  /* &fr.obj        -> callee-saved home */
    __ps_t *epsv;              /* &lbl_80298CA0  -> r23, want psq_l 0(r23) */
    /* Page-anchor pins (the only inline asm in this file; declaration level).
     * want keeps the 0.802A0000 page in r22 for the whole body and reads it
     * at want+0x314 (the probe-loop clamp), and again in r24 for the 0.5f
     * reload inside the loop. A pseudo holding a symbol address is
     * rematerialisable, so GCC 2.95 re-emits `lis` at each use site instead of
     * hoisting it into a callee-saved home; a hard register is not
     * rematerialisable, so the pin is what forces the hoist. The two prologue
     * compares deliberately keep the plain `lbl_80298D88` reference so GCC
     * still emits want's SECOND page copy in r9. s32 (not a pointer) because
     * cc1 silently drops pointer-typed register vars (AGENTS.md 76-178). */
    register s32 pg22 __asm__("r22");
    register s32 pg24 __asm__("r24");
    s32 fzero;                 /* the shared 0   -> callee-saved home */
    s32 r27;
    s32 r30;
    s32 hit;

    if (arg0->unk0x114 == 2) {
        return;
    }

    f31 = fn_800144C8();

    pg22 = 0x802A0000;

    if (arg0->unk0x19C > lbl_80298D88) {
        arg0->unk0x19C = arg0->unk0x19C - f31;
    } else {
        hit = 1;
        if (!(arg0->unk0xFC & 2)) {
            hit = 0;
        }
        if (hit == 0) {
            fn_800BA9C8(arg0);
        }
    }

    if (arg0->unk0x110 >= lbl_80298D88) {
        if (!(arg0->unk0x110 <= f31)) {
            goto sub110;
        }
        nd = arg0->unk0x0C;
        vt = nd->unk0x08;
        vt->unk0x3C((char *)nd + vt->unk0x38);
        goto after110;
sub110:
        arg0->unk0x110 = arg0->unk0x110 - f31;
after110:
        ;
    }

    if (arg0->unk0x114 == 0) {
        nd = arg0->unk0x0C;
        nd->unk0xD0 = arg0->unk0x158;
        nd->unk0xD8 = arg0->unk0x160;
        nd->unk0xE0 = arg0->unk0x168;
        nd->unk0xE8 = arg0->unk0x170;
        nd->unk0xF0 = arg0->unk0x178;
        nd->unk0xF8 = arg0->unk0x180;
        nd->unk0x100 = arg0->unk0x188;
        nd->unk0x108 = arg0->unk0x190;
        return;
    }

    sp = &fr;
    fn_800BA704(arg0);

    /* these four are live across every call in the loop, so retail homes them
     * in callee-saved registers (r25 zero, r26/r28 &fr, r29 &fr.obj,
     * r23 lbl_80298CA0) — that is what makes want's single `stmw r22` span
     * r22..r31 and puts the CR slot at 0x124. */
    pg24 = 0x802A0000;
    epsv = &lbl_80298CA0;
    ep = (void *)&fr.obj;
    fzero = 0;
    c29 = lbl_80298D90;        /* 6.0f, want f29 */
    f30 = f31;
    r27 = 0;

    for (;;) {
        fr.e0 = f30;
        f31 = f30;
        fn_8010794C(sp);

        /* --- transform build, interleaved with fn_80107B20's args --- */
        q0 = *(volatile __ps_t *)&fr.e0;   /* psq_l 232(r1) */
        q1 = arg0->unk0x128;
        u0 = BCAST(q0);
        q2 = arg0->unk0x118;
        q1 = __builtin_ps_muls0(q1, u0);
        fr.p0 = q2;
        t2 = f30 * *(f32 *)(pg24 - 0x7274);
        t2 = t2 * f30;
        fr.e2 = t2;
        q3 = arg0->unk0x130;
        q3 = __builtin_ps_muls0(q3, u0);
        u1 = *(volatile __ps_t *)&fr.e2;   /* psq_l 240(r1) */
        q4 = arg0->unk0x20;
        q5 = arg0->unk0x28;
        u2 = BCAST(u1);
        q0 = arg0->unk0x118;
        q4 = __builtin_ps_muls0(q4, u2);
        q6 = arg0->unk0x120;
        q5 = __builtin_ps_muls0(q5, u2);
        fr.v3 = q3;
        fr.v2 = q1;
        q0 = __builtin_ps_add(q0, q1);
        fr.v1 = q5;
        q6 = __builtin_ps_add(q6, q3);
        fr.v0 = q4;
        q0 = __builtin_ps_add(q0, q4);
        q6 = __builtin_ps_add(q6, q5);
        fr.p2 = q0;
        fr.p3 = q6;
        fr.p1 = q6;

        r30 = fn_80107B20(sp, 0, 0);

        if (r30 != 0) {
            u0 = sp->p1;
            q0 = fr.p3;
            u1 = arg0->unk0x130;
            q0 = __builtin_ps_sub(q0, u0);
            u2 = sp->p0;
            u0 = fr.p2;
            q1 = __builtin_ps_mul(q0, u0);
            q2 = *epsv;
            q3 = arg0->unk0x128;
            u0 = __builtin_ps_sub(u0, u2);
            u1 = __builtin_ps_mul(u1, u0);
            fr.v1 = u0;
            q1 = __builtin_ps_merge00(q1, q2);
            u1 = __builtin_ps_merge00(u1, q2);
            fr.v2 = q0;
            u0 = __builtin_ps_madd(u0, u0, q1);
            q3 = __builtin_ps_madd(q3, q3, u1);
            u0 = __builtin_ps_sum0(u0, u0, u0);
            q3 = __builtin_ps_sum0(q3, q3, q3);
            u0 = __builtin_ps_rsqrte(u0);
            q3 = __builtin_ps_rsqrte(q3);
            u0 = __builtin_ps_res(u0);
            q3 = __builtin_ps_res(q3);
            fr.w0 = u0;
            fr.w1 = q3;
            t0 = *(volatile f32 *)&fr.w0;
            t1 = sp->f80;
            t2 = t1 * t0 - c29;
            t0 = *(volatile f32 *)&fr.w1;
            f31 = t2 / t0;
            if (f31 < *(f32 *)(pg22 - 0x7278)) {
                f31 = *(f32 *)(pg22 - 0x7278);
            }
        }

        fn_800BB02C(arg0, f31);

        if (r30 != 0) {
            fn_800BCE9C(arg0, sp);
        }

        f30 = f30 - f31;
        if (r27 == 4) {
            fn_800BA678(arg0);
            if (fr.obj != 0) {
                CObject_RemoveRefLink(fr.obj, ep);
                fr.obj = fzero;
            }
            break;
        }
        r27 = r27 + 1;
        if (fr.obj != 0) {
            CObject_RemoveRefLink(fr.obj, ep);
            fr.obj = fzero;
        }
    } while (r30 != 0);

    if (fn_800BB9BC(arg0) != 0) {
        fn_800BBFF8(arg0);
    }

    if (arg0->unk0xA4 != 0) {
        fn_800BC968(arg0);
    }

    fn_800BB738(arg0);
    fn_800BB8A4(arg0);

    /* --- three scalar cross-product rows, then two pairs --- */
    lf = (f32 *)&arg0->unk0x158;
    t0 = arg0->unk0xBC;
    t1 = t0 * lf[4];
    t2 = t0 * lf[5];
    fr.r0 = arg0->unk0xB8 * lf[0] + t1;
    fr.r1 = arg0->unk0xB8 * lf[1] + t2;
    fr.r2 = arg0->unk0xB8 * lf[2] + (t0 * lf[6]);
    fr.r3 = arg0->unk0xC4;
    fr.r0 = arg0->unk0xC0 * lf[8] + fr.r0;
    fr.r1 = arg0->unk0xC0 * lf[9] + fr.r1;
    fr.r2 = arg0->unk0xC0 * lf[10] + fr.r2;

    q0 = *(volatile __ps_t *)&fr.r0;
    q1 = *(volatile __ps_t *)&fr.r2;
    fr.p2 = q0;
    fr.p3 = q1;
    fr.p2 = BCAST(fr.p2);
    fr.p3 = BCAST(fr.p3);
    fr.p0 = __builtin_ps_add(arg0->unk0x118, fr.p2);
    fr.p1 = __builtin_ps_add(arg0->unk0x120, fr.p3);
    nd = arg0->unk0x0C;
    nd->unk0x58 = fr.p0;
    nd->unk0x60 = fr.p1;
    nd2 = arg0->unk0x0C;
    nd2->unk0x78 = arg0->unk0x158;
    nd2->unk0x80 = arg0->unk0x160;
    nd2->unk0x88 = arg0->unk0x168;
    nd2->unk0x90 = arg0->unk0x170;
    nd2->unk0x98 = arg0->unk0x178;
    nd2->unk0xA0 = arg0->unk0x180;
    nd2->unk0xA8 = arg0->unk0x188;
    nd2->unk0xB0 = arg0->unk0x190;
    nd2->unk0xD0 = arg0->unk0x158;
    nd2->unk0xD8 = arg0->unk0x160;
    nd2->unk0xE0 = arg0->unk0x168;
    nd2->unk0xE8 = arg0->unk0x170;
    nd2->unk0xF0 = arg0->unk0x178;
    nd2->unk0xF8 = arg0->unk0x180;
    nd2->unk0x100 = arg0->unk0x188;
    nd2->unk0x108 = arg0->unk0x190;
    nd2 = arg0->unk0x0C;
    nd2->unk0xB8 = arg0->unk0x128;
    nd2->unk0xC0 = arg0->unk0x130;

    if (lbl_80301B14 != 0) {
        fn_800BDAD4(arg0);
    }
}
