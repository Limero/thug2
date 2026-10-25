// PARKED 2026-10-05: parked NEAR 58.4% (was 8.0% DIFF), object
// 548B == want 548B.
// family=m2c range=0x80176B78-0x80176D9C size=548B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT IT DOES: a QB script operator that reads four float fields off the
// `QB_SKATERBALANCETRICK` struct of the current element, scales them by one
// float constant (lbl_802A8E54) and hands them, as integers, to four
// `fn_801B0368` "set float" calls (keys taken from `a->0x10/14/18/1C`);
// `arg0->unk0x394` is an accumulating success flag that every call ORs in.
//
// 8.0% -> 58.4%, and the object is now the right size.  Four
// independent fixes, all of them "fix the type / fix the declaration", no
// flags:
//
// 1. **The three scaled fields are `f32`, not `s32`.**  structs.h types
//    Unk_9F352E7C.unk0x58/0xC8/0x138 as `s32`, which made GCC synthesise
//    int->float conversions (the `lis 0x4330 / xoris 0x8000 / fsub 2^52`
//    software sequence) and ~20 extra instructions per site.  Declaring a
//    local `Bal` struct with `f32` at those three offsets restores
//    `lfs` + `fmuls` + `fctiwz` + `stfd 8(r1)` + `lwz 0xc(r1)` exactly.
//    (Don't make `spC` volatile here: GCC 2.95 then miscompiles it.)
// 2. **Absolute globals must be referenced as SYMBOLS, not literals.**
//    want is `lis r9,0x8030 ; lwz r3,0x5f24(r9)`; a literal
//    `*(s32 *)0x80305F24` compiles to `lis ; ori ; lwz 0(r9)` (three
//    instructions + a copy).  `extern s32 lbl_80305F24;` + `lbl_80305F24`
//    gives the two-instruction hi/lo form (the `lo` displacement is
//    relocation-masked, the register is not).
// 3. **`fn_801A6CCC(arg0->unk0x24)` is a separate statement**, not the 2nd
//    argument of `fn_801B0F94(...)`.  As a nested argument, ngccc evaluates
//    arg0 first, so the global is loaded *before* the inner call and has to
//    live in a callee-saved reg (`lwz r30, 0(r9) ; mr r3, r30`, 3 extra
//    insns).  Split: `t = fn_801A6CCC(...); a = fn_801B0F94(lbl_80305F24, t);`
//    then the load lands directly in r3 after the call, as want has it.
// 4. **Wrong arities in the m2c draft**: want calls `fn_801745B4` with ONE
//    argument (only r3 is set up; the draft passes three) and `fn_801813F0`
//    with NO arguments (r3 is not set at all before that call; the draft
//    passes arg0).
//  Also: the last four flag updates are a single OR expression,
//  `arg0->unk0x394 = (arg0->unk0x394 != 0) | (call(...) != 0)` (want emits
//  `or r0,r9,r0`), not `|= 1`.
//
// RESIDUAL: everything that is left is one register-allocation permutation
// plus its knock-on scheduling.  want: arg0=r31, p=r26, a=r27, b=r28,
// flags=r29, v2=r30; this build: p=r29, a=r27, b=r26, arg0=r28,
// flags=r31, v3=r30.  Everything else (all four `fn_801B0368` flag
// patterns, the three float conversions, the epilogue) is already
// instruction-for-instruction identical, so a source shape that shifts the
// callee-saved assignment by one should be worth most of the remaining
// 41.6%.  Tried and *worse*: naming a local for `b->unk0x30` (52% -> 13%:
// the extra live-across-all-calls value spills and the frame grows to 0x38
// with r25 saved), three separate flag temporaries for the two
// `fn_801B06A0` updates (23%), a separate variable for the
// `GetChecksum_3` result (22%, and 4B short).
//  Also unexplained: want has one dead `mr r11, r4` right after the
// `GetChecksum_3` call (a reload artifact of the QB constant pseudo); this
// build emits two (`mr r9, r4` + `mr r11, r4`).
// Callee facts: fn_801B0F94(s32,s32), fn_801A6CCC(s32), fn_801745B4(s32),
// fn_801403CC(ptr), fn_801813F0(), fn_801B06A0(s32,s32,s32)->s32,
// fn_801B0368(s32,s32,s32)->s32, GetChecksum_3(ptr,s32)->ptr.
extern float lbl_802A8E54;
extern s32 lbl_80305EAC;
extern s32 lbl_80305F24;
#include "qb_constants.h"
#include "structs.h"

typedef struct { char pad0x00[0x58]; f32 unk0x58; char pad0x5C[0x6C]; f32 unk0xC8; char pad0xCC[0x6C]; f32 unk0x138; } Bal;

Bal *GetChecksum_3(void *, void *);
s32 fn_801B0F94(s32, s32);
s32 fn_801A6CCC(s32);
Bal *fn_801745B4(s32);
Unk_C7387A53 *fn_801403CC(s32);
s32 fn_801813F0();
s32 fn_801B06A0(s32, s32, s32);
s32 fn_801B0368(s32, s32, s32);

void fn_80176B78(Unk_406F9E9D *arg0) {
    Unk_C8FEE62D *a;
    Unk_C7387A53 *b;
    Bal *p;
    f32 k;
    s32 t;
    s32 f2;
    s32 v1;
    s32 v2;
    s32 v3;

    arg0->unk0x394 = 0;
    t = fn_801A6CCC(arg0->unk0x24);
    a = fn_801B0F94(lbl_80305F24, t);
    p = fn_801745B4(lbl_80305EAC);
    if (p != 0) {
        b = fn_801403CC(p);
        f2 = arg0->unk0x394;
        if (fn_801B06A0(a->unk0x4, fn_801813F0(), 0) != -1) {
            f2 |= 1;
        }
        arg0->unk0x394 = (f2 != 0);
        if (fn_801B06A0(a->unk0x8, b->unk0x34, 0) != -1) {
            f2 |= 1;
        }
        arg0->unk0x394 = (f2 != 0);
        p = GetChecksum_3(p, QB_SKATERBALANCETRICK);
        k = lbl_802A8E54;
        v1 = (s32)(p->unk0xC8 * k);
        v2 = (s32)(p->unk0x58 * k);
        v3 = (s32)(p->unk0x138 * k);
        arg0->unk0x394 = (arg0->unk0x394 != 0) | (fn_801B0368(a->unk0x10, v1, 0) != 0);
        arg0->unk0x394 = (arg0->unk0x394 != 0) | (fn_801B0368(a->unk0x14, v2, 0) != 0);
        arg0->unk0x394 = (arg0->unk0x394 != 0) | (fn_801B0368(a->unk0x18, v3, 0) != 0);
        arg0->unk0x394 = (arg0->unk0x394 != 0) | (fn_801B0368(a->unk0x1C, b->unk0x30, 0) != 0);
    }
}