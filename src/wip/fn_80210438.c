// WIP DRAFT — decode-documented park (groupB PS zone, 2026-08-25)
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 5.5703% -> 9.1864% per-object flags: -Os -fno-rerun-cse-after-loop -> -fno-schedule-insns2
// PARKED (m2c husk retained; hand rebuild not completed).
// 1440B (360 insns), frame 0x180, saves f30/f31 + r25-r31 (7 GPRs).
// Largest of the zone family: opens mr r31,arg0; r30=*(arg0+0x183c);
// bl fn_80213e48; stores lis/ori const 0x439F4704 to arg0+0x80;
// bl fn_802109D8(arg0) [the sibling function!]; then long sequence:
// ~34 calls, 20 op4 words (all standard emittable PS), ~60 psq pairs.
// Rebuild order hint: do AFTER fn_802109D8 cracks (its callee facts feed
// this one); expect the full doc-15/doc-32/allocator-wall set.
// family=m2c range=0x80210438-0x802109D8 size=1440B
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80108104(void *);
s32 Mem_Alloc2(s32);
// FLAG: -fno-schedule-insns2
s32 fn_80107AA0(void *, void *);
s32 fn_8020E014(void *);
s32 *fn_80108F94(s32);                                
void fn_80210438(Unk_75ACDAE8 *arg0) {
    f32 sp128;
    f32 sp120;
    f32 sp11C;
    f32 sp118;
    Unk_59AB5482 sp108;
    s32 spF0;
    s32 sp48;
    Unk_59AB5482 sp38;
    s32 sp28;
    s32 sp18;
    s32 sp8;
    s32 *temp_r26;
    s32 *temp_r27;
    s32 *temp_r29;
    s32 *temp_r30_4;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f13;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f8;
    f32 temp_f9;
    s32 temp_r28;
    s32 temp_r30_2;
    s32 temp_r30_3;
    s32 temp_r3;
    s32 var_r30;
    CStruct *temp_r11;
    Unk_C8FEE62D *temp_r29_2;
    void *temp_r30;
    CStruct *temp_r8;
    temp_r30 = arg0->unk0x183C;
    fn_80213E48();
    arg0->unk0x80 = QB_AIR;
    fn_802109D8(arg0);
    temp_r3 = fn_8020E014(arg0);
    if (temp_r3 == 0) {
        arg0->unk0x1948 = temp_r3;
    }
    if ((s32 *) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x184C) + 0x30) == NULL) {
        temp_r26 = (char *)arg0 + 0x28;
        fn_80214308(arg0);
        fn_80210D10(arg0);
        temp_f1 = fn_802156FC(arg0);
        temp_f9 = arg0->unk0x88;
        temp_r8 = (char *)arg0 + 0x1980;
        sp120 = temp_f9;
        temp_f1_2 = -temp_f1;
        0;
        0;
        sp128 = temp_f9;
        0;
        temp_f8 = arg0->unk0x48;
        0;
        0;
        arg0->unk0x48 = (f32) ((temp_f1_2 * temp_f9) + temp_f8);
        0;
        0;
        0;
        0;
        temp_f13 = arg0->unk0x2C + ((temp_f8 * temp_f9) + (temp_f1_2 * *(f32 *)0x802AF5A4 * (temp_f9 * temp_f9)));
        0;
        arg0->unk0x2C = temp_f13;
        if (temp_f13 > arg0->unk0x1990) {
            temp_f0 = *(f32 *)0x802AF5A8;
            arg0->unk0x1980 = temp_f0;
            *((f32 *)&temp_r8->unk0xC) = (f32) *(f32 *)0x802AF5AC;
            temp_r8->unk0x8 = temp_f0;
            temp_r8->unk0x4 = temp_f0;
        }
        temp_r29 = (char *)arg0 + 0x70;
        fn_801ED360(arg0->unk0x1858);
        fn_80210F58(arg0, temp_r29, temp_r26);
        if (((s32) arg0->unk0x1C == 1) && ((s32 *) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x184C) + 0x30) == NULL)) {
            if (((s32) ((Unk_FFAD6788 *)temp_r30)->unk0x128 != 0) && ((s32) arg0->unk0xAC == 0) && (((u32) (arg0->unk0x24 - 2) > 2U) || (temp_r30_2 = arg0->unk0x20, temp_f31 = (f32) (f64) ((*(s32 *)0x80303150 + Tmr_GetTime(arg0)) - temp_r30_2), GetStructure(QB_WALK_PARAMETERS, 0), GetFloat(QB_REHANG_DELAY, &sp118, 1), ((temp_f31 > sp118) != 0)))) {
                0;
                var_r30 = 0;
                0;
                0;
                if ((fn_800E5FE4(arg0, &sp8, &sp18) != 0) || (fn_800EA190(arg0, temp_r29, temp_r26) != 0)) {
                    var_r30 = 1;
                }
                if (var_r30 != 0) {
                    *(s32 *)0x80302BD8 = 0;
                    return;
                }
                goto block_16;
            }
block_16:
            *(s32 *)0x80302BD8 = 0;
            if ((((s32) *(s32 *)((s32 *)(temp_r30 + 0x24) + 0x1B8) == 0) || (fn_802134A0(arg0) == 0)) && ((temp_r30_3 = arg0->unk0x20, temp_f31_2 = (f32) (f64) ((*(s32 *)0x80303150 + Tmr_GetTime()) - temp_r30_3), GetStructure(QB_WALK_PARAMETERS, 0), GetFloat(QB_REHANG_DELAY, &sp11C, 1), ((temp_f31_2 > sp11C) == 0)) || (fn_80212A28(arg0) == 0))) {
                fn_8021187C(arg0);
                fn_802113EC(arg0);
                temp_r27 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x184C) + 0x30);
                if (temp_r27 == NULL) {
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    0;
                    if (fn_800EB8F8(arg0->unk0x1850, &sp18, &sp28) != 0) {
                        0;
                        0;
                        0;
                        0;
                        0;
                        fn_8010794C(&sp48);
                        temp_f31_3 = *(s32 *)0x802AF5A8;
                        temp_f30 = *(f32 *)0x802AF5B8;
                        *((f32 *)&sp108) = temp_f31_3;
                        sp108.unk0x4 = temp_f30;
                        sp108.unk0x8 = temp_f31_3;
                        sp108.unk0xC = temp_f31_3;
                        0;
                        0;
                        0;
                        0;
                        fn_80107A8C(&sp48, &sp38);
                        *((f32 *)&sp38) = temp_f31_3;
                        sp38.unk0xC = temp_f31_3;
                        sp38.unk0x4 = temp_f30;
                        sp38.unk0x8 = temp_f31_3;
                        0;
                        0;
                        0;
                        0;
                        fn_80107AA0(&sp48, &sp108);
                        if ((fn_80107B20(&sp48, 1, 0) != 0) && (fn_801080D4(&sp48) != 0)) {
                            temp_r29_2 = arg0->unk0x1850;
                            temp_r28 = fn_80108104(&sp48);
                            temp_r30_4 = temp_r29_2->unk0x1C;
                            if (temp_r30_4 != NULL) {
                                temp_r29_2->unk0x70 = (s32 *) *((s32 *)temp_r30_4);
                                if ((s32 *) *((s32 *)temp_r30_4) != NULL) {
                                    CObject_RemoveRefLink(temp_r30_4);
                                    *((s32 *)temp_r30_4) = temp_r27;
                                }
                                Mem_Free(temp_r30_4);
                                temp_r29_2->unk0x1C = temp_r27;
                                temp_r29_2->unk0x74 = (s32) (*(s32 *)0x80303150 + Tmr_GetTime());
                            }
                            Mem_Alloc2(0xB8);
                            temp_r29_2->unk0x1C = fn_80108F94(temp_r28);
                        }
                        temp_f0_2 = *(s32 *)0x802AF5A8;
                        temp_r11 = (char *)arg0 + 0x38;
                        arg0->unk0x38 = temp_f0_2;
                        *((f32 *)&temp_r11->unk0xC) = (f32) *(s32 *)0x802AF5AC;
                        temp_r11->unk0x4 = temp_f0_2;
                        temp_r11->unk0x8 = temp_f0_2;
                        arg0->unk0x48 = temp_f0_2;
                        fn_80210F58(arg0, temp_r26, &sp8);
                        if (spF0 != 0) {
                            CObject_RemoveRefLink();
                            spF0 = 0;
                        }
                    }
                }
            }
        }
    }
}
