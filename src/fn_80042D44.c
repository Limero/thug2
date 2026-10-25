// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80042D44-0x80042DE8 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char _0[0x190];
    char *f190;
} X;

void fn_800427AC(X *arg0, char *arg1);
char *strcpy(char *, const char *);
u32 strlen(const char *);

bool fn_80042D44(X *arg0) {
    char buf[0x60];
    s32 len;

    if (arg0->f190 == 0) {
        return false;
    }
    len = strlen(arg0->f190);
    if (len == 0) {
        return false;
    }
    strcpy(buf, arg0->f190);
    if (len > 1 && buf[len - 1] == 0x5c && buf[len - 2] == 0x5c) {
        buf[len - 2] = 0;
    }
    buf[len - 1] = 0;
    fn_800427AC(arg0, buf);
    return true;
}
