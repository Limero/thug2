// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AB474-0x800AB508 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8037BB68[];
extern char lbl_8029852C[];
s32 strlen(const char *s);
char *strcpy(char *dst, const char *src);
char *strstr(const char *hay, const char *needle);
char *fn_800AB474(char *arg0) {
    s32 i;
    s8 c;
    char *p;

    i = strlen(arg0);
    for (; i >= 0; i--) {
        c = arg0[i];
        if (c == 0x5C) {
            goto found;
        }
        if (c != 0x2F) {
            continue;
        }
    found:
        strcpy(lbl_8037BB68, arg0 + (i + 1));
        break;
    }
    p = strstr(lbl_8037BB68, lbl_8029852C);
    if (p != NULL) {
        *p = 0;
    }
    return lbl_8037BB68;
}
