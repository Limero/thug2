// WIP DRAFT — fn_801204CC (0x801204CC, 172B / 0xAC)
// ProDG/ngccc game code, scalar float only (NO paired-single words in want;
// tools/ps_disasm.py shows 43 plain instructions, no psq_l/psq_st).
// Score: NEAR 90.70% (4 of 43 words differ) — PARKED, see block at the bottom.
// family=m2c
// range=0x801204CC-0x80120578 size=172B
// FLAG: -fno-expensive-optimizations
//
// Shape recovered from want:
//   temp_f31 = farg0;                    # fmr f31,f1 - param homed in f31   #
//   lbl_80302F24 = temp_f31;             # stfs f31,0x2f24(r11)                #
//#   temp_f31 = temp_f31 * 0.5f;          fmuls f31,f31,f0                    #
//   if (fn_801209CC() == 2) {             # callee is genuinely 0-arg           #
//       a = temp_f31 * 32767.0f;          # fmuls f0,f31,f0                     #
//       a = a * 0.01f;                    # fmuls f0,f0,f13                     #
//#       f64 K = 2147483648.0 (lbl_8029D770)                                          #
//       if (!(a >= lbl_8029D770)) {      # cror cr0un,cr0eq,cr0gt / bso        #
//           var_r3 = (s32)a;             # fctiwz;stfd;lwz  — plain path       #
//       } else {
//           var_r3 = (s32)((f64)a - lbl_8029D770) ^ 0x80000000;  # fsub+xoris   #
//       }
//       AUDSimpleAudioSetVolume(var_r3, var_r3);   # clrlwi 0x10 ; mr r4,r3     #
//   }
//   return 1;
// Load-bearing edits vs the inherited m2c draft (DIFF 11.6%):
//   1. fn_801209CC(0x802A0000) -> fn_801209CC()          +?  (phantom arg, dropped a lis+addi)
//   2. real 2-arm if/else instead of the `if (0 == 0)`    restored the whole fixuns pair
//   3. __asm__("" : "+f"(temp_f31)) keeps the fmr f31,f1 param home copy
//   4. AUDSimpleAudioSetVolume prototyped (u16,u16)       killed 1 crclr + the extsh
//   5. FLAG: stale `-Os` (74.4%) replaced by -fno-expensive-optimizations (90.7%)
#include "types.h"
s32 fn_801209CC(void);
void AUDSimpleAudioSetVolume(u16, u16);
extern f32 lbl_8029D760;
extern f32 lbl_8029D764;
extern f32 lbl_8029D768;
extern f64 lbl_8029D770;
extern f32 lbl_80302F24;
s32 fn_801204CC(f32 farg0) {
    volatile double _dummy;
    f32 temp_f31;
    f32 a;
    s32 var_r3;

    temp_f31 = farg0;
    __asm__("" : "+f"(temp_f31));
    lbl_80302F24 = temp_f31;
    temp_f31 = temp_f31 * lbl_8029D760;
    if (fn_801209CC() == 2) {
        a = temp_f31 * lbl_8029D764;
        a = a * lbl_8029D768;
        if (!(a >= lbl_8029D770)) {
            var_r3 = (s32)a;
        } else {
            var_r3 = (s32)((f64)a - lbl_8029D770) ^ 0x80000000;
        }
        AUDSimpleAudioSetVolume(var_r3, var_r3);
    }
    return 1;
}

// === PARKED (2026-10-30) ===
// Score: NEAR 90.70% — object is SIZE-EXACT 172B == symbols.txt size:0xAC == the
// range= marker, and 39 of 43 words are byte-identical. The 4 remaining words are
// ONE fact: GCC allocates the `extendsfdf2` output pseudo (the SF->DF copy that
// feeds `fcmpu` / `fctiwz` / `fsub`) into f13 (the register just freed by the
// `lfs f13, lbl_8029D768` constant) where retail put it in f1:
//     The original copies the single-to-double extend output into f1 and feeds
//     the compare, the convert-to-word and the subtract all from f1, while
//     this draft allocates that extend output into f13 and feeds all three
//     consumers from f13 instead.
// BLOCKER: `local_alloc` hard-register choice, i.e. BELOW the front end and
// below sched.  Evidence: `cc1 -O2 -G0 -mcpu=750 -fno-common
// -fno-expensive-optimizations -dr` shows the post-reload RTL already in want's
// order and shape — insn 46 is
//     (set (reg:DF 99) (float_extend:DF (reg/v:SF 84)))  {extendsfdf2}
//   immediately after the two `mulsf3+1`, i.e. exactly want's `fmr f1,f0` slot,
//   with pseudo 99 dead at insn 44 when the c768 constant dies. Only the hard
//   register differs. f1 IS free at that point (the farg0 pseudo is REG_DEAD at
//   the `"+f"` barrier, insn 13), so this is a reg_alloc_order preference, not
//   pressure.
// TRIED AND MEASURED (all 172B/4-diff or worse — the residual is INVARIANT):
//   * ~40 source shapes: single vs two vs three float locals; the DF value as a
//     named f64 (d = a / d = (f64)a), used in both arms or only in the compare;
//     `(f32)`/`(f64)` cast on the subtraction; xoris written as ^ with the
//     constant on either side or as a separate `^=` statement; `a = a*c` vs
//     `a *= c` vs `c*a`; `a < K` instead of `!(a >= K)`; the fast/slow arms
//     swapped; externs replaced by value-identical C LITERALS for each of the
//     four rodata constants separately and together (§6be-L4); `volatile f32 a`;
//     `volatile double _dummy` -> plain `double` + "m" pin; barrier on a vs b vs
//     on both; temp_f31 barrier as "+f" vs volatile vs none vs on farg0; a
//     nested-scope copy of the param; `s32` vs `u32` result; a pre-initialised
//     result with a conditional overwrite.
//   * hard-register pins: `a`->fr1 (product goes to f1, no copy, 168B);
//     `a`->fr0 (no-op); `a`->fr2/fr4/fr5 (168B); `temp_f31`->fr31 (168B);
//     `c`->fr0/fr11/fr14 (no-op or worse); a nested `register f32 d1 __asm__("fr1"); d1 = a;`
//     (168B — the pin coalesces the whole web onto f1 so the product lands there);
//     `register f64 d __asm__("fr1"); d = (f64)a;` (adds a SECOND copy:
//     fmr f13,f0 + fmr f1,f13, 22 diffs) — the extend always writes a fresh
//     pseudo, so pinning the DF *variable* can never reach the extend's output.
//   * 20+ flags on top of -fno-expensive-optimizations: -fno-schedule-insns(2),
//     -fno-sched-spec, -fno-sched-interblock, -fno-gcse, -fno-thread-jumps,
//     -fno-expensive-optimizations(alone is the winner), -fno-rerun-cse-after-loop,
//     -fno-strength-reduce, -fno-caller-saves, -fno-cse-follow-jumps,
//     -fno-cse-skip-blocks, -fno-branch-count-reg, -conserve-space, -O3,
//     -mcpu=603 — ALL inert (4 diffs, byte-identical output).
// NOTE the inherited `// FLAG: -Os` was STALE and harmful (74.4% vs 86.1%
// flagless); §6bx sign-flip again. -fno-expensive-optimizations is load-bearing
// on the corrected body: it removes a spurious `mr r9,..`+`xoris r3,r9` pair in
// the slow arm (86.1% -> 90.7%) by letting the fctiwz high word coalesce into
// var_r3 in r3.
// TRIED 2026-10-12: the 1-insn fmr wedge (`register f64 d
// __asm__("fr1")` + `__asm__("fmr %0,%1" : "=f"(d) : "f"(a))`, both arms
// rewritten onto d) -> 76.7%: the fr1 pin rotates the WHOLE function FPR
// coloring (f0<->f1, f12->f13, fctiwz dest). Reverted. Wedge route dead.