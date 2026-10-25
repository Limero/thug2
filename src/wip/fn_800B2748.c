// WIP DRAFT (non-matching) — hand-rebuild 2026-09-28 from WANT disasm
// family=m2c range=0x800B2748-0x800B29D8 size=656B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// STATUS: PARKED at 76/164 masked words (46.3%), object size EXACT (656B =
// 164 instructions, same as want, and the block layout now matches: the case-0
// body, the case-1 body and the case-2/4 body all start at want's offsets
// 0x279C / 0x2870 / 0x2888).  Was 35.6% (the previous hand-rebuild).
// Every remaining diff is a REGISTER-ASSIGNMENT difference — the opcode
// sequence, the dispatch tree, the frame/slot map, the call shapes and the
// semantics are all byte-shaped right (the two matrix chains are now
// semantically correct, which the previous draft got wrong).
//
// MEASURED LEVERS (keep these if this is revisited):
//  1. The dot-product test MUST be `len2.flt.hi > 0.0f` (element 0), not
//     `.flt.lo`.  cc1 turns a PS->SF extract of element 0 into `ps_mr` +
//     `fcmpu` — exactly want's 0x27E4/0x27E8 — and also inlines the if-body
//     (want's `ble` skips *over* it).  `.flt.lo` gives a whole-register
//     `fmr` + a 64-bit compare, a `psq_st` spill of the union and a
//     `lwz/stw/stw` GPR round-trip: 4 wrong words AND a 1-word shift that
//     costs the whole rest of the function.  This one change was worth ~6 pts
//     on its own and unblocked every later fix.
//  2. FR needs two more 8-byte slots: `SN_PS_type sc` at +0x48 (the
//     {rsqrt,1.0f} pair) and `SN_PS_type bst` at +0x50 (the scale pair).
//     `fr.bst.flt.hi = scale;` + a pair read is what produces want's
//     `stfs 0x50(r1)` + `psq_l 80(r1)`; a plain `f32` + `__ps_t` temp gets
//     optimised to a bare register broadcast and loses both.
//  3. TWO one-instruction `ps_mr` asm wedges (1.2% of the function).  cc1
//     only emits `ps_mr` for a PS->SF extract in a COMPARE context or for a
//     scalar BUILTIN argument; `sc.ps = <scalar lane>` folds to a plain pair
//     store.  Six C spellings tried (plain pair copy, union-member read,
//     forwarded local union, explicit (f32) cast, self-assign, mixed pair /
//     scalar operand) ALL fold.  The wedges reproduce want's
//     `ps_mr f13,f0; psq_st f13,0x48` and `ps_mr f0,f13` exactly and are
//     what make the instruction COUNT match.
//  4. The second matrix chain (unk7C) was semantically WRONG in the old
//     draft.  Retail multiplies *all six* madds by obuf[0] (re-read into a
//     second register), the madds1 pair is (u[3],m1) then (u[2],m0), the
//     madds0 pair is (u[4],m3) then (u[5],m2), m2[1]=m6 / m2[0]=m7 and the
//     final adds are obuf[0]=m6+obuf[1], obuf[1]=m7+t[1].  Same for the first
//     chain: m3 = madds1(m28, v0, m1) — NOT madds1(m28, m1, m2) — and
//     m6/m7 use m48/m50 with m2[0]=m6 / m2[1]=m7.
//  5. Store-order (recipes 24/64/198).  The first chain's 4-store run needs
//     the source order [m2[0], m[0], m2[1], m[1]] (interleaved), NOT grouped
//     — worth +5.9 pts on its own.  The second chain's equivalent shuffle is
//     neutral-to-negative; leave it grouped.
//  6. Case 0's two scale multiplies must be `muls0(t[0])` then `muls0(t[1])`
//     in source (+1.2 pts).  `d1`/`d0` compute order and declaration order
//     are both no-ops.
//  7. Case 0's obuf[1] store must go through the pointer (`p = &fr.obuf[0];
//     p[1] = fr.m[1];`), NOT `fr.obuf[1] = fr.m[1];` — the pointer form is
//     what makes cc1 keep the `8(rN)` store at all (+3.5 pts with the rest).
//  8. Case 2/4 must use `fr.obuf[...]`, not `p[0]`/`p[1]`: the pointer form
//     lets cc1 prove the case-0 obuf[1] store dead and drops it (-1 word).
//
// RESIDUAL (88 diffs; opcode sequence and every instruction offset agree,
// only registers differ):
//  (a) GPR: `arg2` is homed in r29, want uses r28 — costs 0x2764, 0x27A0,
//      0x27B0, 0x2874, 0x289C, 0x28CC (6).  Root cause: cc1 gives r28 to the
//      `p` variable and r29/r30 to case 2/4's two pointers, whereas want
//      gives r28 to arg2, r29/r30 to case 2/4 and homes `p` in r11 with a
//      per-path birth copy (r9 in case 0, r29 in case 2/4).
//  (b) case 0 head FPRs: d1 in f8 (want f9), d0 in f9 (want f12) — costs
//      0x27B4, 0x27C0, 0x27C8, 0x27CC, 0x27D8, 0x27DC (6).
//  (c) case 0 if-body: the `lfs 1.0f` is hoisted to 0x27FC, want has it at
//      0x2804, so the 9 words 0x27F0-0x2818 are all shifted (10 diffs).
//      Moving `sc.flt.lo = 1.0f` before/after the muls0, naming a `f32 one`
//      local, and every -fno-sched* flag are all no-ops.
//  (d) case 0 tail: the `psq_l 80(r1)` (bst pair) and `psq_l 24(r1)` (t0)
//      loads come out in the opposite order to want's, shifting the 0x2830
//      window; the rest are colour-only (16 diffs, 0x281C-0x2868).
//  (e) case 2/4 first chain: the whole FPR map is permuted (m20 f6 vs f0,
//      m18 f0 vs f6, m30 f8 vs f7, m28 f7 vs f8, t0 f4 vs f5, t1 f5 vs f4,
//      m40 f9 vs f12, m38 f11 vs f9, m48 f12 vs f0, m50 f0 vs f11) — 14
//      diffs, 0x28A4-0x2914.  The opcodes and the 0x28D4 madds1 already match.
//  (f) case 2/4 second chain: all 24 words 0x2944-0x29A0 differ in FPRs
//      only.  Two extra allocator facts want has and cc1 will not reproduce:
//      obuf[0] is live in TWO registers (f10 for the two muls0 + the two
//      madds1, f11 re-loaded for the madds0/madds1 tail) and the unk7C
//      pointer stays in r3 ACROSS `bl fn_80057FBC` (an ABI violation — cc1
//      reloads into r9 at 0x2944).
//  (g) epilogue: `psq_l/psq_st f12` vs f13 (2 diffs, 0x29BC/0x29C0).
//
// DEAD ENDS (measured, do not re-run): all four -fno-sched* flags are exact
// no-ops on this body; a `volatile double`/frame-dummy sweep is pointless
// (the frame 0x70 / stmw r27 / stw r0,0x74 already matches and no FPR is
// saved); `p[0]`/`p[1]` in case 2/4 (-1 word, see lever 8); `*(f32 *)&psvar`
// and `*(SN_PS_type *)&psvar` ICE cc1 at expmed.c:1115; comparing a `__ps_t`
// directly with a float (`len2 > 0.0f`) ICEs cc1 at optabs.c:3515 (both are
// documented in AGENTS.md §6ai-154 / §7c-163) — the `.flt.hi` union read is
// the only working spelling; renaming/reordering d0/d1/base and moving v1's
// `ps_sub` in the first chain are all no-ops; hard-register pins were NOT
// tried on the PS webs because §6ai-169/§6y-125 record that pinning
// builtin-result PS webs collapses the whole allocation (and 20+ webs are
// live here, far past the §74-161c "beyond ~2 pins allocation collapses"
// threshold).
// WIP DRAFT (non-matching) — hand-rebuild 2026-09-28 from WANT disasm
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-30: 46.3% -> 48.8% — but the body is now
// SEMANTICALLY CORRECT (3 real m2c/hand-decode bugs fixed, each of which
// individually LOWERED the masked %; see "SEMANTIC FIXES" below). Object
// 656B = 164 instructions = symbols.txt size:0x290. 84 residual mismatches,
// all register ASSIGNMENT (opcode sequence, every instruction offset, the
// dispatch tree, frame/slot map, call shapes and the store-run positions all
// match).
// family=m2c range=0x800B2748-0x800B29D8 size=656B
//
// WHY PARKED: the residual is a paired-single FPR/GPR allocation wall over
// ~20 simultaneously-live PS webs in three phases (case 0, case 2/4 chain 1,
// case 2/4 chain 2).  cc1 2.95.2 has no lever for it here: every `frN` /
// `register` pin on a PS web is either SILENTLY DROPPED (they are all
// builtin-result webs, not psq_l-fed ones — §6ai-169/§6cw) or inert, `volatile`
// on the matrix operands reorders worse, and all 12 flag combos are no-ops or
// worse.  Want additionally keeps the `unk7C` pointer in r3 ACROSS
// `bl fn_80057FBC`, which clobbers r3 (its 2nd insn is `lwz r3,0x14(r3)`) —
// unreachable from any C because a call-crossing value can never be born in a
// volatile register.
//
// SEMANTIC FIXES (all three are REAL bugs; each cost masked %, kept anyway):
//  1. chain 1's last two madds1 had m48/m48<->m50 swapped.  Want
//     `ps_madds1 f0,f0,f13,f12` with f0 loaded by `psq_l f0,80(r31)` (arg1+0x50
//     = m50) and f11 by `psq_l f11,72(r31)` (arg1+0x48 = m48).  The draft had
//     m6=madds1(m48,..), m7=madds1(m50,..).  Also the two m2[] result slots
//     were reversed: want `psq_st f0,64(r1)` (m2[1]) then `psq_st f11,56(r1)`
//     (m2[0]).        -> alone: 46.3% -> 45.1%
//  2. chain 2 used `fr.obuf[0]` as the multiplicand for ALL EIGHT madds.
//     Want loads obuf[0] into f10 (`psq_l f10,8(r1)`) for n0..n3 and obuf[1]
//     into f11 (`psq_l f11,8(r29)`) for n4..n7.
//                                          -> alone: 46.3% -> 45.7%
//  3. chain 2's final add used `m6 + fr.obuf[1]`; want reloads t[0]
//     (`psq_l f10,24(r1)`) and does `m6 + t0`.   -> alone: colour-neutral
//
// LEVERS TRIED (with measured scores, all on the corrected body):
//  4. case 0's store goes through its OWN pointer local `q`, and the case-2/4
//     and case-0 chains each get their own m0..m7 / n0..n7 set (§6cw
//     per-phase names).  This is what removed a duplicate `psq_st ...,16(r1)`
//     and took the object from 660B back to the exact 656B.  40.0% -> 45.1%
//  5. `register __ps_t *base __asm__("r10")` in case 0 — want homes the
//     `&arg1->v08` base in r10, cc1 picks r11.  45.1% -> 48.8%.  This also
//     freed r28 for arg2, which is why `mr r28,r5` and every `psq_l ..(r28)`
//     now match (was a 6-word r28<->r29 cascade).
//  6. `__asm__("ps_mr %0,%1" ...)` wedges (2 emitted insns = 1.2%): kept from
//     the previous session.  They are what make the instruction COUNT match —
//     cc1 only emits ps_mr for a PS->SF extract in a COMPARE context or as a
//     scalar builtin argument; `sc.ps = <scalar lane>` folds to a plain pair
//     store in every C spelling.
// DEAD ENDS (measured, do not re-run): staging every result into a fresh named
//  local before storing (§6bu) — byte-identical, cc1 folds the temps back;
//  pinning d0/d1/v0/v1/m6 to their want FPRs (fr12/fr9/fr10/fr13/fr0) — all
//  exact no-ops (pin dropped); `volatile` on the eight matrix operands in chain 1
//  (43.9%, worse) or on the eight `unk7C[]` operands in chain 2 (38.2%, worse);
//  `volatile` reads of the two rodata f32 constants (45.1%, inert); moving
//  `p = &fr.obuf[0]` to the end of each case arm (27.4%); removing the
//  post-switch `p` and reading `fr.obuf[1]` directly (8.2%, 636B); routing the
//  chain-2 obuf[1] stores through a pointer (45.5%, 660B); a `default:` arm
//  replacing the post-switch `p` (byte-identical); declaring `v1` before `v0`
//  (inert); swapping the `m0`/`m1` source order in chain 1 (45.7%); renaming
//  the `lst`/`bst` broadcast to a distinct asm output instead of a tied
//  operand (byte-identical); pinning `p` to r11 (5.1%, 632B — cc1 reserves the
//  register and the frame collapses); pinning a copy of arg2 to r28 (5.4%).
//  FLAG SWEEP (12 combos, `-mps-float` always on): default 40.0%;
//  -fno-sched-interblock / -fno-sched-spec / -fno-thread-jumps / -O3 /
//  -fno-expensive-optimizations / -fno-strength-reduce all 40.0% (no-ops);
//  -fno-schedule-insns2 35.8%; -fno-rerun-cse-after-loop 29.9%;
//  -fno-schedule-insns 24.2%; -fno-gcse 7.9%; -Os 7.9%.  The inherited
//  `// extra_cflags: -mps-float` is REQUIRED (no flag = the whole body folds).
//
// MEASURED LEVERS from the previous session (still load-bearing, keep):
//  A. The dot-product test MUST be `len2.flt.hi > 0.0f` (element 0), not
//     `.flt.lo`.  cc1 turns a PS->SF extract of element 0 into `ps_mr` +
//     `fcmpu` — exactly want's 0x27E4/0x27E8 — and also inlines the if-body
//     (want's `ble` skips *over* it).  `.flt.lo` gives a whole-register `fmr`
//     + a 64-bit compare, a `psq_st` spill of the union and a `lwz/stw/stw`
//     GPR round-trip.  Comparing a `__ps_t` directly with a float ICEs cc1 at
//     optabs.c:3515; the `.flt.hi` union read is the only working spelling.
//  B. FR needs two extra 8-byte slots: `SN_PS_type sc` at +0x48 (the
//     {rsqrt,1.0f} pair) and `SN_PS_type bst` at +0x50 (the scale pair).
//     `fr.bst.flt.hi = scale;` + a pair read is what produces want's
//     `stfs 0x50(r1)` + `psq_l 80(r1)`; a plain `f32` + `__ps_t` temp gets
//     optimised to a bare register broadcast and loses both.
//  C. Frame/slot map is exact and confirmed by the closed form: stwu -0x70,
//     stmw r27,0x5c, stw r0,0x74, 5 saved GPRs => locals = 0x70-16-20 = 0x50,
//     which is exactly obuf[2]+t[2]+m[2]+m2[2]+sc+bst = 80 bytes at
//     r1+0x08..r1+0x57.  Do not touch it.
//  D. Case 0's obuf[1] store must go through a pointer (`q[1] = fr.m[1];`),
//     not `fr.obuf[1] = fr.m[1];`, or cc1 folds the two into one store.
//  E. Case 0's two scale multiplies must be `muls0(t[0])` then `muls0(t[1])`
//     in source.  The first chain's 4-store run needs the interleaved source
//     order [m2[1], m[0], m2[0], m[1]] (recipes 24/64/198); the second chain's
//     run is best left grouped.
//  F. Callee arities are audited and correct: fn_80007A4C 3-arg, fn_800079D8
//     2-arg, fn_80057FBC 1-arg — every one has a prototype, so there are zero
//     spurious `crclr cr1eq` in the object.  `fn_80057FBC((void *)arg1->unk7C)`
//     and the eight `arg1->unk7C[i]` reads are the only unk7C uses.
//  G. `*(f32 *)&psvar` / `*(SN_PS_type *)&psvar` ICE cc1 at expmed.c:1115; a
//     `volatile double _dummy` sweep is pointless (no FPR is saved and the
//     frame already matches).
//
// RESIDUAL (84 words; opcode sequence and every instruction offset agree,
// only registers differ):
//  (a) the `p` merge web: want homes it in r11 (a VOLATILE register — it is
//      born after the last call in every path: 0x277C/0x2794 default,
//      0x2820+0x2828 case 0, 0x2880 case 1, 0x288C+0x2948 case 2/4).  cc1
//      gives it r29 because it coalesces `p` with case 2/4's `q` (same value),
//      inheriting q's call-crossing range.  7 words.  Every source shape tried
//      (per-path `p = q`, `default:` arm, post-switch `p`, dropping the
//      post-switch `p`, routing the chain-2 obuf[1] stores through `q`) makes
//      GCC normalise to the same object; pinning `p` collapses the frame.
//  (b) case 0 head FPRs: d1 in f8 (want f9), d0 in f9 (want f12) — 6 words.
//      The `ps_rsqrte`/`ps_mr` pair is also colour-swapped: got rsq=f13/bcast=f0,
//      want rsq=f0/bcast=f13 (2 words) — the two roles are identical values.
//  (c) case 0 if-body: the `lfs 1.0f` is hoisted to 0x27FC, want has it at
//      0x2804, so the 0x27F0-0x2818 window slides (3 words).  Naming a `f32
//      one` local, and `volatile` on the constant, are both inert.
//  (d) case 0 tail: the `psq_l 80(r1)` (bst) and `psq_l 32(r1)` (t1) loads come
//      out in the opposite order, and `ps_mr f0,f0` is a self-copy where want
//      has `ps_mr f0,f13` (10 words).
//  (e) case 2/4 chain 1: the whole FPR map is permuted (t0 f4 vs f5, t1 f5 vs
//      f4, m1 f5 vs f6, m4 f6 vs f4, m5 f9 vs f12, m6 f0 vs f12, m7 f11 vs f9)
//      and the matrix-member loads come out pairwise swapped — cc1 orders the
//      eight independent `psq_l`s m18,m20,m28,m30,m38,m40,m48,m50 where want
//      emits them in source order m20,m18,m30,m28,m40,m38,m50,m48.  ~20 words.
//  (f) case 2/4 chain 2: all 24 words of 0x2944-0x29A0 differ in FPRs, and
//      the `unk7C` pointer register is r9 instead of r3 (see WHY PARKED).
//  (g) epilogue: `psq_l/psq_st f12` vs f13 (2 words).

#include "types.h"
#include "dolphin/SN_PS.h"
typedef struct Self {
    char pad00[8];
    __ps_t v08;
    __ps_t v10;
    __ps_t m18;
    __ps_t m20;
    __ps_t m28;
    __ps_t m30;
    __ps_t m38;
    __ps_t m40;
    __ps_t m48;
    __ps_t m50;
    char pad58[0x18];
    s32 unk70;
    f32 unk74;
    char pad78[4];
    __ps_t *unk7C;
    char pad80[4];
} Self;

typedef struct FR {
    __ps_t obuf[2];
    __ps_t t[2];
    __ps_t m[2];
    __ps_t m2[2];
    SN_PS_type sc;
    SN_PS_type bst;
} FR;

extern __ps_t lbl_802987BC;
extern f32 lbl_8029881C;
extern f32 lbl_80298820;

void fn_80007A4C(void *a, void *b, void *c);
void fn_800079D8(void *a, void *b);
void fn_80057FBC(void *p);

void *fn_800B2748(void *arg0, Self *arg1, __ps_t *arg2) {
    FR fr;
    __ps_t *p;

    switch (arg1->unk70) {
    case 0: {
        __ps_t d1;
        __ps_t d0;
        __ps_t sq;
        __ps_t bcast;
        __ps_t bpair;
        __ps_t inv;
        SN_PS_type len2;
        register __ps_t *base __asm__("r10");
        __ps_t *q;

        base = &arg1->v08;
        d1 = __builtin_ps_sub(arg2[1], base[1]);
        d0 = __builtin_ps_sub(arg2[0], arg1->v08);
        fr.t[1] = d1;
        fr.t[0] = d0;
        sq = __builtin_ps_mul(d1, d1);
        sq = __builtin_ps_merge00(sq, lbl_802987BC);
        len2.ps = __builtin_ps_madd(d0, d0, sq);
        len2.ps = __builtin_ps_sum0(len2.ps, len2.ps, len2.ps);
        if (len2.flt.hi > lbl_8029881C) {
            inv = __builtin_ps_rsqrte(len2.ps);
            __asm__("ps_mr %0,%1" : "=f"(bcast) : "f"(inv));
            fr.sc.ps = bcast;
            fr.t[0] = __builtin_ps_muls0(d0, inv);
            fr.sc.flt.lo = lbl_80298820;
            fr.t[1] = __builtin_ps_mul(d1, fr.sc.ps);
        }
        fr.bst.flt.hi = arg1->unk74;
        bpair = fr.bst.ps;
        __asm__("ps_mr %0,%1" : "=f"(bpair) : "0"(bpair));
        fr.t[0] = __builtin_ps_muls0(fr.t[0], bpair);
        fr.t[1] = __builtin_ps_muls0(fr.t[1], bpair);
        fr.obuf[0] = __builtin_ps_add(arg1->v08, fr.t[0]);
        fr.m[0] = fr.obuf[0];
        fr.m[1] = __builtin_ps_add(base[1], fr.t[1]);
        q = &fr.obuf[0];
        q[1] = fr.m[1];
        p = q;
        break;
    }
    case 1:
        fn_80007A4C(&arg1->pad80[0], (void *)arg2, (void *)&fr.obuf[0]);
        p = &fr.obuf[0];
        break;
    case 2:
    case 4: {
        __ps_t v0;
        __ps_t v1;
        __ps_t m0;
        __ps_t m1;
        __ps_t m2;
        __ps_t m3;
        __ps_t m4;
        __ps_t m5;
        __ps_t m6;
        __ps_t m7;
        __ps_t n0;
        __ps_t n1;
        __ps_t n2;
        __ps_t n3;
        __ps_t n4;
        __ps_t n5;
        __ps_t n6;
        __ps_t n7;

        p = &fr.obuf[0];
        fn_800079D8((void *)&fr.t[0], (void *)&arg1->pad80[0]);
        v0 = __builtin_ps_sub(arg2[0], fr.t[0]);
        v1 = __builtin_ps_sub(arg2[1], fr.t[1]);
        m0 = __builtin_ps_muls0(arg1->m20, v0);
        m1 = __builtin_ps_muls0(arg1->m18, v0);
        m2 = __builtin_ps_madds1(arg1->m30, v0, m0);
        m3 = __builtin_ps_madds1(arg1->m28, v0, m1);
        m4 = __builtin_ps_madds0(arg1->m40, v1, m2);
        m5 = __builtin_ps_madds0(arg1->m38, v1, m3);
        m6 = __builtin_ps_madds1(arg1->m50, v1, m4);
        m7 = __builtin_ps_madds1(arg1->m48, v1, m5);
        fr.m2[1] = m6;
        fr.m[0] = __builtin_ps_add(m7, fr.t[0]);
        fr.m2[0] = m7;
        fr.m[1] = __builtin_ps_add(m6, fr.t[1]);
        fn_80007A4C((void *)&arg1->pad80[0], (void *)&fr.m[0], (void *)&fr.obuf[0]);
        fr.obuf[0] = __builtin_ps_sub(fr.obuf[0], fr.t[0]);
        fr.obuf[1] = __builtin_ps_sub(fr.obuf[1], fr.t[1]);
        fn_80057FBC((void *)arg1->unk7C);
        n0 = __builtin_ps_muls0(arg1->unk7C[0], fr.obuf[0]);
        n1 = __builtin_ps_muls0(arg1->unk7C[1], fr.obuf[0]);
        n2 = __builtin_ps_madds1(arg1->unk7C[3], fr.obuf[0], n1);
        n3 = __builtin_ps_madds1(arg1->unk7C[2], fr.obuf[0], n0);
        n4 = __builtin_ps_madds0(arg1->unk7C[4], fr.obuf[1], n3);
        n5 = __builtin_ps_madds0(arg1->unk7C[5], fr.obuf[1], n2);
        n6 = __builtin_ps_madds1(arg1->unk7C[6], fr.obuf[1], n4);
        n7 = __builtin_ps_madds1(arg1->unk7C[7], fr.obuf[1], n5);
        fr.m2[0] = n6;
        fr.m2[1] = n7;
        fr.obuf[0] = __builtin_ps_add(n6, fr.t[0]);
        fr.obuf[1] = __builtin_ps_add(n7, fr.t[1]);
        break;
    }
    }
    p = &fr.obuf[0];
    ((__ps_t *)arg0)[0] = fr.obuf[0];
    ((__ps_t *)arg0)[1] = p[1];
    return arg0;
}
