// WIP DRAFT (non-matching) - PARKED 9.4% (-mps-float needed): m2c husk kept
// family=m2c range=0x80212C54-0x80212E50 size=508B
// as placeholder; full hand-decode below for a future rebuild session.
// DECODE (2026-08-25, ps_disasm + raw-word PS decode of all opcode-4 words):
// void fn(arg0 r3->r29, arg1 r4->r27, arg2 f32* r5->r26); frame 0x40,
// stmw r30/r31 only, NO FPR saves. All PS words standard Gekko: ps_mr
// XO10=72 (D1C), ps_mul xo5=25 VD13/VA10/VB0 (D24), ps_merge00 C=16 (D30),
// ps_madd xo5=29 VD0/VA9/VB13/VC0 (D34), ps_sum0 xo5=10 (D38), ps_sel x4,
// plus psq_l/st pairs throughout.
//  1. mgr=r28=*(arg0+0x1850); node=r30=*(mgr+0x1C); flag r11:
//     node==0 -> 0; *node!=0 -> 1; else release-seq: *(mgr+0x70)=*node;
//     if (*node) { CObject_RemoveRefLink(*node,node); *node=0; } Mem_Free(node);
//     *(mgr+0x1C)=0; Tmr_GetTime(); *(mgr+0x74)=*(u32*)lbl_80303150+r3
//     (lis -0x7fd0 / lwz 0x3150(r9) folded global + chained ret).
//  2. cmpwi r11,0; beq ELSE. flag!=0: r3=*(mgr+0x1C); fn_801090B8(r3,arg1)
//     (r4=r27 untouched passthrough); or. r29,r3,r3; beq -> release-seq
//     REPEATED (FD4-1C, §70-150 duplicate-fixup shape) then li r0,0;
//     ret!=0 -> li r0,1. ELSE: li r0,0.
//  3. BIG BLOCK gate cmpwi r0,0/beq 178. Preheader: addi r25=arg0+0x1a20,
//     r24=arg0+0x1a28, r26=arg0+0x1a08, r27=arg0+0x1a10, r28=r1+8,
//     r10=0x802AF450 page, r8 page -0x7fd5. Body: psq blend vsel of
//     obj+0x1a20/28 pairs against *(mgr)->+96/+104 pairs stored back;
//     guard *(mgr+0xB0)==0 skips rest; scalar dot blocks: lfs f10=*(obj+
//     0x1a0c), f12/f9/f11=*(obj+0x1a08..0x1a14 lanes), fmuls/fmadds chains
//     vs mgr->0x70..0x98 matrix cols -> stfs sp18/sp1C/sp20/sp24, psq copy
//     back to obj+0x1a08/0x1a10; fcmpu f10 vs lbl_802AF668(f8) beq-skip;
//     stfs f7(lbl_802AF66C-page -0x97c); second dot via ps_mr f10/f13,
//     ps_mul f13,f10,f0, ps_merge00, ps_madd f0,f9,f13,f0, ps_sum0 ->
//     sp18 hi-lane test fcmpu ble; psq normalize writes obj+0x1a08 block.
//  4. TAIL 178-E38: fn_800CC3E0(*(arg0+0x1840),&sp38,&sp3C,&sp40) 4-arg;
//     ratio=(sp3C-sp38)/(sp40-sp38) fdivs; fadds+f29(lbl_802AF684);
//     fn_8002B8E4(r3=&sp28,r4=&sp38?) lerp-helper; fn_8002B8E8;
//     f31=lbl_802AF688(-0x978); clamp f10=f30/*(obj+0x1a18) vs f31 (ble/
//     fmr f12,f31 max-pick); fmadds f31=(f29+fneg f9)*f12+f9;
//     fn_80271170(f31) [sinf] + fn_80271070(f31) [cosf] results to
//     sp58/sp60/sp64; magic lis 0x4fe6/ori 0x69c -> *(obj+0x80)=0x4FE6069C;
//     psq pair math on obj+0x80/0x88 vs sp58-block, *(obj+0xB4) store;
//     final two vmhaddshs-mislabeled words E8/E0 = ps_madds0-family pair
//     writes obj+0x80/0x88 pairs. Epilogue lmw r24, lfd f29/f30/f31.
// NOT attempted: byte matching. Est. difficulty high (PS web colors across
// ~25 ops + doc-15-class call setups + repeated release-seq scheduling).
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 14.2% ([1]rev->11.0% [0]rev->14.2%).
#include "types.h"
#include "structs.h"
extern char lbl_802AF668[];
extern f32 lbl_802AF66C;
extern char lbl_80303150[];
void CObject_RemoveRefLink(CStruct *, CStruct *);
static s32 sp18;

void fn_80212C54(Unk_9C8D3F51 *arg0, s32 arg1, f32 *arg2) {
    f32 sp20;
    s32 *temp_r30;
    s32 *temp_r30_2;
    s32 *temp_r31;
    f32 temp_f0;
    f32 temp_f8;
    s32 var_r11;
    Unk_C8FEE62D *temp_r28;
    Unk_C8FEE62D *temp_r31_2;
    CStruct *temp_r9;

    temp_r30 = temp_r28->unk0x1C;
    temp_r28 = arg0->unk0x1850;
    if (temp_r30 == NULL) {
        var_r11 = 0;
    } else {
        temp_r31 = *((s32 *)temp_r30);
        if (temp_r31 != NULL) {
            var_r11 = 1;
        } else {
            temp_r28->unk0x70 = temp_r31;
            if ((s32 *) *((s32 *)temp_r30) != NULL) {
                CObject_RemoveRefLink(*(s32 *)((char *)temp_r30), temp_r30);
                *((s32 *)temp_r30) = temp_r31;
            }
            Mem_Free(arg0, arg0, arg1, arg0, arg1, temp_r30);
            temp_r28->unk0x74 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
            var_r11 = 0;
            temp_r28->unk0x1C = temp_r31;
        }
    }
    if (var_r11 != 0) {
        temp_f8 = *(f32 *)&lbl_802AF668;
        0;
        0;
        0;
        0;
        if (sp18 > temp_f8) {
            sp20 = arg0->unk0x88;
            0;
            0;
            0;
            0;
            0;
        }
        *arg2 += arg0->unk0x196C;
        arg0->unk0x196C = temp_f8;
        0;
        0;
        0;
        0;
    } else {
        temp_f0 = *(s32 *)&lbl_802AF668;
        temp_r9 = (char *)arg0 + 0x1968;
        arg0->unk0x1968 = temp_f0;
        *((f32 *)&temp_r9->unk0xC) = lbl_802AF66C;
        temp_r9->unk0x8 = temp_f0;
        temp_r9->unk0x4 = temp_f0;
    }
    temp_r31_2 = arg0->unk0x1850;
    temp_r30_2 = temp_r31_2->unk0x1C;
    if (temp_r30_2 != NULL) {
        temp_r31_2->unk0x70 = (s32 *) *((s32 *)temp_r30_2);
        if ((s32 *) *((s32 *)temp_r30_2) != NULL) {
            CObject_RemoveRefLink(*(s32 *)((char *)temp_r30_2), temp_r30_2);
            *((s32 *)temp_r30_2) = NULL;
        }
        Mem_Free(temp_r30_2);
        temp_r31_2->unk0x1C = NULL;
        temp_r31_2->unk0x74 = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
    }
}
