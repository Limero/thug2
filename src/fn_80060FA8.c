// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80060FA8-0x80061140 (408B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
extern char lbl_80293EE8[];

s32 strcpy(s32, s32);
s32 strstr(s32, s32);
void strcat(s32, s32);
void LowerCase(s32);
s32 fn_8005CDF4(s32, s32, s32);
void Script_GetInteger(s32, s32);

s32 fn_80060FA8(CStruct *arg0, s32 arg1, s32 arg2, s32 arg3) {
    char sp8[0x200];
    char sp208[0x200];
    struct {
        void *volatile slot408;
        s32 pad40C;
        void *volatile slot410;
    } slots;
    Unk_C7387A53 *temp_r9;
    Unk_C7387A53 *temp_r9_3;
    CStruct *temp_r9_2;
    CStruct *head_tmp;
    CStruct *cur_tmp;
    CStruct *temp_r3s;
    CStruct *temp_r3b;
    s32 p208;
    char *temp_r3;
    void *var_r0;
    void *temp_r0;
    s32 var_r25;
    s32 var_r26;
    s32 temp_r0_2;

    temp_r9 = (Unk_C7387A53 *)arg0->unk0x50;
    var_r25 = (arg1 == 0xC4E78E22);
    var_r26 = 0;
    ((s32 (*)(void *))*(s32 *)((char *)temp_r9 + 0x5C))((char *)arg0 + *(s16 *)((char *)temp_r9 + 0x58));
    strcpy((s32)sp8, arg2);
    LowerCase((s32)sp8);
    if (strstr((s32)sp8, (s32)lbl_80293EE8) == 0) {
        strcat((s32)sp8, (s32)lbl_80293EE8);
    }
    strcpy((s32)sp208, arg3);
    LowerCase((s32)sp208);
    temp_r3 = (char *)strstr((s32)sp208, (s32)lbl_80293EE8);
    if (temp_r3 != 0) {
        *temp_r3 = 0;
    }
    temp_r9_2 = (CStruct *)arg0->unk0x10;
    var_r0 = 0;
    slots.slot408 = temp_r9_2;
    if (temp_r9_2 != 0) {
        var_r0 = (void *)temp_r9_2->unk0x4;
    }
    slots.slot410 = var_r0;
    if (var_r0 != temp_r9_2) {
        do {
            p208 = (s32)sp208;
            temp_r3s = (CStruct *)(*(s32 *)slots.slot410);
            temp_r0_2 = temp_r3s->unk0x8;
            if (((arg1 == temp_r0_2) || (var_r25 != 0) || (temp_r0_2 == 0)) && (temp_r3b = (CStruct *)(*(s32 *)slots.slot410), temp_r3b->unk0x4 != 0) && (fn_8005CDF4(temp_r3b->unk0x4, (s32)sp8, p208) != 0)) {
                var_r26 = 1;
            }
            cur_tmp = (CStruct *)slots.slot410;
            head_tmp = (CStruct *)slots.slot408;
            temp_r0 = (void *)cur_tmp->unk0x4;
            slots.slot410 = temp_r0;
        } while (temp_r0 != head_tmp);
    }
    if (var_r26 == 0) {
        Script_GetInteger(QB_CAS_ARTIST, 0);
    }
    temp_r9_3 = (Unk_C7387A53 *)arg0->unk0x50;
    ((s32 (*)(void *))*(s32 *)((char *)temp_r9_3 + 0x64))((char *)arg0 + *(s16 *)((char *)temp_r9_3 + 0x60));
    return var_r26;
}
