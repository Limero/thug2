// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80154BAC-0x80154DF8 (588B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_802A7F30[];
extern char lbl_802A7F48[];
extern char lbl_802A7F4C[];
extern char lbl_802A7F50[];
extern char lbl_802A7F54[];
extern s32 GetText(CStruct *, void *, void *, s32);
extern u32 strlen(void *);
extern void Script_RunScript(s32, s32, s32, s32, s32);
extern s32 Script_GenerateCRC(void *);
extern void *fn_801259C8(s32, s32);
extern void *fn_80129528(CStruct *, s32);
extern s32 fn_80128CB0(CStruct *, void *, void *, s32);
extern s32 fn_80128E64(CStruct *, void *, void *, s32);

bool ScriptTryCheatString(CStruct *pParams, CScript *pScript) {
    s32 sp94;
    s32 sp90;
    s32 sp8C;
    u8 *sp88;
    u8 sp8[0x80];
    s32 temp_r25;
    s32 temp_r28;
    s32 temp_r29;
    void *temp_r30;
    s32 temp_r5;
    s32 var_r26;
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;
    s32 var_r3;
    u8 *var_r10;
    u8 temp_r0;
    u8 temp_r11;
    CStruct *arr;

    GetText(pParams, QB_STRING, &sp88, 1);
    if (strlen(sp88) <= 5U) {
        Script_RunScript(QB_CHEAT_PLAYSOUND_BAD, 0, 0, 0, 0);
    } else {
        sprintf(sp8, lbl_802A7F30);
        var_r29 = 0;
        var_r30 = 0;
        sprintf(sp8, sp88);
        var_r3 = Script_GenerateCRC(sp88);
        do {
            temp_r5 = var_r30 + var_r3;
            var_r30 += 1;
            sprintf(sp8, lbl_802A7F48, temp_r5);
            sp8[strlen(sp8)] = 0x58;
            var_r10 = sp8;
            if (sp8[0] != 0) {
                do {
                    temp_r0 = *(u8 *)var_r10;
                    temp_r11 = *(u8 *)(++var_r10);
                    var_r29 += ((s8) temp_r0 << 0xA) - (s8) temp_r0;
                } while ((s32) temp_r11 != 0);
            }
            var_r3 = Script_GenerateCRC(sp8);
        } while (var_r30 <= 0x1869F);
        var_r26 = 0;
        var_r31 = 0;
        temp_r28 = Script_GenerateCRC(&sp88[strlen(sp88) / 3]);
        temp_r25 = Script_GenerateCRC(sp8);
        temp_r28 = temp_r28 ^ var_r29;
        temp_r25 = temp_r25 ^ var_r29;
        arr = fn_801259C8(QB_CHEAT_ARRAY_GAMECUBE, 0);
        temp_r29 = arr->unk0x4;
        if (var_r26 < temp_r29) {
            do {
                temp_r30 = fn_80129528(arr, var_r31);
                fn_80128CB0(temp_r30, (s32)lbl_802A7F4C, &sp8C, 1);
                fn_80128CB0(temp_r30, (s32)lbl_802A7F50, &sp90, 1);
                fn_80128E64(temp_r30, (s32)lbl_802A7F54, &sp94, 1);
                if (sp8C == temp_r28) {
                    if (sp90 == temp_r25) {
                        Script_RunScript(QB_CHEAT_PLAYSOUND_GOOD, 0, 0, 0, 0);
                        var_r26 = 1;
                        Script_RunScript(sp94, 0, 0, 0, 0);
                    }
                }
                var_r31 += 1;
            } while (var_r31 < temp_r29);
        }
        if (var_r26 == 0) {
            Script_RunScript(QB_CHEAT_PLAYSOUND_BAD, 0, 0, 0, 0);
        }
    }
    return false;
}
