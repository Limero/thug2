// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80154A8C-0x80154B54 (200B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305EC0;
extern void *fn_801746A4(Unk_C7387A53 *, s32);
extern s32 fn_80198D70(void *);
extern s32 fn_8005DE84(void);
extern void fn_8005E08C(s32);
extern s32 fn_801403CC(void *);
extern void fn_80182AA8(s32);
bool ScriptSetScreenModeFromGameMode(CStruct *pParams, CScript *pScript) {
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r3_3;
    u32 var_r31;
    Unk_FFAD6788 *temp_r3_2;

    temp_r30 = lbl_80305EAC;
    var_r31 = 0U;
    do {
        fn_801746A4(temp_r30, var_r31);
        var_r31 += 1;
    } while (var_r31 <= 7U);
    temp_r31 = fn_80198D70((void *)lbl_80305EC0);
    temp_r3 = fn_8005DE84();
    if (((temp_r31 != 1) || (temp_r3 != 2)) && ((temp_r31 != 2) || (temp_r3 != 1))) {
        fn_8005E08C(temp_r31);
    }
    var_r31 = 0U;
    do {
        temp_r3_2 = fn_801746A4(temp_r30, var_r31);
        if ((temp_r3_2 != NULL) && (temp_r3_2->unk0xC8 != 0)) {
            temp_r3_3 = fn_801403CC(temp_r3_2);
            if (temp_r3_3 != 0) {
                fn_80182AA8(temp_r3_3);
            }
        }
        var_r31 += 1;
    } while (var_r31 <= 7U);
    return true;
}
