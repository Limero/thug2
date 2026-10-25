// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012AD8-0x80012B78 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8031349C[];
int strcasecmp(const char *, const char *);
s32 fn_80012AD8(char *arg0) {
    if (arg0 == NULL) {
        s32 i;
        for (i = 0; i < 0x64; i++) {
            s32 v = ((s32 *)lbl_8031349C)[i];
            if (v != 0) {
                return v;
            }
        }
    } else {
        s32 found = 0;
        s32 p = (s32)lbl_8031349C;
        s32 end = (s32)lbl_8031349C + 0x18C;
        do {
            s32 v = *(s32 *)p;
            p += 4;
            if (v != 0) {
                if (found != 0) {
                    return v;
                }
                if (strcasecmp((char *)v, arg0) == 0) {
                    found = 1;
                }
            }
        } while (p <= end);
    }
    return 0;
}
