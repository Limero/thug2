// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243C18-0x80243C84 (108B). Byte-identical.
#include "types.h"
void strcpy(char *, char *);

s32 fn_80243C18(s32 arg0, s32 arg1, s32 *arg2) {
    char *base = (char *)arg0 + 4;
    s32 off = arg1 * 4;

    if (*(s32 *)(base + off) != 0) {
        char *fb = (char *)arg0 + 0x84;
        *arg2 = *(s32 *)(fb + off) == 0;
        strcpy(*(char **)(base + off) + 0xC0, *(char **)(base + off) + 0x1C);
        return (s32)*(s32 *)(base + off) + 0x9C;
    }
    return 0;
}
