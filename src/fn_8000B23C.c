// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000B23C-0x8000B348 (268B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern u8 _ctype_[];
u32 strlen(const char *);
s32 strcasecmp(const char *, const char *);
// CommandLineContainsFlag @ 0x8000B23C
bool CommandLineContainsFlag(s8 *arg0, s32 argc, s8 **argv) {
    s8 buf1[0x100];
    s8 buf2[0x100];
    u32 i;
    s32 n;
    s32 c;
    if (arg0 == 0) return false;
    i = 0;
    while (i < strlen((const char *)arg0) + 1) {
        c = (s8)arg0[i];
        if (*(u8 *)(c + (s32)(_ctype_ + 1)) & 1) c += 0x20;
        buf1[i] = (s8)c;
        i++;
    }
    for (n = 0; n < argc; n++) {
        i = 0;
        while (i < strlen((const char *)argv[n]) + 1) {
            c = (s8)argv[n][i];
            if (*(u8 *)(c + (s32)(_ctype_ + 1)) & 1) c += 0x20;
            buf2[i] = (s8)c;
            i++;
        }
        if (strcasecmp((const char *)buf2, (const char *)buf1) == 0) return true;
    }
    return false;
}
