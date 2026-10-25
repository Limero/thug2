// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F1F74-0x800F2010 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "structs.h"
extern char lbl_8029B364[];
u32 strlen(const char *);
void strcpy(char *, const char *);
s32 sprintf();
bool fn_800F1F74(char *arg0, char *arg1) {
    char *p;
    char *q;

    p = &arg0[strlen(arg0) - 1];
    while (*p != '\\' && *p != '/') {
        p--;
    }
    strcpy(arg1, p + 1);
    q = arg1;
    while (*q != 0 && *q != '.') {
        q++;
    }
    sprintf(q, lbl_8029B364);
    return true;
}
