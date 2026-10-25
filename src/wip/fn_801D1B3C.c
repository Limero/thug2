// PARKED 6.2% (m2c stub baseline): 1095-insn multi-subsystem reset/dispatch routine.
// Structural map from disasm for future rebuild (all addresses rel. fn start):
// 0x00-0x14: prologue stfd f31 + stmw r23 (9 saved GPRs!), frame 0x108; r29=0, r31=arg0.
// 0x18-0x1CC: SEVEN identical countdown-reset blocks over mgr=*(arg0+0x15BC):
//   offsets {0x60,0x3C,0x48,0xA8,0xF0,0xB4,0xFC}: if *(mgr+off+4)!=0 { =0;
//   t=Tmr_GetTime(); *(mgr+off+8)=lbl_80303150+t; } (r30 = mgr+off each time).
// 0x1D0-0x250: calls Kenacosf / fn_800058CC / fn_8014030C(hash,...) w/ PS pair
//   math inline (vsel-labeled words = ps ops) + float compares vs f31.
// 0x25C-0x2E4: hash switch on *(mgr_15B8->0x1C) vs {0x3506CE64, 0x0AC90769,
//   0xA549B57B, 0xEF2413B} -> dispatch: case0: fn_801D2C58(arg0); if ret!=0
//   fn_801D2D94(arg0); then fn_801D2FE8/30E0 chains. Other cases set 0x388 flags.
// 0x2F0+: more subsystem calls fn_801A3E4C/fn_8020C54C/fn_801A6F44...
// Rebuild order suggestion: crack the seven-block reset series first (template in
// src/wip/fn_801D1210.c countdown-reset block), then the hash dispatch via
// recipe-124 phantom-case steering. Callee arities audited where promoted.
// family=m2c range=0x801D1B3C-0x801D2C58 size=4380B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 1.4% ([1]rev->1.3% [7]rev->1.4%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801D488C(void *);
s32 fn_801A3E4C(s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
static s32 sp78;
static s32 spA8;
static s32 spB0;

s32 *fn_801090B8(s32 *, void *);                        

void fn_801D1B3C(Unk_71062261 *arg0) {
    f32 spC8;
    f32 spC0;
    f32 spBC;
    f32 spA0;
    f32 sp98;
    f32 sp90;
    f32 sp88;
    f32 sp80;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    Unk_59AB5482 sp18;
    f32 spC;
    Unk_59AB5482 sp8;
    s32 *temp_r29_2;
    s32 *temp_r30_10;
    s32 *temp_r30_11;
    s32 *temp_r3_3;
    Unk_12C58B0B *temp_r8;
    s32 *temp_r9_2;
    Unk_12C58B0B *temp_r9_3;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f13;
    f32 temp_f1;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f5;
    f32 temp_f6;
    f32 temp_f7;
    f32 temp_f7_2;
    f32 temp_f7_3;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 temp_f8_3;
    f32 temp_f9;
    f32 temp_f9_2;
    s32 temp_r30_8;
    s32 temp_r30_9;
    s32 temp_r3_2;
    s32 temp_r9;
    s32 var_r0;
    s32 var_r11;
    s32 var_r28;
    s32 var_r29;
    u8 temp_r30_12;
    Unk_C7387A53 *temp_r10;
    Unk_6A70655D *temp_r11;
    void *temp_r27;
    Unk_C8FEE62D *temp_r28;
    void *temp_r29;
    CStruct *temp_r30;
    CStruct *temp_r30_13;
    CStruct *temp_r30_14;
    CStruct *temp_r30_2;
    CStruct *temp_r30_3;
    CStruct *temp_r30_4;
    CStruct *temp_r30_5;
    CStruct *temp_r30_6;
    CStruct *temp_r30_7;
    void *temp_r3;

    temp_r30 = arg0->unk0x15BC + 0x60;
    if ((s32) temp_r30->unk0x4 != 0) {
        temp_r30->unk0x8 = (s32) (*(s32 *)0x80303150 + Tmr_GetTime());
        temp_r30->unk0x4 = 0;
    }
    temp_r30_2 = arg0->unk0x15BC + 0x3C;
    if ((s32) temp_r30_2->unk0x4 != 0) {
        temp_r30_2->unk0x4 = 0;
        temp_r30_2->unk0x8 = (s32) (*(s32 *)0x80303150 + Tmr_GetTime(arg0));
    }
    temp_r30_3 = arg0->unk0x15BC + 0x48;
    if ((s32) temp_r30_3->unk0x4 != 0) {
        temp_r30_3->unk0x4 = 0;
        temp_r30_3->unk0x8 = (s32) (*(s32 *)0x80303150 + Tmr_GetTime());
    }
    temp_r30_4 = arg0->unk0x15BC + 0xA8;
    if ((s32) temp_r30_4->unk0x4 != 0) {
        temp_r30_4->unk0x4 = 0;
        temp_r30_4->unk0x8 = (s32) (*(s32 *)0x80303150 + Tmr_GetTime());
    }
    temp_r30_5 = arg0->unk0x15BC + 0xF0;
    if ((s32) temp_r30_5->unk0x4 != 0) {
        temp_r30_5->unk0x4 = 0;
        temp_r30_5->unk0x8 = (s32) (*(s32 *)0x80303150 + Tmr_GetTime());
    }
    temp_r30_6 = arg0->unk0x15BC + 0xB4;
    if ((s32) temp_r30_6->unk0x4 != 0) {
        temp_r30_6->unk0x4 = 0;
        temp_r30_6->unk0x8 = (s32) (*(s32 *)0x80303150 + Tmr_GetTime());
    }
    temp_r30_7 = arg0->unk0x15BC + 0xFC;
    if ((s32) temp_r30_7->unk0x4 != 0) {
        temp_r30_7->unk0x8 = (s32) (*(s32 *)0x80303150 + Tmr_GetTime());
        temp_r30_7->unk0x4 = 0;
    }
    arg0->unk0x1558 = 0;
    arg0->unk0x25C = 0;
    arg0->unk0x274 = 0;
    arg0->unk0x568 = 0;
    arg0->unk0x314 = 0;
    arg0->unk0x334 = 0;
    temp_f31 = *(f32 *)0x802AD410;
    temp_f1 = Kenacosf(*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x98)) * *(f32 *)0x802AD40C;
    arg0->unk0x3B0 = temp_f1;
    if (*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0xA0) < temp_f31) {
        arg0->unk0x3B0 = (f32) (*(f32 *)0x802AD414 - temp_f1);
    }
    temp_r29 = (char *)arg0 + 0x70;
    0;
    0;
    0;
    if (sp78 > *(f32 *)0x802AD418) {
        fn_800058CC(arg0->unk0xC + 0xB8, temp_r29);
    }
    temp_f13 = *(f32 *)0x802AD41C;
    spC = fn_8014030C(QB_PHYSICS_GROUND_GRAVITY, 1, arg0->unk0xC);
    *((f32 *)&sp8) = temp_f31;
    sp8.unk0x8 = temp_f31;
    sp8.unk0xC = temp_f13;
    if ((arg0->unk0x3B8 != temp_f31) && (*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0xBC) > temp_f31)) {
        sp8.unk0x8 = temp_f31;
        ((Unk_560A7BB5 *)&sp8)->unk0x4 = (f32) arg0->unk0x3C8;
        sp8.unk0xC = temp_f13;
        *((f32 *)&sp8) = temp_f31;
    }
    fn_80005854(&sp8, temp_r29);
    sp80 = arg0->unk0x94;
    0;
    0;
    0;
    0;
    0;
    arg0->unk0x360 = 0;
    temp_r3 = arg0->unk0x15B8;
    temp_r9 = ((Unk_31DE137E *)temp_r3)->unk0x1C;
    switch (temp_r9) {                              
    case QB_LIP:
        break;
    case 0x0:
        temp_r3_2 = fn_801D2C58(arg0);
        if (temp_r3_2 != 0) {
            fn_801D2D94(arg0);
        } else {
            arg0->unk0x388 = temp_r3_2;
            if (fn_801D2FE8(arg0) != 0) {
                fn_801D30E0(arg0);
            }
        }
        break;
    case QB_MANUAL:
    case 0xAC90769:
        arg0->unk0x388 = 0;
        if ((s32) arg0->unk0x35C != 0) {
            arg0->unk0x360 = 1;
            if (fn_801D2FE8(arg0) != 0) {
                fn_801D30E0(arg0);
            }
        }
        fn_801A3E4C(arg0->unk0x15B8 + 0x28);
        fn_8020C54C(arg0->unk0x15AC, 1);
        if (fn_801A6F44(*(s32 *)((s32 *)(*(void **)0x80305EAC) + 0x24), QB_CHEAT_PERFECT_MANUAL) != 0) {
            temp_r30_8 = *(s32 *)((s32 *)(*(void **)0x80305EAC) + 0x24);
            fn_801A6F8C(temp_r30_8, Script_GetInteger(QB_CHEAT_PERFECT_MANUAL, 0));
            temp_f0 = *(s32 *)0x802AD410;
            *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15B8) + 0x5C) = temp_f0;
            *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15B8) + 0x60) = temp_f0;
block_42:
            *(s32 *)0x80305F04 = 1;
        }
        break;
    case QB_SKITCH:
        fn_801A3E4C(temp_r3 + 0x178);
        if (fn_801A6F44(*(s32 *)((s32 *)(*(s32 *)0x80305EAC) + 0x24), QB_CHEAT_PERFECT_SKITCH) != 0) {
            temp_r30_9 = *(s32 *)((s32 *)(*(s32 *)0x80305EAC) + 0x24);
            fn_801A6F8C(temp_r30_9, Script_GetInteger(QB_CHEAT_PERFECT_SKITCH, 0));
            temp_f0_2 = *(s32 *)0x802AD410;
            *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15B8) + 0x1AC) = temp_f0_2;
            *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15B8) + 0x1B0) = temp_f0_2;
            goto block_42;
        }
        break;
    }
    fn_801D32A0(arg0);
    fn_801D3D18(arg0);
    sp88 = arg0->unk0x94;
    0;
    if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15BC) + 0xC4) != 0) {
        temp_r9_2 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15C0) + 0x1C);
        if ((temp_r9_2 != NULL) && ((s32) *((s32 *)temp_r9_2) != NULL)) {
            sp90 = fn_8012570C(QB_SKITCH_SPEED_MATCH, 1);
            0;
            0;
            0;
        }
        temp_f0_3 = *(s32 *)0x802AD410;
        *((f32 *)&sp18) = temp_f0_3;
        ((Unk_E266FB50 *)&sp18)->unk0xC = (f32) *(s32 *)0x802AD41C;
        sp18.unk0x8 = temp_f0_3;
        sp18.unk0x4 = temp_f0_3;
        fn_801D488C(arg0);
    }
    temp_r28 = arg0->unk0x15C0;
    temp_r30_10 = temp_r28->unk0x1C;
    temp_r27 = arg0->unk0xC + 0x58;
    if (temp_r30_10 == NULL) {
        var_r11 = 0;
    } else {
        temp_r29_2 = *((s32 *)temp_r30_10);
        if (temp_r29_2 != NULL) {
            var_r11 = 1;
        } else {
            temp_r28->unk0x70 = temp_r29_2;
            if ((s32 *) *((s32 *)temp_r30_10) != NULL) {
                CObject_RemoveRefLink(*(s32 *)((char *)temp_r30_10), temp_r30_10);
                *((s32 *)temp_r30_10) = temp_r29_2;
            }
            Mem_Free(temp_r30_10);
            temp_r28->unk0x1C = temp_r29_2;
            var_r11 = 0;
            temp_r28->unk0x74 = (s32) (*(s32 *)0x80303150 + Tmr_GetTime());
        }
    }
    if (var_r11 != 0) {
        temp_r3_3 = fn_801090B8(temp_r28->unk0x1C, temp_r27);
        if (temp_r3_3 != NULL) {
            var_r0 = 1;
        } else {
            temp_r30_11 = temp_r28->unk0x1C;
            if (temp_r30_11 != NULL) {
                temp_r28->unk0x70 = (s32 *) *((s32 *)temp_r30_11);
                if ((s32 *) *((s32 *)temp_r30_11) != NULL) {
                    CObject_RemoveRefLink(*(s32 *)((char *)temp_r30_11), temp_r30_11);
                    *((s32 *)temp_r30_11) = temp_r3_3;
                }
                Mem_Free(temp_r30_11);
                temp_r28->unk0x1C = temp_r3_3;
                temp_r28->unk0x74 = (s32) (*(s32 *)0x80303150 + Tmr_GetTime());
            }
            goto block_62;
        }
    } else {
block_62:
        var_r0 = 0;
    }
    if ((var_r0 != 0) && ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15BC) + 0xC4) == 0)) {
        0;
        0;
        0;
        0;
        temp_r11 = arg0->unk0xC;
        temp_r8 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15C0) + 0x1C);
        if ((s32) temp_r8->unk0xB0 != 0) {
            temp_r10 = (char *)arg0 + 0x20;
            sp38 = (temp_r11->unk0x84 * *((s32 *)&temp_r8->unk0xA0)) + ((temp_r11->unk0x80 * *((s32 *)&temp_r8->unk0x90)) + ((temp_r11->unk0x78 * *((s32 *)&temp_r8->unk0x70)) + (temp_r11->unk0x7C * *((s32 *)&temp_r8->unk0x80))));
            sp3C = (temp_r11->unk0x84 * *((s32 *)&temp_r8->unk0xA4)) + ((temp_r11->unk0x80 * *((s32 *)&temp_r8->unk0x94)) + ((temp_r11->unk0x78 * *((s32 *)&temp_r8->unk0x74)) + (temp_r11->unk0x7C * *((s32 *)&temp_r8->unk0x84))));
            sp40 = (temp_r11->unk0x84 * *((s32 *)&temp_r8->unk0xA8)) + ((temp_r11->unk0x80 * *((s32 *)&temp_r8->unk0x98)) + ((temp_r11->unk0x78 * *((s32 *)&temp_r8->unk0x78)) + (temp_r11->unk0x7C * *((s32 *)&temp_r8->unk0x88))));
            sp44 = (temp_r11->unk0x84 * *((s32 *)&temp_r8->unk0xAC)) + ((temp_r11->unk0x80 * *((s32 *)&temp_r8->unk0x9C)) + ((temp_r11->unk0x78 * *((s32 *)&temp_r8->unk0x7C)) + (temp_r11->unk0x7C * *((s32 *)&temp_r8->unk0x8C))));
            sp48 = (temp_r11->unk0x94 * *((s32 *)&temp_r8->unk0xA0)) + ((temp_r11->unk0x90 * *((s32 *)&temp_r8->unk0x90)) + ((temp_r11->unk0x88 * *((s32 *)&temp_r8->unk0x70)) + (temp_r11->unk0x8C * *((s32 *)&temp_r8->unk0x80))));
            sp4C = (temp_r11->unk0x94 * *((s32 *)&temp_r8->unk0xA4)) + ((temp_r11->unk0x90 * *((s32 *)&temp_r8->unk0x94)) + ((temp_r11->unk0x88 * *((s32 *)&temp_r8->unk0x74)) + (temp_r11->unk0x8C * *((s32 *)&temp_r8->unk0x84))));
            sp50 = (temp_r11->unk0x94 * *((s32 *)&temp_r8->unk0xA8)) + ((temp_r11->unk0x90 * *((s32 *)&temp_r8->unk0x98)) + ((temp_r11->unk0x88 * *((s32 *)&temp_r8->unk0x78)) + (temp_r11->unk0x8C * *((s32 *)&temp_r8->unk0x88))));
            sp54 = (temp_r11->unk0x94 * *((s32 *)&temp_r8->unk0xAC)) + ((temp_r11->unk0x90 * *((s32 *)&temp_r8->unk0x9C)) + ((temp_r11->unk0x88 * *((s32 *)&temp_r8->unk0x7C)) + (temp_r11->unk0x8C * *((s32 *)&temp_r8->unk0x8C))));
            sp58 = (temp_r11->unk0xA4 * *((s32 *)&temp_r8->unk0xA0)) + ((temp_r11->unk0xA0 * *((s32 *)&temp_r8->unk0x90)) + ((temp_r11->unk0x98 * *((s32 *)&temp_r8->unk0x70)) + (temp_r11->unk0x9C * *((s32 *)&temp_r8->unk0x80))));
            sp5C = (temp_r11->unk0xA4 * *((s32 *)&temp_r8->unk0xA4)) + ((temp_r11->unk0xA0 * *((s32 *)&temp_r8->unk0x94)) + ((temp_r11->unk0x98 * *((s32 *)&temp_r8->unk0x74)) + (temp_r11->unk0x9C * *((s32 *)&temp_r8->unk0x84))));
            sp60 = (temp_r11->unk0xA4 * *((s32 *)&temp_r8->unk0xA8)) + ((temp_r11->unk0xA0 * *((s32 *)&temp_r8->unk0x98)) + ((temp_r11->unk0x98 * *((s32 *)&temp_r8->unk0x78)) + (temp_r11->unk0x9C * *((s32 *)&temp_r8->unk0x88))));
            sp64 = (temp_r11->unk0xA4 * *((s32 *)&temp_r8->unk0xAC)) + ((temp_r11->unk0xA0 * *((s32 *)&temp_r8->unk0x9C)) + ((temp_r11->unk0x98 * *((s32 *)&temp_r8->unk0x7C)) + (temp_r11->unk0x9C * *((s32 *)&temp_r8->unk0x8C))));
            sp68 = (temp_r11->unk0xB4 * *((s32 *)&temp_r8->unk0xA0)) + ((temp_r11->unk0xB0 * *((s32 *)&temp_r8->unk0x90)) + ((temp_r11->unk0xA8 * *((s32 *)&temp_r8->unk0x70)) + (temp_r11->unk0xAC * *((s32 *)&temp_r8->unk0x80))));
            sp6C = (temp_r11->unk0xB4 * *((s32 *)&temp_r8->unk0xA4)) + ((temp_r11->unk0xB0 * *((s32 *)&temp_r8->unk0x94)) + ((temp_r11->unk0xA8 * *((s32 *)&temp_r8->unk0x74)) + (temp_r11->unk0xAC * *((s32 *)&temp_r8->unk0x84))));
            sp70 = (temp_r11->unk0xB4 * *((s32 *)&temp_r8->unk0xA8)) + ((temp_r11->unk0xB0 * *((s32 *)&temp_r8->unk0x98)) + ((temp_r11->unk0xA8 * *((s32 *)&temp_r8->unk0x78)) + (temp_r11->unk0xAC * *((s32 *)&temp_r8->unk0x88))));
            sp74 = (temp_r11->unk0xB4 * *((s32 *)&temp_r8->unk0xAC)) + ((temp_r11->unk0xB0 * *((s32 *)&temp_r8->unk0x9C)) + ((temp_r11->unk0xA8 * *((s32 *)&temp_r8->unk0x7C)) + (temp_r11->unk0xAC * *((s32 *)&temp_r8->unk0x8C))));
            0;
            0;
            0;
            0;
            0;
            0;
            temp_f8 = arg0->unk0x24;
            temp_r9_3 = *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15C0) + 0x1C);
            temp_f7 = arg0->unk0x20;
            temp_f9 = arg0->unk0x28;
            temp_f10 = arg0->unk0x2C;
            sp28 = (temp_f10 * *((s32 *)&temp_r9_3->unk0xA0)) + ((temp_f9 * *((s32 *)&temp_r9_3->unk0x90)) + ((temp_f7 * *((s32 *)&temp_r9_3->unk0x70)) + (temp_f8 * *((s32 *)&temp_r9_3->unk0x80))));
            sp2C = (temp_f10 * *((s32 *)&temp_r9_3->unk0xA4)) + ((temp_f9 * *((s32 *)&temp_r9_3->unk0x94)) + ((temp_f7 * *((s32 *)&temp_r9_3->unk0x74)) + (temp_f8 * *((s32 *)&temp_r9_3->unk0x84))));
            sp30 = (temp_f10 * *((s32 *)&temp_r9_3->unk0xA8)) + ((temp_f9 * *((s32 *)&temp_r9_3->unk0x98)) + ((temp_f7 * *((s32 *)&temp_r9_3->unk0x78)) + (temp_f8 * *((s32 *)&temp_r9_3->unk0x88))));
            temp_f8_2 = arg0->unk0x34;
            temp_f7_2 = arg0->unk0x30;
            sp34 = (temp_f10 * *((s32 *)&temp_r9_3->unk0xAC)) + ((temp_f9 * *((s32 *)&temp_r9_3->unk0x9C)) + ((temp_f7 * *((s32 *)&temp_r9_3->unk0x7C)) + (temp_f8 * *((s32 *)&temp_r9_3->unk0x8C))));
            temp_f10_2 = arg0->unk0x3C;
            temp_f9_2 = arg0->unk0x38;
            sp38 = (temp_f10_2 * *((s32 *)&temp_r9_3->unk0xA0)) + ((temp_f9_2 * *((s32 *)&temp_r9_3->unk0x90)) + ((temp_f7_2 * *((s32 *)&temp_r9_3->unk0x70)) + (temp_f8_2 * *((s32 *)&temp_r9_3->unk0x80))));
            sp3C = (temp_f10_2 * *((s32 *)&temp_r9_3->unk0xA4)) + ((temp_f9_2 * *((s32 *)&temp_r9_3->unk0x94)) + ((temp_f7_2 * *((s32 *)&temp_r9_3->unk0x74)) + (temp_f8_2 * *((s32 *)&temp_r9_3->unk0x84))));
            sp40 = (temp_f10_2 * *((s32 *)&temp_r9_3->unk0xA8)) + ((temp_f9_2 * *((s32 *)&temp_r9_3->unk0x98)) + ((temp_f7_2 * *((s32 *)&temp_r9_3->unk0x78)) + (temp_f8_2 * *((s32 *)&temp_r9_3->unk0x88))));
            sp44 = (temp_f10_2 * *((s32 *)&temp_r9_3->unk0xAC)) + ((temp_f9_2 * *((s32 *)&temp_r9_3->unk0x9C)) + ((temp_f7_2 * *((s32 *)&temp_r9_3->unk0x7C)) + (temp_f8_2 * *((s32 *)&temp_r9_3->unk0x8C))));
            sp48 = (temp_r10->unk0x2C * *((s32 *)&temp_r9_3->unk0xA0)) + ((temp_r10->unk0x28 * *((s32 *)&temp_r9_3->unk0x90)) + ((temp_r10->unk0x20 * *((s32 *)&temp_r9_3->unk0x70)) + (temp_r10->unk0x24 * *((s32 *)&temp_r9_3->unk0x80))));
            temp_f6 = arg0->unk0x54;
            temp_f5 = arg0->unk0x50;
            sp4C = (temp_r10->unk0x2C * *((s32 *)&temp_r9_3->unk0xA4)) + ((temp_r10->unk0x28 * *((s32 *)&temp_r9_3->unk0x94)) + ((temp_r10->unk0x20 * *((s32 *)&temp_r9_3->unk0x74)) + (temp_r10->unk0x24 * *((s32 *)&temp_r9_3->unk0x84))));
            temp_f7_3 = arg0->unk0x58;
            temp_f8_3 = arg0->unk0x5C;
            sp50 = (temp_r10->unk0x2C * *((s32 *)&temp_r9_3->unk0xA8)) + ((temp_r10->unk0x28 * *((s32 *)&temp_r9_3->unk0x98)) + ((temp_r10->unk0x20 * *((s32 *)&temp_r9_3->unk0x78)) + (temp_r10->unk0x24 * *((s32 *)&temp_r9_3->unk0x88))));
            sp54 = (temp_r10->unk0x2C * *((s32 *)&temp_r9_3->unk0xAC)) + ((temp_r10->unk0x28 * *((s32 *)&temp_r9_3->unk0x9C)) + ((temp_r10->unk0x20 * *((s32 *)&temp_r9_3->unk0x7C)) + (temp_r10->unk0x24 * *((s32 *)&temp_r9_3->unk0x8C))));
            sp58 = (temp_f8_3 * *((s32 *)&temp_r9_3->unk0xA0)) + ((temp_f7_3 * *((s32 *)&temp_r9_3->unk0x90)) + ((temp_f5 * *((s32 *)&temp_r9_3->unk0x70)) + (temp_f6 * *((s32 *)&temp_r9_3->unk0x80))));
            sp5C = (temp_f8_3 * *((s32 *)&temp_r9_3->unk0xA4)) + ((temp_f7_3 * *((s32 *)&temp_r9_3->unk0x94)) + ((temp_f5 * *((s32 *)&temp_r9_3->unk0x74)) + (temp_f6 * *((s32 *)&temp_r9_3->unk0x84))));
            sp60 = (temp_f8_3 * *((s32 *)&temp_r9_3->unk0xA8)) + ((temp_f7_3 * *((s32 *)&temp_r9_3->unk0x98)) + ((temp_f5 * *((s32 *)&temp_r9_3->unk0x78)) + (temp_f6 * *((s32 *)&temp_r9_3->unk0x88))));
            sp64 = (temp_f8_3 * *((s32 *)&temp_r9_3->unk0xAC)) + ((temp_f7_3 * *((s32 *)&temp_r9_3->unk0x9C)) + ((temp_f5 * *((s32 *)&temp_r9_3->unk0x7C)) + (temp_f6 * *((s32 *)&temp_r9_3->unk0x8C))));
            0;
            0;
            0;
            0;
        }
    }
    var_r28 = 0;
    temp_f31_2 = *(f32 *)0x802AD428;
    do {
        var_r29 = 0;
        0;
        0;
        0;
        0;
        if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15BC) + 0xC4) == 0) {
            fn_801D4D74(arg0);
        }
        if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15BC) + 0xC4) != 0) {
            sp98 = *(f32 *)0x802AD420;
            spA0 = *(f32 *)0x802AD424;
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
            if (fn_801EC684(arg0, 0x10, 0) != 0) {
                temp_r30_12 = *(s32 *)((s32 *)((char *)arg0 + 0xB0) + 0x5A);
                fn_801F13D0(arg0->unk0x15BC, temp_r30_12);
                *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15A8) + 0x20) = temp_r30_12;
            }
        } else {
            fn_801D59F8(arg0);
        }
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
        if ((var_r28 == 0) && ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15BC) + 0x1C) == 0) && (spA8 < (spB0 - temp_f31_2))) {
            0;
            0;
            if (0 > *(s32 *)0x802AD410) {
                0;
                spBC = *(s32 *)0x802AD41C;
                0;
            }
            spC0 = spB0;
            var_r29 = 1;
            var_r28 = 1;
            spC8 = *(s32 *)0x802AD41C - (spA8 / spB0);
            0;
        }
    } while (var_r29 != 0);
    if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15BC) + 0x1C) == 0) {
        if ((s32) arg0->unk0x31C == 0) {
            fn_801DA88C(arg0);
        }
        if ((s32) arg0->unk0x400 == 0) {
            fn_801DB148(arg0, arg0->unk0xC + 0xB8);
        }
        if ((s32) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x15BC) + 0xC4) == 0) {
            fn_801DB240(arg0);
            fn_801DE248(arg0);
        }
        if ((s32) arg0->unk0x400 == 0) {
            fn_801DE50C(arg0);
        }
        if (fn_801DE800(arg0) != 0) {
            fn_801D657C(arg0);
            temp_r30_13 = arg0->unk0x15BC + 0x60;
            if ((s32) temp_r30_13->unk0x4 != 1) {
                temp_r30_13->unk0x4 = 1;
                temp_r30_13->unk0x8 = (s32) (*(s32 *)0x80303150 + Tmr_GetTime());
            }
            temp_r30_14 = arg0->unk0x15BC + 0x138;
            if ((s32) temp_r30_14->unk0x4 != 1) {
                temp_r30_14->unk0x4 = 1;
                temp_r30_14->unk0x8 = (s32) (*(s32 *)0x80303150 + Tmr_GetTime());
            }
        }
        fn_8020C58C(arg0->unk0x15AC, arg0->unk0x1D0);
        arg0->unk0x36C = (f32) *(s32 *)0x802AD410;
    }
}