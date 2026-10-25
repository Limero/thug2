// PARKED 30% (m2c baseline): 198-insn skater-reset/init routine, hand-rebuild needed.
// Structural map from disasm (all offsets abs):
// prologue: frame 0x28, stmw r25 (7 saved GPRs r25-r31), r31=arg0 r30=arg1 r27=arg2 r26=arg3.
// 1. bl fn_801D1380 (0-arg). If arg1!=0: fn_801D1458(arg0,0); *(arg0+0x9C)=0.
//    else: fn_801D1458(arg0,1); r29=1; *(arg0+0x9C)=1; TWO countdown-reset blocks via
//    mgr=*(arg0+0x15BC): off 0x114 and 0xFC - if *(mgr+off+4)!=1 { =1; t=Tmr_GetTime();
//    *(mgr+off+8)=lbl_80303150+t; } guarded by *(arg0->0x15C8->0xB0)!=0 for the second.
// 2. join 0xFBC: t=Tmr_GetTime(); *(arg0+0x98)=lbl_80303150+t; derived r10=arg0+0x20.
// 3. BIG PS pair-copy shuffle obj=*(arg0+0xC) <-> arg0 fields (16 psq pairs, mixed
//    r9/r11 obj webs - per-copy reload decisions needed; see recipe 59/M5.0d idioms).
// 4. scalar inits: r6=1 -> +0x374; r28=0 -> +0x1E5(STB!); f12=lbl_802AD3C4-class floats
//    -> +0x304; zeros 0x3F0/0x418/0x41C/0x3D8/0x370/mgr->0x160; cond-store +0x3B8
//    (cmp vs lbl float @page-0x2C38); zeros 0x560/0x564/0x56C/0x568; f0->0x42C.
// 5. if arg2!=0: cleanup via mgr2=*(arg0+0x15C0): free list node (8009DFC0/80009AAC),
//    Mem_Alloc2(0xB8)+fn_80108F94 alloc, fn_801E72F0(arg0,arg2,[+0x14],[+0x10],1,1),
//    4 more pair copies. else if arg3!=0: fn_801D99B4(arg0,arg3).
// Suggested attack: same trio as promoted zone-mates (hidden args audited, protos,
// lbl folds); the pair-copy shuffle wants the fn_801D16C0-style named-base treatment.
// family=m2c range=0x801D0EF8-0x801D1210 size=792B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// UPDATED 2026-09-15 (e): 12.1% -> 23.7%. raw address literal -> registered lbl_ symbol: MWCC emits lis+ori for a literal constant but lis+addi for a symbol address (fn_8006A8C0 recipe). tools/raw_sym_scan.py automated the A/B; keep the best body.
#include "types.h"
extern char lbl_802AD3C4[];
extern char lbl_802AD3C8[];
extern char lbl_802AD3CC[];
extern char lbl_80303150[];
#include "structs.h"
s32 fn_801E72F0(void *, void *, void *, void *, void *, void *);
s32 fn_801D1458(s32, s32);
void fn_801D0EF8(Unk_E5AABED0 *arg0, s32 arg1, Unk_C8FEE62D *arg2, Unk_DB0E2BAB *arg3) {
    f32 temp_f12;
    s32 *temp_r30_3;
    s32 *temp_r30_4;
    s32 temp_r28;
    Unk_C8FEE62D *temp_r29;
    Unk_C8FEE62D *temp_r29_2;
    CStruct *temp_r30;
    CStruct *temp_r30_2;

    fn_801D1380();
    if (arg1 != 0) {
        fn_801D1458(arg0, 0);
        arg0->unk0x9C = 0;
    } else {
        fn_801D1458(arg0, 1);
        arg0->unk0x9C = 1;
        temp_r30 = arg0->unk0x15BC + 0x114;
        if ((s32) temp_r30->unk0x4 != 1) {
            temp_r30->unk0x4 = 1;
            temp_r30->unk0x8 = (s32) (*(s32 *)lbl_80303150 + Tmr_GetTime());
        }
        if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15C8) + 0xB0) != 0) {
            temp_r30_2 = arg0->unk0x15BC + 0xFC;
            if ((s32) temp_r30_2->unk0x4 != 1) {
                temp_r30_2->unk0x4 = 1;
                temp_r30_2->unk0x8 = (s32) (*(s32 *)lbl_80303150 + Tmr_GetTime());
            }
        }
    }
    arg0->unk0x98 = (s32) (*(s32 *)lbl_80303150 + Tmr_GetTime());
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    temp_f12 = *(f32 *)lbl_802AD3C4;
    0;
    arg0->unk0x374 = 1;
    *(s32 *)((char *)arg0 + (s32)0x1E5) = 0;
    arg0->unk0x304 = temp_f12;
    arg0->unk0x3F0 = 0;
    arg0->unk0x418 = 0;
    arg0->unk0x41C = 0;
    arg0->unk0x3D8 = 0;
    arg0->unk0x370 = 0;
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15BC) + 0x160) = 0;
    if (arg0->unk0x3B8 != *(f32 *)(s32)lbl_802AD3C8) {
        arg0->unk0x3B8 = temp_f12;
    }
    arg0->unk0x560 = 0;
    arg0->unk0x564 = 0;
    arg0->unk0x42C = (f32) *(f32 *)lbl_802AD3CC;
    arg0->unk0x56C = 0;
    arg0->unk0x568 = 0;
    if (arg2 != NULL) {
        temp_r29 = arg0->unk0x15C0;
        temp_r30_3 = temp_r29->unk0x1C;
        if (temp_r30_3 != NULL) {
            temp_r29->unk0x70 = (s32) *((s32 *)temp_r30_3);
            if ((s32) *((s32 *)temp_r30_3) != 0) {
                CObject_RemoveRefLink(temp_r30_3);
                *((s32 *)temp_r30_3) = 0;
            }
            Mem_Free(temp_r30_3);
            temp_r29->unk0x1C = NULL;
            temp_r29->unk0x74 = (s32) (*(s32 *)lbl_80303150 + Tmr_GetTime());
        }
        temp_r28 = arg2->unk0x18;
        if (temp_r28 != 0) {
            temp_r29_2 = arg0->unk0x15C0;
            temp_r30_4 = temp_r29_2->unk0x1C;
            if (temp_r30_4 != NULL) {
                temp_r29_2->unk0x70 = (s32) *((s32 *)temp_r30_4);
                if ((s32) *((s32 *)temp_r30_4) != 0) {
                    CObject_RemoveRefLink(temp_r30_4);
                    *((s32 *)temp_r30_4) = 0;
                }
                Mem_Free(temp_r30_4);
                temp_r29_2->unk0x1C = NULL;
                temp_r29_2->unk0x74 = (s32) (*(s32 *)lbl_80303150 + Tmr_GetTime());
            }
            Mem_Alloc2(0xB8);
            temp_r29_2->unk0x1C = fn_80108F94(arg0, temp_r28);
        }
        fn_801E72F0(arg0, arg2, arg2->unk0x14, arg2->unk0x10, 1, 1);
        0;
        return;
    }
    if (arg3 != 0) {
        fn_801D99B4(arg0, arg3);
    }
}
