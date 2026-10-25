// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010C6C0-0x8010C86C (428B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_80119470(void);
extern s32 GetString(CStruct *, s32 *, s32 *, s32);
extern void strcpy(void *, void *);
extern s32 strlen(void *);
extern s32 Script_GenerateCRC(s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern char lbl_8029CE18[];
extern f32 lbl_8029CE1C;
extern f32 lbl_8029CE20;

bool fn_8010C6C0(CStruct *arg0, Unk_01476648 *arg1) {
    void *volatile sp8;
    f32 temp_f0;
    f32 temp_f13;
    char *var_r30;
    s32 temp_r0;
    s32 temp_r3;
    s32 var_r11;

    temp_r0 = fn_80119470();
    if (temp_r0 != 0) {
        return false;
    }
    temp_f0 = lbl_8029CE1C;
    temp_f13 = lbl_8029CE20;
    arg1->unk0x68 = temp_r0;
    arg1->unk0x78 = temp_f13;
    arg1->unk0x80 = temp_f0;
    sp8 = lbl_8029CE18;
    arg1->unk0x0 = (u8)temp_r0;
    arg1->unk0x6C = temp_f0;
    arg1->unk0x70 = temp_f0;
    arg1->unk0x74 = temp_f0;
    arg1->unk0x7C = temp_f0;
    if (GetString(arg0, QB_SOUND, &sp8, 0) == 0) {
        return false;
    }
    var_r30 = (char *)arg1;
    strcpy(arg1, sp8);
    temp_r3 = strlen(arg1);
    for (var_r11 = 0; var_r11 < temp_r3; var_r11++) {
        char c = ((char *)arg1)[var_r11];
        if (c == '\\' || c == '/') {
            var_r30 = (char *)arg1 + (var_r11 + 1);
        }
    }
    *((s32 *)&arg1->unk0x68) = Script_GenerateCRC(var_r30);
    GetFloat(arg0, QB_MAXPITCH, (f32 *)((char *)arg1 + 0x6c), 0);
    GetFloat(arg0, QB_MINPITCH, (f32 *)((char *)arg1 + 0x70), 0);
    GetFloat(arg0, QB_MAXVOL, (f32 *)((char *)arg1 + 0x74), 0);
    GetFloat(arg0, QB_MINVOL, (f32 *)((char *)arg1 + 0x78), 0);
    GetFloat(arg0, QB_LOADPITCH, (f32 *)((char *)arg1 + 0x7c), 0);
    GetFloat(arg0, QB_LOADVOL, (f32 *)((char *)arg1 + 0x80), 0);
    return true;
}
