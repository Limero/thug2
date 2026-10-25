// WIP DRAFT (non-matching) — C body re-derived by hand from the want bytes
// family=m2c range=0x8001ABC4-0x8001ACCC size=264B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 2026-10-02 (w75/0x8001ABC4): NEAR 74.2%, 260B vs 264B want.
// Root cause (located with `cc1 -drtl`): WANT keeps TWO `li r3,0` error blocks —
// 0x8001AC48 is the fall-through of the first `dvd_file_eof` test and 0x8001AC90 is
// final.c's TAIL-MERGE of the second test's error block into its predecessor. With
// two plain `return 0;` sites the RTL entering final() is already exactly WANT's
// shape at BOTH sites (`if_then_else (eq cc 0) -> work else pc` then
// `set r3,0; jump L` — identical blocks, identical successor), and final.c
// CROSS-MERGES them into one block with two predecessors; neither site can
// tail-merge afterwards (needs a single pred), so the object is 1 word short and
// E1 collapses to `cmpwi; bne` instead of `cmpwi; li r3,0; bne`.
// This body shares ONE error block via `goto err` (see the `goto body` / `err:` /
// `body:` label triple — that label triple is what forces the branch-over so the
// error block stays the branch's FALL-THROUGH and site 1 matches byte-for-byte),
// which wins 45.5% -> 74.2%, but then E1 must branch to the shared block.
// No source spelling of zero survives to RTL to differentiate the two error blocks
// (every constant-expression form folds in combine — verified via `-drtl`), and
// ProDG cc1 has no `-fcrossjumping` / `-freorder-blocks` (recipes §103, §6ep —
// identical wall at fn_8014E114 and fn_801A2E88). Making the two returns
// textually different (`return 1` vs `return 0`) DOES reproduce WANT's layout
// exactly, which proves the layout is reachable and only the merge is in the way.
// Secondary residual (2 words, 0x8001AC10/0x8001AC18): the pre-reload scheduler
// hoists `mr r27,r31` (total=cached) above the `bl GetCacheBytes` and sinks
// `subf r30,r31,r30` below it; WANT keeps subf before the call and the copy after.
// `-fno-schedule-insns` fixes block B but then swaps the prologue's
// `mr r28,r4` / `li r27,0` pair (net worse); every other ngccc flag tried is a
// byte-identical no-op here (-fno-regmove, -fno-peephole, -fno-schedule-insns2,
// -fno-thread-jumps, -fno-cse-follow-jumps, -fno-branch-probabilities,
// -fno-sched-interblock, -fno-sched-spec, -fno-expensive-optimizations,
// -fno-branch-count-reg).
// UPDATE 2026-10-18: differentiating the two error blocks with a zero-code
// `__asm__ volatile("")` (plain and with memory clobber) does NOT block the
// merge — both measure 73.1% with the blocks still cross-jumped (ProDG merges
// through empty volatile asms, or drops them before final.c). Reverted to the
// shared-`goto err` 74.2% body.
// Tried (pcts, this body as base): plain two `return 0` 45.5%; shared `goto err`
// 74.2%; `goto`+label split of both error sites 45.5% (cross-jump merges them);
// zero-code volatile-asm differentiation 73.1% (merge not blocked);
// err-block placed between the two guards 47.0%; duplicated `return var_r27`
// 45.5%; switch/do-while/plain-truth spellings 45.5% each.
// Applies to: dvd_file_read family / any function with two identical constant
// `return` blocks that WANT keeps separate.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void GetCacheBytes(Unk_C7387A53 *file, void *dest, s32 len);
s32 dvd_file_eof(Unk_C7387A53 *file);
void dvd_file_fill_cache(Unk_C7387A53 *file);
s32 dvd_file_read_anywhere(s32, s32, s32, s32);

s32 dvd_file_read(Unk_C7387A53 *arg0, void *arg1, s32 arg2) {
    s32 temp_r31 = arg0->unk0x70;
    s32 var_r27 = 0;
    s32 var_r28 = (s32)arg1;
    s32 var_r30 = arg2;
    s32 var_t;
    s32 temp_r31_2;

    if (temp_r31 >= var_r30) {
        GetCacheBytes(arg0, arg1, arg2);
        return var_r30;
    }
    if (temp_r31 != 0) {
        var_r30 -= temp_r31;
        GetCacheBytes(arg0, var_r28, temp_r31);
        var_r28 += temp_r31;
        var_r27 = temp_r31;
    }
    var_t = var_r30;
    if (var_r30 < 0) {
        var_t = var_r30 + 0x1F;
    }
    temp_r31_2 = var_t & QB_UNKNOWN_0xFFFFFFE0;
    if (temp_r31_2 != 0) {
        if (dvd_file_eof(arg0) != 0) {
            goto err;
        }
        goto body;
err:
        return 0;
body:
        var_r30 -= temp_r31_2;
        var_r27 += dvd_file_read_anywhere((char *)arg0 + 0x28, var_r28, temp_r31_2, arg0->unk0x74);
        var_r28 += temp_r31_2;
        arg0->unk0x74 = (s32)(arg0->unk0x74 + temp_r31_2);
    }
    if (var_r30 != 0) {
        if (dvd_file_eof(arg0) != 0) {
            goto err;
        }
        var_r27 += var_r30;
        dvd_file_fill_cache(arg0);
        GetCacheBytes(arg0, var_r28, var_r30);
    }
    return var_r27;
}