// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80121314-0x801213D0 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8039B8D0[];
extern s32 lbl_80303030[];
extern char lbl_8029DE44[];
extern s32 lbl_80302F28;
extern s32 lbl_8039B8CC;
s32 fn_8000A778(s32);
s32 fn_80120824(char *, s32);
char *strchr(const char *, int);
int sprintf(char *, const char *, ...);

s32 fn_80121314(s32 arg0) {
    s32 i;
    char *p;

    lbl_8039B8CC = arg0;
    lbl_80302F28 = 0;
    for (i = 0; i <= 0x42U; i++) {
        p = strchr((char *)lbl_80303030[i], '/');
        if ((p != 0) && (arg0 == fn_8000A778(p + 1))) {
            sprintf(lbl_8039B8D0, lbl_8029DE44, lbl_80303030[i]);
            return fn_80120824(lbl_8039B8D0, 1);
        }
    }
    lbl_8039B8D0[0] = 0;
    return 0;
}
