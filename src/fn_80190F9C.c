// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80190F9C-0x80191050 (180B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A97D4[];
extern u8 lbl_802A9804;
extern char lbl_80305EAC[];
s32 fn_80174A58(void *, CStruct *);
u8 *fn_801A5848(s32);
extern char *strstr(char *, char *);

void fn_80190F9C(s32 arg0, u8 *arg1) {
    u8 *sp8;
    u8 **pp;
    u8 *temp_r9;
    u8 *var_r3;

    sp8 = fn_801A5848(fn_80174A58(*(s32 *)&lbl_80305EAC, 0));
    pp = &sp8;
    *arg1 = lbl_802A9804;
    if (strstr((char *)sp8, (char *)lbl_802A97D4) == 0) {
        strcpy((char *)arg1, (char *)sp8);
        return;
    }
    var_r3 = arg1;
    if ((s32)*sp8 != 0x20) {
        do {
            temp_r9 = *pp;
            *var_r3 = *temp_r9;
            var_r3 += 1;
            *pp = temp_r9 + 1;
        } while ((s32)*(temp_r9 + 1) != 0x20);
    }
    *var_r3 = 0;
}
