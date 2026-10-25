// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F18D8-0x800F198C (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
#include "qb_constants.h"
// FLAG: -fno-gcse
extern s32 fn_80129528(s32, s32);
extern void GetChecksum_2(s32, s32, void *, s32);
s32 fn_800F18D8(s32 arg0, s32 arg1) {
    s32 sp8;
    s32 res;
    register s32 zero __asm__("r25");
    char *base;
    char *base2;
    char *tab;
    char *n2;
    s32 idx;
    s32 bo;
    s32 lo;
    s32 entry;
    s32 hi;

    base = (char *)arg0 + 4;
    idx = arg1 & 0x3FFF;
    bo = idx * 4;
    if (*(s16 *)(base + bo) == -1) {
        return 0;
    }
    tab = (char *)arg0 + 0x10010;
    base2 = base;
    n2 = (char *)arg0 + 2;
    zero = 0;
    for (;;) {
        hi = *(u16 *)(n2 + bo);
        lo = *(s16 *)(base2 + bo);
        entry = *(s32 *)(tab + hi * 0xC);
        GetChecksum_2(res = fn_80129528(entry, lo), QB_NAME, (sp8 = zero, &sp8), 1);
        if (sp8 != arg1) {
            idx = (idx + 1) & 0x3FFF;
            bo = idx * 4;
            if (*(s16 *)(base2 + bo) == -1) {
                return 0;
            }
            continue;
        }
        return res;
    }
}
