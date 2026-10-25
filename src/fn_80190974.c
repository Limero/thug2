// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80190974-0x80190ACC (344B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A97D4[];
extern char lbl_80305EAC[];
s32 GetText(CStruct *, void *, void *, s32);
s32 Script_GenerateCRC(void *);
s32 fn_80174A58(void *, CStruct *);
u8 *fn_801A5848(s32);
s32 fn_801A572C(s32);
s32 fn_80191FD4(s32 *);
extern char *strstr(char *, char *);

u8 *fn_80190974(void *arg0) {
    u8 sp8[0x80];
    register u8 **pp __asm__("r30");
    u8 *sp88;
    u8 *sp8C;
    u8 *sp90;
    u8 *temp_r9;
    u8 *temp_r11;
    u8 *var_r3;
    u8 *base;
    char *temp_str;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;
    s32 var_r27;

    if (GetText(temp_r28 = fn_80191FD4(arg0), QB_PRO, &sp88, 0) == 0) {
        goto block_null;
    }
    var_r27 = 0;
    sp8C = fn_801A5848(temp_r29 = fn_80174A58(*(s32 *)&lbl_80305EAC, 0));
    if (fn_801A572C(temp_r29) != 0) {
        base = sp8;
        temp_str = strstr((char *)sp8C, (char *)lbl_802A97D4);
        pp = &sp8C;
            if (temp_str == NULL) {
                strcpy((char *)base, (char *)sp8C);
            } else {
                var_r3 = base;
                __asm__("" : "+r"(var_r3));
                if ((s32)*sp8C != 0x20) {
                    do {
                        temp_r9 = *pp;
                        *var_r3 = *temp_r9;
                        var_r3 += 1;
                        temp_r11 = *pp;
                        *pp = temp_r11 + 1;
                    } while ((s32)*(temp_r11 + 1) != 0x20);
                }
                *var_r3 = 0;
            }
            if (fn_801A572C(temp_r29) != 0) {
                temp_r30 = Script_GenerateCRC(sp8);
                if (temp_r30 == Script_GenerateCRC(sp88)) {
                    if (GetText(temp_r28, QB_ALTERNATE_PRO, &sp90, 0) == 0) {
                    block_null:
                        return NULL;
                    }
                    var_r27 = 1;
            }
        }
    }
    if (var_r27 != 0) {
        return sp90;
    }
    return sp88;
}
