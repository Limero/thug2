// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009628-0x80009738 (272B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern char lbl_8028FEFC[];
extern s32 lbl_802FFE48;
extern char lbl_80311268[];

s32 sprintf();
u32 strlen(const char *);

// PrintThousands @ 0x80009628
char* PrintThousands(s32 arg0, char arg1) {
    char *bufPtr;
    char str[32];
    char *strPtr;
    char sep;
    s32 len;

    bufPtr = lbl_80311268;

    if (arg0 < 0) {
        *bufPtr++ = '-';
        arg0 = -arg0;
    }

    sprintf(str, (s32)lbl_8028FEFC, arg0);
    len = strlen(str);
    strPtr = str;

    switch (lbl_802FFE48) {
    case 3:
        sep = ' ';
        break;
    case 4:
        sep = '.';
        break;
    case 5:
        sep = '.';
        break;
    case 6:
        sep = '.';
        break;
    default:
        sep = ',';
        break;
    }

    while (len != 0) {
        *bufPtr++ = *strPtr++;
        len--;

        if (len != 0 && len % 3 == 0) {
            *bufPtr++ = sep;
        }
    }

    *bufPtr++ = 0;

    return lbl_80311268;
}
