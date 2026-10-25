// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80061140-0x800612A8 (360B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80366474;
extern char lbl_80293EE8[];

s32 strcpy(s32, s32);
s32 strstr(s32, s32);
void strcat(s32, s32);
void LowerCase(s32);
s32 fn_8005CF80(s32, s32);
s32 fn_8005CE88(s32, s32, s32);
void Script_GetInteger(s32, s32);

s32 fn_80061140(CStruct *arg0, s32 arg1, s32 arg2, s32 arg3) {
    char sp8[0x200];
    struct {
        void * volatile slot208;
        s32 pad20c;
        void * volatile slot210;
    } slots;
    CStruct *temp_r9_2;
    void *var_r0;
    s32 tmp_r28;
    s32 var_r25;
    s32 var_r26;
    Unk_C7387A53 *temp_r9;
    Unk_C7387A53 *temp_r9_3;
    CStruct *temp_r3;
    void *temp_r0;
    CStruct *cur_tmp;
    void *head_tmp;

    temp_r9 = (Unk_C7387A53 *)arg0->unk0x50;
    var_r25 = (arg1 == 0xC4E78E22);
    var_r26 = 0;
    ((s32 (*)(void *))*(s32 *)((char *)temp_r9 + 0x5C))((char *)arg0 + *(s16 *)((char *)temp_r9 + 0x58));
    strcpy((s32)sp8, arg2);
    LowerCase((s32)sp8);
    if (strstr((s32)sp8, (s32)lbl_80293EE8) == 0) {
        strcat((s32)sp8, (s32)lbl_80293EE8);
    }
    tmp_r28 = fn_8005CF80(lbl_80366474, arg3);
    temp_r9_2 = (CStruct *)arg0->unk0x10;
    var_r0 = NULL;
    slots.slot208 = temp_r9_2;
    if (temp_r9_2 != NULL) {
        var_r0 = (void *)temp_r9_2->unk0x4;
    }
    slots.slot210 = var_r0;
    if (var_r0 != temp_r9_2) {
        do {
            temp_r3 = (CStruct *)((CStruct *)slots.slot210)->unk0x0;
            if (((arg1 == temp_r3->unk0x8) || (var_r25 != 0)) && (temp_r3->unk0x4 != 0) && (fn_8005CE88(temp_r3->unk0x4, (s32)sp8, tmp_r28) != 0)) {
                var_r26 = 1;
            }
            cur_tmp = (CStruct *)slots.slot210;
            head_tmp = (void *)slots.slot208;
            temp_r0 = (void *)cur_tmp->unk0x4;
            slots.slot210 = temp_r0;
        } while (temp_r0 != head_tmp);
    }
    if (var_r26 == 0) {
        Script_GetInteger(QB_CAS_ARTIST, 0);
    }
    temp_r9_3 = (Unk_C7387A53 *)arg0->unk0x50;
    ((s32 (*)(void *))*(s32 *)((char *)temp_r9_3 + 0x64))((char *)arg0 + *(s16 *)((char *)temp_r9_3 + 0x60));
    return var_r26;
}
