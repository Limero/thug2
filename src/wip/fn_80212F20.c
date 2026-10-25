// WIP DRAFT (non-matching) - PARKED 5.5% (-mps-float needed): m2c husk kept
// family=m2c range=0x80212F20-0x80213318 size=1016B
// as placeholder; hand-decode below for a future rebuild (1016B, 254 insns).
// DECODE (2026-08-25, ps_disasm + raw-word decode; shares fn_80212C54's
// opening family and fn_80212A28/B18's release-sequence idiom):
// s32? fn(arg0 r3->r31); frame 0xB8; stfd f29/f30/f31 @a0/a8/b0; stmw r24.
//  1. r28=*(arg0+0x1850); r27=arg0+0x28; node=*(r28+0x1C); flag r11 0/1 via
//     same release-seq as C54 (CObject_RemoveRefLink/Mem_Free/Tmr_GetTime +
//     *(mgr+0x74)=lbl_80303150-page load + ret).
//  2. if flag: ret=fn_801090B8(*(r28+0x1C), r27); or. r29,r3,r3; beq ->
//     repeated release-seq + li r11=... wait: li r0,1/li r0,0 flag r0;
//     FINAL cmpwi r0,0 beq SKIP(178). Preheader addi r25..r28 =
//     arg0+0x1a20/0x1a28/arg0+0x1a08/0x1a10, pages -0x7fd5/-0x7fd5b0.
//  3. BIG BLOCK 48-174: psq vsel blends of obj+0x1a20/28 pairs vs
//     mgr->+96/+104; guard *(mgr+0xB0); scalar fmuls/fmadds dot chains vs
//     mgr->0x70-0x98 matrix -> sp18-sp24, psq back to obj+0x1a08/10;
//     threshold compare *(obj+0x1a0c) vs lbl_802AF684(-0x97c) fcmpu/beq;
//     second PS dot: ps_mr f13(f0), psq_l f12 const-pair lbl_802AF450,
//     ps_mul f13,f10,f0(D24-equiv), ps_merge00, ps_madd f0,f9,f13,f0,
//     ps_sum0 f0,f0,f0,f0 -> hi-lane fcmpu ble; normalize writes.
//  4. TAIL 178-314: fn_800CC3E0(*(arg0+0x1840), &sp38,&sp3C,&sp40);
//     ratio=(sp3C-sp38)/(sp40-sp38); fadds f30=ratio+f29(lbl_802AF684);
//     fn_8002B8E4(&sp28, ...); psq lerp of obj+0x19d0/0x19d8/0x19f0/0x19f8
//     blocks (ps_sum-family words 1F4-206 mislabeled vmsumshm = standard
//     ps_xxx); fn_8002B8E8(&sp18,&sp28); clamps vs lbl_802AF688(f31);
//     *(obj+0x40/0x48/0x30/0x50-region) pair stores; fn_80271170 [sinf] +
//     fn_80271070 [cosf] on f31-clamped value; magic lis 0x4fe6/ori 0x69c
//     -> *(obj+0x80)=0x4FE6069C; ps_madds-family pairs write obj+0x80/0x88
//     pairs and obj+0xB4. Epilogue restores f29/f30/f31.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 7.9% ([1]rev->7.9%).
// UPDATED 2026-09-15 (f): 16.9% -> 17.3% by dropping the stale `-Os` token from the FLAG line (tools/flagtok_scan.py -- the other tokens are still load-bearing).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Mem_Free(s32);
// FLAG: -fno-rerun-cse-after-loop
extern char lbl_802AF684[];
extern char lbl_802AF688[];
extern char lbl_80303150[];
void CObject_RemoveRefLink(CStruct *, CStruct *);
s32 *fn_801090B8(s32 *, void *);                        
void fn_80212F20(Unk_D538E2BB *arg0) {
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp50;
    f32 sp4C;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    s32 sp8;
    s32 *temp_r29;
    s32 *temp_r30;
    s32 *temp_r30_2;
    s32 *temp_r3;
    Unk_4877B8EF *temp_r9;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f11;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f7;
    f32 temp_f9;
    f32 temp_f9_2;
    f32 temp_f9_3;
    f32 var_f12;
    s32 var_r0;
    s32 var_r11;
    Unk_C8FEE62D *temp_r28;
    temp_r28 = arg0->unk0x1850;
    temp_r30 = temp_r28->unk0x1C;
    if (temp_r30 == NULL) {
        var_r11 = 0;
    } else {
        temp_r29 = *((s32 *)temp_r30);
        if (temp_r29 != NULL) {
            var_r11 = 1;
        } else {
            temp_r28->unk0x70 = temp_r29;
            if ((s32 *) *((s32 *)temp_r30) != NULL) {
                CObject_RemoveRefLink(*(s32 *)((char *)temp_r30), temp_r30);
                *((s32 *)temp_r30) = temp_r29;
            }
            Mem_Free(temp_r30);
            temp_r28->unk0x74 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
            var_r11 = 0;
            temp_r28->unk0x1C = temp_r29;
        }
    }
    if (var_r11 != 0) {
        temp_r3 = fn_801090B8(temp_r28->unk0x1C, (char *)arg0 + 0x28);
        if (temp_r3 != NULL) {
            var_r0 = 1;
        } else {
            temp_r30_2 = temp_r28->unk0x1C;
            if (temp_r30_2 != NULL) {
                temp_r28->unk0x70 = (s32 *) *((s32 *)temp_r30_2);
                if ((s32 *) *((s32 *)temp_r30_2) != NULL) {
                    CObject_RemoveRefLink(*(s32 *)((char *)temp_r30_2), temp_r30_2);
                    *((s32 *)temp_r30_2) = temp_r3;
                }
                Mem_Free(temp_r30_2);
                temp_r28->unk0x1C = temp_r3;
                temp_r28->unk0x74 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
            }
            goto block_14;
        }
    } else {
block_14:
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        0;
        0;
        0;
        0;
        temp_r9 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x1850) + 0x1C);
        if ((s32) temp_r9->unk0xB0 != 0) {
            temp_f10 = arg0->unk0x1A0C;
            temp_f9 = arg0->unk0x1A08;
            temp_f11 = arg0->unk0x1A10;
            temp_f7 = *(f32 *)&lbl_802AF684;
            sp18 = (temp_f11 * temp_r9->unk0x90) + ((temp_f9 * *((s32 *)&temp_r9->unk0x70)) + (temp_f10 * temp_r9->unk0x80));
            sp1C = (temp_f11 * temp_r9->unk0x94) + ((temp_f9 * temp_r9->unk0x74) + (temp_f10 * temp_r9->unk0x84));
            sp24 = arg0->unk0x1A14;
            sp20 = (temp_f11 * temp_r9->unk0x98) + ((temp_f9 * temp_r9->unk0x78) + (temp_f10 * temp_r9->unk0x88));
            0;
            0;
            0;
            if (arg0->unk0x1A0C != temp_f7) {
                arg0->unk0x1A0C = temp_f7;
                0;
                if (0 > temp_f7) {
                    0;
                    0;
                    sp4C = *(f32 *)&lbl_802AF688;
                    0;
                }
            }
        }
    }
    fn_800CC3E0(arg0->unk0x1840, &sp38, &sp3C, &sp40);
    temp_f29 = *(s32 *)&lbl_802AF684;
    temp_f31 = *(s32 *)&lbl_802AF688;
    temp_f30 = ((sp3C - sp38) / (sp40 - sp38)) + temp_f29;
    fn_8002B8E4(&sp28);
    sp50 = temp_f30;
    0;
    0;
    0;
    fn_8002B8E8(&sp18, &sp28);
    temp_f10_2 = temp_f30 / arg0->unk0x1A18;
    0;
    0;
    0;
    var_f12 = temp_f10_2;
    0;
    temp_f9_2 = -arg0->unk0x1A1C;
    0;
    if (temp_f10_2 > temp_f31) {
        var_f12 = temp_f31;
    }
    temp_f31_2 = ((temp_f29 - temp_f9_2) * var_f12) + temp_f9_2;
    0;
    0;
    sp60 = sinf(temp_f31_2);
    sp58 = cosf(temp_f31_2);
    sp64 = temp_f29;
    sp5C = temp_f29;
    temp_f9_3 = arg0->unk0x1A00;
    arg0->unk0x80 = QB_ANIMWAIT;
    arg0->unk0xB4 = (f32) (((arg0->unk0x1A04 - temp_f9_3) * temp_f30) + temp_f9_3);
    0;
    0;
    0;
    0;
}
