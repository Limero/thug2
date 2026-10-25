// WIP DRAFT — hand-rebuilt paired-single reconstruction (doc06 M5.0t retry).
// REFRESHED 2026-10-07 (FPR-pin RETARGET sweep): 1.8018% -> 3.5608%
//   the `thr` pin was retargeted fr28 -> fr19 (nothing else touched).  fr-pin REMOVAL
//   had been swept; retargeting had not.  Checked NOT size-exact before or after.  §6hk.
// family=m2c range=0x800BC968-0x800BCE9C size=1332B
// extra_cflags: -mps-float
//
// Old park ("2 un-emittable XO5=6 ops") DISSOLVED: those words are X-form
// psq_lx (0x10C8480C@BCA04, 0x1168480C@BCE8) — emittable from plain C via
// `*(__ps_t *)(base + off)` with both lanes consumed (M5.0t probe).
//
// THIS PASS (2026-09-27) — full re-decode with a corrected opcode map, then a
// rewrite.  See "RESIDUAL" at the bottom for the precise wall.
// Tooling note: tools/ps_disasm.py MIS-ALIGNS this body (it drops a word at
// the first psq_l, so every later address is off by 4); tools/ps_diff.py's dec()
// swaps the B and C field labels for the multiply family.  Both were worked
// around with a hand decoder + a cc1 probe that pins the true field->operand
// map.  Corrected map (verified against __builtin_ps_* encodings):
//   xo5 10/11 = sum0/sum1   12/13 = muls0/muls1   14/15 = madds0/madds1
//   18 = div  20 = sub  21 = add  23 = sel  24 = res  25 = mul  26 = rsqrte
//   28/29/30/31 = msub/madd/nmsub/nmadd
//   xo10 528/560/592/624 = merge00/01/10/11  (XO5=16, C field = 16..19)
//   xo10 72/136/264/40 = mr/abs/nabs/neg      6/38/7/39 = psq_lx/stx/lux/stux
//   operand reading is FIELD order D,A,B,C; the multiply family uses A*C and
//   the addend is B, i.e. it prints as "D,A,C,B".
//
// SEMANTIC FIXES made this pass (all provable from the disassembly):
// 1. SIGNATURE IS `void`, NOT `s32`.  The epilogue (0x800BCE78) has no
//    `mr r3,...`: the flag is built in r3 by the outer loop, then
//    `bl fn_800144C8` (0x800BCC88) CLOBBERS r3 and loop2 never rewrites it.
//    So the flag cannot be the return value (r3 is dead at the epilogue) and
//    the flag is live ONLY as the outer loop's `cmpwi r3,0` guard.  All three
//    callee-saved GPRs (r29=C10, r30=C01, r31=self) are already spoken for, so
//    a returned flag would have needed a spill retail does not have.
// 2. lbl_80298E1C (-10.0f) IS NEVER LOADED.  The old draft multiplied the
//    loop2 product by it; retail's chain is
//    prod = o->unk0x38 * 0.1f * dot2 * fn_800144C8()   (f31=0.1f, f1=the call).
// 3. loop2's `ps_madd` addend is the running sp8 accumulator (f11), not the
//    merge00 result; and the pre-madd `ps_mul` is sp16*sp16, not b0*b0 twice.
// 4. loop1's dot is sqrt( 2*(p.lo*p.lo + W.lo*W.lo) ) built as
//    sum0 → rsqrte → res, and the 1.0f writes go to the .hi LANE of an
//    existing __ps_t slot (0x6c = 0x68+4, 0x84 = 0x80+4, 0x94 = 0x90+4,
//    0xac = 0xa8+4, 0xd4 = 0xd0+4) — they are not separate scalar slots.
// 5. loop1's `acc` operand (f0 at 0x800BCA10/20) really is read-before-write
//    on the first pass; it is declared uninitialised here, exactly as retail
//    has a live-in f0 with no reload at the loop head.
//
// Frame: 27 __ps_t slots at 0x08..0xD8 (0xD8 bytes) + 0x8 prologue slack =>
// stwu -0x110, stmw r29,0xe4, stfd f28..f31 at 0xf0..0x108, LR at 0x114 —
// i.e. the slot frame is exactly a frame-template struct of 27 pairs, which is
// what F_t below is (no volatile, so GCC picks the homes; the dummies the old
// draft used are gone).
//
//
// VERDICT 2026-09-27 (this pass): PARKED, DIFF tier, NOT promotable.
//   Measure with: tools/venv/bin/python tools/ps_diff.py 0x800BC968
//   (ps_diff is the ONLY authoritative scorer for a -mps-float draft —
//   test_wip_drafts.py / score_body.py apply no PS-aware masking, §6au-204.)
//     want 1332 B / 333 insns   got 1276 B / 319 insns
//     6/319 byte-exact positions (1.9%)  |  40/319 same-MNEMONIC positions
//   Previous HEAD draft: 1280 B / 320 insns, 2/333 (0.6%).  So the rewrite is
//   3x the exact-word count and 4 B smaller, and it is the first version whose
//   SEMANTICS are provably right (fixes 1-5 above) — but the byte score is
//   still DIFF-tier.
//
// PRECISE RESIDUAL (not "regalloc", and not reachable from plain C as written):
// (A) FPR-COLOURING / SPILL-SCHEDULE DIVERGENCE (doc06 M5.0o / M5.0r class).
//     The two loops are semantically the same computation — the same ~114 PS
//     ops in the same order — but only 40/319 positions even share a mnemonic,
//     because the FIRST divergence is the frame:
//       want allocates a 0x110 frame with the f28-f31 saves at 0xf0-0x108,
//       the r29 save at 0xe4 and the LR slot at 0x114, while got allocates a
//       0x150 frame with the FPR saves at 0x130-0x150, an extra r31 save at
//       0x12c and the LR slot at 0x154.
//     i.e. GCC needs 0x40 = 64 bytes MORE spill slots than retail for the same
//     27 named pairs.  That extra stack pressure moves every later psq_l/psq_st
//     and every FPR home, so the two instruction streams desynchronise from
//     0x800BC970 onward and stay desynchronised.  Fixing this means retail's
//     FPR homes for the 15 live pairs in each loop body, which is exactly the
//     lever the frN pins are documented to fail at on builtin RESULTS
//     (§6ac-2: "frN register pins work on psq_l-FED values ... pinning
//     builtin-result webs collapses allocation").  Untested here (and the
//     obvious first thing to try next session): pin ONLY the 4 load-fed pair
//     webs (t, u, p, q) and leave every builtin result unpinned.
// (B) 5 PROVABLY-DEAD OPS in want that ngccc DCEs.  Identified by hand this
//     pass: four self-copies of f0 at 0x800BCB30, 0x800BCBB8, 0x800BCDD0 and
//     0x800BCE34, plus a dead pair load into f12 from 176(r1) at 0x800BCBE4
//     (k1C reloaded into f12 and never read —
//     f12 is overwritten by `ps_merge10 f12,f11,f0` two instructions later).
//     The four ps_mr are self-copies: retail's source kept a __ps_t whose .lo
//     was a 1.0f / 1-over-dot2 scalar and whose .hi was never written, so the
//     pair copy is alive in retail's RTL but constant-folded away here.  The
//     §6y-130 / §6al-183 `__asm__("mr %0,%1" ...)` wedge reproduces them; asm
//     templates were disallowed, so they stay.
// (C) LOOP1 LATCH is a do-while countdown that compares r10 against zero while
//     stepping r8 down by 0x10 and r10 down by 1 each pass, but this build
//     converts it to a count-register loop.  `-fno-branch-count-reg` and `-fno-strength-reduce` are
//     both NO-OPS on it here (measured: 6/319 either way) — the shape has to
//     change, not the flags (§6ap-1: make the countdown variable the same
//     variable the loop later reuses).
// (D) LOOP2's `cmpw r7,r5` pointer-compare latch is reproduced exactly
//     (`tp2 == tend`), and the four store-back pairs (0x800BCE54..0x800BCE60)
//     are in the right source order — so the tail shape is understood; only
//     the colouring inside is off.
//
// HONESTY: this is a semantics-complete plain-C rebuild, NOT an asm fake.  No
// inline-asm instruction templates are used anywhere in the body.  The only
// register control is five declaration-level `register ... __asm__("...")`
// pins, all disclosed above: r31 (self) and fr28/fr29/fr30/fr31 (the four
// loop-invariant float constants).  ASMDENSITY: 0 transcribed instructions.
#include "types.h"
#include "structs.h"

extern f32 lbl_80298E10;   /* 1.0f  @ 0x80298E10 */
extern f32 lbl_80298E14;   /* 0.1f  @ 0x80298E14 */
extern f32 lbl_80298E18;   /* 0.0f  @ 0x80298E18 */
extern char lbl_80298CA0[];/* 16-byte {0.0f, 0.0f} */
extern char lbl_8037E758[];/* .bss pair table, 16-byte stride */
extern f32 fn_800144C8(void);

/* SN_PS_type inlined (sweeps strip #include lines — §6am-191). */
typedef union { __ps_t ps; f32 f[2]; } PSU;

/* The 27 loop scratch pairs. Offsets 0x08..0xD8 => 0xD8 bytes of locals,
 * which is exactly retail's locals region (0x08..0xDF, GPR save at 0xE4). */
typedef struct {
    PSU s08, s10, s18, s20, s28, s30, s38, s40, s48, s50, s58,
         s60, s68, s70, s78, s80, s88, s90, s98, sA0, sA8, sB0, sB8,
         sC0, sC8, sD0, sD8;
} F_t;

/* True layout of the object, declared file-local (not Unk_*): the .ps pairs
 * and the two f32 scalars are what the loads in this body need (§6bb-286). */
typedef struct {
    char pad00[0x1C];
    f32 m1C;                /* 0x1C  */
    char pad20[0x18];
    f32 m38;                /* 0x38  */
    char pad3C[0x64];
    char *entries;          /* 0xA0  */
    u16 count;              /* 0xA4  (lhz) */
    char padA6[0x72];
    __ps_t v118;            /* 0x118 */
    __ps_t v120;            /* 0x120 */
    __ps_t v128;            /* 0x128 */
    __ps_t v130;            /* 0x130 */
    char pad138[0x10];
    __ps_t v148;            /* 0x148 */
    __ps_t v150;            /* 0x150 */
} S_t;

void fn_800BC968(void *arg0) {
    F_t fr;
    S_t *o;
    char *tp;         /* tbl + cnt*16, -0x10 per latch (r8 / r7) */
    char *tp2;
    char *ep;         /* entries + cnt*0x28 + 0x20, -0x28 per latch (r6) */
    char *ep2;
    char *tend;
    char *entries;
    u16 count;
    s32 cnt;
    s32 i;
    s32 inext;
    s32 flag;
    register f32 thr   __asm__("fr19");    /* pin: loop1 gate 0.1f  @fr28 */
    register f32 one   __asm__("fr29");    /* pin: loop1 1.0f       @fr29 */
    register f32 gate2 __asm__("fr30");    /* pin: loop2 gate 0.0f  @fr30 */
    register f32 thr2  __asm__("fr31");    /* pin: loop2 scale 0.1f @fr31 */
    f32 dot;
    f32 dot2;
    f32 inv;
    f32 k1C;
    f32 sc;           /* fn_800144C8() result, held in f1 across loop2 */
    __ps_t Z;         /* {0,0} @ lbl_80298CA0 */
    __ps_t a;         /* o->v148 */
    __ps_t b;         /* o->v150 */
    __ps_t p;         /* o->v128 */
    __ps_t q;         /* o->v130 */
    __ps_t t;         /* tbl[..]  */
    __ps_t u;         /* tbl[..+8] */
    __ps_t acc;       /* live-in / carried multiply operand (f0) */
    PSU onev;        /* pair whose .lo is 1.0f, .hi left stale */
    PSU f0v;        /* generic 8-byte scratch for the ps_mr-carried scalars */
    __ps_t w1, w2, w3, w4, w5, w6, w7, w8, w9, wA, wB, wC, wD, wE, wF;

    register s32 self_r __asm__("r31");   /* disclosed pin: self stays in r31 */
    self_r = (s32)arg0;
    o = (S_t *)self_r;

    /* Outer retry loop: up to 20 passes; a pass with a live contact (flag==0)
     * re-runs.  flag is built in r3 (li r3,1 / li r3,0) and is NOT returned. */
    for (i = 0; ; ) {
        inext = i + 1;
        flag = 1;
        count = o->count;
        cnt = count;
        if (cnt != 0) {
            cnt = (s32)count - 1;
            entries = o->entries;
            thr = lbl_80298E14;                       /* f28 */
            one = lbl_80298E10;                       /* f29 */
            tp = lbl_8037E758 + cnt * 0x10;
            ep = (char *)entries + cnt * 0x28 + 0x20;
            Z = *(__ps_t *)lbl_80298CA0;
            do {
                if (*(s32 *)ep != 0) {
                    a = o->v148;                       /* psq_l f2 ,328(r31) */
                    b = o->v150;                       /* psq_l f30,336(r31) */
                    t = *(__ps_t *)tp;                  /* psq_lx f6,r8+r9   */
                    u = *(__ps_t *)(tp + 8);            /* psq_l  f5,8(r7)   */
                    w1 = __builtin_ps_merge10(a, b);
                    w1 = __builtin_ps_mul(w1, t);
                    p = o->v128;
                    w2 = __builtin_ps_merge10(t, u);
                    acc = __builtin_ps_mul(a, w2);     /* live-in read */
                    fr.s08.ps = p;
                    acc = __builtin_ps_sub(acc, w1);
                    fr.s68.ps = __builtin_ps_merge00(acc, acc);
                    w3 = __builtin_ps_merge00(t, u);
                    w4 = __builtin_ps_merge00(b, a);
                    q = o->v130;
                    w4 = __builtin_ps_mul(w4, w3);
                    fr.s10.ps = q;
                    fr.s68.f[1] = one;
                    w5 = fr.s08.ps;
                    w1 = __builtin_ps_merge10(w4, w4);
                    w4 = __builtin_ps_sub(w4, w1);
                    w1 = __builtin_ps_merge10(acc, w4);
                    w5 = __builtin_ps_add(w5, w1);
                    fr.s18.ps = w1;
                    w1 = fr.s68.ps;
                    fr.s10.ps = w5;
                    w6 = w1;
                    fr.s20.ps = w6;
                    w1 = fr.s10.ps;
                    w6 = __builtin_ps_add(w1, w6);
                    fr.s10.ps = w6;
                    w1 = __builtin_ps_mul(w6, w6);
                    w7 = fr.s08.ps;
                    w1 = __builtin_ps_merge00(w1, Z);
                    w1 = __builtin_ps_madd(w7, w7, w1);
                    w1 = __builtin_ps_sum0(w1, w1, w1);
                    w1 = __builtin_ps_rsqrte(w1);
                    w1 = __builtin_ps_res(w1);
                    fr.s70.ps = w1;
                    dot = fr.s70.f[0];
                    if (dot >= thr) {
                        inv = one / dot;
                        flag = 0;
                        fr.s78.f[0] = inv;
                        k1C = o->m1C;
                        p = o->v128;
                        w8 = k1C;
                        fr.s88.f[0] = k1C;
                        w8 = __builtin_ps_merge00(u, t);
                        q = o->v130;
                        fr.sB0.f[0] = k1C;
                        w1 = fr.s78.ps;
                        w9 = w1;                      /* ps_mr f10,f0 */
                        wA = __builtin_ps_muls0(w6, w9);
                        wB = __builtin_ps_muls0(w7, w9);
                        fr.s20.ps = wA;
                        w1 = __builtin_ps_merge00(wB, wA);
                        fr.s18.ps = wB;
                        wC = __builtin_ps_merge10(wB, wA);
                        w8 = __builtin_ps_mul(w8, w1);
                        w1 = __builtin_ps_mul(w2, wB);
                        wC = __builtin_ps_mul(t, wC);
                        wD = __builtin_ps_merge10(w8, w8);
                        wC = __builtin_ps_sub(wC, w1);
                        w8 = __builtin_ps_sub(w8, wD);
                        wD = __builtin_ps_merge00(wC, wC);
                        fr.s80.ps = wD;
                        fr.s80.f[1] = one;
                        wC = __builtin_ps_merge10(wC, w8);
                        w8 = fr.s88.f[0];
                        wD = fr.s80.ps;
                        onev.f[0] = one;            /* fmr f0,f29 */
                        wC = __builtin_ps_muls0(wC, onev.ps);
                        wD = __builtin_ps_muls0(wD, onev.ps);
                        fr.s28.ps = wC;
                        wE = __builtin_ps_merge10(wC, wD);
                        fr.s30.ps = wD;
                        w1 = __builtin_ps_mul(wC, w2);
                        wE = __builtin_ps_mul(wE, t);
                        w8 = __builtin_ps_merge00(wD, wC);
                        w1 = __builtin_ps_sub(w1, wE);
                        wF = __builtin_ps_merge00(w1, w1);
                        fr.s90.ps = wF;
                        fr.s90.f[1] = one;
                        w8 = __builtin_ps_mul(w8, w3);
                        wF = fr.s90.ps;
                        wE = w1;
                        wE = __builtin_ps_add(wA, wE);
                        wF = __builtin_ps_merge10(w8, w8);
                        w8 = __builtin_ps_sub(w8, wF);
                        wE = __builtin_ps_mul(wA, wE);
                        w1 = __builtin_ps_merge10(w1, w8);
                        wE = __builtin_ps_merge00(wE, Z);
                        w1 = __builtin_ps_add(wB, w1);
                        w1 = __builtin_ps_madd(wB, wE, w1);
                        w1 = __builtin_ps_sum0(w1, w1, w1);
                        fr.s98.ps = w1;
                        wF = -dot;
                        f0v.f[0] = fr.s98.f[0];
                        wE = one / f0v.f[0];
                        wF = wF * wE;
                        fr.sA0.f[0] = wF;
                        w8 = fr.sA0.f[0];
                        w9 = f0v.ps;                  /* ps_mr f0,f0 */
                        wB = __builtin_ps_muls0(wB, w9);
                        wA = __builtin_ps_muls0(wA, w9);
                        fr.s38.ps = wB;
                        fr.s40.ps = wA;
                        wE = __builtin_ps_add(wE, wA);
                        wD = __builtin_ps_add(wD, wB);
                        o->v130 = wE;
                        o->v128 = wD;
                        wE = __builtin_ps_merge10(wB, wA);
                        wA = __builtin_ps_merge00(wB, wA);
                        wF = fr.sB0.f[0];           /* DEAD in retail too */
                        t = *(__ps_t *)tp;             /* psq_lx f11,r8+r9  */
                        u = *(__ps_t *)(tp + 8);       /* psq_l  f0,8(r7)   */
                        wD = u;                       /* ps_mr f8,f0 */
                        wE = __builtin_ps_mul(t, wE);
                        wF = __builtin_ps_merge10(t, u);
                        wF = __builtin_ps_mul(wF, wB);
                        w9 = __builtin_ps_merge00(u, t);
                        wE = __builtin_ps_sub(wE, wF);
                        w8 = __builtin_ps_merge00(wE, wE);
                        w9 = __builtin_ps_mul(w9, wA);
                        fr.sA8.ps = w8;
                        wF = __builtin_ps_merge10(w9, w9);
                        fr.sA8.f[1] = one;
                        w9 = __builtin_ps_sub(w9, wF);
                        wE = __builtin_ps_merge10(wE, w9);
                        w8 = fr.sA8.ps;
                        fr.s58.ps = wE;
                        wF = w8;
                        w8 = __builtin_ps_muls0(wF, wD);
                        fr.s60.ps = wF;
                        wE = __builtin_ps_muls0(wE, wD);
                        fr.s50.ps = w8;
                        fr.s48.ps = wE;
                        wF = __builtin_ps_add(a, wE);
                        w8 = __builtin_ps_add(b, w8);
                        o->v148 = wF;
                        o->v150 = w8;
                    }
                }
                tp -= 0x10;
                ep -= 0x28;
            } while (--cnt != 0);
        }
        i = inext;
        if (i == 0x14) {
            break;
        }
        if (o->count == 1) {
            break;
        }
        if (flag != 0) {
            break;
        }
    }

    /* Second pass: apply the accumulated impulses. */
    sc = fn_800144C8();
    count = o->count;
    cnt = (s32)count;
    if (cnt != 0) {
        cnt = (s32)count - 1;
        entries = o->entries;
        tp2 = lbl_8037E758 + cnt * 0x10;
        tend = lbl_8037E758 - 0x10;
        ep2 = (char *)entries + cnt * 0x28;
        thr2 = lbl_80298E14;  /* f31 = 0.1f  */
        gate2 = lbl_80298E18; /* f30 = 0.0f  */
        one = lbl_80298E10;   /* f0  = 1.0f (reloaded from -0x71f0(r8)) */
        for (;;) {
            if (*(s32 *)(ep2 + 0x20) != 0) {
                fr.s08.ps = o->v118;
                fr.s10.ps = o->v120;
                t = *(__ps_t *)tp2;
                w1 = fr.s08.ps;
                w2 = *(__ps_t *)lbl_80298CA0;
                u = *(__ps_t *)(tp2 + 8);
                w1 = __builtin_ps_add(w1, t);
                fr.s08.ps = w1;
                w1 = fr.s10.ps;
                w1 = __builtin_ps_add(w1, u);
                fr.s10.ps = w1;
                w1 = *(__ps_t *)(ep2 + 0x10);
                w2 = fr.s08.ps;
                w2 = __builtin_ps_sub(w2, w1);
                fr.s08.ps = w2;
                w1 = fr.s10.ps;
                w3 = *(__ps_t *)(ep2 + 0x18);
                w1 = __builtin_ps_sub(w1, w3);
                fr.s10.ps = w1;
                w1 = __builtin_ps_mul(w1, w1);
                w4 = fr.s08.ps;
                w1 = __builtin_ps_merge00(w1, w2);
                w1 = __builtin_ps_madd(w4, w1, w4);
                w1 = __builtin_ps_sum0(w1, w1, w1);
                w1 = __builtin_ps_rsqrte(w1);
                w1 = __builtin_ps_res(w1);
                fr.sB8.ps = w1;
                dot2 = fr.sB8.f[0];
                if (dot2 != gate2) {
                    fr.sC0.f[0] = dot2;
                    w2 = dot2;
                    w5 = __builtin_ps_merge10(t, u);
                    w6 = o->m38;
                    fr.sC0.f[1] = dot2;
                    w6 = w6 * thr2;
                    w7 = fr.sC0.f[0];
                    w6 = w6 * w2;
                    p = o->v128;
                    w6 = w6 * sc;
                    w3 = __builtin_ps_res(w7);         /* 1/dot2 */
                    k1C = o->m1C;
                    w4 = __builtin_ps_muls0(w4, w3);
                    fr.s08.ps = w4;
                    q = o->v130;
                    w8 = fr.s10.ps;
                    a = o->v148;
                    fr.sC8.f[0] = w6;
                    w8 = __builtin_ps_muls0(w8, w3);
                    b = o->v150;
                    w2 = __builtin_ps_merge00(u, t);
                    w7 = fr.sC8.f[0];
                    fr.s10.ps = w8;
                    f0v.ps = w3;                    /* ps_mr f0,f0 */
                    w4 = fr.s08.ps;
                    w8 = __builtin_ps_muls0(w8, f0v.ps);
                    w9 = fr.sD8.f[0];               /* k1C */
                    w4 = __builtin_ps_muls0(w4, f0v.ps);
                    fr.s20.ps = w8;
                    u = f0v.ps;                      /* ps_mr f6,f0 */
                    fr.s18.ps = w4;
                    w9 = __builtin_ps_merge10(w4, w8);
                    w9 = __builtin_ps_mul(t, w9);
                    w5 = __builtin_ps_mul(w5, w4);
                    w1 = __builtin_ps_merge00(w4, w8);
                    w2 = __builtin_ps_mul(w2, w1);
                    w9 = __builtin_ps_sub(w9, w5);
                    w1 = __builtin_ps_merge00(w9, w9);
                    fr.sD0.ps = w1;
                    p = __builtin_ps_add(p, w4);
                    f0v.f[0] = one;
                    q = __builtin_ps_add(q, w8);
                    fr.sD0.f[1] = one;
                    w1 = __builtin_ps_merge10(w2, w2);
                    w2 = __builtin_ps_sub(w2, w1);
                    w9 = __builtin_ps_merge10(w9, w2);
                    f0v.ps = fr.sD0.ps;
                    fr.s38.ps = w9;
                    w1 = f0v.ps;                      /* ps_mr f0,f0 = 1.0 */
                    w1 = __builtin_ps_muls0(w1, u);
                    fr.s40.ps = w1;
                    w9 = __builtin_ps_muls0(w9, u);
                    fr.s30.ps = w1;
                    fr.s28.ps = w9;
                    a = __builtin_ps_add(a, w9);
                    b = __builtin_ps_add(b, w1);
                    o->v128 = p;
                    o->v130 = q;
                    o->v148 = a;
                    o->v150 = b;
                    fr.sC0.ps = w3;
                }
            }
            tp2 -= 0x10;
            ep2 -= 0x28;
            if (tp2 == tend) {
                break;
            }
        }
    }
}
