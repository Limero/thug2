// WIP DRAFT (non-matching) - PARKED 0.2%: m2c statics-DCE husk (26 phantom
// family=m2c range=0x802134A0-0x80213E48 size=2472B
// file-scope spN statics; body DCE-eaten). >1.5KB timebox rule: structural
// park with decode notes, no verified rebuild attempted.
// DECODE SKETCH (2026-08-25, first 40 insns + prologue audit):
// frame 0x230; mfcr r12 saved @0x158 (doc-28 long-range CR class);
// saves f14-f31 (18 stfd @0x1a0-0x228) + stmw r15-r31 @0x15c — heaviest
// FPR saver of the group; needs -mps-float + N-dummy/frame-template work
// (§6ac-9 caveat: N>1 dummy coalescing unreliable, prefer frame struct).
// Opens: mgr=*(arg0+0x184c); guard *(mgr+0x28)==0 bne far-exit(13d98);
// page anchors lis r29(-0x7fd0)/r9(-0x7fd5); r11=*(page+0x5eac)
// [lbl_80305EAC chase]; args r5=arg0+0x28/r6=arg0+0x810/r7=arg0+0x824;
// lfs f1=const -0x96c(lbl_802AF694); big call setup follows (mr r15/r26/r16
// param homes). Body per m2c husk: ~600 insns, hash-dispatch + list walks +
// heavy PS math (not yet decoded). Full rebuild = a large job.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 0.8% ([8]rev->0.8%).
// UPDATED 2026-09-18: 1.0% -> 1.1%. m2c SCALED POINTER ARITHMETIC bug:
// (T *)((T *)(X) + off) adds off * sizeof(T) bytes because the offset sits
// OUTSIDE the cast, while the binary uses a byte displacement (2 cast(s) in
// this body).  Recasing the base to char * keeps the deref type and makes the
// arithmetic byte-wise; automated A/B via tools/fix_scaled_ptr.py (same recipe
// class as tools/raw_sym_scan.py).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -Os
extern char lbl_80305EAC[];
extern char lbl_802AF694[];
extern f32 lbl_802AF698;
extern char lbl_80301A38[];
static s32 sp14;
static s32 sp148;
static s32 sp18;
static s32 sp1C;
static s32 sp20;
static s32 sp24;
static s32 sp28;
static s32 sp2C;
static s32 sp30;
static s32 sp34;
static s32 sp38;
static s32 sp3C;
static s32 sp40;
static s32 sp44;
static s32 sp50;
static s32 sp54;
static s32 sp60;
static s32 sp64;
static s32 sp6C;
static s32 sp70;
static s32 sp74;
static s32 sp78;
static s32 sp7C;
static s32 sp80;
static s32 sp84;
static s32 spC;

s32 fn_802134A0(Unk_F94F30DE *arg0) {
    s32 sp158;
    f32 sp150;
    f32 sp138;
    f32 sp130;
    f32 sp128;
    f32 sp120;
    f32 sp11C;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp100;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp68;
    f32 sp5C;
    f32 sp58;
    f32 sp4C;
    f32 sp48;
    Unk_59AB5482 sp8;
    f32 *temp_r3;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f10_3;
    f32 temp_f10_4;
    f32 temp_f11;
    f32 temp_f11_2;
    f32 temp_f11_3;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f13_3;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f20;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f25;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f31;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 temp_f4_4;
    f32 temp_f5;
    f32 temp_f5_2;
    f32 temp_f5_3;
    f32 temp_f5_4;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f7;
    f32 temp_f7_2;
    f32 temp_f7_3;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 temp_f8_3;
    f32 temp_f9;
    s32 temp_cr0_eq;
    s32 temp_r30;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_r28;
    void *temp_r5;
    void *temp_r6;
    void *temp_r7;
    Unk_C7387A53 *temp_r9;
    Unk_C7387A53 *temp_r9_2;
    void *var_r29;

    sp158 = 0;
    temp_r30 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x184C) + 0x28);
    if (temp_r30 == 0) {
        temp_r5 = (char *)arg0 + 0x28;
        temp_r6 = (char *)arg0 + 0x810;
        temp_r7 = (char *)arg0 + 0x824;
        var_r28 = fn_801AD5DC(*(s32 *)((char *)(*(void **)(s32)lbl_80305EAC) + 0x28), (char *)arg0 + 0x70, temp_r5, temp_r6, temp_r7, 0, 0.0f, *(f32 *)&lbl_802AF694);
        if (var_r28 != 0) {
            arg0->unk0x828 = temp_r30;
            arg0->unk0x820 = (f32 *) *(s32 *)((char *)(*(void **)(s32)lbl_80305EAC) + 0x28);
        } else {
            temp_f0 = *(s32 *)&lbl_802AF694;
            arg0->unk0x34 = temp_f0;
            arg0->unk0x7C = temp_f0;
            var_r29 = fn_800A200C(*(s32 *)&lbl_80301A38, QB_RAILMANAGER);
            if (var_r29 != NULL) {
loop_5:
                fn_800EF294(&sp8, var_r29);
                var_ctr = 4;
                do {
                    var_ctr -= 1;
                } while (var_ctr != 0);
                var_ctr_2 = 4;
                0;
                0;
                0;
                0;
                0;
                0;
                do {
                    var_ctr_2 -= 1;
                } while (var_ctr_2 != 0);
                sp10C = (sp5C * sp74) - (sp6C * sp64);
                spF0 = (sp58 * sp84) - (sp78 * sp64);
                sp100 = (sp58 * sp80) - (sp78 * sp60);
                temp_f3 = (sp70 * sp84) - (sp80 * sp74);
                temp_f24 = (sp5C * sp84) - (sp7C * sp64);
                temp_f31 = (sp68 * sp84) - (sp78 * sp74);
                temp_f27 = (sp6C * sp84) - (sp7C * sp74);
                temp_f2 = (sp6C * sp80) - (sp7C * sp70);
                temp_f5 = (sp60 * sp84) - (sp80 * sp64);
                sp108 = sp78 * sp5C;
                temp_f20 = (sp58 * sp74) - (sp68 * sp64);
                temp_f4 = (sp60 * sp74) - (sp70 * sp64);
                temp_f28 = sp6C * sp60;
                sp110 = temp_f28;
                spD8 = sp60 * temp_f27;
                spE0 = sp60 * temp_f31;
                temp_f26 = (sp68 * sp80) - (sp78 * sp70);
                temp_f1 = (sp5C * sp80) - (sp7C * sp60);
                sp150 = sp50 * temp_f31;
                spF4 = sp50 * spF0;
                temp_f25 = (sp48 * sp10C) - (sp4C * temp_f20);
                sp114 = temp_f25;
                temp_f28_2 = (sp58 * sp7C) - sp108;
                spF8 = (sp48 * temp_f5) - spF4;
                temp_f7 = (sp68 * sp7C) - (sp78 * sp6C);
                temp_f8 = (sp5C * temp_f3) - spD8;
                spB8 = -((sp60 * temp_f7) + ((sp58 * temp_f2) - (sp5C * temp_f26)));
                spDC = temp_f8;
                spE4 = (sp58 * temp_f3) - spE0;
                spA4 = (sp54 * ((sp58 * sp70) - (sp68 * sp60))) + ((sp48 * temp_f4) - (sp50 * temp_f20));
                spBC = (sp50 * temp_f7) + ((sp48 * temp_f2) - (sp4C * temp_f26));
                spC0 = -((sp50 * temp_f28_2) + ((sp48 * temp_f1) - (sp4C * sp100)));
                sp8C = -((sp54 * temp_f2) + ((sp4C * temp_f3) - (sp50 * temp_f27)));
                spA8 = (sp64 * temp_f7) + ((sp58 * temp_f27) - (sp5C * temp_f31));
                sp9C = (sp54 * temp_f26) + ((sp48 * temp_f3) - sp150);
                spB4 = -((sp54 * ((sp58 * sp6C) - (sp68 * sp5C))) + temp_f25);
                spAC = -((sp54 * temp_f7) + ((sp48 * temp_f27) - (sp4C * temp_f31)));
                sp94 = -((sp54 * ((sp5C * sp70) - sp110)) + ((sp4C * temp_f4) - (sp50 * sp10C)));
                sp88 = (sp64 * temp_f2) + temp_f8;
                sp98 = -((sp64 * temp_f26) + spE4);
                spA0 = -((sp54 * sp100) + spF8);
                sp90 = (sp54 * temp_f1) + ((sp4C * temp_f5) - (sp50 * temp_f24));
                spB0 = (sp54 * temp_f28_2) + ((sp48 * temp_f24) - (sp4C * spF0));
                temp_f11 = sp68;
                temp_f10 = sp58;
                temp_f0_2 = sp5C;
                temp_f24_2 = *(s32 *)&lbl_802AF694;
                spC4 = (sp50 * ((temp_f10 * sp6C) - (temp_f11 * temp_f0_2))) + ((sp48 * ((temp_f0_2 * sp70) - temp_f28)) - (sp4C * ((temp_f10 * sp70) - (temp_f11 * sp60))));
                temp_f4_2 = (sp68 * sp84) - (sp78 * sp74);
                temp_f27_2 = (sp6C * sp84) - (sp7C * sp74);
                sp11C = temp_f4_2;
                temp_f11_2 = (sp70 * sp84) - (sp80 * sp74);
                temp_f12 = (sp68 * sp80) - (sp78 * sp70);
                temp_f13 = (sp6C * sp80) - (sp7C * sp70);
                temp_f1_2 = (sp68 * sp7C) - (sp78 * sp6C);
                temp_f2_2 = ((sp50 * ((sp64 * temp_f1_2) + ((sp58 * temp_f27_2) - (sp5C * sp11C)))) + ((sp48 * ((sp64 * temp_f13) + ((sp5C * temp_f11_2) - (sp60 * temp_f27_2)))) - (sp4C * ((sp64 * temp_f12) + ((sp58 * temp_f11_2) - (sp60 * temp_f4_2)))))) - (sp54 * ((sp60 * temp_f1_2) + ((sp58 * temp_f13) - (sp5C * temp_f12))));
                if (temp_f2_2 != temp_f24_2) {
                    temp_f2_3 = temp_f24_2 / temp_f2_2;
                    if (temp_f2_3 != temp_f24_2) {
                        sp138 = temp_f2_3;
                        sp120 = temp_f2_3;
                        sp128 = temp_f2_3;
                        sp130 = temp_f2_3;
                        0;
                        0;
                        0;
                        0;
                        0;
                        0;
                    }
                }
                0;
                temp_f10_2 = arg0->unk0x74;
                0;
                temp_f4_3 = arg0->unk0x70;
                0;
                0;
                0;
                temp_f5_2 = arg0->unk0x78;
                temp_f6 = arg0->unk0x7C;
                0;
                sp98 = (temp_f6 * sp78) + ((temp_f5_2 * sp68) + ((temp_f4_3 * sp48) + (temp_f10_2 * sp58)));
                sp9C = (temp_f6 * sp7C) + ((temp_f5_2 * sp6C) + ((temp_f4_3 * sp4C) + (temp_f10_2 * sp5C)));
                spA0 = (temp_f6 * sp80) + ((temp_f5_2 * sp70) + ((temp_f4_3 * sp50) + (temp_f10_2 * sp60)));
                0;
                spB0 = temp_f13_3;
                temp_f13_3 = (temp_f13_2 * sp80) + temp_f10_4;
                spB4 = temp_f9;
                temp_f10_4 = (temp_f10_3 * sp70) + temp_f12_3;
                spAC = temp_f2_4;
                temp_f9 = (temp_f13_2 * sp84) + temp_f7_2;
                spA8 = temp_f3_2;
                temp_f2_4 = (temp_f13_2 * sp7C) + ((temp_f10_3 * sp6C) + ((temp_f12_2 * sp4C) + (temp_f0_3 * sp5C)));
                temp_f3_2 = (temp_f13_2 * sp78) + temp_f1_3;
                spA4 = temp_f6_2;
                temp_f1_3 = (temp_f10_3 * sp68) + ((temp_f12_2 * sp48) + (temp_f0_3 * sp58));
                temp_f6_2 = (temp_f6 * sp84) + temp_f5_3;
                temp_f7_2 = (temp_f10_3 * sp74) + temp_f8_2;
                temp_f12_3 = (temp_f12_2 * sp50) + (temp_f0_3 * sp60);
                temp_f5_3 = (temp_f5_2 * sp74) + temp_f4_4;
                temp_f8_2 = (temp_f12_2 * sp54) + temp_f11_3;
                temp_f13_2 = arg0->unk0x34;
                temp_f10_3 = arg0->unk0x30;
                temp_f11_3 = temp_f0_3 * sp64;
                temp_f4_4 = (temp_f4_3 * sp54) + (temp_f10_2 * sp64);
                temp_f12_2 = arg0->unk0x28;
                temp_f0_3 = arg0->unk0x2C;
                0;
                0;
                temp_r9 = ((Unk_C8FEE62D *)var_r29)->unk0x18;
                ((s32 (*)(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32))temp_r9->unk0x74)(var_r29 + temp_r9->unk0x70, temp_f1_3, temp_f2_4, temp_f3_2, temp_f4_4, temp_f5_3, temp_f6_2, temp_f7_2, temp_f8_2, temp_f9, temp_f10_4, temp_f11_3, temp_f12_3, temp_f13_3);
                var_r28 = fn_801AD5DC(&sp88, &sp98, temp_r6, temp_r7, NULL, 0, *(s32 *)&lbl_802AF694);
                0;
                if (var_r28 != 0) {
                    temp_r9_2 = ((Unk_C8FEE62D *)var_r29)->unk0x18;
                    temp_r3 = ((s32 (*)(void *))temp_r9_2->unk0x74)(var_r29 + temp_r9_2->unk0x70);
                    temp_f8_3 = arg0->unk0x814;
                    temp_f5_4 = arg0->unk0x810;
                    temp_f7_3 = arg0->unk0x818;
                    temp_f12_4 = arg0->unk0x81C;
                    spB8 = (temp_f12_4 * sp38) + ((temp_f7_3 * sp28) + ((temp_f5_4 * *((f32 *)&sp8)) + (temp_f8_3 * sp18)));
                    spBC = (temp_f12_4 * sp3C) + ((temp_f7_3 * sp2C) + ((temp_f5_4 * spC) + (temp_f8_3 * sp1C)));
                    arg0->unk0x820 = temp_r3;
                    spC0 = (temp_f12_4 * sp40) + ((temp_f7_3 * sp30) + ((temp_f5_4 * sp8.unk0x8) + (temp_f8_3 * sp20)));
                    0;
                    spC4 = (temp_f12_4 * sp44) + ((temp_f7_3 * sp34) + ((temp_f5_4 * sp14) + (temp_f8_3 * sp24)));
                    0;
                    0;
                    arg0->unk0x828 = (s32) ((Unk_C8FEE62D *)var_r29)->unk0xC;
                }
                var_r29 = ((Unk_C8FEE62D *)var_r29)->unk0x14;
                temp_cr0_eq = var_r29 == NULL;
                if ((temp_cr0_eq == 0) && (temp_cr0_eq != 0)) {
                    goto loop_5;
                }
            }
        }
        if ((var_r28 != 0) && (fn_801E6F54(arg0->unk0x1858, arg0->unk0x824, arg0->unk0x820, 1) != 0)) {
            fn_80107998(&sp8, temp_r5, temp_r6);
            if (fn_80107B20(&sp8, 1, 0) != 0) {
                0;
                0;
                0;
                0;
                0;
                0;
                if (sp148 > lbl_802AF698) {
                    if ((s32) spB0 != 0) {
                        CObject_RemoveRefLink();
                        spB0 = 0.0f;
                    }
                    goto block_22;
                }
            }
            fn_80125A3C(QB_OUTPUT_TRACKING_LINES, 1);
            arg0->unk0x808 = 1;
            arg0->unk0x80 = QB_RAIL;
            if ((s32) spB0 != 0) {
                CObject_RemoveRefLink();
                spB0 = 0.0f;
            }
            0;
            return 1;
        }
        goto block_22;
    }
block_22:
    0;
    return 0;
}
