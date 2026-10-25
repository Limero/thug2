// PARKED 2026-10-03 (a34): DIFF 28.6% (was DIFF 25.2%).
// Reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8003AFC8
//
// WHAT IS NOW EXACT: frame (stwu -0x80 / stmw r29,0x74 / lr 0x84), r31=arg0,
// r30=arg2, and the whole 20-case unsigned decision tree (all 20 pivots, cmpw
// =, cmplw/bgt shape). The case constants were never the problem.
//
// LOCAL MAP (derived from the binary — m2c's decls were wrong):
//   0x08..0x14  V4 v8   : read, multiplied, passed to fn_80062528. NEVER
//                         WRITTEN in the binary — it is only read, so the C
//                         must keep the dead-store form `v8.x *= v18.x` (a
//                         plain `v8 = f(v8)` would emit stores we don't want).
//   0x18..0x24  V4 v18  : splat of lbl_80292014, arg to fn_80053e7C
//   0x28..0x68  17 s32  : GetChecksum_2/GetInteger out-params (0x28 addgeom,
//                         0x2c/0x30 hidegeom, 0x34..0x3c uvoffset, 0x40/0x44
//                         allocuv, 0x48 replace, 0x4c setcreated, 0x50
//                         objectscale, 0x54 bonescale, 0x58/0x5c bodyshape,
//                         0x60 cleargeom, 0x64/0x68 runscript)
// m2c used a 0x40-byte Unk_59AB5482 + Unk_E266FB50 + `static` sp1C/sp20/sp24
// -> frame 0xc0. Two plain V4 locals give 0x80 exactly.
//
// arg0->unk0x8 is a table of 17 {s16 offset, void *fn} pairs at +0x50..+0xD4
// (stride 8). The offset fields load with LHA, so Unk_C7387A53 (s32) is
// unusable — a local struct with s16 offsets is required. Calls are mtlr/blrl.
//
// fn_8003AB40 and fn_8003AB44 take TWO args; m2c invented a third 0x80300000
// that never materialises in the binary. Callee prototypes are load-bearing:
// unprototyped calls emit `crclr cr1eq` (recipes M5.22 item 16) — adding the
// full protos removed all 18 of them.
//
// REMAINING DIFF (got 1760B vs want 1804B = 11 instructions short):
//  1. WANT has `li r3,1; b epilogue` immediately after the DEBUGPRINTAPPEARANCE
//     body (0x8003B188) and every other case branches there; GOT emits only
//     `b <shared block>` with the shared block parked at 0x8003b450. Tried the
//     `break` + single trailing `return 1` form: 27.7%, WORSE (the post-switch
//     block lands even later). GCC block placement, not the C shape.
//  2. WANT keeps THREE mtlr/blrl tails (0x8003B614, 0x8003B67C, 0x8003B6A4)
//     even though 0x8003B614 and 0x8003B6A4 are byte-identical; GOT cross-
//     jumps them together. Note 0x8003B67C is entered with r3 ALREADY built:
//     ALLOCATEUV and RUNSCRIPT do their own `add r3,r31,r3` at the call site,
//     which is what keeps that third tail alive — i.e. those two cases compute
//     the member address separately instead of sharing the `add`.
//  3. Arg setup order: WANT materialises `mr r3,r30` LAST for the 4-arg
//     GetChecksum_2 calls (lis r4; addi r5; ori r4; li r6; mr r3; bl) but
//     THIRD for the literal-0 GetInteger call (li r4; addi r5; mr r3; li r6;
//     bl). GOT always emits `mr r3` early. No prototype/typing change found.
//  4. HIDEGEOM: WANT CSEs the pair address — `lha r0,0x60(r9); addi r10,r9,0x60;
//     lwz r0,4(r10)` — GOT re-loads `lwz r0,0x64(r11)`. Suggests the original
//     passes a pointer to the {offset,fn} PAIR rather than two lvalues.
//
// NEXT IDEA: attack (2) first — it is ~8 of the 11 missing instructions.
// Write the ALLOCATEUV/RUNSCRIPT cases so the member address is built at the
// call site (hoisted into its own temp) and see whether a third tail survives.
// WIP DRAFT (non-matching) — C body from m2c, types corrected by hand.
// family=m2c range=0x8003AFC8-0x8003B6D4 size=1804B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
extern f32 lbl_80292014;
extern s32 lbl_803003E8;
extern s32 lbl_803003EC;
extern char lbl_803003F0[];
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

// arg0->unk0x8 points at a table of (s16 memberOffset, void *fn) pairs, one per
// case, at +0x50 .. +0xD4 (stride 8).  The offset fields are halfwords in the
// binary (lha), the handlers are called via mtlr/blrl on `arg0 + offset`.
typedef struct {
    char pad0x0[0x50];
    s16 o50;
    void (*f54)(void *, s32);
    s16 o58;
    void (*f5C)(void *, s32);
    s16 o60;
    void (*f64)(void *, s32, s32);
    s16 o68;
    void (*f6C)(void *, CStruct *);
    s16 o70;
    void (*f74)(void *, s32, s32, s32);
    s16 o78;
    void (*f7C)(void *, s32, s32);
    s16 o80;
    void (*f84)(void *, s32);
    s16 o88;
    void (*f8C)(void *, s32);
    s16 o90;
    void (*f94)(void *);
    s16 o98;
    void (*f9C)(void *);
    s16 oA0;
    void (*fA4)(void *);
    s16 oA8;
    void (*fAC)(void *);
    s16 oB0;
    void (*fB4)(void *, s32, s32);
    s16 oB8;
    void (*fBC)(void *);
    s16 oC0;
    void (*fC4)(void *);
    s16 oC8;
    void (*fCC)(void *);
    s16 oD0;
    void (*fD4)(void *, s32, s32);
} VTable;

void fn_8003AB40(s32, s32);
s32 fn_8003AB44(s32, s32);
s32 fn_8003ABA0(s32, s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void GetInteger(CStruct *, s32, s32 *, s32);
void GetStructure_2(s32 *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_80128978(CStruct *, s32);
s32 fn_80128E04(CStruct *, s32, s32 *, s32);
void fn_80128E34(CStruct *, s32, s32 *, s32);
s32 fn_801289E4(CStruct *, s32);
void fn_801284EC(s32 *, s32, s32 *, s32);
s32 fn_80053E7C(void *, s32);
void fn_80062528(s32, void *);
s32 fn_800379CC(s32);
s32 fn_8009EE2C(void *, CStruct *);

s32 fn_8003AFC8(Unk_9994C3F5 *arg0, s32 arg1, CStruct *arg2) {
    u32 swv1;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    V4 v8;
    V4 v18;
    VTable *t;
    s32 *temp_r3;
    s32 temp_r3_2;

    switch (swv1 = arg1) {
    case QB_DEBUGPRINTAPPEARANCE:
        fn_8003AB40(*(s32 *)&lbl_803003F0, 0);

    case QB_MODELAPPLYFACETEXTURE:
        return 1;
    case QB_MODELADDGEOM:
        GetChecksum_2(arg2, QB_PART, &sp28, 1);
        t = (VTable *)arg0->unk0x8;
        t->f54((char *)arg0 + t->o50, sp28);
        return 1;
    case QB_MODELHIDEGEOM:
        GetChecksum_2(arg2, QB_PART, &sp2C, 1);
        GetInteger(arg2, 0, &sp30, 1);
        t = (VTable *)arg0->unk0x8;
        t->f64((char *)arg0 + t->o60, sp2C, sp30 != 0);
        return 1;
    case QB_GEOMMODULATECOLOR:
        t = (VTable *)arg0->unk0x8;
        t->f6C((char *)arg0 + t->o68, arg2);
        return 1;
    case QB_GEOMSETUVOFFSET:
        GetChecksum_2(arg2, QB_PART, &sp34, 1);
        GetChecksum_2(arg2, QB_MATERIAL, &sp38, 1);
        GetInteger(arg2, QB_PASS, &sp3C, 1);
        t = (VTable *)arg0->unk0x8;
        t->f74((char *)arg0 + t->o70, sp34, sp38, sp3C);
        return 1;
    case QB_GEOMALLOCATEUVMATRIXPARAMS:
        GetChecksum_2(arg2, QB_MATERIAL, &sp40, 1);
        GetInteger(arg2, QB_PASS, &sp44, 1);
        t = (VTable *)arg0->unk0x8;
        t->f7C((char *)arg0 + t->o78, sp40, sp44);
        return 1;
    case QB_GEOMREPLACETEXTURE:
        GetChecksum_2(arg2, QB_PART, &sp48, 1);
        t = (VTable *)arg0->unk0x8;
        t->f84((char *)arg0 + t->o80, sp48);
        return 1;
    case QB_GEOMSETCREATEDTEXTURE:
        GetChecksum_2(arg2, QB_PART, &sp4C, 1);
        t = (VTable *)arg0->unk0x8;
        t->f8C((char *)arg0 + t->o88, sp4C);

    case QB_MODELREMOVEPOLYS:
        t = (VTable *)arg0->unk0x8;
        t->f9C((char *)arg0 + t->o98);
        return 1;
    case QB_MODELAPPLYOBJECTSCALE:
        sp50 = 0;
        if (fn_80128E04(arg2, QB_BODY_SHAPE, &sp50, 0) != 0) {
            v18.x = lbl_80292014;
            v18.y = lbl_80292014;
            v18.z = lbl_80292014;
            v18.w = lbl_80292014;
            if (fn_80053E7C(&v18, sp50) != 0) {
                v8.x *= v18.x;
                v8.y *= v18.y;
                v8.z *= v18.z;
                v8.w *= v18.w;
                fn_80062528(lbl_803003E8, &v8);
            }
        } else {
            t = (VTable *)arg0->unk0x8;
            t->fBC((char *)arg0 + t->oB8);
        }
        return 1;
    case QB_MODELAPPLYBONESCALE:
        if (fn_80128978(arg2, QB_BONE_SCALING) != 0) {
            sp54 = 0;
            if (fn_8003ABA0(*(s32 *)&lbl_803003F0, QB_SKATER_M_HEAD) != 0) {
                fn_80128E34(arg2, QB_MALE_CAS_PART, &sp54, 0);
            } else if (fn_8003ABA0(*(s32 *)&lbl_803003F0, QB_SKATER_F_HEAD) != 0) {
                fn_80128E34(arg2, QB_FEMALE_CAS_PART, &sp54, 0);
            }
            GetChecksum_2(arg2, QB_PART, &sp58, 1);
            t = (VTable *)arg0->unk0x8;
            t->fB4((char *)arg0 + t->oB0, sp58, sp54);
        }
        return 1;
    case QB_MODELAPPLYBODYSHAPE:
        sp5C = 0;
        if (fn_80128E04(arg2, QB_BODY_SHAPE, &sp5C, 0) != 0) {
            temp_r3 = fn_8003AB44(*(s32 *)&lbl_803003F0, QB_SKATER_M_HEAD);
            if ((temp_r3 != 0) && (ContainsFlag(arg2, QB_IS_BIGHEAD_CHEAT) != 0)) {
                GetStructure_2(temp_r3, QB_BIGHEAD_SCALE_INFO, &sp5C, 0);
            }
            if (lbl_803003EC != 0) {
                return fn_800379CC(sp5C);
            }
            return 1;
        }
        t = (VTable *)arg0->unk0x8;
        t->fAC((char *)arg0 + t->oA8);
        return 1;
    case QB_APPEARANCEALLOWSCALINGCHEAT:
        temp_r3_2 = fn_8003AB44(*(s32 *)&lbl_803003F0, QB_BODY);
        if (temp_r3_2 != 0) {
            return ContainsFlag(temp_r3_2, QB_NO_SCALING_ALLOWED) ^ 1;
        }
        return 1;
    case QB_MODELRESETSCALE:
        t = (VTable *)arg0->unk0x8;
        t->fA4((char *)arg0 + t->oA0);
        return 1;
    case QB_MODELCLEARGEOM:
        GetChecksum_2(arg2, QB_PART, &sp60, 1);
        t = (VTable *)arg0->unk0x8;
        t->f5C((char *)arg0 + t->o58, sp60);
        return 1;
    case 0xECF0248:
        t = (VTable *)arg0->unk0x8;
        t->f94((char *)arg0 + t->o90);
        return 1;
    case QB_MODELRUNSCRIPT:
        GetChecksum_2(arg2, QB_PART, &sp64, 1);
        GetChecksum_2(arg2, QB_TARGET, &sp68, 1);
        t = (VTable *)arg0->unk0x8;
        t->fD4((char *)arg0 + t->oD0, sp64, sp68);
        return 1;
    case QB_MODELFINALIZE:
        t = (VTable *)arg0->unk0x8;
        t->fC4((char *)arg0 + t->oC0);
        return 1;
    case QB_MODELPROPAGATEHEADCOLOR:
        t = (VTable *)arg0->unk0x8;
        t->fCC((char *)arg0 + t->oC8);
        return 1;
    default:
        return fn_8009EE2C(arg0, arg2);
    }
}