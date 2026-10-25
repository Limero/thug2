// WIP DRAFT (non-matching) — C body rebuilt by hand from the paired-single
// disassembly (replaces the m2c draft that scored 20.7%).
// family=m2c range=0x800A0E6C-0x800A0F2C size=192B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// === PARKED (2026-10-01) — 81.2% masked (39/48), SIZE-EXACT 192B ===
// `tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800A0E6C` ->
//   "NEAR m2c 0x800A0E6C (192B) 81.2%"  (was 20.7%).
//
// The body is retail-correct semantically and 39/48 words byte-exact: prologue,
// callee audit (GetChecksum_2 / fn_800F0F84 / fn_800F078C chained on r3,
// fn_8012772C with QB_DIST=0x7E832F08), the whole frame layout
// (0x48 = sp8[4]@0x08 + Pair2 d@0x18/0x20 + sp28@0x28 + the union spill@0x30),
// both dead psq_st spills, the two ps_sub register choices, the ps_mul/merge00
// colours, and the psq_st+lfs readback of the dot product.
//
// 9 words left, TWO root causes, both inside the paired-single block:
//  (1) the `lbl_80297B28` psq_l sits at 0x68, want has it at 0x58 (3rd load).
//      This shifts B0/B1/mul by two slots -> 4 diffs (0x58/0x64/0x68/0x6C).
//      It is a pure final-scheduler priority choice: ProDG sinks that load even
//      when it is written FIRST in the source (`C = lbl;` as statement 1 gives
//      the identical 0x68 placement).  Every -fno-sched*/-fno-gcse flag tried is
//      either inert or destroys the block (-fno-schedule-insns 54.2%).
//  (2) `ps_madd` writes f13 (coalesced with its multiplicand); want writes f0
//      (the accumulator's own register).  One colour choice -> 5 diffs
//      (0x88..0x98 madd/sum0/rsqrte/res/psq_st).  ProDG always coalesces the
//      madd output with the multiplicand here: same result with the chain split
//      into acc/s1/s2/s3, with B read from the struct member vs a staged temp,
//      with block-scoped temps, and on both statement orders.  Note the
//      PROMOTED twins do the opposite (fn_800A07F0/800A1230/800B69A0 all emit
//      `ps_madd f0,f0,f0,f13` = dest == multiplicand), so retail itself is not
//      self-consistent about this insn: it is a reload-pass tie-break.
// Load-bearing: `register __ps_t B0 __asm__("fr13")` on the arg0->0x58 read
// (79.2% -> 81.2%).  Pinning dot->fr0, A1->fr0, the const->fr10, or both
// B0/A1 together is neutral; a pin on sp8[2] alone costs 3 words.
//
// UPDATE 2026-10-12: ps_sub -> ps_add/ps_neg split tried (both subs
//   and d.f0-only): 43.8% / 47.9% — ps_neg emits a REAL extra insn (200B/196B
//   vs 192B), so the split is semantically wrong-shaped. Do not retry.
// NOT TRIED: a 1-instruction asm window to force the const psq_l up two slots
// (kept out per the <30%-asm rule), and rewriting the two ps_subs as explicit
// `ps_add(x, ps_neg(y))` pairs to change the operands' live ranges.
//
// Key mechanism worth recording (see AGENTS-recipes): retail keeps the inverse-
// 1/sqrt chain in a plain `__ps_t`, but the FINAL value goes through a *union*
// (`SN_PS_type res; res.ps = dot; x = res.flt.hi;`, block-scoped, declared after
// the s32) - a union assignment forces the psq_st and the `.flt.hi` read forces
// the lfs.  That is the only spelling found that reproduces the psq_st@0x30 +
// lfs@0x30 pair AND puts the pair at 0x30 (declaration order); a
// `volatile __ps_t` with the same role allocates the 8-byte slot at 0x28 and the
// s32 at 0x30 (swapped), and hoisting the `volatile` decl above `sp28` does not
// change it.  ProDG's local-slot order is declaration order for address-taken /
// union / volatile locals (verified with a 8-local probe) but NOT for a bare
// `volatile __ps_t` next to an address-taken s32 - diagnostic: compile a
// function whose every local's address is passed to an external call and read
// the `addi rX, r1, off` operands.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "dolphin/SN_PS.h"
extern __ps_t lbl_80297B28;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800F0F84(s32, s32);
void fn_800F078C(s32, void *);
void fn_8012772C(s32, s32, f32);
typedef struct {
    __ps_t f0;
    __ps_t f8;
} Pair2;
s32 fn_800A0E6C(Unk_64D775D7 *arg0, CStruct *arg1, CScript *arg2) {
    f32 sp8[4];
    Pair2 d;
    s32 sp28;
    __ps_t dot;
    register __ps_t B0 __asm__("fr13");

    sp28 = 0;
    GetChecksum_2(arg1, 0, &sp28, 0);
    fn_800F078C(fn_800F0F84(sp28, 1), &sp8);
    B0 = arg0->unk0x58;
    d.f8 = __builtin_ps_sub(arg0->unk0x60, ((__ps_t *)&sp8)[1]);
    d.f0 = __builtin_ps_sub(B0, ((__ps_t *)&sp8)[0]);
    dot = __builtin_ps_merge00(__builtin_ps_mul(d.f8, d.f8), lbl_80297B28);
    dot = __builtin_ps_madd(d.f0, d.f0, dot);
    dot = __builtin_ps_sum0(dot, dot, dot);
    dot = __builtin_ps_rsqrte(dot);
    dot = __builtin_ps_res(dot);
    {
        SN_PS_type res;
        f32 x;
        res.ps = dot;
        x = res.flt.hi;
        fn_8012772C(arg2->unk0x18, QB_DIST, x);
    }
    return 1;
}