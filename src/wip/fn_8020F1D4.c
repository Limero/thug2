// WIP DRAFT — decode-documented park (groupB PS zone, 2026-08-25)
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 3.0189% -> 3.7736% per-object flags: -fno-rerun-cse-after-loop -> -O1
// PARKED (m2c husk retained; hand rebuild not completed).
// 1060B, frame 0x130, saves f30/f31 + r29-r31. Same skater-step family as
// fn_802101D0/80210D10 (see those headers for full recipe notes):
//   r30=&sp8 desc; mr r29,r30 (desc ptr in TWO saved regs!);
//   bl fn_8010794C(desc); pair copies arg0+0x28->sp8, +0x30->sp10;
//   hash chain: GetStructure(0x6775E538,0) -> fn_8028E0(?,0xCEE3A3E1,&spE8,1)
//   [r3 chained]; spC += spE8; second copy run to sp18/sp20;
//   2nd hash call -> &spEC (0xAF3E4251). PS inventory: 5 op4 words, ALL
//   standard emittable ops (ps_mul/sub/madd family); ~27 psq pairs.
//   24 calls total incl. repeated fn_80107B20 probes and node cleanup
//   tail (CObject_RemoveRefLink + li 0) at end.
// Walls expected: desc-ptr double-home (r30+mr r29), FPR f30/f31 roles,
// spill-slot layout in 0x130 frame — same allocator classes documented
// in fn_802101D0/fn_8020F938 headers.
// family=m2c range=0x8020F1D4-0x8020F5F8 size=1060B
// PARK-NOTE 2026-08-29: static-temp artifact sweep — moved the file-scope `static s32 spXX` temps into the function as locals (the 80114E4C fix). Best form so far: 5.0% -> 6.0% masked. Remaining diffs are structural, not the artifact.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 2.6% ([2]rev->2.6%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_802134A0(void *);
s32 fn_800DF004(s32, s32, s32);
// FLAG: -O1
extern f32 lbl_802AF564;
extern f32 lbl_802AF568;
extern char lbl_802AF56C[];
extern f32 lbl_802AF570;
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_8020F1D4(Unk_3CB21567 *arg0) {
    f32 spF8;
   
    s32 sp94;
 f32 spF0;
    f32 spEC;
    f32 spE8;
    s32 spB0;
    f32 sp1C;
    f32 spC;
    Unk_DA7C2D0D sp8;
    Unk_C7387A53 *temp_r9_2;
    s32 var_r4;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f13;
    s32 temp_r3;
    s32 var_r0;
    CStruct *temp_r9;

    fn_8010794C(&sp8);
    0;
    0;
    GetStructure(QB_WALK_PARAMETERS, 0);
    GetFloat(QB_SNAP_UP_HEIGHT, &spE8, 1);
    spC += spE8;
    0;
    GetStructure(QB_WALK_PARAMETERS, 0);
    GetFloat(QB_SNAP_DOWN_HEIGHT, &spEC, 1);
    sp1C -= spEC;
    if ((fn_80107B20(&sp8, 1, 0) == 0) || (sp8.unk0x58 & 2)) {
        if (fn_80107B20(&sp8, 1, 0) != 0) {
            spF8 = lbl_802AF564;
            0;
            0;
            0;
            0;
            0;
        }
        if (((s32) arg0->unk0x1940 == 0) || (fn_800DF004(arg0->unk0x1848, 0x802AF7FC, (char *)arg0 + 0x1880), (((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x184C) + 0x30) == 0) != 0))) {
            if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x183C) + 0x1DC) != 0) {
                temp_r9 = (char *)arg0 + 0x28;
                var_r0 = 0;
                if ((arg0->unk0x28 == arg0->unk0x70) && (temp_r9->unk0x4 == arg0->unk0x74) && (temp_r9->unk0x8 == arg0->unk0x78)) {
                    0;
                    var_r0 = ((u32) 0 >> 1U) & 1;
                }
                if (var_r0 != 0) {
                    arg0->unk0x74 = (f32) (arg0->unk0x74 + lbl_802AF568);
                }
                if (fn_802134A0(arg0) == 0) {
                    goto block_14;
                }
                goto block_32;
            }
block_14:
            if ((fn_800E9F8C(arg0) == 0) && (temp_r3 = fn_800E53FC(arg0), ((temp_r3 == 0) != 0))) {
                fn_8020D2E4(arg0, 1);
                0;
                0;
                fn_80212C54(arg0, (char *)arg0 + 0x38, (char *)arg0 + 0x48);
                arg0->unk0x80 = QB_WALKOFFEDGE;
                fn_8009F054(arg0->unk0xC, QB_SKATEROFFEDGE, 0, *(s32 *)&lbl_802AF56C);
                if (spB0 != 0) {
                    CObject_RemoveRefLink(spB0, &spB0);
                    spB0 = temp_r3;
                }
            } else {
                goto block_32;
            }
        } else {
            goto block_32;
        }
    } else {
        temp_f30 = sp94 - arg0->unk0x2C;
        GetStructure(QB_WALK_PARAMETERS, 0);
        temp_f31 = fabs(temp_f30);
        GetFloat(QB_MAX_UNNOTICED_GROUND_SNAP, &spF0, 1);
        if (temp_f31 > spF0) {
            var_r4 = QB_SNAPDOWNEDGE;
            if (temp_f30 > *(f32 *)&lbl_802AF56C) {
                var_r4 = QB_SNAPUPEDGE;
            }
            fn_8009F010(arg0->unk0xC, var_r4, 0);
        }
        temp_f12 = *(s32 *)&lbl_802AF56C;
        arg0->unk0x2C = sp94;
        if ((temp_f30 > temp_f12) || (temp_f30 < lbl_802AF570)) {
            var_f13 = temp_f0;
            temp_f0 = arg0->unk0x7CC - temp_f30;
            if (temp_f0 < temp_f12) {
                var_f13 = temp_f12;
            }
            arg0->unk0x7CC = var_f13;
        }
        temp_r9_2 = (char *)arg0 + 0x1880;
        if (((s32) temp_r9_2->unk0x5C == (s32) sp8.unk0x5C) || ((((s32) arg0->unk0x1940 == 0) || (fn_800DF004(arg0->unk0x1848, 0x802AF82C, temp_r9_2), (((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x184C) + 0x30) == 0) != 0))) && (fn_800DF004(arg0->unk0x1848, 0x802AF820, &sp8), (((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x184C) + 0x30) == 0) != 0)))) {
            fn_800C9350(temp_r9_2, &sp8);
            arg0->unk0x1940 = 1;
            0;
            0;
            fn_800EB67C(arg0->unk0x1850, &sp8);
            fn_801F13D0(*((s32 *)&arg0->unk0x1854), *(s32 *)((char *)&sp8 + 0x5A));
        }
block_32:
        if (spB0 != 0) {
            CObject_RemoveRefLink(spB0, &spB0);
            spB0 = 0;
        }
    }
}
