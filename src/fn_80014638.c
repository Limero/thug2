// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014638-0x800146A4 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80314330[];
void *fn_80014638(void) {
    s32 i;
    s32 one;
    s32 magic;
    char *b;
    char *p;

    i = 3;
    b = lbl_80314330;
    magic = 0x1234ABCD;
    one = 1;
    p = lbl_80314330 + 0x84;
    for (; i != 0; i--) {
        if (*(s32 *)(p - 0x70) == 0) {
            *(s32 *)(p - 0x70) = one;
            *(s32 *)(p + 0x64) = 0;
            *(s32 *)(p + 0x68) = 0;
            *(s32 *)(p + 0x70) = 0;
            *(s32 *)(p + 0x74) = 0;
            *(s32 *)(p + 0x24) = 0;
            *(s32 *)p = magic;
            return b;
        }
        b += 0xFC;
        p += 0xFC;
    }
    __asm__ volatile("li 0,3\n\tmtctr 0\n\tbdnz .");
    return 0;
}
