// FPR-frame fix: volatile double dummy (issue 01, M4.92)
// WIP DRAFT (non-matching) — C body rebuilt by hand from the want
// family=m2c range=0x800F1C34-0x800F1DB0 size=380B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// UPDATED 2026-10-02: 11.8% -> 33.7%. Semantics recovered from the want:
//  * `GetVector` is a 4-arg call `GetVector(ctx, QB_POSITION, &sp8, 0)` — m2c
//    dropped the ctx arg and the trailing 0 (one `crclr cr1eq` + wrong hash reg).
//  * `fn_800F1B5C`'s result is dead; the `beq cr4` at 0x800F1D7C tests the
//    *hoisted* `cmpwi cr4, r30, 0` (r30 == arg2 there), so the guard is
//    `if (arg2 != 0)`, not `if (0)` (m2c could not see the cr4 source).
//  * the vector is 4 floats {lbl_8029B35C, same, same, lbl_8029B360} =
//    {0.0f,0.0f,0.0f,1.0f}; the SetVector call is
//    `fn_8012788C(ctx, QB_POS, sp8.x, sp8.w, -sp8.z)` (m2c used a static
//    `spC` for arg 3 instead of sp8.w).
//  * the record table is 12-byte records at arg0+0x1000C indexed by
//    arg0[0x10008] — needs a real `struct {s32,s32,s32}` array, not
//    `(s32*)arg0 + 0x1000C + n*0xC` (that scales the stride to 0x30 and emits
//    `add`+`addis` instead of want's `addis r11;addi r10/r8/r7;stwx`).
//  * guard idiom: `if (guard() != 0) return 0; ... r = 1; return r;` — this is
//    the ONLY plain-C form found that emits want's shadow `li r3,0` *before*
//    the `bne` and merges the zero path into the shared epilogue (recipes 2 /
//    129 / fn_8011CA08 / fn_8011C924). `r = 0; if(...) {…; r = 1;} return r;`
//    puts the accumulator in a callee-saved reg and loses the shadow-li;
//    if/else with explicit `return 0/1` sinks the zero block to the bottom.
//  * two `volatile double` locals give want's `stwu -0x58` + `stfd 0x48/0x50`
//    (issue-01 +8 rule), and declaring the V4 *first* puts it at 8(r1) as want
//    does.
//
// PARKED 2026-10-02 (w75/0x800F1C34): pure register-allocation wall in the
// loop preheader. Want keeps 6 callee-saved GPRs and parks both float-literal
// addresses in *volatile* scratch (r9/r11) and the &sp8 address in a
// callee-saved reg (`addi r30,r1,8`; then `4(r30)/8(r30)/c(r30)/mr r5,r30`):
//   Retail sequences the branch guard, two float-page loads into scratch
//   registers r9 and r11, the f31 load, the frame-base derivation into the
//   callee-saved r30, and the f30 load. The build matches that shape except
//   that the two page loads land in callee-saved r25 and r26 and the
//   frame-base copy becomes a register-to-register move into r4.
// ngccc gives the two `lis` pseudos callee-saved r25/r26, which (a) grows the
// save to `stmw r25` (7 regs vs want's 6) and (b) leaves no callee-saved reg
// for &sp8, so it is rematerialised as `addi r5,r1,8` per use and the loop's
// `mr r4,i` is hoisted into the preheader (=> object is 4B short, 376 vs 380).
// Tried: reads inside the loop before the call (hoists to f30/f31, addresses
// callee-saved); reads after the call (no hoist, values remat to f0/f13);
// reads before the loop (addresses volatile but the loads land *before* the
// `cmpw/bge` instead of after); one shared `f32 cv[2]` base (would be 3 insns,
// want has 4). Register-allocation order is not steerable from plain C.
// Residual = the whole register numbering (r26->r27 …) plus the 1-word loop
// shift. Applies to any fn_800Fxxxx/vcall body that reads two .rodata floats
// into f30/f31 while keeping 6 GPRs live across the loop.
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029B35C;
extern f32 lbl_8029B360;
extern s32 GetVector(CStruct *, s32, CStruct *, s32);
s32 fn_800F1F2C(CStruct *, s32);
s32 fn_801259C8(s32, s32);
void fn_800F0308(s32);
s32 fn_800F164C(CStruct *, s32);
s32 fn_80129528(CStruct *, s32);
void fn_801270B4(CStruct *, s32);
void fn_8012788C(CStruct *, s32, f32, f32, f32);
void fn_800F1B5C(CStruct *, s32);
void fn_800A7F38(void);
void fn_800A80D8(void);
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;
typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
} Rec12;
typedef struct {
    char pad[0x10008];
    s32 count;
    Rec12 recs[1];
} Tbl;
s32 fn_800F1C34(Tbl *arg0, s32 arg1, s32 arg2) {
    V4 sp8;
    volatile double _dummy;
    volatile double _dummy1;
    s32 _pad;
    CStruct *tbl;
    CStruct *ctx;
    f32 zero;
    f32 one;
    s32 i;
    s32 n;
    s32 cnt;
    s32 r;
    if (fn_800F1F2C(arg0, arg1) != 0) {
        return 0;
    }
    {
        tbl = (CStruct *)fn_801259C8(arg1, 1);
        arg0->recs[arg0->count].f0 = arg1;
        arg0->recs[arg0->count].f1 = (s32)tbl;
        arg0->recs[arg0->count].f2 = arg2;
        cnt = arg0->count;
        arg0->count = cnt + 1;
        fn_800F164C(arg0, cnt);
        fn_800F0308(arg1);
        n = *(s32 *)((char *)tbl + 4);
        i = 0;
        while (i < n) {
            zero = lbl_8029B35C;
            one = lbl_8029B360;
            ctx = (CStruct *)fn_80129528(tbl, i);
            sp8.x = zero;
            sp8.y = zero;
            sp8.z = zero;
            sp8.w = one;
            if (GetVector(ctx, QB_POSITION, (CStruct *)&sp8, 0) != 0) {
                fn_801270B4(ctx, QB_POSITION);
                fn_8012788C(ctx, QB_POS, sp8.x, sp8.w, -sp8.z);
            }
            i++;
        }
        fn_800F1B5C(arg0, (s32)tbl);
        if (arg2 != 0) {
            fn_800A7F38();
            fn_800A80D8();
        }
        r = 1;
    }
    return r;
}