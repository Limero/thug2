// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80161044-0x80161108 (196B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 strlen(char *);

s32 GetString(CStruct *, s32 *, s32 *, s32);
void AddString(CStruct *, s32, void *);

bool ScriptGetTextureFromPath(CStruct *pParams, CScript *pScript) {
    u8 sp8[32];
    s32 sp28;
    s32 temp_r3;
    s32 var_r9;
    s32 var_r11;
    u8 temp_r0;
    s32 var_r31;
    char *p;

    var_r31 = 0;
    GetString(pParams, QB_PATH, &sp28, 1);
    temp_r3 = strlen((char *)sp28);
    var_r9 = temp_r3;
    if (temp_r3 >= 0) {
        p = (char *)sp28;
        temp_r0 = *(u8 *)(p + temp_r3);
        goto check;
        do {
            var_r9 -= 1;
            if (var_r9 < 0) {
                break;
            }
            temp_r0 = *(u8 *)(p + var_r9);
        check:;
        } while (((s8)temp_r0 != '/') && ((s8)temp_r0 != '\\'));
    }
    for (var_r11 = var_r9 + 1; var_r11 <= temp_r3; var_r11 += 1) {
        sp8[var_r31] = *(u8 *)((char *)sp28 + var_r11);
        var_r31 += 1;
    }
    AddString(pScript->unk0x18, QB_TEXTURE, sp8);
    return true;
}
