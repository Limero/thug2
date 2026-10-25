// PARKED 2026-09-27 (ag07): best 10.6% (was 10.6%). 764B paired-single vector
//   function (skate-inable lip/horiz offset) — ~34/191 words are
//   psq_l/psq_st/ps_sub/ps_add/ps_muls0/ps_mr; the m2c husk scalarizes all of
//   them and DCEs the rest (compiles 452B vs 764B want). A faithful __ps_t
//   reconstruction is BLOCKED by a cc1 ICE (optabs.c:4338) on the
//   "write lane 0 (stfs) then read pair (psq_l)" idiom — see analysis below.
//   Known family: doc-06 PS + cc1 ICE (optabs.c:4338 / expmed.c:347).
// family=m2c range=0x801CEB2C-0x801CEE28 size=764B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT WAS TRIED (all verified against the DOL):
//   - Full __ps_t reconstruction (both branches, all PS ops, -mps-float):
//     ICE at optabs.c:4338 on sp38/sp40/sp48/sp50 (write lane 0 via stfs,
//     read pair via psq_l). Every form of the partial-pair-write idiom ICEs:
//     union .lo write, SN_PS_type .flt.lo, f32->__ps_t conversion, cast read,
//     f32[2] array, PS_BUILD compound literal. The matched PS fns
//     (fn_800A07F0 etc.) only write FULL pairs via __builtin_ps_* then read
//     a lane — never the partial write. sp8's pattern (write pair, then
//     lane-1 scalar RMW) DOES compile (union) — only the 4 scalar-written
//     locals are blocked.
//   - fn_801EC684(arg0, ...) with arg0 : Unk_E04AE13E* (callee wants
//     Unk_E2C810EF*): ICE at expmed.c:347 until a (Unk_E2C810EF*) cast is
//     added (byte-neutral).
//   - Cleaned scalar version (no PS): 1.2% — worse than the husk.
//
// FULL DATA-FLOW ANALYSIS (verified, for the next attempt):
//   arg0 = Unk_E04AE13E* (unk0xC = s32 ptr, unk0x244 = f32, unk0x254 = s32;
//   pair fields at 0x230/0x238/0x240/0x248 are NOT in the regenerated class
//   — use raw __ps_t casts). arg1 = CStruct*. Matched helpers:
//   ContainsFlag(CStruct*, s32); f32 fn_8014030C(s32 hash, s32, Unk_FFAD6788*);
//   s32 fn_801EC684(Unk_E2C810EF*, s32, s32). r9 = arg0->unk0xC.
//   Stack: sp8/sp10/sp18/sp20/sp28/sp30 = __ps_t at 0x8/0x10/0x18/0x20/0x28/
//   0x30; sp38/sp40/sp48/sp50 = __ps_t at 0x38/0x40/0x48/0x50 (lane-0 stfs
//   write, psq_l read, lane 1 dead); spC (0xC) = lane 1 of sp8 (scalar RMW).
//   LIP branch: sp38=LIPHORIZOFFSET, arg0->unk0x244 -= LIPDOWNOFFSET (after
//   the pair stores), PS math, 2x fn_801EC684(arg0,0x10,0)!=0 -> block_2.
//   Non-LIP: sp48=HORIZ, sp50=2*HORIZ, spC -= DOWNOFFSET, PS math,
//   ContainsFlag(QB_LEFT) picks the pair-store order, fn_801EC684==0 ->
//   return 0. block_2: return arg0->unk0x254 != 0.
//   RETRY HINT: the partial-pair-write idiom needs a source construct that
//   doesn't crash cc1 — check whether any matched PS fn writes a scalar to
//   lane 0 of a __ps_t local and reads it back as a pair (none found; they
//   all write full pairs). May need an inline-asm wedge (last resort) or a
//   dtk/postprocessor route.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801EC684(Unk_E2C810EF *, void *, void *);
s32 ContainsFlag(CStruct *, void *);
s32 fn_801CEB2C(Unk_E04AE13E *arg0, CStruct *arg1) {
    f32 sp50;
    f32 sp48;
    f32 sp40;
    f32 sp38;
    f32 spC;
    s32 sp8;
    f32 temp_f1;
    f32 temp_f1_2;
    s32 temp_r30;

    temp_r30 = arg0->unk0xC;
    if (ContainsFlag(arg1, QB_LIP) != 0) {
        sp38 = fn_8014030C(QB_SKATEINABLE_LIPHORIZOFFSET, 1, temp_r30);
        0;
        0;
        arg0->unk0x244 = (f32) (arg0->unk0x244 - fn_8014030C(QB_SKATEINABLE_LIPDOWNOFFSET, 1, temp_r30));
        0;
        0;
        0;
        0;
        0;
        0;
        0;
        if (fn_801EC684(arg0, 0x10, 0) != 0) {
            goto block_2;
        }
        sp40 = fn_8014030C(QB_SKATEINABLE_LIPEXTRACHECKHORIZOFFSET, 1, temp_r30);
        0;
        0;
        0;
        0;
        0;
        0;
        0;
        arg0->unk0x244 = (f32) (arg0->unk0x244 - fn_8014030C(QB_SKATEINABLE_LIPEXTRACHECKDOWNOFFSET, 1, temp_r30));
        0;
        0;
        if (fn_801EC684(arg0, 0x10, 0) != 0) {
            goto block_2;
        }
        goto block_10;
    }
    temp_f1 = fn_8014030C(QB_SKATEINABLE_HORIZOFFSET, 1, temp_r30);
    sp48 = temp_f1;
    temp_f1_2 = 2.0f * temp_f1;
    sp50 = temp_f1_2;
    0;
    0;
    0;
    0;
    0;
    spC -= fn_8014030C(QB_SKATEINABLE_DOWNOFFSET, 1, temp_r30, temp_f1_2);
    0;
    0;
    0;
    0;
    if (ContainsFlag(arg1, QB_LEFT) != 0) {
        0;
        0;
        0;
        0;
    } else {
        0;
        0;
        0;
        0;
    }
    if (fn_801EC684(arg0, 0x10, 0) == 0) {
block_10:

        return 0;
    }
block_2:
    if ((s32) arg0->unk0x254 != 0) {
        return 1;
    }
    return 0;
}
