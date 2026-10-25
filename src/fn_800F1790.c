// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F1790-0x800F18B0 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_80129528(s32, s32);
void GetChecksum_2(s32, s32, void *, s32);
void fn_800F1790(s32 arg0, s32 arg1) {
    u32 sp8;
    s32 spC;
    s32 n;
    char *base;
    char *walker;
    s16 m1;
    s16 m2;
    char *tab;
    s32 idx;
    s32 next;
    s32 off;
    s32 bo2;

    base = (char *)arg0 + 4;
    m1 = -1;
    walker = base;
    for (n = 0x4000; n != 0; n--) {
        if ((*(s16 *)walker != -1) && (*(u16 *)(walker - 2) == arg1)) {
            *(s16 *)walker = m1;
        }
        walker += 4;
    }
    tab = (char *)arg0 + 0x10010;
    idx = 0;
    m2 = -1;
    do {
        off = idx * 4;
        next = idx + 1;
        if (*(s16 *)(base + off) != -1) {
            s32 slot = off + arg0;
            u32 word = *(u32 *)((char *)slot + 2);
            *(s16 *)(base + off) = m2;
            sp8 = word;
            {
                s32 hi = (s32)(word >> 16);
                s32 entry = *(s32 *)(tab + hi * 12);
                s32 lo = (s16)(*(u16 *)((char *)&sp8 + 2));
                s32 *pp = &spC;
                GetChecksum_2(fn_80129528(entry, lo), 0xA1DC81F9, (spC = 0, pp), 1);
            }
            {
                u32 j = (*(u16 *)((char *)&spC + 2)) & 0x3FFF;
                s32 bo = (s32)(j * 4);
                if (*(s16 *)(base + bo) != -1) {
                    register s32 probe __asm__("r10");
                    probe = (s32)base;
                    do {
                        j = (j + 1) & 0x3FFF;
                        bo2 = (s32)(j * 4);
                    } while (*(s16 *)((char *)probe + bo2) != -1);
                }
                *(u32 *)((char *)((s32)(j * 4) + arg0) + 2) = sp8;
            }
        }
        idx = next;
    } while (idx <= 0x3FFF);
}
