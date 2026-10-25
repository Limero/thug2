// PARKED 2026-10-03 (a37): DIFF 33.3% (was DIFF 25.0% before the semantics pass
// family=m2c range=0x800363BC-0x80036578 size=444B
// below; body is now semantically right, only register/frame assignment is off).
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800363BC
// What the semantics pass fixed (each was worth real words):
//   - prototypes for EVERY callee: a missing proto makes ngccc emit `crclr cr1eq`
//     before each `bl` (6 of them) and pads the body; WANT has none.
//   - `fn_8003A31C` takes ONE arg (m2c invented a 2nd). Dropping it also makes the
//     `& 1` test in place: WANT `andi. r9,r0,1` + `beq`.
//   - the 0x40 record filled by loop 3 is NOT Unk_DB0E2BAB (all-s32): offsets
//     0/0x14/0x28/0x3C are s32 (WANT `stw`), the other 12 words f32 (`stfs`).
//     Local Unk_40_REC replaces the cast; the old shape cost an fctiwz+stfd spill.
//   - the two dead asserts are guards on a VARIABLE that is 0, not `if (0)`:
//     GCC 2.95 has no cross-BB constant propagation, so `s32 v=0; ... if (v != 0)`
//     keeps WANT's `li r26,0` ... `cmpwi r26,0` + `beq` + the dead call, while a
//     literal `0 != 0` is folded away.
//   - loop 1 tail must be a POST-decrement test (`while (var_r31-- != 0)`), which
//     yields WANT's `cmpwi r31,0; addi r31,-1; bne`; a plain `while (v) {v--;}`
//     gets fused into `addic.` and m2c's temp-flag form into `subfic`+`adde`.
//   - GOT length is now 444B = WANT length (was 436B; the scorer is positional, so
//     any length skew misaligns every later word).
// Concrete remaining diff:
//   (1) FRAME BASE: WANT `stwu -0x30` = 16+8*nFPR+locals (FPR-frame quirk,
//       recipes 4c / issue-01); ngccc gives 8+8*nFPR+locals => GOT -0x28. Costs
//       6 words: stwu imm, stfd/stmw/stw(lr) disps, lfd disp, `addi r1` imm.
//   (2) ARG REGISTERS: GOT arg0=r29/arg1=r28, WANT arg0=r28/arg1=r29 -- every
//       body word downstream differs, which is most of the missing 66%.
//   (3) loop 2's empty 4-iteration nest: WANT keeps the outer var in r9 and does
//       `addi r30,r9,-1` ... `mr r9,r30`; GOT decrements r30 in place.
//   (4) block-1 alloc-result/walker regs (r27/r30) follow from (2).
// Ruled out (all measured, all worse or neutral):
//   - `volatile double _dummy;` (the 4c FPR-frame fix) gives the +8 (stmw lands at
//     0x10) but ProDG then rewrites the loop-invariant f32 constant into a GPR
//     bit pattern: no `stfd/lfd f31` at all and all 16 stores become `stw`. Same
//     with `volatile u32 _dummy[2]`, so it is the local's existence, not its type.
//   - `extern f32 lbl_80291EDC;` (typed extern instead of `char[]`+cast) does the
//     same float->GPR rewrite on its own (kills f31 even with no dummy); the m2c
//     `char[]`+`*(f32*)` pun keeps f31. Keep the pun.
//   - per-object `-mps-float`: frame collapses to 0x20, no FPR save at all.
//   - `__builtin_alloca(8)`: emits `mr r31,r1`, wrong codegen.
//   - a 3rd incoming int param: frame *shrinks* to 0x20 and f31 is dropped, so the
//     +8 is NOT the incoming-arg area (it is the FPR quirk). All call sites set at
//     most r3+r4, so the outgoing arg area is 8B too; want's 16 cannot be an arg
//     area. There are no BL/pointer references to 0x800363BC in the DOL, so arity
//     cannot be recovered from a caller either.
//   - the FPR quirk cannot be had together with f31 in this body by any frame
//     knob tried; both `volatile double _dummy` and a 3rd param lose the FPR.
// Most promising next idea: recover the +8 by making the ORIGINAL's 8-byte local
// explicit in a shape ProDG does not de-FPR the constant -- i.e. find the real
// source construct behind the frame (a `double` local that the game code kept).
// Every 8-byte local I could synthesise also flips the f32 constant into GPRs, so
// the frame and the FPR look coupled in ngccc 3.9.3. Second-best: chase the
// r28/r29 arg-order coin flip (it flipped once, with m2c's subfic/adbe loop tail),
// which is the single biggest scoring item.
#include "types.h"
extern char lbl_80291ED8[];
extern char lbl_80291EDC[];
extern char lbl_802FFE98[];
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    s32 i0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    s32 i5;
    f32 f6;
    f32 f7;
    f32 f8;
    f32 f9;
    s32 i10;
    f32 f11;
    f32 f12;
    f32 f13;
    f32 f14;
    s32 i15;
} Unk_40_REC;

void fn_8000F320(void *);
void fn_80036370(void *);
void fn_80036864(void *, void *);
s32 fn_800368FC(void *, void *);
s32 fn_8003A31C(void *);
s32 Mem_Alloc(s32);

void *fn_800363BC(Unk_DB0E2BAB *arg0, Unk_09D16053 *arg1) {
    s32 temp_r3;
    s32 temp_r3_3;
    s32 temp_r31;
    s32 var_r9;
    s32 var_ctr;
    s32 var_r26;
    s32 var_r27;
    s32 var_r31;
    void *temp_r3_2;
    void *temp_r3_4;
    void *var_r30;
    void *var_r30_2;
    f32 temp_f31;
    Unk_40_REC *rec;

    arg0->unk0x0 = 0;
    if ((arg1->unk0x594 & 1) != 0) {
        arg0->unk0x0 = QB_UNKNOWN_0x10000000;
    }
    var_r26 = 0;
    fn_8003A31C(arg1);
    temp_r3 = fn_8003A31C(arg1);
    temp_r3_2 = Mem_Alloc(temp_r3 << 5);
    var_r31 = temp_r3 - 1;
    var_r30 = temp_r3_2;
    if (temp_r3 != 0) {
        do {
            fn_80036370(var_r30);
            var_r30 += 0x20;
        } while (var_r31-- != 0);
    }
    arg0->unk0x18 = temp_r3_2;
    if (var_r26 != 0) {
        fn_8000F320(*(void **)&lbl_802FFE98);
    }
    var_r26 = 0;
    fn_8003A31C(arg1);
    temp_r3_3 = fn_8003A31C(arg1);
    temp_r3_4 = Mem_Alloc(temp_r3_3 << 6);
    var_r9 = temp_r3_3 - 1;
    if (temp_r3_3 != 0) {
        do {
            var_ctr = 4;
loop_8:
            var_ctr -= 1;
            if (var_ctr != 0) {
                goto loop_8;
            }
            var_r9 -= 1;
        } while (var_r9 != -1);
    }
    arg0->unk0x4 = temp_r3_4;
    if (var_r26 != 0) {
        fn_8000F320(*(void **)&lbl_802FFE98);
    }
    temp_r31 = *(s32 *)lbl_80291ED8;
    var_r27 = 0;
    temp_f31 = *(f32 *)lbl_80291EDC;
    var_r30_2 = arg0->unk0x4;
loop_14:
    if (var_r27 < fn_8003A31C(arg1)) {
        rec = (Unk_40_REC *)var_r30_2;
        rec->i0 = temp_r31;
        var_r27 += 1;
        rec->f1 = temp_f31;
        rec->f2 = temp_f31;
        rec->f3 = temp_f31;
        rec->f4 = temp_f31;
        rec->i5 = temp_r31;
        rec->f6 = temp_f31;
        rec->f7 = temp_f31;
        rec->f8 = temp_f31;
        rec->f9 = temp_f31;
        rec->i10 = temp_r31;
        rec->f11 = temp_f31;
        rec->f12 = temp_f31;
        rec->f13 = temp_f31;
        rec->f14 = temp_f31;
        rec->i15 = temp_r31;
        var_r30_2 += 0x40;
        goto loop_14;
    }
    arg0->unk0x14 = fn_8003A31C(arg1);
    fn_800368FC(arg0, arg1);
    fn_80036864(arg0, arg1);
    arg0->unk0x8 = arg1;
    arg0->unk0x10 = 0x1F;
    return arg0;
}
