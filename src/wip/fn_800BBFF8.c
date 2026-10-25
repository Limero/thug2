// family=m2c range=0x800BBFF8-0x800BC968 size=2416B
// WIP DRAFT (non-matching) — m2c body, semantic corrections applied
// INERT: not registered in splits.txt/configure.py — never compiled, not
// counted in objdiff progress. activate via tools/wip.py.
//
// ============================================================================
// STATUS: PARKED. Retail is an EXPLICIT paired-single instruction stream, not
// scalar C that a PS-enabled compiler happens to vectorise.
//
// Measured (tools/ps_diff.py 0x800BBFF8, PS-aware masked diff):
//   want 2416B / 604 insns   |   got 1168B / 292 insns   |   0.3% (1/292)
// The masked score is POSITIONAL, so on a function this far from a match it
// is noise — the previous m2c husk scored 1.0% at 1148B purely because its
// first 287 words happened to line up better. Both are DIFF tier; neither is
// a promotion candidate. The semantics below are strictly more correct than
// the husk's, which is the reason to keep this version.
//
// The residual is not "regalloc". It is structural:
//  * 82 psq_l + 78 psq_st + 4 psq pair-ops and ~90 more primary-opcode-4
//    Gekko PS words (ps_mul / ps_madd / ps_sum0 / ps_muls0 / ps_rsqrte /
//    ps_res / ps_merge00..11 / ps_mr / ps_add / ps_sub) spread over ~45
//    distinct 8-byte stack slots between r1+0x08 and r1+0x130. m2c dropped
//    every one of them to a bare `0;` statement and modelled the slots it
//    still needed as FILE-SCOPE `static s32`, so ngccc dead-stripped ~55% of
//    the body (§4i/§6ai-152 statics-DCE pathology: 287 insns vs retail 604,
//    frame 0x78 vs retail 0x1b0).
//  * Probed the toolchain to see what is reachable. ProDG 3.9.3 + `-mps-float`
//    DOES emit the whole PS set (verified by compiling one builtin at a time:
//    ps_mul, ps_add, ps_sub, ps_muls0, ps_madd, ps_sum0, ps_rsqrte, ps_res,
//    ps_neg, ps_abs, ps_div, ps_msub, ps_sel and all four ps_merge0x).
//    Two caveats found: `__builtin_ps_mr` aliases ps_sum0 instead of emitting
//    XO9=72, and retail has 8 ps_mr; and `__builtin_ps_sum0` takes TWO args
//    ({a.lo + b.lo, ...}), which is why retail's `ps_sum0 fX,fX,fX` DOUBLES
//    the lo lane — the scalar model below reproduces that doubling.
//  * plain f32[4] array code is NOT an alternative source form: a 4-wide
//    straight-line f32 array body stays fully scalar (lfs/fmuls/stfs) under
//    -mps-float — GCC 2.95's SLP pass does not build ps_reg on this target.
//    So the original really was hand-written PS code, and the m2c draft's
//    "just let the compiler vectorise it" hope is dead.
//  * FPR pressure: retail keeps 30+ live PS values in f0..f13 and homes only
//    5 in f27..f31, so everything else goes to the ~45 stack slots. Spelling
//    the same maths with plain f32 scalars makes GCC demand 9 callee-saved
//    FPRs (f23..f31) and a 0xD8 frame instead of 5 and 0x1B0 — see the got
//    prologue in the ps_diff dump. That is the §4c/§6an-216 allocator wall,
//    reached here because the values cannot live in PS pair registers.
//
// Below are the corrections applied THIS round; every one is positively
// verified against the retail disassembly (no guessing):
//  1. FILE-LOCAL `BBObj` typedef with the TRUE field types. The shared
//     Unk_C399A1AE types every 0x128/0x148/0x158..0x180 slot as `s32`, so
//     m2c's body compiled `lfs` into `lwz`. Real layout: 0x1C, 0x30, 0x34,
//     0x38, 0x128, 0x12C, 0x130, 0x134, 0x148, 0x14C, 0x150, 0x154, 0x158,
//     0x15C, 0x160, 0x168, 0x16C, 0x170, 0x178, 0x17C, 0x180 are f32; 0x94
//     is u16 (retail `lhz`); 0x198 is u8 (retail `lbz` + `extsb`);
//     0x0C/0xD8/0xDC are s32 and 0x90 is a pointer.  (AGENTS.md trap 1.)
//  2. FILE-LOCAL `BBEntry` (0x30 bytes: 8 f32 + u8@0x2C + u8@0x2D +
//     s8@0x2E) and `BBRow` (0x18 bytes: 4 f32 + u8@0x10) for the real table
//     and barycentric-row layouts. m2c used four different
//     Unk_98537C55 / Unk_CB5A467A / Unk_C7387A53 / Unk_C399A1AE casts for the
//     SAME object, and read the row base as `*((s32 *)idx + rows)` — a *4
//     scale. Retail is `lfsx f12, r11, r10` = a raw 0x18*idx BYTE offset.
//  3. `fn_800BBEDC` returns f32, not s32. Verified: its epilogue is
//     `lfs f0,0x50(r1); fmr f1,f0; fdivs f1,f4,f1; blr`. m2c's `s32` proto
//     made `e->f20 = fn_800BBEDC(...)` store a bit pattern, not a float.
//     (M8.31 return-type flip.)
//  4. `fn_8009F27C` takes FIVE args, not four. Retail sets r3=self->0xC,
//     r4=self->0xD8, r5=self->0xDC, r6=0, r7=0, and the callee's prologue is
//     `mr r8,r6; mr r3,r4; stw r7,0xc(r1); mr r4,r5` — it consumes r3..r7.
//     m2c passed (0xC, 0xDC, 0, 0): it dropped the 0xD8 argument entirely and
//     invented a 4th. (doc-10 callee audit / §6e-32.)
//  5. `flag2D` is an 8-bit store (retail `stb r0,0x2d(r31)`) and `flag2C` an
//     8-bit load; m2c wrote `*(s32 *)((char *)e + 0x2D) = 1U`, a 4-byte store
//     at an odd address.
//  6. Pass 1 is now reconstructed in real scalars instead of being deleted.
//     Its LO lane at r1+0x90 is `ps_sum0(ps_madd(...), itself)`, i.e. exactly
//     twice `e[4]*va_lo + e[2]*vb_lo`, which is what `f31` and therefore the
//     whole max-tracking / lazy-init / delta chain actually test. Every line
//     carries the retail instruction it came from.
//  7. Known unreproducible detail, flagged rather than faked: retail reloads
//     r1+0x98 and r1+0xC0 with `psq_l` although only their LO halves are ever
//     written (`stfs`), then `ps_add`s the pair into self->0x130 / self->0x128
//     — so retail itself stores an uninitialised HI lane into self. No C can
//     reproduce an uninitialised value; this draft keeps the LO update and
//     leaves the HI lane alone, which is the honest reading.
// ============================================================================
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_80298E00;   /* 0.0f    */
extern f32 lbl_80298E04;   /* 1.0f    */
extern f32 lbl_80298E08;   /* ~1e-4f  */
extern f32 lbl_80298E0C;   /* 60.0f   */
extern bool lbl_80301B18;
extern char lbl_8037DFD8[];

/* --- real object layout (retail field types) ---------------------------- */
typedef struct {
    char pad0x00[0x0C];
    s32 unk0x0C;
    char pad0x10[0x0C];
    f32 f1C;
    char pad0x20[0x10];
    f32 f30;
    f32 f34;
    f32 f38;
    char pad0x3C[0x54];
    char *rows90;
    u16 mode94;
    char pad0x96[0x42];
    s32 unk0xD8;
    s32 unk0xDC;
    char pad0xE0[0x48];
    f32 f128;
    f32 f12C;
    f32 f130;
    f32 f134;
    char pad0x138[0x10];
    f32 f148;
    f32 f14C;
    f32 f150;
    f32 f154;
    f32 f158;
    f32 f15C;
    f32 f160;
    char pad0x164[0x04];
    f32 f168;
    f32 f16C;
    f32 f170;
    char pad0x174[0x04];
    f32 f178;
    f32 f17C;
    f32 f180;
    char pad0x184[0x14];
    u8 count198;
} BBObj;

/* --- real 0x30-byte lbl_8037DFD8 table entry --------------------------- */
typedef struct {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    u8 flag2C;
    u8 flag2D;
    s8 idx2E;
} BBEntry;

/* --- real 0x18-byte barycentric row of self->rows90 --------------------- */
typedef struct {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    u8 used;
} BBRow;

/* --- callees (arity / return type audited against the retail prologues) - */
f32 fn_800BBEDC(void *arg0, void *arg1, void *arg2);
f32 fn_800144C8(void);
void fn_80005A90(void *arg0, void *arg1);
void fn_8003EF4C(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_800BD050(BBObj *arg0, void *arg1, f32 arg2);
void fn_8009F27C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_801309EC(BBObj *arg0);

/* --- m2c's file-scope stand-ins for the PS-computed stack slots --------- */
/* Only the r1+0x90 slot is reconstructible in plain scalars (see the pass-1
   body: its LO lane is the doubled ps_sum0 of a ps_madd, and all three of
   those are plain scalar products). The other four stay m2c's stand-ins. */
static s32 spB8;
static s32 spC8;
static s32 spD8;
static s32 spE8;

/* The f32 slots retail keeps at r1+0x08..0x30 and r1+0x88..0x98. */
typedef struct {
    f32 s20a; /* r1+0x08  copy of self+0x128 lo */
    f32 s20b; /* r1+0x0C  copy of self+0x12C     */
    f32 s28a; /* r1+0x10  copy of self+0x130 lo */
    f32 s28b; /* r1+0x14  copy of self+0x134     */
    f32 s30a; /* r1+0x18  copy of self+0x148 lo */
    f32 s30b; /* r1+0x1C  copy of self+0x14C     */
    f32 s38a; /* r1+0x20  copy of self+0x150 lo */
    f32 s38b; /* r1+0x24  copy of self+0x154     */
    f32 s40a; /* r1+0x28  running 0x128 lo  */
    f32 s40b; /* r1+0x2C  running 0x128 hi  */
    f32 s48a; /* r1+0x30  running 0x130 lo  */
    f32 s48b; /* r1+0x34  running 0x130 hi  */
    f32 s80a; /* r1+0x88  broadcast X lo    */
    f32 s80b; /* r1+0x8C  broadcast X hi    */
    f32 s88a; /* r1+0x90  ps_sum0 result lo */
    f32 s88b; /* r1+0x94  ps_sum0 result hi */
    f32 s90;  /* r1+0x98  delta             */
    f32 s94;  /* r1+0x9C  self+0x1C         */
} BBSlots;

void fn_800BBFF8(BBObj *arg0) {
    static BBSlots sl;
    BBEntry *e;
    BBRow *rp;
    f32 fmax;
    f32 f29v;
    f32 f28v;
    f32 f30v;
    f32 f31v;
    s32 i;
    s32 k;
    s32 n;
    s32 anyUpdate;
    f32 t0;
    f32 t1;
    f32 vc0, vc1, vd0, vd1, va0, va1, vb0, vb1;
    f32 x0, x1, q1, u0, u1, m0, m1, s90;

    /* --- prologue: four pair snapshots of self + three constants -------- */
    sl.s20a = arg0->f128;
    sl.s20b = arg0->f12C;
    sl.s28a = arg0->f130;
    sl.s28b = arg0->f134;
    sl.s30a = arg0->f148;
    sl.s30b = arg0->f14C;
    sl.s38a = arg0->f150;
    sl.s38b = arg0->f154;
    f28v = lbl_80298E04; /* 1.0f  -> callee-saved f28 */
    f29v = lbl_80298E00; /* 0.0f  -> callee-saved f29 */
    fmax = f29v;         /*        -> callee-saved f27 */

    i = 0;
    for (;;) {
        /* ---------------------------------------------- pass 1 --------- */
        n = (s8)arg0->count198;
        anyUpdate = 1;
        if (n != 0) {
            k = n - 1;
            e = (BBEntry *)lbl_8037DFD8 + k;
            do {
                if (e->flag2C != 0) {
                    vc0 = arg0->f148; vc1 = arg0->f14C; /* C = {0x148,0x14C} */
                    vd0 = arg0->f150; vd1 = arg0->f154; /* D = {0x150,0x154} */
                    va0 = arg0->f128; va1 = arg0->f12C; /* A = {0x128,0x12C} */
                    vb0 = arg0->f130; vb1 = arg0->f134; /* B = {0x130,0x134} */

                    /* p0 = merge10(C,D) = {vc0, vd1};
                       p1 = merge10(e[0..1],e[4..7]) = {e00, e0C};
                       p0 = p0 * e[0..3];  p1 = C * p1;  p1 = p1 - p0;
                       x0 = vc0*e00 - vc0*e00;  x1 = vc1*e0C - vd1*e04 */
                    x0 = vc0 * e->f00 - vc0 * e->f00;
                    x1 = vc1 * e->f0C - vd1 * e->f04;
                    sl.s80a = x0;
                    sl.s80b = x1;

                    /* p2 = merge00(e[0..3],e[4..7]) = {e00, e08};
                       p3 = merge00(D,C) = {vd0, vc0};  p3 = p3 * p2;
                       p3 = bcast(p3) - {x0,x1}  -> q1 (only its hi is used) */
                    q1 = vd0 * e->f00 - x1;
                    vb0 = vb0 + x0;                /* ps_add f7,f7,{x0,x1} */
                    vb1 = vb1 + x1;
                    sl.s48a = vb0;                 /* fr.s28 at r1+0x28 */
                    sl.s48b = vb1;
                    va0 = va0 + x0;                /* ps_add f6,f6,{x0,x1} */
                    va1 = va1 + x1;
                    sl.s40a = va0;                 /* fr.s20 at r1+0x20 */
                    sl.s40b = va1;
                    sl.s30a = x0;                 /* merge10(p1,p3) = {x0,q1} */
                    sl.s30b = q1;

                    /* p4 = merge00(e[4..7] * B, K) = {e10*vb0, 0.0f};
                       p5 = ps_madd(e[4..7], A, p4);
                       ps_sum0(p5,p5) doubles the LO lane. */
                    u0 = e->f10 * vb0;
                    u1 = e->f14 * vb1;
                    m0 = e->f08 * va0 + u0;
                    m1 = e->f0C * va1 + 0.0f;
                    s90 = m0 + m0;
                    sl.s88a = s90;                 /* r1+0x90 */
                    sl.s88b = m1;

                    /* retail: lfs f12,0x90(r1); fmr f31,f12;
                             fcmpu f31,f29; bgt <next entry> */
                    f31v = s90;
                    if (!(f31v > f29v)) {
                        t0 = -f31v;               /* fneg f0,f31 */
                        anyUpdate = 0;
                        if (t0 > fmax) {          /* fcmpu f0,f27; ble; fmr */
                            fmax = t0;
                        }
                        f30v = -arg0->f30 * f31v; /* lfs 0x30; fneg; fmuls */
                        if (e->flag2D == 0) {     /* lbz 0x2D; cmpwi r0,0 */
                            e->f20 = fn_800BBEDC(arg0, (char *)e + 0x10, e);
                            e->flag2D = 1;        /* stb r0,0x2D(r31) */
                        }
                        /* fsubs f13,f30,f31; fmuls f13,f13,f12; fadds f0;
                           stfs f0,0x24(r31) */
                        t0 = (f30v - f31v) * e->f20;
                        e->f24 = e->f24 + t0;
                        sl.s90 = t0;              /* stfs f13,0x98(r1) */
                        sl.s94 = arg0->f1C;       /* stfs f12,0xa8(r1) */
                        /* ps_muls0 x2 then ps_add into the two self pairs.
                           Retail's psq_l of r1+0x98 has a HIGH lane it never
                           writes; only the LO lane (= t0) reaches a store. */
                        arg0->f130 = vb0 + t0;
                        arg0->f128 = va0 + t0;
                        arg0->f150 = vd0 + (-e->f08) * arg0->f1C;
                        arg0->f148 = vc0 + (-e->f08) * arg0->f1C;
                    }
                }
                e--;
                k--;
            } while (k != 0);
        }
        i++;
        if (i == 0x14) {
            if (arg0->unk0xD8 != 0) {
                fn_8009F27C(arg0->unk0x0C, arg0->unk0xD8, arg0->unk0xDC, 0, 0);
                fn_801309EC(arg0);
                return;
            }
            /* retail: stfs f29,0x128(r30); stfs f28,0xc(r26); stfs f29,4(r26);
                     stfs f29,8(r26); stfs f29,0x148(r30); stfs f28,0xc(r25);
                     stfs f29,8(r25); stfs f29,4(r25)  (r26=self+0x128,
                     r25=self+0x148) */
            arg0->f128 = f29v;
            arg0->f12C = f28v;
            arg0->f130 = f29v;
            arg0->f134 = f29v;
            arg0->f148 = f29v;
            arg0->f14C = f28v;
            arg0->f150 = f29v;
            arg0->f154 = f29v;
            return;
        }
        /* retail: lhz r0,0x94(r30); cmpwi r0,1; beq <body>;
                   cmpwi r23,0; beq 0x800bc070 (loop back into pass 1) */
        if (arg0->mode94 == 1 || anyUpdate != 0) {
            /* ------------------------------------- pass 2 (weighted) --- */
            if (n != 0) {
                k = n - 1;
                e = (BBEntry *)lbl_8037DFD8 + k;
                do {
                    if (e->flag2C != 0) {
                        /* retail: lwz r10,0x90(r30), then
                         * mulli r11,(s8)e->0x2E,0x18; add r9,r11,r10;
                         * lbz r0,0x10(r9); cmpwi r0,0 — a raw 0x18*idx
                         * BYTE offset, not the *4 index m2c wrote. */
                        rp = (BBRow *)((char *)arg0->rows90 +
                                       (s8)e->idx2E * 0x18);
                        if (rp != 0 && rp->used != 0) {
                            /* lfs f12,0xb8(r1); fmr f13,f12; fneg f13;
                               fcmpu f13,f9; ble <skip> */
                            if ((f32)spB8 > lbl_80298E08) {
                                /* lfs f0,lbl_80298E04; fdivs f0,f0,f13;
                                   stfs f0,0xe0(r1) */
                                spC8 = (s32)(lbl_80298E04 / (f32)spB8);
                                fn_80005A90(&spC8, &spD8);
                            }
                        }
                        /* retail: lfs f0,0xe8(r1); fmr f31,f0;
                                 fcmpu f31,f12; blt <next entry> */
                        if (!((f32)spD8 < lbl_80298E08)) {
                            /* mr r3,r30; mr r4,r1+0x38; mr r5,r31;
                               bl fn_800BBEDC -> f1 */
                            t0 = fn_800BBEDC(arg0, &spC8, e);
                            /* lfs f13,0x34(r30); lfs f0,0x24(r31);
                               fmuls f13,f13,f0; fcmpu f12,f13; ble;
                               fmr f12,f13; fneg f12,f12; stfs f12,0xf8 */
                            t1 = arg0->f34 * e->f24;
                            if (t0 * (f32)spE8 > t1) {
                                t0 = t1;
                            }
                            t1 = -t0;
                        }
                    }
                    e--;
                    k--;
                } while (k != 0);
            }
            /* --------------------------------------- pass 3 (damping) --- */
            t1 = fn_800144C8();            /* bl fn_800144c8; fmr f31,f1 */
            if (n != 0) {
                k = n - 1;
                e = (BBEntry *)lbl_8037DFD8 + k;
                do {
                    if (e->flag2C != 0) {
                        /* lfs f0,0x38(r30); lfs f12,0x28(r31); fneg f0;
                           fneg f0,f0; fmuls f0,f0,f12; fmuls f0,f0,f31;
                           stfs f0,0x110(r1) */
                        t0 = -arg0->f38 * e->f28 * t1;
                        if (lbl_80301B18 != 0) { /* lwz r0,0x1b18(r9) */
                            fn_8003EF4C(&spC8, &spE8, 0xFFFF00FF, 0, 1);
                        }
                    }
                    e--;
                    k--;
                } while (k != 0);
            }
            /* --------------------------------- pass 4 (resolve & call) - */
            /* retail walks the POINTER down and compares it against
             lbl_8037DFD8-0x30 (cmpw r9,r11) rather than a counter, and
             RETURNS from inside the body. */
            if (n != 0) {
                e = (BBEntry *)lbl_8037DFD8 + (n - 1);
                for (;;) {
                    if (e->flag2C != 0) {
                        /* mr r3,r30; addi r4,r1,0x28; fmr f1,f27;
                           bl fn_800bd050; b <epilogue> */
                        fn_800BD050(arg0, &spC8, fmax);
                        return;
                    }
                    e--;
                    if (e == (BBEntry *)lbl_8037DFD8 - 1) {
                        break;
                    }
                }
            }
            return;
        }
    }
}
