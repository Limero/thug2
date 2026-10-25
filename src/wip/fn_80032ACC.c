// PARKED 2026-10-16: 93.5% -> 96.7% (diffs 18->9, size-exact 1100B).
// BREAKTHROUGH: frame-struct pad ordering. Four loose `volatile double`
// pads were allocated LOW by ngccc, pushing the three address-taken locals
// to r1+0x28/0x2c/0x30. Packing locals+padding into one struct
// (`struct { s32 sp8; f32 spC; s32 sp10; volatile double pad[4]; }`) forces
// member order, so locals sit at r1+8/0xc/0x10 exactly like the WANT.
// Residual (9 words) is a pure callee-saved colouring wall: WANT homes arg2
// in r25 and arg3 in r26 with int/float homes interleaved
// (r25,r27,f31,f30,r26,f29,r30,f28); ngccc groups all int homes first so
// arg2 lands in r26 and arg3 in r25. Explicit register pins collapse the
// whole allocation (5.5%), and explicit arg-copy locals do not move it.
// Kept INERT (not promoted).
// WIP DRAFT (non-matching) — hand-rebuilt from the retail disassembly.
// family=m2c range=0x80032ACC-0x80032F18 size=1100B
// REBUILT 2026-10-06. Was the restored 12.7% m2c body; this is a
// from-WANT semantic re-derivation.  Main fixes over the m2c body:
//   * EVERY callee was undeclared (implicit int/varargs) so ngccc emitted a
//     spurious `crclr cr1eq` before most of the 48 calls; real prototypes
//     added (GetChecksum_2/GetFloat/GetStructure_2/ContainsFlag/AddChecksum/
//     fn_8012772C/fn_80127C14/CStruct_*).
//   * AddChecksum is 3-arg (obj, key, value) and fn_8012772C is 3-arg
//     (obj, key, f32): the m2c body dropped the object, sending the key in r3.
//   * The anim keys are the named QB constants (QB_TYPE/QB_WOBBLE/QB_BONEDANIM/
//     QB_DIFFERENCEANIM/QB_LOOKAT/QB_FLIPROTATE/QB_DIFFERENCEANIMNAME/
//     QB_STARTTIME/QB_ENDTIME/QB_BLENDPERIOD/QB_SPEED/QB_WOBBLETARGETALPHA/
//     QB_ANIMNAME/QB_LOOPTYPE/QB_FLIPPED/QB_LOOKATPARAMS/
//     QB_ENABLEDIFFERENCEANIM/QB_DIFFERENCEANIMAMOUNT), not m2c's bogus float
//     literals used as the key argument.
//   * The element walker advanced a `void **` by 4 (i.e. 16 bytes/iteration);
//     the WANT advances 4 BYTES.  Uses the matched sibling fn_80033360.c's
//     `Node *entries[6]` + `entries[i]` idiom (same Obj/Node/Vt shape).
//   * The look-at block was disabled by m2c as `if (0)`.  The WANT has TWO
//     separate `if (arg4 != 0)` blocks (the mfcr r29 / mtcrf 0x80,r29 pair is
//     GCC sharing the CR0 test across the calls between them), not one nested.
//   * The WOBBLE-target ctor call had garbage args `CStruct_new(arg0,arg1,arg2,8)`.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_80291B48;
extern f32 lbl_80291B4C;

/* vtable-ish dispatch header on each animation node (mirrors fn_80033360.c):
   +0x20 is the s16 `this` displacement, +0x24 the thunk. */
typedef struct {
    char pad0x0[0x20];
    s16 unk0x20;
    char pad0x22[0x2];
    s32 (*unk0x24)(void *, s32, void *, s32);
} Vt;

typedef struct {
    char pad0x0[0x14];
    Vt *unk0x14;
} Node;

typedef struct {
    char pad0x0[0x3C];
    s32 unk0x3C;
    Node *unk0x40[6];
    s32 unk0x58;
    f32 unk0x5C;
} Obj;

void fn_80032F18(Obj *);
void fn_80032FB4(Obj *, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void CStruct_delete(void *, s32);
void AddChecksum(void *, s32, s32);
void AddInteger(void *, s32, s32);
void fn_80032388(Obj *, void *);
s32 GetChecksum_2(void *, s32, s32 *, s32);
s32 ContainsFlag(void *, s32);
s32 GetFloat(void *, s32, f32 *, s32);
s32 GetStructure_2(void *, s32, s32 *, s32);
void fn_8012772C(void *, s32, f32);
void fn_80127C14(void *, s32, void *);

void fn_80032ACC(Obj *arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    struct { s32 sp8; f32 spC; s32 sp10; volatile double pad[4]; } fr;
#define sp8 fr.sp8
#define spC fr.spC
#define sp10 fr.sp10
    void *obj;
    s32 i;
    Node **entries;
    Node *node;
    Vt *vt;

    fn_80032F18(arg0);
    fn_80032FB4(arg0, arg1);
    arg0->unk0x3C = 2;
    arg0->unk0x5C = lbl_80291B48;
    if (arg2 == 3) {
        obj = CStruct_ctor(CStruct_new(8));
        AddChecksum(obj, QB_TYPE, QB_WOBBLE);
        fn_80032388(arg0, obj);
        if (obj != 0) {
            CStruct_delete(obj, 3);
        }
    } else {
        obj = CStruct_ctor(CStruct_new(8));
        AddChecksum(obj, QB_TYPE, QB_BONEDANIM);
        fn_80032388(arg0, obj);
        if (obj != 0) {
            CStruct_delete(obj, 3);
        }
    }
    sp8 = arg1;
    spC = lbl_80291B4C;
    if (arg4 != 0) {
        if ((GetChecksum_2(arg4, QB_DIFFERENCEANIMNAME, &sp8, 0) != 0) ||
            (ContainsFlag(arg4, QB_ENABLEDIFFERENCEANIM) != 0)) {
            GetFloat(arg4, QB_DIFFERENCEANIMAMOUNT, &spC, 0);
            obj = CStruct_ctor(CStruct_new(8));
            AddChecksum(obj, QB_TYPE, QB_DIFFERENCEANIM);
            fn_80032388(arg0, obj);
            if (obj != 0) {
                CStruct_delete(obj, 3);
            }
        }
    }
    if (arg4 != 0) {
        sp10 = 0;
        if (GetStructure_2(arg4, QB_LOOKATPARAMS, &sp10, 0) != 0) {
            obj = CStruct_ctor(CStruct_new(8));
            AddChecksum(obj, QB_TYPE, QB_LOOKAT);
            fn_80127C14(obj, 0, sp10);
            fn_80032388(arg0, obj);
            if (obj != 0) {
                CStruct_delete(obj, 3);
            }
        }
    }
    obj = CStruct_ctor(CStruct_new(8));
    AddChecksum(obj, QB_TYPE, QB_FLIPROTATE);
    AddInteger(obj, QB_FLIPPED, arg3);
    fn_80032388(arg0, obj);
    if (obj != 0) {
        CStruct_delete(obj, 3);
    }
    i = 0;
    obj = CStruct_ctor(CStruct_new(8));
    fn_8012772C(obj, QB_WOBBLETARGETALPHA, lbl_80291B4C);
    if (i < arg0->unk0x58) {
        entries = arg0->unk0x40;
        do {
            node = entries[i];
            vt = node->unk0x14;
            vt->unk0x24((char *)node + vt->unk0x20, QB_SETWOBBLETARGET, obj, 0);
            i++;
        } while (i < arg0->unk0x58);
    }
    if (obj != 0) {
        CStruct_delete(obj, 3);
    }
    i = 0;
    obj = CStruct_ctor(CStruct_new(8));
    AddChecksum(obj, QB_ANIMNAME, arg1);
    fn_8012772C(obj, QB_STARTTIME, farg0);
    fn_8012772C(obj, QB_ENDTIME, farg1);
    AddInteger(obj, QB_LOOPTYPE, arg2);
    fn_8012772C(obj, QB_BLENDPERIOD, farg2);
    fn_8012772C(obj, QB_SPEED, farg3);
    AddChecksum(obj, QB_DIFFERENCEANIMNAME, sp8);
    fn_8012772C(obj, QB_DIFFERENCEANIMAMOUNT, spC);
    if (i < arg0->unk0x58) {
        entries = arg0->unk0x40;
        do {
            node = entries[i];
            vt = node->unk0x14;
            vt->unk0x24((char *)node + vt->unk0x20, QB_PLAYSEQUENCE, obj, 0);
            i++;
        } while (i < arg0->unk0x58);
    }
    if (obj != 0) {
        CStruct_delete(obj, 3);
    }
}

// MEASURED 2026-10-16: 96.7% NEAR, size-exact 1100B
// (`test_wip_drafts.py --addr 0x80032ACC`, base flags, no extra_cflags).
// Frame exact (0x78, stmw r25, f28-f31); no inline asm, no flags.
// REVIEWED 2026-10-18 (random triage): arg2/arg3 home swap + int/float
// interleave is an allocation-order wall (all homes live-from-entry, so no
// source order reaches it; pins collapse). Body untouched.
