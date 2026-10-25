// WIP DRAFT (non-matching) — m2c body + hand fixes from disasm (PS-heavy).
// family=m2c range=0x801C84E8-0x801C8DEC size=2308B
// extra_cflags: -mps-float
// PARKED ~15%: body compiles but is DCE-shrunken (384B vs 2308B) because the
// m2c skeleton lost the paired-single webs producing most values. Rebuild
// roadmap (every idiom proven in src/wip/fn_801C7FF0.c, same session):
//   1. Intro @0x8510-0x85A8: pair diffs ps_sub (10005828/11AD6028), magnitude
//      mul/merge00(lbl_802ACD30)/madd/sum0 (fn_800A11D8 template), rsqrte+
//      res+muls0 normalize; duplicated pair stores sp28/sp30 + sp38/sp40.
//   2. fn_801C7FF0 args are (arg0, &sp118, &sp1E8); sp118 filled from arg1
//      pairs before the call.
//   3. Mid PS lerps: ps_muls0 (10000318/11ad0318/10000358/118c0358) +
//      ps_sel (vsel-labeled words) vs consts ACDE4/ACDE8/ACDEC/ACDF0;
//      results write back to *(arg0+0xC)+0x58/+0x60.
//   4. Tail @0x89AC-0x8DA8 = fn_801C7FF0's 16x fmadds + psq copy-out shape,
//      with its own li/mtctr/bdnz$ window @0x8994-0x89E4.
//   5. Cleanup: twin CObject_RemoveRefLink sites crossjump-merged — early-exit passes
//      r4=&spF0, normal path r4=arg2; both then stw r0,0xf0(r1).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802ACDD4;
extern char lbl_802ACDD8[];
extern f32 lbl_802ACDDC;
extern f32 lbl_802ACDE0;
extern f32 lbl_802ACDE4;
extern f32 lbl_802ACDE8;
extern f32 lbl_802ACDEC;
extern f32 lbl_802ACDF0;
void CObject_RemoveRefLink(CStruct *, CStruct *);
extern __ps_t lbl_802ACD30;
f32 fn_801C7FF0(Unk_C7387A53 *, Unk_EA529D06 *, f32 *);
void fn_8010794C(Unk_C7387A53 *);
void fn_80107AB4(void *, void *, void *);
void fn_80107A80(Unk_C5652918 *, s32, s32);
s32 fn_80107B20(Unk_E9DCA07D *, s32, void *);
f32 fn_8014030C(s32, s32, Unk_FFAD6788 *);

void fn_801C84E8(Unk_C7387A53 *arg0, void *arg1, void *arg2) {
    f32 sp250;
    f32 sp24C;
    f32 sp248;
    f32 sp244;
    f32 sp240;
    f32 sp230;
    f32 sp228;
    f32 sp224;
    f32 sp210;
    f32 sp208;
    f32 sp200;
    f32 sp1FC;
    f32 sp1E8;
    f32 sp1E4;
    f32 sp1E0;
    f32 sp1DC;
    f32 sp1D8;
    f32 sp1D4;
    f32 sp1D0;
    f32 sp1CC;
    f32 sp1C8;
    f32 sp1C4;
    f32 sp1C0;
    f32 sp1BC;
    f32 sp1B8;
    f32 sp1B4;
    f32 sp1B0;
    f32 sp1AC;
    f32 sp1A8;
    s32 sp168;
    s32 sp118;
    s32 spF0;
    s32 sp48;
    __ps_t sp28;
    __ps_t sp30;
    __ps_t sp38;
    __ps_t sp40;
    s32 sp18;
    s32 sp8;
    Unk_59AB5482 sp1F0;
    f32 sp218;
    f32 sp238;
    f32 temp_f11;
    f32 temp_f1;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    s32 var_ctr;
    void *temp_r29;
    Unk_DB0E2BAB *temp_r31;

    0;
    0;
    temp_r29 = arg0->unk0xC;
    /* NOTE: want 0x8518-0x8546 computes two pair differences
       d0 = *(__ps_t *)(m+0x58) - *(__ps_t *)(arg0+0x50)
       d1 = *(__ps_t *)(m+0x60) - *(__ps_t *)(arg0+0x58)   (m=*(arg0+0xC))
       via ps_sub f0,f0,f11 / ps_sub f13,f13,f12, stores BOTH pairs twice
       (sp28/sp30 AND sp38/sp40), then normalizes d1 (see PARKED note).
       Omitted here until the consuming webs below are rebuilt. */
    fn_8010794C(&sp48);
    0;
    temp_f29 = lbl_802ACDD4;
    if (0 > temp_f29) {
        0;
        sp1FC = *(f32 *)&lbl_802ACDD8;
        0;
    }
    temp_r29 = arg0->unk0xC;
    sp200 = fn_8014030C(QB_SKATER_FIRST_FORWARD_COLLISION_HEIGHT, 1, temp_r29);
    0;
    0;
    temp_f31 = fn_801C7FF0(arg0, &sp118, &sp1E8);
    temp_f11 = fabs(temp_f31);
    temp_f28 = lbl_802ACDDC;
    temp_f1 = fn_8012570C(arg0, arg1, QB_WALL_BOUNCE_DONT_SLOW_ANGLE, 1) * temp_f28;
    if (temp_f11 > temp_f1) {
        sp208 = *(s32 *)&lbl_802ACDD8 - ((temp_f11 - temp_f1) / (lbl_802ACDE0 - temp_f1));
        0;
        0;
    }
    0;
    0;
    0;
    0;
    sp210 = lbl_802ACDE4;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    if (0 > temp_f29) {
        sp224 = *(s32 *)&lbl_802ACDD8;
        0;
    }
    sp228 = sp218;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    sp230 = fn_8014030C(QB_SKATER_FIRST_FORWARD_COLLISION_LENGTH, 1, temp_r29);
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    if (sp238 > lbl_802ACDE8) {
        if (spF0 != 0) {
            goto block_16;
        }
    } else {
        fn_80107AB4(&sp48, &sp8, &sp18);
        fn_80107A80(&sp48, 0x10, 0);
        if ((fn_80107B20(&sp48, 1, 0) != 0) && ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0xC8) != 0)) {
            temp_f30 = temp_f28 * lbl_802ACDEC;
            temp_f31_2 = temp_f30 - sp1E8;
            sp248 = sinf(temp_f31_2);
            sp240 = cosf(temp_f31_2);
            sp24C = temp_f29;
            var_ctr = 4;
            sp244 = temp_f29;
            0;
            0;
            0;
            0;
            temp_r31 = arg0->unk0xC + 0x78;
            do {
                var_ctr -= 1;
            } while (var_ctr != 0);
            *((s32 *)&sp1F0) = fn_80003EB0(&sp168, temp_f30 - sp1E8);
            sp1F0.unk0x4 = temp_r31;
            sp1A8 = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0xC * temp_r31->unk0x30) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x8 * temp_r31->unk0x20) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x0 * temp_r31->unk0x0) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x4 * temp_r31->unk0x10)));
            sp1AC = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0xC * temp_r31->unk0x34) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x8 * temp_r31->unk0x24) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x0 * temp_r31->unk0x4) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x4 * temp_r31->unk0x14)));
            sp1B0 = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0xC * temp_r31->unk0x38) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x8 * temp_r31->unk0x28) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x0 * temp_r31->unk0x8) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x4 * temp_r31->unk0x18)));
            sp1B4 = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0xC * temp_r31->unk0x3C) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x8 * temp_r31->unk0x2C) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x0 * temp_r31->unk0xC) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x4 * temp_r31->unk0x1C)));
            sp1B8 = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x1C * temp_r31->unk0x30) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x18 * temp_r31->unk0x20) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x10 * temp_r31->unk0x0) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x14 * temp_r31->unk0x10)));
            sp1BC = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x1C * temp_r31->unk0x34) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x18 * temp_r31->unk0x24) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x10 * temp_r31->unk0x4) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x14 * temp_r31->unk0x14)));
            sp1C0 = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x1C * temp_r31->unk0x38) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x18 * temp_r31->unk0x28) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x10 * temp_r31->unk0x8) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x14 * temp_r31->unk0x18)));
            sp1C4 = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x1C * temp_r31->unk0x3C) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x18 * temp_r31->unk0x2C) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x10 * temp_r31->unk0xC) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x14 * temp_r31->unk0x1C)));
            sp1C8 = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x2C * temp_r31->unk0x30) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x28 * temp_r31->unk0x20) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x20 * temp_r31->unk0x0) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x24 * temp_r31->unk0x10)));
            sp1CC = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x2C * temp_r31->unk0x34) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x28 * temp_r31->unk0x24) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x20 * temp_r31->unk0x4) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x24 * temp_r31->unk0x14)));
            sp1D0 = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x2C * temp_r31->unk0x38) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x28 * temp_r31->unk0x28) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x20 * temp_r31->unk0x8) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x24 * temp_r31->unk0x18)));
            sp1D4 = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x2C * temp_r31->unk0x3C) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x28 * temp_r31->unk0x2C) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x20 * temp_r31->unk0xC) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x24 * temp_r31->unk0x1C)));
            sp1D8 = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x3C * temp_r31->unk0x30) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x38 * temp_r31->unk0x20) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x30 * temp_r31->unk0x0) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x34 * temp_r31->unk0x10)));
            sp1DC = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x3C * temp_r31->unk0x34) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x38 * temp_r31->unk0x24) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x30 * temp_r31->unk0x4) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x34 * temp_r31->unk0x14)));
            sp1E0 = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x3C * temp_r31->unk0x38) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x38 * temp_r31->unk0x28) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x30 * temp_r31->unk0x8) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x34 * temp_r31->unk0x18)));
            sp1E4 = (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x3C * temp_r31->unk0x3C) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x38 * temp_r31->unk0x2C) + ((((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x30 * temp_r31->unk0xC) + (((Unk_DB0E2BAB *)*((s32 *)&sp1F0))->unk0x34 * temp_r31->unk0x1C)));
            0;
            sp250 = lbl_802ACDF0;
            0;
            0;
            0;
            0;
            0;
            0;
            0;
        }
        if (spF0 != 0) {
block_16:
            CObject_RemoveRefLink(*(s32 *)((char *)&spF0), &spF0);
            spF0 = 0;
        }
    }
}
