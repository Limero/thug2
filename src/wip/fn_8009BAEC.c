// WIP DRAFT (non-matching) — rewritten by hand for w75/0x8009BAEC
// family=m2c range=0x8009BAEC-0x8009BBE8 size=252B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *Mem_Alloc(s32);

// 2026-10-08: reload_pin_sweep WIN — retype `s32 cur` ->
// `register s32 cur __asm__("r3")` => official 88.9% (was 79.4%). Note the
// note above lists many *statement-order* spellings of the same webs (all
// 79.4%); the register pin is what actually moves it.
// 2026-10-13: re-measured type-directed variants on the 95.2% body,
// all byte-neutral (95.24%): u32 arg1/arg3, u32 state, u32 bytes/base, switch-form of
// the duplicated arg2==2 pair. Confirms the residual is the dead-cmpwi sched tie,
// not a signedness/shape artefact. Body unchanged; park stands.
// 2026-10-10: `register s32 base __asm__("r29")` pin => 88.9% -> 92.1%
// (13 diffs -> 5). The pin flips the count/base colour coin (count r28, base
// r29 = want). A second type-directed edit gives 95.2% (3 diffs): the
// allocation result is a `char *` cursor, while the size arithmetic remains
// `s32` bytes. This removes unnecessary pointer/integer arithmetic casts and
// preserves the actual byte units, without changing emitted control flow.
//  (a) dead `cmpwi r26,2` sits 3rd in want (after mr r26/mr r31), 5th in got
//      (after mr r30/mr r28 too). The homes follow strict arg-use order, so the
//      cmpwi+its (merged-away) branch scheduled as a unit BEFORE jump-merge
//      stranded it early in retail; no C form reorders dead-insn rank.
//  (b) flag1 `slwi r0,r28,2; add r3,r29,r0`: want uses r0 for the scaled
//      count and r3 for the sum; ngccc reuses r3 for both. Cur's old value is
//      dead here and keeping an independent temporary across Mem_Alloc costs
//      a callee-saved home. The `char *` cursor preserves byte units but cannot
//      keep that dead value live; scheduling-only flags tested do not help.
//  So 95.2% is the current best; park pending a new register-liveness or
//  scheduling lever for these independent residuals.
//// PARKED 2026-10-02 (w75/0x8009BAEC): NEAR 79.4% (13/63 words). Semantics are
// now fully recovered — allocation size = count*12 + 4*(flags&1) + 8*(flags&2)
// + 12*(flags&4), the optional 4/8/12-byte-per-item sub-buffers at 0x30/0x34/
// 0x2C are only handed out when their flag bit is set (otherwise the *masked
// flag itself* is stored, which is why r27/r0 carry `flags & bit` into those
// stores), 0x28/0x38/0x3C/0x40 and the `unk0x4 |= 2` tail are exact.
// Residual = ONE register-allocation coin flip: ngccc puts count (arg3) in r29
// and base (count*12) in r28; WANT has count in r28 and base in r29. That single
// swap shifts the dead `cmpwi r26,2` one slot later (WANT emits it between
// `mr r31,r3` and `mr r30,r4`), so all 13 mismatches are the same shift.
// Tried (all 79.4%, identical object): `cur = arg3*12; base = cur;` vs
// `base = arg3*12; cur = base;` vs `cur = base = arg3*12;`; local decl order;
// `cur += arg3*4` vs `cur = base + arg3*4` vs `cur = arg3*4 + base`;
// if/else and ternary spellings of the flag-1 arm; `arg3<<2/<<3` instead of
// `*4/*8`; no `base` local at all (all `arg3*12` inlined); a separate `p` for
// the Mem_Alloc result (28.1%, worse). Source order 1,2,4 ALWAYS yields
// count=r29; order 2,1,4 yields count=r28 but emits the flag tests in the wrong
// order. So the allocation is coupled to the flag-test order and I could not
// decouple them in C. Applies to any "N accumulations guarded by bits of one
// flags word, one of the accumulators also live across a call" family member.
//
// The dead `cmpwi r26,2` (a compare whose CR0 is overwritten by the next
// `cmpwi r0,1` with no branch in between — see the note below) is reproduced
// by the deliberately-duplicated `if (arg2 == 2) state = arg0->unk0xC; else
// state = arg0->unk0xC;` pair: ProDG block-merges small identical arms, leaves
// the compare, and hoists the load to the merge point. Hoisting the shared
// value into `state` is what lets the (large, call-containing) body live AFTER
// the merge — duplicating the body itself makes GCC emit a live `bne` guard
// instead (verified). A `switch (arg2) { case 2: ... default: ... }` spelling of
// the same pair behaves identically.
void fn_8009BAEC(Unk_C8FEE62D *arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 base __asm__("r29");
    register char *cur __asm__("r3");
    s32 bytes;
    s32 state;

    if (arg2 == 2) {
        state = arg0->unk0xC;
    } else {
        state = arg0->unk0xC;
    }
    if (state == 1) {
        bytes = arg3 * 12;
        base = bytes;
        if (arg1 & 1)
            bytes = base + arg3 * 4;
        if (arg1 & 2)
            bytes += arg3 * 8;
        if (arg1 & 4)
            bytes += base;
        cur = (char *)Mem_Alloc(bytes);
        arg0->unk0x28 = (s32)cur;
        cur += base;
        if (arg1 & 1) {
            arg0->unk0x30 = (s32)cur;
            cur += arg3 * 4;
        } else {
            arg0->unk0x30 = arg1 & 1;
        }
        if (arg1 & 2) {
            arg0->unk0x34 = (s32)cur;
            cur += arg3 * 8;
        } else {
            arg0->unk0x34 = arg1 & 2;
        }
        if (arg1 & 4) {
            arg0->unk0x2C = (s32)cur;
        } else {
            arg0->unk0x2C = arg1 & 4;
        }
    }
    arg0->unk0x38 = arg1;
    arg0->unk0x3C = arg2;
    arg0->unk0x40 = arg3;
    arg0->unk0x4 = (arg0->unk0x4 & QB_UNKNOWN_0xFFFFFFFE) | 2;
}
