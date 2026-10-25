// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EC3F0-0x801EC620 (560B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800F0F84(s32, s32);
s32 GetChecksum_2(s32, s32, s32 *, s32);
extern s32 Tmr_GetTime(void);
void Mem_Free(void *);
void fn_800DF24C(void *, void *, void *, void *, void *);
extern s32 lbl_80305EAC;
extern s32 lbl_80303150;
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_801EC3F0(Unk_83A1E37F *arg0, void *arg1) {
    s32 spC;
    s32 ck;
    s32 sp8;
    s32 temp_r30;
    CStruct *temp_r31_2;
    s32 var_r7;
    s32 temp_r26;
    s32 var_r0;
    s32 var_r11;
    s32 var_r27;
    s32 var_r29;
    Unk_C8FEE62D *temp_r29;
    Unk_C7387A53 *var_r30;
    Unk_C7387A53 *var_r31;
    Unk_C7387A53 *head;
    CStruct *var_r31_2;
    if ( arg0->unk0x25C != NULL) {
        if ((s32) arg0->unk0x260 == 0) {
            arg0->unk0x260 = *(s32 *)((char *)lbl_80305EAC + 0x28);
        }
        var_r31 = arg0->unk0x25C;
        head = var_r31;
        var_r29 = fn_800F0F84(var_r31->unk0x54, 0);
        if (var_r29 != 0) {
            sp8 = 0;
            if (GetChecksum_2(var_r29, QB_TRIGGERSCRIPT, &sp8, 0) == 0) {
                var_r30 = var_r31;
                var_r27 = 0;
                var_r31 = var_r31->unk0x4C;
                while (var_r31 != NULL && var_r31 != head && var_r31 != var_r30) {
                    var_r29 = fn_800F0F84(var_r31->unk0x54, 1);
                    if (GetChecksum_2(var_r29, QB_TRIGGERSCRIPT, &sp8, 0) != 0) {
                        break;
                    }
                    var_r31 = var_r31->unk0x4C;
                    if (var_r27 != 0) {
                        var_r30 = var_r30->unk0x4C;
                    }
                    var_r27 ^= 1;
                }
            }
            if (sp8 != 0) {
                GetChecksum_2(var_r29, QB_NAME, &spC, 1);
                if (spC != (s32) arg0->unk0x274) {
                    var_r31_2 = arg0->unk0x15BC + 0x120;
                    if ((s32) var_r31_2->unk0x4 != 1) {
                        var_r31_2->unk0x4 = 1;
                        var_r31_2->unk0x8 = lbl_80303150 + Tmr_GetTime();
                    }
                } else {
                    var_r31_2 = arg0->unk0x15BC + 0x120;
                    if ((s32) var_r31_2->unk0x4 != 0) {
                        var_r31_2->unk0x4 = 0;
                        var_r31_2->unk0x8 = lbl_80303150 + Tmr_GetTime();
                    }
                }
                ck = spC;
                temp_r29 = arg0->unk0x15C0;
                arg0->unk0x270 = ck;
                arg0->unk0x274 = ck;
                temp_r26 = arg0->unk0x15A4;
                temp_r31_2 = temp_r29->unk0x1C;
                if (temp_r31_2 == NULL) {
                    var_r11 = 0;
                } else {
                    temp_r30 = temp_r31_2->unk0x0;
                    if (temp_r30 != NULL) {
                        var_r11 = 1;
                    } else {
                        temp_r29->unk0x70 = temp_r30;
                        if (temp_r31_2->unk0x0 != NULL) {
                            CObject_RemoveRefLink(temp_r31_2->unk0x0, temp_r31_2);
                            temp_r31_2->unk0x0 = temp_r30;
                        }
                        Mem_Free(temp_r31_2);
                        temp_r29->unk0x1C = temp_r30;
                        temp_r29->unk0x74 = lbl_80303150 + Tmr_GetTime();
                        var_r11 = 0;
                    }
                }
                if (var_r11 != 0) {
                    var_r7 = *(s32 *)arg0->unk0x15C0->unk0x1C;
                } else {
                    var_r7 = 0;
                }
                fn_800DF24C(temp_r26, arg1, ck, 0, var_r7);
            }
        }
    }
}
