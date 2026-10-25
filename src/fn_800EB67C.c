// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EB67C-0x800EB8F8 (636B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 Mem_Free(s32);
extern char lbl_80303150[];
s32 fn_801080D4(Unk_0352A96C *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
s32 *fn_80108F94(Unk_DF3972E8 *, CStruct *);                           
s32 fn_80108104(Unk_C7387A53 *o);
s32 Tmr_GetTime(void);
Unk_DB0E2BAB * Mem_Alloc2(s32 arg0);
bool fn_800EB67C(Unk_C8FEE62D *arg0,Unk_0352A96C * arg1) {
    s32 *temp_r30;
    s32 *temp_r30_2;
    s32 *temp_r30_3;
    s32 *temp_r30_4;
    s32 *temp_r30_6;
    s32 *temp_r30_7;
    s32 *temp_r31;
    s32 *temp_r31_2;
    s32 *temp_r31_3;
    s32 temp_r30_5;
    s32 var_r11;
    s32 var_r11_2;
    s32 var_r11_3;
    if (fn_801080D4(arg1) != 0) {
        temp_r30 = arg0->unk0x1C;
        if (temp_r30 == NULL) {
            var_r11 = 0;
        } else {
            temp_r31 = *((s32 *)temp_r30);
            if (temp_r31 != NULL) {
                var_r11 = 1;
            } else {
                arg0->unk0x70 = temp_r31;
                if ((s32 *) *((s32 *)temp_r30) != NULL) {
                    CObject_RemoveRefLink(*(s32 *)((char *)temp_r30), temp_r30);
                    *((s32 *)temp_r30) = temp_r31;
                }
                Mem_Free(temp_r30);
                arg0->unk0x1C = temp_r31;
                arg0->unk0x74 = (s32) (*(s32 *)lbl_80303150 + Tmr_GetTime());
                var_r11 = 0;
            }
        }
        if (var_r11 != 0) {
            temp_r30_2 = **((s32 * *)&arg0->unk0x1C);
            if (temp_r30_2 != fn_80108104(arg1)) {
                temp_r30_3 = arg0->unk0x1C;
                if (temp_r30_3 != NULL) {
                    arg0->unk0x70 = (s32 *) *((s32 *)temp_r30_3);
                    if ((s32 *) *((s32 *)temp_r30_3) != NULL) {
                        CObject_RemoveRefLink(*(s32 *)((char *)temp_r30_3), temp_r30_3);
                        *((s32 *)temp_r30_3) = NULL;
                    }
                    Mem_Free(temp_r30_3);
                    temp_r30_3 = 0;
                    arg0->unk0x1C = temp_r30_3;
                    arg0->unk0x74 = (s32) (*(s32 *)lbl_80303150 + Tmr_GetTime());
                    goto block_14;
                }
                goto block_15;
            }
        }
block_14:
        temp_r30_4 = arg0->unk0x1C;
        if (temp_r30_4 == NULL) {
block_15:
            var_r11_2 = 0;
        } else {
            temp_r31_2 = *((s32 *)temp_r30_4);
            if (temp_r31_2 != NULL) {
                var_r11_2 = 1;
            } else {
                arg0->unk0x70 = temp_r31_2;
                if ((s32 *) *((s32 *)temp_r30_4) != NULL) {
                    CObject_RemoveRefLink(*(s32 *)((char *)temp_r30_4), temp_r30_4);
                    *((s32 *)temp_r30_4) = temp_r31_2;
                }
                Mem_Free(temp_r30_4);
                arg0->unk0x1C = temp_r31_2;
                arg0->unk0x74 = (s32) (*(s32 *)lbl_80303150 + Tmr_GetTime());
                var_r11_2 = 0;
            }
        }
        if (var_r11_2 == 0) {
            temp_r30_5 = Mem_Alloc2(0xB8);
            arg0->unk0x1C = fn_80108F94(temp_r30_5, fn_80108104(arg1));
            return true;
        }
        goto block_35;
    }
    temp_r30_6 = arg0->unk0x1C;
    if (temp_r30_6 == NULL) {
        var_r11_3 = 0;
    } else {
        temp_r31_3 = *((s32 *)temp_r30_6);
        if (temp_r31_3 != NULL) {
            var_r11_3 = 1;
        } else {
            arg0->unk0x70 = temp_r31_3;
            if ((s32 *) *((s32 *)temp_r30_6) != NULL) {
                CObject_RemoveRefLink(*(s32 *)((char *)temp_r30_6), temp_r30_6);
                *((s32 *)temp_r30_6) = temp_r31_3;
            }
            Mem_Free(temp_r30_6);
            arg0->unk0x1C = temp_r31_3;
            arg0->unk0x74 = (s32) (*(s32 *)lbl_80303150 + Tmr_GetTime());
            var_r11_3 = 0;
        }
    }
    if (var_r11_3 != 0) {
        temp_r30_7 = arg0->unk0x1C;
        if (temp_r30_7 != NULL) {
            arg0->unk0x70 = (s32 *) *((s32 *)temp_r30_7);
            if ((s32 *) *((s32 *)temp_r30_7) != NULL) {
                CObject_RemoveRefLink(*(s32 *)((char *)temp_r30_7), temp_r30_7);
                *((s32 *)temp_r30_7) = NULL;
            }
            Mem_Free(temp_r30_7);
            temp_r30_7 = 0;
            arg0->unk0x1C = temp_r30_7;
            arg0->unk0x74 = (s32) (*(s32 *)lbl_80303150 + Tmr_GetTime());
        }
    }
block_35:
    return false;
}
