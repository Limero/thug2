// PARKED 2026-09-30: 86.0% -> 97.7% NEAR
// PROBE 2026-10-07: the last 2 words are `lfs f11,<const>` + `fadds f1,f1,f11`
//   where we get f13.  NEW EVIDENCE: the constant's register TRACKS the ps_mr pin set —
//   sweeping the block-1 `t`/`m` pins gives const = the higher of the two registers for
//   regs in {11,12,13} (t=11,m=13 -> f13; t=11,m=12 -> f12; t=12,m=11 -> f12;
//   t=12,m=13 -> f13), and with `m` unpinned it falls to f0.  want needs f11, i.e. BOTH
//   f12 and f13 occupied at +0x74, which cannot be arranged without emitting extra code.
//   The naive `register f32 kc __asm__("fr11")` still miscompiles (the lis/lfs pair is
//   folded away, cc1 emits `fadds f11,f1,f11`, 336B = 31.4%) because fr11 is already a
//   DFmode __ps_t pin, so the same-mode dual-pin precondition (recipes section 6hj) fails.
//   Also measured: removing the block-1 z pin costs 2 words (95.35%) and does NOT move
//   the constant; a named/union/volatile temp for the constant reschedules >=8B and drops
//   to 5.7-25%.  Parked.
// family=m2c range=0x800BE410-0x800BE568 size=344B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// SKATE script command "ApplyRandomAdjustment" (QB_APPLYRANDOMADJUSTMENT
// 0x8ACE8A0F) on the skater script-motion object: copy the "rigid body"
// node's Pos-pair into the object's QB_VEL pairs (0x128/0x130), copy them
// out to *(obj+0xC) at 0xB8/+0xC0, clamp the 0x12C magnitude lane, then
// the same copy-in/scale for the 0x148/0x150 pair, and finally
// fn_800BA64C(obj) (recompute the derived motion from the node).
//
// Body is paired-single: two copies of the idiom
//     psq_l f11,sp ; ps_mr f13,f11 ; ps_muls0 fD,fD,f13 ; ps_muls0 fD2,fD2,f13
// (scale a __ps_t pair by a random scalar) with the psq load/store pairs
// going through the member slots directly (Unk_B950D1C2 has __ps_t at
// 0x128/0x130/0x148/0x150, proven by the promoted siblings
// src/fn_800BDF64.c / src/fn_800BDE4C.c).
//
// The two stack scalars are fr[0]/fr[1] of a `__ps_t fr[2]` local (NOT two
// separate f32s): that is what reproduces the retail frame exactly —
// stwu -0x28 / stmw r29,0x1c / lrsave 0x2c, with the stores landing at
// 8(r1) and 0x10(r1). Two `volatile f32` scalars give 8(r1)/0xc(r1) and a
// 0x20 frame (verified).
//
// ROUND r3 RESULT: 86.0% (74/86) -> 97.7% (84/86), object .text 344B ==
// symbols.txt size:0x158 == the range marker, no .rodata/.data section.
// Two semantic/codegen fixes, ZERO new emitted instructions:
//
//  1. SECOND-BLOCK LANE ORDER (86.0% -> 90.7%, +4 words).  The m2c body
//     loaded the 0x150 lane first and then assigned 0x148 first, which
//     compiled to `psq_l f0,336` / `psq_l f13,328` — the two lanes
//     transposed vs retail's `f0<-0x148` / `f13<-0x150`.  Fix: read the
//     lanes in ASCENDING offset order (p0 = 0x148, p1 = 0x150) but STORE
//     them in the opposite order (0x150 first, then 0x148).  That is the
//     documented per-store-class rotate (recipes 24/64/159/206): ngccc
//     emits the class's LAST source statement first, and here the first
//     block (which matches with 0x128-then-0x130 source order) shows the
//     plain reversed store run while this block wants source order
//     [0x150, 0x148].  Two identical-shape psq loads/stores swapping
//     lanes is a field-ASSIGNMENT bug, not a permutation problem
//     (AGENTS §6bh), so no search was needed.
//
//  2. "SECOND LANE" FPR COLOUR (90.7% -> 97.7%, +6 words).  Retail uses
//     f11 as the register for the *second* 8-byte lane of each of the
//     three copy pairs (0xC0<-rigid, 0xC0->sub, 0x150<-rb); cc1 reuses
//     f0 because the first lane's f0 is already dead.  A bare
//     `register __ps_t z __asm__("fr11")` around a copy is SILENTLY
//     DROPPED (the store coalesces into the load, so there is no pseudo
//     to bind — §6az-245/§6cw).  It binds only when the web is kept
//     alive by a zero-code `__asm__("" : "+f"(z))` barrier
//     (AGENTS §6aj-3/§6am-155); with the barrier the copy lands in f11
//     and the object's length is unchanged (344B, 0 extra insns).
//
// RESIDUAL (2 of 86 words, both the SAME fact):
//   want  0x74: lfs f11,-0x7174(r9)   got  lfs f13,0(r9)
//   want  0x7C: fadds f1,f1,f11       got  fadds f1,f1,f13
// i.e. the `lbl_80298E8C` scalar constant inside
// `Mth_PlusOrMinus(lbl_80298E88) + lbl_80298E8C` wants f11 — the register
// retail shares with the four __ps_t webs that now DO match — while cc1
// hands it f13 (the `m` pin's register, free at that point).  It is a pure
// register-preference choice: the two instructions are otherwise
// identical and the ADDR16 relocation is masked.  Every route tried and
// its measured score (on the 97.7% body):
//   -fno-sched-spec / -fno-sched-interblock / -fno-gcse /
//   -fno-thread-jumps / -fno-expensive-optimizations /
//   -fno-rerun-cse-after-loop / -O3 / -fconserve-space  ... all 97.7% (no-op)
//   -fno-schedule-insns2 90.7%   -fno-schedule-insns 73.3%   -Os 21.8%
//   block-1 `m` pin swept fr0/fr1/fr2/fr3/fr8/fr9/fr10/fr11/fr12/fr14:
//     73-78/86, and the constant's register moved f13/f12/f0 but NEVER f11
//   block-2 `m` pin swept fr0/fr8/fr9/fr10/fr11/fr13 : 71-78/86
//   block-1 `t` pin swept fr8/fr9/fr10 : 95.3%   fr12 : 91.9%
//   `register f32 kc __asm__("fr11")` on the constant: 31.4% AND 336B —
//     cc1 2.95 miscompiles it (the `lis`/`lfs` pair disappears and it
//     emits `fadds f11,f1,f11`); the same pin with a `"+f"` barrier also
//     31.4%/336B, with an input-only `"f"` barrier 84.9%
//   const-qualified `extern const f32 lbl_80298E8C` : 97.7% (no-op)
//   named `f32` temp for the sum (3 spellings) : 97.7% (no-op, +8B frame
//     for one of them) — 0x74/0x7c unchanged
//   commuted operands / extra `__asm__ volatile("":::"memory")` : 89.5%
//   one shared fr11 variable for all three z-webs instead of three : 97.7%
//   volatile-store instead of the `"+f"` barrier on the z-webs : 96.5%
// Diagnosis for a future attempt: cc1 treats fr11 as globally reserved
// (allocate_registry_registers runs before local_alloc), so once the
// three second-lane webs and the two `t` webs are pinned there is no way
// to hand the SAME register to a plain `f32` pseudo; the only untried
// route is a 1-instruction asm `lfs` with a hard-pinned f11 output fed
// by the existing page anchor (needs a `"s"` extern char[] decl, cf.
// §6ds2/§6br), which is fragile for the ADDR16 and was not attempted.
//
// DISCLOSED COMPILER TRICKS (all pre-existing, none added this round):
//  * one declaration-level hard-register pin, `register s32 a1c
//    __asm__("r30")`, holding a copy of arg1 (retail homes arg1 in r30 and
//    the fn_800A398C result in r29; without the pin cc1 swaps them, -4
//    words).  Also verified load-bearing: dropping BOTH __ps_t pin sets
//    drops the body to 74.4%.
//  * `register __ps_t t __asm__("fr11")` / `m __asm__("fr13")` in block 1
//    and `t __asm__("fr11")` / `m __asm__("fr12")` in block 2.
//  * 2 EMITTED inline instructions total: the two
//    `__asm__ volatile("ps_mr %0,%1" : "=f"(m) : "f"(t))` templates (the
//    ps_mr at want+0x88 and want+0x124; 2/86 = 2.3% of the function, far
//    under the 30% ceiling, cf. §4g/§6af-180).  The other four __asm__
//    sites (three `"+f"` barriers, one `"memory"` fence) and every
//    `register ... __asm__("rN")` are ZERO-instruction.
//
// 2026-10-07 (worker pass 18/34): both open items were
// re-attempted against the packet and are now closed as WALLS, not residuals.
// No body change was kept below: the body printed here IS the best-known match.
//
//  A) "REMOVE THE TWO EMITTED `ps_mr` TEMPLATES" -> IMPOSSIBLE IN THIS COMPILER.
// The first attempt already measured the plain-C spelling (`m = t;` with a `"+f"`
//     barrier on the SOURCE `t`) at 36.05%: copy-propagation deletes the move,
//     the object loses both words (342B), and the index-aligned score collapses
//     in the usual size-mismatch cascade.  ngccc 2.95 emits `ps_mr` ONLY from
//     the explicit template — a plain DFmode move between two FPRs is an `fmr`
//     (different encoding), and the `z`-web idiom emits no copy at all (it only
//     forces the psq load/store to USE the pinned register).  So the templates
//     are the sole possible source of want+0x88 / want+0x124: deleting them can
//     never reach 86/86, and re-expressing them as `fmr` caps the score at
//     85/86 = 98.8% at best.  If a future agent wants the asm-free, 1-word-off
//     body, the untried spelling is a DESTINATION-only barrier: pin `m`, write
//     `m = t;` then `__asm__("" : "+f"(m));`, and drop the `=f` template — it
//     cannot emit `ps_mr`, but it may still emit the `fmr` copy instead of
//     deleting it.
//
//  B) THE 2-WORD RESIDUAL (const wants f11; we get f13) -> REGISTER-REGISTRY
//     WALL.  `allocate_registry_registers` runs before local_alloc and reserves
//     fr11 globally for the five pinned `__ps_t` webs, so no plain `f32` pseudo
//     can ever be coloured f11.  That is precisely why every `m`/`t` pin sweep
//     moved the constant through f0/f12/f13 but never f11, and why pinning the
//     constant itself (`f32` or with a `"+f"` barrier) makes cc1 miscompile the
//     `lis`/`lfs` pair.  The two instructions are otherwise byte-identical
//     (ADDR16 masked), so this is a colour tie-break the source cannot reach.
//     The header's noted last resort (a 1-instruction asm `lfs` with a pinned
//     f11 output) was NOT attempted: it is inline asm and the user explicitly
//     excludes it.
//
// PARKED 2026-10-07: keep this 97.67% / 344B body. Its two
// missing words are (B) a reserved-register colour tie-break no source spelling
// reaches, and the cost of the two templates that (A) no C spelling can remove.
// Do NOT restore the historical 100% whole-body-inline-asm body (AGENTS.md
// bans whole-body transcription regardless of the verdict).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 fn_80127358(CStruct *, Unk_C7387A53 *);
s32 fn_800A398C(s32, s32);
s32 ContainsFlag(CStruct *, s32);
f32 Mth_PlusOrMinus(f32);
void *GetChecksum_3(Unk_6A70655D *, s32);
void fn_800BA64C(void *);

extern s32 lbl_80301A38;
extern f32 lbl_80298E88;
extern f32 lbl_80298E8C;

s32 fn_800BE410(Unk_B950D1C2 *arg0, s32 arg1) {
    __ps_t fr[2];
    __ps_t t;
    __ps_t m;
    s32 *rigid;
    s32 *sub;
    s32 flag;
    register s32 a1c __asm__("r30");

    a1c = arg1;
    {
        s32 rigid_off = *(s32 *)((char *)fn_80127358(a1c, 0) + 8);
        rigid = (s32 *)fn_800A398C(lbl_80301A38, rigid_off);
    }
    flag = ContainsFlag(a1c, QB_APPLYRANDOMADJUSTMENT);
    arg0->unk0x128 = ((__ps_t *)rigid)[23];
    { register __ps_t z __asm__("fr11");
      z = ((__ps_t *)rigid)[24];
      __asm__("" : "+f"(z));
      arg0->unk0x130 = z; }
    if (flag) {
        *(f32 *)&fr[0] = Mth_PlusOrMinus(lbl_80298E88) + lbl_80298E8C;
        {
            register __ps_t t __asm__("fr11");
            register __ps_t m __asm__("fr13");
            t = *(__ps_t *)&fr[0];
            __asm__("ps_mr %0,%1" : "=f"(m) : "f"(t));
            arg0->unk0x128 = __builtin_ps_muls0(arg0->unk0x128, m);
            arg0->unk0x130 = __builtin_ps_muls0(arg0->unk0x130, m);
        }
    }
    sub = (s32 *)arg0->unk0xC;
    __asm__ volatile("" ::: "memory");
    ((__ps_t *)sub)[23] = arg0->unk0x128;
    { register __ps_t z __asm__("fr11");
      z = arg0->unk0x130;
      __asm__("" : "+f"(z));
      ((__ps_t *)sub)[24] = z; }
    if (*(s32 *)((char *)arg0 + 0x114) == 0) {
        if (fabsf(*(f32 *)((char *)arg0 + 0x12C)) < lbl_80298E8C) {
            *(f32 *)((char *)arg0 + 0x12C) = lbl_80298E8C;
        }
    }
    {
        s32 *rb = (s32 *)GetChecksum_3((Unk_6A70655D *)rigid, QB_RIGIDBODY);
        if (rb != 0) {
            arg0->unk0x148 = ((__ps_t *)rb)[41];
            { register __ps_t z __asm__("fr11");
              z = ((__ps_t *)rb)[42];
              __asm__("" : "+f"(z));
              arg0->unk0x150 = z; }
            if (flag) {
                *(f32 *)&fr[1] = Mth_PlusOrMinus(lbl_80298E88);
                {
                    register __ps_t t __asm__("fr11");
                    register __ps_t m __asm__("fr12");
                    __ps_t p0, p1;
                    t = *(__ps_t *)&fr[1];
                    __asm__ volatile("" ::: "memory");
                    p0 = arg0->unk0x148;
                    p1 = arg0->unk0x150;
                    __asm__ volatile("ps_mr %0,%1" : "=f"(m) : "f"(t));
                    arg0->unk0x150 = __builtin_ps_muls0(p1, m);
                    arg0->unk0x148 = __builtin_ps_muls0(p0, m);
                }
            }
        }
    }
    fn_800BA64C(arg0);
    return 1;
}
