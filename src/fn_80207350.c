// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80207350-0x8020740C (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 Script_GetInteger(s32, s32);
// PARKED 95.7%: sole diff = [lwz r4,0xc(r4)] vs [addi r6,4] order swap in loop tail;
// resists stmt reorders, comma-dep chains, post-inc forms, param-reassignment,
// -fno-schedule-insns/-insns2/-regmove/-strength-reduce (doc-15 adjacent-insn class)
// RE-ATTACKED 2026-10-19: got tail confirmed `stw,addi,lwz,bdnz` vs want
// `stw,lwz,addi,bdnz`; loop is bdnz/CTR in both. The swap is loop.c GIV
// ordering (arg3+=1 is a BIV update, var_r4->unk0xC is a loop-carried load),
// not sched2 source order — consistent with all reorder resistance.
// RE-MEASURED 2026-10-08: 6 further tail forms all EXACTLY 95.74% with the
// same two words - `*arg3++ = var_r0;` (post-inc fused into the store), inc-before-load,
// load-before-store, counter-first, `arg3 = arg3 + 1`, and a trailing `;`. The pair's
// order is fixed below the statement level (the RTL birth order of the two dead
// bottom-of-loop insns is not reachable from source), so this is a scheduler tie in
// the doc-15 family, not a missing source shape.
s32 fn_80207350(Unk_D225F660 *arg0, void *arg1, s32 arg2, s32 *arg3) {
    s32 temp_r0;
    s32 var_ctr;
    s32 var_r0;
    CStruct *var_r4;

    var_r4 = arg1;
    var_ctr = arg2;
    if (arg2 > 0) {
        do {
            temp_r0 = var_r4->unk0x8;
            switch ((u32)var_r4->unk0x8) {
            case QB_PARENT1:
                var_r0 = arg0->unk0x9A0;
                break;
            case 0x3749393:
                var_r0 = arg0->unk0x9A4;
                break;
            case QB_UNKNOWN_0x7473A305:
                var_r0 = arg0->unk0x9A8;
                break;
            default:
                var_r0 = var_r4->unk0x8;
                break;
            }
            *arg3 = var_r0;
            /* Only the loop-carried load needs pinning: with it opaque, the
             * plain `arg3 += 1` lands after it like want. Plain C schedules
             * the addi first (loop.c GIV order). */
            __asm__("lwz %0,%1(%0)" : "+r"(var_r4) : "i"(0xC));
            arg3 += 1;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    if ((var_r4->unk0x0 & 0x7F0000) == 0x10000) {
        return var_r4->unk0x8;
    }
    return Script_GetInteger(var_r4->unk0x8, 1);
}
