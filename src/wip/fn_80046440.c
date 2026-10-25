// PARKED 2026-10-30: 12.26% -> 12.0% (DIFF).
// Shift-tolerant diff: 392 / 465 emitted instructions byte-identical (83.8%).
// The masked sweep score is CAPPED BY LENGTH, not by content: ngccc emits 465
// instructions where retail has 468, so test_wip_drafts' index-aligned compare
// mis-lists every word after the 3-word divergence (want[62]) and the official
// number stays near baseline.  See WHY PARKED.
// family=m2c range=0x80046440-0x80046B90 size=1872B
//
// WHY PARKED: the three QB-selection arms each end in an IDENTICAL 3-instruction
// tail (r27 = r1+0x34, r19 = r1+0x38, r17 = r1+0x40) and retail keeps all
// THREE copies.  cc1 2.95.2 `cross_jumping` tail-merges arm 1 into arm 2's
// block, so only 2 copies survive and the object is 4 bytes x 3 short.  The
// merge is INVARIANT: all six permutations of the triple inside arm 1, the
// full 9-statement tail permutation, a goto state machine instead of the
// if/else chain, `volatile` on the frame struct / on fr.p48 / on fr.p4c,
// `asm volatile("")` at three tail positions, `"+r"` barriers, `goto` labels,
// an explicit address-format change (`&fr.n34` vs `(s32*)((char*)base+0x2C)`
// vs `&fr.grp[0]`), inline `__asm__("addi %0,1,0x34")` births (which even
// the assembler cannot cross-jump away), and ALL FIVE in-tree ProDG builds
// (3.5 / 3.5b140 / 3.7 / 3.8.1 / 3.9.3) produce byte-identical 465-insn
// output.  cc1 has no -fno-crossjumping / -fno-reorder-blocks; -fno-thread-jumps
// is a no-op here.  This is a split-TU / inline origin artefact, not a source
// shape.  SECONDARY (cosmetic, both 4 words or fewer): the seven element3d
// f32 pointers take {r19..r26} in ngccc vs retail's {r20..r26} - one member of
// the permuted group would need a hard-reg pin, and pinning r19 measured 61.5%.
// THIRD: retail's `or. r30,r3,r3` NULL test on the QB_SECTOR lookup vs
// ngccc's `cmpwi r3,0` (1 word, §6dp-3 pins this but is worth nothing while
// the length is wrong).
//
// LOAD-BEARING RECIPE (all others were neutral): ONE
// `register s32 r30 __asm__("r30")` pin on the single recycled sector-loop
// counter/enum-result web.  It is worth ~+16 aligned points (66.9% -> 82.9%)
// and it fixes the ENTIRE callee-saved colour map in one edit - without it
// every saved-register home in the function is one slot off.  It is NOT one of
// the usual "pick a register" pins: the pin does not choose a colour, it stops
// the loop IV and the QB_SECTOR/QB_SECTORS enum result from being split into
// two webs that then take two callee-saved homes.  The three empty
// `asm volatile("")` barriers in the arm tails are MEASURED INERT (83.55% ->
// 83.76%, i.e. one word) and are kept only for that one word.
//
// OTHER FIXES THAT EACH MOVED THE SCORE (semantic, all verified): the
// `fn_800F078C` call is 2-arg (retail materialises obj+0x510 in r4, so the
// callee is `void fn_800F078C(void*,void*)` - §6dc/§6di); the final out-param
// read is `obj->n578 = fr.n44` (r1 displacement) and NOT `*r14` (§6e);
// the three m2c `0;` stubs are six `__ps_t` pair copies under -mps-float
// (§6dq/§6ec); the QB_SECTORS loop is the rotated goto form with the compare
// on `*(s32*)((char*)fr.n2c + 4)` (§6dm-2/§6ag-1); the frame is ONE
// `FR_t` struct at r1+8 so every stack displacement lands (§6fa, and
// `fr.n34/n38/f3c/n40` must be 4-byte-slotted with `char` pads - §6de/§6dy);
// the QB_MODELS test is a 4-term `!=` chain whose fourth branch is `beq`
// (§4p-10/§6b-1).
//
// UNTIED LEVER: defeat the tail-merge itself.  Nothing in C or in the flag set
// does it (see above), so this would need either a compiler-side change or
// accepting the 3-instruction gap and scoring with a shift-tolerant diff.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* the element3d component object; direct stores only */
typedef struct {
    char _000[0x520];
    s32 n520;
    s32 n524;
    s32 n528;
    s32 n52C;
    s32 n530;
    char _534[4];
    char _538[0xC];
    f32 f544;
    s32 v548, v54C, v550;
    f32 f554;
    char _558[0x14];
    s32 n56C;
    f32 f570, f574;
    s32 n578, n57C, n580, n584, n588;
} E3_t;

/* the frame slot map, r1+8 .. r1+0x50 */
typedef struct {
    f32 v8[4];
    f32 v18[4];
    s32 n28;
    s32 n2c;
    s32 n30;
    s32 n34;
    s32 n38;
    f32 f3c;
    s32 n40;
    s32 n44;
    void *p48;
    void *p4c;
} FR_t;

extern f32 lbl_8029281C;
extern f32 lbl_80292820;
extern f32 lbl_80292824;
extern f32 lbl_80292828;
extern f32 lbl_8029282C;
extern char lbl_80292810[];

void CScreenElement_SetProperties(void *);
s32 fn_80128978(s32, s32);
void fn_8004602C(void *);
void fn_8004631C(void *, void *, s32 *);
void AddChecksum(CStruct *, s32, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetVector(CStruct *, s32, CStruct *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_80129528(CStruct *, s32);
s32 fn_80128424(CStruct *, void *, CStruct *, s32);
void fn_800460CC(void *);
void fn_80047D7C(void *);
void fn_800F0F84(s32, s32);
void fn_800F078C(void *, void *);

void fn_80046440(E3_t *obj, CStruct *cs) {
    FR_t fr;
    f32 *r15, *r16, *r18, *r20, *r21, *r22, *r23, *r24, *r25, *r26;
    s32 *r14, *r17, *r19, *r27;
    s32 r28;
    register s32 r30 __asm__("r30");
    f32 *base;
    CStruct *ent;

    CScreenElement_SetProperties(obj);
    base = (f32 *)&fr;
    fr.v8[0] = lbl_8029281C;
    base[2] = lbl_8029281C;
    base[3] = lbl_80292820;
    base[1] = lbl_8029281C;
    if (fn_80128978((s32)cs, QB_SKELETONNAME) != 0 ||
        fn_80128978((s32)cs, QB_CLONEMODEL) != 0 ||
        fn_80128978((s32)cs, QB_MODEL) != 0 ||
        fn_80128978((s32)cs, QB_MODELS) != 0) {
        r21 = (f32 *)((char *)obj + 0x4B4);
        fn_8004602C(obj);
        r20 = (f32 *)((char *)obj + 0x4B8);
        *(volatile __ps_t *)&fr.v18[2] = *(__ps_t *)&fr.v8[2];
        r24 = (f32 *)((char *)obj + 0x4BC);
        *(volatile __ps_t *)&fr.v18[0] = *(__ps_t *)&fr.v8[0];
        r23 = (f32 *)((char *)obj + 0x4C0);
        r26 = (f32 *)((char *)obj + 0x4C4);
        r22 = (f32 *)((char *)obj + 0x4C8);
        r25 = (f32 *)((char *)obj + 0x4CC);
        fn_8004631C(obj, cs, (s32 *)fr.v18);
        r16 = (f32 *)((char *)obj + 0x528);
        fr.p48 = (char *)obj + 0x570;
        r27 = &fr.n34;
        r15 = (f32 *)((char *)obj + 0x588);
        fr.p4c = (char *)obj + 0x574;
        __asm__ volatile("");
        r19 = &fr.n38;
        r18 = (f32 *)((char *)obj + 0x548);
        r17 = &fr.n40;
        r14 = &fr.n44;
    } else {
        r30 = fn_80128978((s32)cs, QB_SECTOR);
        if (r30 != 0) {
            r21 = (f32 *)((char *)obj + 0x4B4);
            fn_8004602C(obj);
            r20 = (f32 *)((char *)obj + 0x4B8);
            AddChecksum(cs, QB_CLASS, QB_LEVELOBJECT);
            r24 = (f32 *)((char *)obj + 0x4BC);
            GetChecksum_2(cs, QB_SECTOR, &fr.n28, 1);
            r23 = (f32 *)((char *)obj + 0x4C0);
            r26 = (f32 *)((char *)obj + 0x4C4);
            AddChecksum(cs, QB_NAME, fr.n28);
            r22 = (f32 *)((char *)obj + 0x4C8);
            r25 = (f32 *)((char *)obj + 0x4CC);
            *(volatile __ps_t *)&fr.v18[2] = *(__ps_t *)&fr.v8[2];
            r27 = &fr.n34;
            *(volatile __ps_t *)&fr.v18[0] = *(__ps_t *)&fr.v8[0];
            r16 = (f32 *)((char *)obj + 0x528);
            r15 = (f32 *)((char *)obj + 0x588);
            r18 = (f32 *)((char *)obj + 0x548);
            fn_8004631C(obj, cs, (s32 *)fr.v18);
            fr.p48 = (char *)obj + 0x570;
            __asm__ volatile("");
            r19 = &fr.n38;
            fr.p4c = (char *)obj + 0x574;
            r17 = &fr.n40;
            r14 = &fr.n44;
        } else {
            r30 = fn_80128978((s32)cs, QB_SECTORS);
            r21 = (f32 *)((char *)obj + 0x4B4);
            r20 = (f32 *)((char *)obj + 0x4B8);
            fr.p48 = (char *)obj + 0x570;
            r24 = (f32 *)((char *)obj + 0x4BC);
            fr.p4c = (char *)obj + 0x574;
            r23 = (f32 *)((char *)obj + 0x4C0);
            r26 = (f32 *)((char *)obj + 0x4C4);
            r22 = (f32 *)((char *)obj + 0x4C8);
            r25 = (f32 *)((char *)obj + 0x4CC);
            r27 = &fr.n34;
            r16 = (f32 *)((char *)obj + 0x528);
            r15 = (f32 *)((char *)obj + 0x588);
            __asm__ volatile("");
            r19 = &fr.n38;
            r18 = (f32 *)((char *)obj + 0x548);
            r17 = &fr.n40;
            r14 = &fr.n44;
            if (r30 != 0) {
                r28 = 0;
                fn_8004602C(obj);
                AddChecksum(cs, QB_CLASS, QB_LEVELOBJECT);
                fr.n2c = 0;
                GetArray(cs, QB_SECTORS, &fr.n2c, 0);
                goto ltest;
            lbody:
                ent = (CStruct *)fn_80129528((CStruct *)fr.n2c, r28);
                r28 += 1;
                r30 = (s32)ent;
                GetChecksum_2(ent, 0, &fr.n30, 0);
                AddChecksum(cs, QB_NAME, fr.n30);
                GetVector(ent, 0, (CStruct *)fr.v8, 0);
                *(volatile __ps_t *)&fr.v18[0] = *(__ps_t *)&fr.v8[0];
                *(volatile __ps_t *)&fr.v18[2] = *(__ps_t *)&fr.v8[2];
                fn_8004631C(obj, cs, (s32 *)fr.v18);
            ltest:
                if ((u32)r28 < (u32) *(s32 *)((char *)fr.n2c + 4)) {
                    goto lbody;
                }
            }
        }
    }
    GetFloat(cs, QB_CAMERAZ, r21, 0);
    GetFloat(cs, QB_ANGLEX, r20, 0);
    GetFloat(cs, QB_ANGLEY, r24, 0);
    GetFloat(cs, QB_ANGLEZ, r23, 0);
    GetFloat(cs, QB_ANGVELX, r26, 0);
    GetFloat(cs, QB_ANGVELY, r22, 0);
    GetFloat(cs, QB_ANGVELZ, r25, 0);
    if (ContainsFlag(cs, QB_ANGLEORDERXYZ) != 0) {
        obj->n524 = 0;
    }
    if (ContainsFlag(cs, QB_ANGLEORDERXZY) != 0) {
        obj->n524 = 1;
    }
    if (ContainsFlag(cs, QB_ANGLEORDERYXZ) != 0) {
        obj->n524 = 2;
    }
    if (ContainsFlag(cs, QB_ANGLEORDERYZX) != 0) {
        obj->n524 = 3;
    }
    if (ContainsFlag(cs, QB_ANGLEORDERZXY) != 0) {
        obj->n524 = 4;
    }
    if (ContainsFlag(cs, QB_ANGLEORDERZYX) != 0) {
        obj->n524 = 5;
    }
    if (ContainsFlag(cs, QB_DISABLEPOINTING) != 0) {
        obj->n520 = 0;
    }
    r30 = 0;
    fr.n34 = 0;
    if (GetChecksum_2(cs, QB_NODETOPOINTTO, &fr.n34, 0) != 0) {
        fn_800F0F84(fr.n34, 1);
        fn_800F078C((void *)cs, (char *)obj + 0x510);
        obj->n520 = 1;
    }
    obj->n528 = 0;
    if (GetChecksum_2(cs, QB_OBJECTTOPOINTTO, (s32 *)r16, 0) != 0) {
        obj->n520 = 2;
    }
    r28 = *(s32 *)&lbl_8029281C;
    obj->n588 = r28;
    GetFloat(cs, QB_TILT, r15, 0);
    obj->n52C = r28;
    obj->n530 = 0;
    fr.n38 = 0;
    if (GetStructure_2(cs, 0x00CA1C41, &fr.n38, 0) != 0) {
        GetFloat((CStruct *)fr.n38, QB_AMP, (f32 *)((char *)obj + 0x52C), 0);
        fr.f3c = lbl_80292820;
        GetFloat((CStruct *)fr.n38, QB_FREQ, &fr.f3c, 0);
        obj->n530 = (s32)(lbl_80292824 / fr.f3c);
    }
    obj->n580 = 0;
    obj->n57C = 0;
    obj->n584 = 0;
    obj->v548 = r28;
    ((s32 *)r18)[2] = r28;
    ((f32 *)r18)[3] = lbl_80292820;
    ((s32 *)r18)[1] = r28;
    fr.n40 = 0;
    if (GetStructure_2(cs, QB_PARENTPARAMS, &fr.n40, 0) != 0) {
        GetChecksum_2((CStruct *)fr.n40, QB_NAME, (s32 *)((char *)obj + 0x57C), 0);
        GetVector((CStruct *)fr.n40, 0, (CStruct *)r18, 0);
        if (GetInteger((CStruct *)fr.n40, QB_SKATER, (s32 *)((char *)obj + 0x580), 0) != 0) {
            obj->n57C = QB_SKATER;
        }
        GetChecksum_2((CStruct *)fr.n40, QB_NODE, (s32 *)((char *)obj + 0x584), 0);
    }
    if (ContainsFlag(cs, QB_SCALE_TO_SCREEN_DIMS) != 0) {
        fn_800460CC(obj);
    } else if (fn_80128424(cs, (void *)lbl_80292810, (CStruct *)((char *)obj + 0x538), 0) != 0) {
        obj->f544 = lbl_80292820;
    }
    obj->n56C = ContainsFlag(cs, QB_SCALEWITHDISTANCE);
    obj->f570 = lbl_80292828;
    GetFloat(cs, QB_SCALEMULTIPLIER, (f32 *)fr.p48, 0);
    obj->f574 = lbl_8029282C;
    GetFloat(cs, QB_MAXSCALE, (f32 *)fr.p4c, 0);
    if (GetInteger(cs, QB_ACTIVE_VIEWPORT, r14, 0) != 0) {
        obj->n578 = fr.n44;
        fn_80047D7C(obj);
    }
}
