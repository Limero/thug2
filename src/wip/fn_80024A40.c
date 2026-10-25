// PARKED 2026-09-26 — PS POSE-BUILD, single f11/f12 register-role tie-break.
// 27/33 words (81.8%), SIZE-EXACT 132B. Up from 9/33 (27.3%)/128B: the
// `ps_mr` copy and the whole load/mul/store SCHEDULE are now reproduced in
// pure C. The only residual is which of the two overlapping PS webs gets
// f11 vs f12 (see PARK REASON).
//
// family=m2c range=0x80024A40-0x80024AC4 size=132B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// VERIFY (the sweep does NOT auto-detect PS drafts — §6v-107, pass the flag):
//   tools/venv/bin/python tools/ps_diff.py 0x80024A40 132 "-mps-float"
//   tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80024A40 \
//       --extra-cflags "-mps-float"
//
// DECODED SEMANTICS (all 5 op-4 words resolved via ps_diff.dec):
//   s  = arg0->unk0x28 (f32)                       ; scale, broadcast to lane 0
//   a  = arg0->unk0x18, b = arg0->unk0x20          ; __ps_t pairs
//   d0 = arg1[0], d1 = arg1[1]                     ; __ps_t pairs
//   ps_mr f10,f0 ; ps_muls0 f13,f13,f10 ; ps_muls0 f11,f11,f10
//   blk[2] = a * s ; blk[3] = b * s
//   ps_sub f0,f0,f13 ; ps_sub f12,f12,f11
//   blk[0] = d0 - blk[2] ; blk[1] = d1 - blk[3]
//   fn_8002464C(arg0->unk0xC, blk)   ; blk[] is __ps_t[4] at r1+8
//   fn_800550B4(arg0->unk0x10, arg0->unk0xC)
// Frame 0x38 = 8 hdr + 0x28 locals: blk[4] at 0x08..0x28, the 8-byte scale
// pair at 0x28, stmw r30 at 0x30, LR at 0x3c. (s32 unk0x10 / s32 unk0x14:
// unk0x10 is loaded into r3 for the fn_800550B4 call; unk0x14 is padding.)
//
// SOLVED THIS ROUND (was the whole park reason before):
//   1. The missing `ps_mr f10,f0`. A plain `__ps_t` copy is always coalesced
//      away by cc1 (probed: plain assign / self-assign / ternary / comma /
//      union / array / struct-field / address-taken / `volatile __ps_t` /
//      old-style `__ps_t`-in / out-of-line static identity helper — ALL
//      compile with NO ps_mr, because `__ps_t` is a plain mode(PS) rvalue).
//      A whole-`SN_PS_type` (SNAPS builtin, also used by 33 promoted src/
//      files) copy is what emits it: a *partial* field write followed by a
//      `.ps` read keeps the pair in a register and materialises the copy.
//          SN_PS_type sc;  sc.flt.hi = arg0->unk0x28;   -> lfs/stfs/psq_l
//          ...muls0(a, sc.ps); ...muls0(b, sc.ps);      -> ps_mr fY,fX
//      `.flt.hi` is the byte-offset-0 field (= PS lane 0, the one `muls0`
//      consumes); `.flt.lo` is +4 and would put the stfs at 0x2c (1 word off).
//   2. The whole intra-block SCHEDULE. Want emits
//      sc-pair, a, b, ps_mr, d1, a*s, d0, b*s, st blk[2], sub e0, st blk[3],
//      sub e1, st blk[0], st blk[1] — i.e. source order
//      sc,a,b,d0,d1,ta,tb, blk[2],blk[3], e0,e1, blk[0],blk[1] reproduces it
//      verbatim once the copy exists (the pre-copy drafts scheduled 132B
//      streams differently, which is why the old body looked like a
//      scheduling wall). 24 permutations of the 5 value-loads x both muls
//      orders were measured; this one is the unique 132B+sound-schedule peak.
//
// PARK REASON (single residual, 6 words = 2 webs x 3 insns):
//   `b` (=arg0->unk0x20) and `d1` (=arg1[1]) OVERLAP (live ranges 0x2c..0x50
//   and 0x34..0x5c), so they must take different caller-saved FPRs. Want:
//   b->f11, d1->f12. We get b->f12, d1->f11. Every opcode, every displacement,
//   the whole 33-word stream and the size are otherwise identical.
//   This is a pure global-alloc tie-break, NOT a scheduling or type issue:
//    - `__ps_t` REGISTER PINS do not work in this cc1 at all (probed:
//      `register __ps_t y __asm__("fr10")` is SILENTLY IGNORED, the value lands
//      in f13; the AGENTS.md §6am-189 `psf`-typed pin does not apply because
//      `psf`/`sn_ps` are not types this cc1 knows — only `__ps_t` and
//      `SN_PS_type` are).
//    - 24 declaration permutations of {a,b,d0,d1}: no effect (allocation
//      follows RTL birth order, not declaration order).
//    - all 6 relative orders of the b/d0/d1 loads, both muls orders, both
//      sub/store tails: capped at 27, the 27 form is the only sound one.
//    - web-shape variants (implicit copy / explicit `sd = sc` / `__ps_t sb =
//      sc.ps` / both / struct-pun a,b / sub-reading-memory): all 27, same diff.
//    - flags: -fno-gcse/-fno-sched-spec/-fno-expensive-optimizations/
//      -fno-cse-follow-jumps/-fno-thread-jumps/-fno-inline/
//      -fno-keep-inline-functions/-fno-strength-reduce = 27 (no change);
//      -fno-schedule-insns2 = 22, -fno-expensive-optimizations = 20,
//      -fno-schedule-insns = 6 (all regress). -fno-ree/-fno-crossjumping/
//      -fno-cmv/-fno-tree-pre do not exist in this cc1.
//   Do NOT re-grind the copy or the schedule — both are exact. The only
//   untried lever left is an explicit `ps_mr` asm wedge, which this round's
//   scope excludes (and which the promoted PS siblings fn_801CCF08 /
//   fn_801B19DC do use for exactly this idiom).
//
// m2c-decode baseline for reference: the original stub body read the whole
// block as `0;` statements (one per op-4 word) and called fn_8002464C with
// 3 args.
#include "types.h"
typedef struct {
    char pad0[0xC];
    void *unk0xC;
    s32 unk0x10;
    s32 unk0x14;
    __ps_t unk0x18;
    __ps_t unk0x20;
    f32 unk0x28;
} Obj24A40;
void fn_8002464C(__ps_t *, __ps_t *);
void fn_800550B4(s32, s32);
void fn_80024A40(Obj24A40 *arg0, __ps_t *arg1) {
    __ps_t blk[4];
    SN_PS_type sc;
    __ps_t a, b, d0, d1, ta, tb, e0, e1;
    sc.flt.hi = arg0->unk0x28;
    a = arg0->unk0x18;
    b = arg0->unk0x20;
    d0 = arg1[0];
    d1 = arg1[1];
    ta = __builtin_ps_muls0(a, sc.ps);
    tb = __builtin_ps_muls0(b, sc.ps);
    blk[2] = ta;
    blk[3] = tb;
    e0 = __builtin_ps_sub(d0, ta);
    e1 = __builtin_ps_sub(d1, tb);
    blk[0] = e0;
    blk[1] = e1;
    fn_8002464C((__ps_t *)arg0->unk0xC, blk);
    fn_800550B4(arg0->unk0x10, arg0->unk0xC);
}
