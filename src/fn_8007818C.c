// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007818C-0x80078274 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800780A8(s32, s32, s32, s32, u16 *, u8 *, u8 *, u8 *);
void fn_8007818C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u8 spC;
    u8 spB;
    u8 spA;
    u16 sp8;
    u32 i;
    u32 j;
    u32 c1;
    u32 c2;
    u8 *p0;
    u8 *p1;
    s32 off;
    s32 off2;
    u8 b0, b1, b2, b3;
    c1 = arg3 - arg5;
    c2 = arg2 - arg4;
    if (c1 > 4U) {
        c1 = 4U;
    }
    if (c2 > 4U) {
        c2 = 4U;
    }
    for (i = 0; i < c1; i++) {
        off = i * 8;
        p0 = arg6 + off;
        p1 = arg6 + (off2 = off + 0x20);
        for (j = 0; j < c2; j++) {
            fn_800780A8(arg0, arg2, arg4 + j, arg5 + i, &sp8, &spA, &spB, &spC);
            b0 = spC;
            b1 = *(u8 *)((char *)&sp8 + 1);
            b2 = spA;
            b3 = spB;
            *p0 = b0;
            *(p0 + 1) = b1;
            *p1 = b2;
            p0 += 2;
            *(p1 + 1) = b3;
            p1 += 2;
        }
    }
}
