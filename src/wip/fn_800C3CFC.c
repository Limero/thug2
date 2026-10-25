// PARKED 2026-10-17: NEAR 66.3% masked, size-exact 332B (was 328B). The NEXT IDEA
// (sp[6] via named temp m6 AND inline sp[6] in the second muls0) FIXED THE SIZE:
// reload now keeps two regs (ps_diff shows the block; test_wip reports 332B).
// Residual is FPR colour + pair-load order in the tail block (ps_mr/ps_muls0/
// ps_add/psq sequence and f10/f11/f12/f13 assignment differ; load order
// [sp5,o20,o28,sp6] vs want [sp6,o20,o28,sp5] invariant to source order).
// PARKED 2026-10-03: NEAR 66.3% masked (baseline was NEAR 62.7%).
//   LEAF_TMPDIR=<private dir> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800C3CFC
// Object is 328B = exactly 1 word SHORT of the 0x14C (332B) split, so the whole
// 0x800C3DE8..0x800C3E30 PS block is shifted and want_got.py reports the
// index-aligned pct as "meaningless until the length matches". 27 real word
// diffs remain, all in the tail block, in exactly three groups:
//
//  (1) SIZE DEFICIT: want has one extra instruction, a pair copy into f11 at
//      0x800C3E08. It is a pure copy of the pair loaded from sp[6] at 56(r1).
//      want keeps sp[6] in f0 and then must copy it to f11 because f0 is then
//      reused for the sp[4] load at 40(r1) feeding the second scaled multiply;
//      in every object I can make, cc1 instead gives sp[6] a *fresh* reg
//      (f10) and recycles f0 for sp[4], so no conflict and no regmove.
//
//  (2) FPR COLOURING (direct consequence of (1)). want: sp[6]->f0, copy->f11,
//      o20->f10, o28->f12, sp[5]->f13.  got: sp[5]->f12, o20->f11,
//      o28->f13, sp[6]->f10, sp[4]->f0.  Same web set, different draw order.
//      The knob that decides "fresh f10 vs recycled f0" for sp[6] was never
//      identified; that is the whole ballgame.
//
//  (3) ORDER OF THE FOUR PAIR LOADS. want emits them in the order
//      [sp[6], o20, o28, sp[5]]; got emits [sp[5], o20, o28, sp[6]] — the
//      first and last are swapped (addresses/registers otherwise correspond).
//
//  RULED OUT (each measured with the repro command above):
//   - `volatile __ps_t sp[7]` for the out-struct: 62.7% (WORSE by 4 words).
//     Plain `__ps_t sp[7]` + `volatile f32 *` punned scalar stores = 66.3%.
//     (This also supersedes the old "68.3% non-volatile" note below: that was
//     a different body; every body here is 328B.)
//   - Dropping the `register f32 kA8 __asm__("fr13")` pin: 62.7%. The pin IS
//     load-bearing — keep it.
//   - Reordering the four pair reads in the source (3 orders tried: obj-first,
//     sp5-first, sp6-first). The emitted load order is INVARIANT: cc1 always
//     hoists the sp[5] read to the front of the block and sinks the sp[6] read
//     behind both obj pair loads, no matter where they sit in the source.
//     So (3) is not reachable by statement order.
//   - Reading `sp[6]` inline twice (relying on CSE to fold the two reads into
//     one load + one regmove): no `ps_mr` is emitted, still 328B, same 66.3%.
//   - `-mps-float` is MANDATORY, not optional: without it ngccc ICEs at
//     expr.c:2802 on this body. With it, the scalar fmuls/fdivs/fsubs in the
//     first half still come out as scalar ops, so it does not corrupt that part.
//
//  MOST PROMISING NEXT IDEA: attack (1)/(2) by making sp[6]'s value need to
//  live in two registers at once in a way reload cannot coalesce — e.g. keep
//  sp[6] in a named temp AND also pass `sp[6]` inline to the *second* muls0,
//  so reload sees two operands it must satisfy in different regs while the
//  psq_l is still emitted once. (The reverse of what was tried: there, the
//  inline reads CSE'd into a single pseudo and the regmove never appeared.)
//
//  All earlier findings below are still valid; only the verdict/size numbers in
//  the old header were stale and have been corrected above.
//
// WIP DRAFT (non-matching) — hand-rebuilt from want (m2c could not read any
// paired-single; the whole tail block was re-derived from the raw words).
// family=m2c range=0x800C3CFC-0x800C3E48 size=332B
// The first half (0x800C3CFC..0x800C3DB8, 41 insns) is byte-identical.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ------------------------------------------------------------------ DECODING
// fn_8003EF4C (the callee) is a 4-byte `blr` stub (symbols.txt size:0x4), so
// the 56-byte out-struct it receives is dead computation — but the game
// really computes it, and we must reproduce the instruction stream.
//
// out-struct = r1+0x08, 0x38 bytes, so the local is `__ps_t sp[7]` and the
// callee gets `sp` itself. Slot map (sp index -> r1 offset):
//   sp[0]=0x08  sp[1]=0x10  sp[2]=0x18  sp[3]=0x20  sp[4]=0x28  sp[5]=0x30
//   sp[6]=0x38 (+0x3C is never written — want really reads it uninitialised,
//              which is why the 5 lane stores are scalar `stfs` and only the
//              three TAIL slots are read back as 64-bit pairs).
// Constants (lbl_8029909C..B0 = .rodata2 f32): 0.3, 386.4, -386.4, 0.0, 1.0,
// 0.05, i.e. A8=0.0, AC=1.0, B0=0.05, A4=-386.4. Dataflow of the tail:
//   t   = lbl_802990A4 / arg0->unk0x170
//   sp[4] = {0.0, t};  sp[5] = {0.0, 1.0};  sp[6] = {0.05, <uninit>}
//   a = muls0(sp[5], sp[6]);   b = muls0(sp[4], sp[6])
//   sp[1] = obj[0x28] + a;     sp[0] = obj[0x20] + b
//   sp[2] = b;                 sp[3] = a
// PS A-form decode (MSB-first, per tools/ps_disasm.py convention):
//   ps_add  -> VD=d VA=a VB=b XO=21  (2nd operand in VB)
//   ps_muls0-> VD=d VA=a VC=b XO=12  (2nd operand in VC)
//   ps_mr   -> X-form XO10=72
// so `__builtin_ps_add(x,y)` / `__builtin_ps_muls0(x,y)` order the operands
// as the raw words show (src/wip/fn_80035A98.c header has the same probe).
// The 0x4330-style `0x323200FF` args are QB_UNKNOWN placeholders in
// qb_constants.h (byte-neutral either way).
//
// ------------------------------------------------------------------ FIXES vs
// the previous m2c draft (it did not even reach a size-correct object):
//  1. Tmr_GetTime is `(void)` — its prologue overwrites r3 and never reads
//     entry r3, so `Tmr_GetTime()` (bare bl) is the only form that leaves r3
//     untouched for the `add r0,r0,r3`; the old `Tmr_GetTime(arg0)` forced a
//     spurious arg move. (src/wip/fn_800B6404.c uses the same signature.)
//  2. `extern s32 lbl_80303150;` (scalar) not `char[]` — the scalar decl is
//     what folds @l into the load displacement (`lis r9; lwz 0x3150(r9)`).
//  3. Real callee is fn_8003EF4C (5 args from the call site), not fn_800A02A4.
//  4. The obj pair loads are at obj+0x20 AND obj+0x28 (two psq_l), not one.
//  5. The muls0 results must live in NAMED __ps_t temps — want keeps `a` in
//     f13 across its `ps_add` and the `psq_st`.
//  6. The 9 dead `0;` statements m2c left are the psq pair traffic; rebuilt
//     as real `__ps_t` / `__builtin_ps_*` code (needs -mps-float).
//
// ------------------------------------------------------------------ FLAGS
// Every scheduler flag tried is a no-op or much worse:
//   -fno-sched-spec / -fno-gcse / -fno-expensive-optimizations /
//   -fno-sched-interblock / -fno-thread-jumps / -O3 / -fno-regmove /
//   -fno-defer-pop  => all identical objects;
//   -fno-schedule-insns 23.4% (308B), -fno-schedule-insns2 53.7%.
// `-mps-float` itself is required (see RULED OUT above).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029909C;
extern f32 lbl_802990A0;
extern f32 lbl_802990A4;
extern f32 lbl_802990A8;
extern f32 lbl_802990AC;
extern f32 lbl_802990B0;
extern s32 lbl_80303150;
s32 Tmr_GetTime(void);
void fn_8003EF4C(void *, void *, s32, s32, s32);
void fn_800C3CFC(Unk_6423C969 *arg0) {
    __ps_t sp[7];
    s32 temp_r30;

    if ((arg0->unk0x12C != 0) && (temp_r30 = arg0->unk0x130,
        (u32)(*(s32 *)&lbl_80303150 + Tmr_GetTime()) - (u32)temp_r30 > 0x12CU)) {
        arg0->unk0x13C = arg0->unk0x13C - ((arg0->unk0x132C * lbl_8029909C * lbl_802990A0) / arg0->unk0x170);
    } else {
        arg0->unk0x13C = arg0->unk0x13C - ((arg0->unk0x132C * lbl_802990A0) / arg0->unk0x170);
    }
    if (arg0->unk0x1350 != 0) {
        __ps_t o20, o28, s5, m6, a, b;
        register f32 kA8 __asm__("fr13");
        kA8 = lbl_802990A8;
        ((volatile f32 *)sp)[8] = kA8;
        ((volatile f32 *)sp)[11] = lbl_802990AC;
        ((volatile f32 *)sp)[10] = kA8;
        ((volatile f32 *)sp)[12] = lbl_802990B0;
        m6 = sp[6];
        o20 = *(__ps_t *)((char *)arg0 + 0x20);
        o28 = *(__ps_t *)((char *)arg0 + 0x28);
        s5 = sp[5];
        a = __builtin_ps_muls0(s5, m6);
        ((volatile f32 *)sp)[9] = lbl_802990A4 / arg0->unk0x170;
        b = __builtin_ps_muls0(sp[4], sp[6]);
        sp[3] = a;
        sp[1] = __builtin_ps_add(o28, a);
        sp[2] = b;
        sp[0] = __builtin_ps_add(o20, b);
        fn_8003EF4C((char *)arg0 + 0x20, sp, QB_UNKNOWN_0x323200FF, QB_UNKNOWN_0x323200FF, 1);
    }
}
