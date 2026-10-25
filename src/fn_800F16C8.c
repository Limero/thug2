// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F16C8-0x800F1790 (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, void *, s32 *, void *);
void fn_800F16C8(s32 arg0, s16 arg1, s16 arg2, CStruct *arg3) {
    s32 sp8;
    s32 spC;
    u32 idx;
    char *base;
    s32 bo;
    {
        register s32 probe __asm__("r10");
        s16 *keys;

        sp8 = 0;
        GetChecksum_2(arg3, QB_CLASS, &sp8, 0);
        if (sp8 != -QB_UNKNOWN_0x36AC99F2) {
            spC = 0;
            if (GetChecksum_2(arg3, QB_NAME, &spC, 0) != 0) {
                idx = *(u16 *)((char *)&spC + 0x2) & 0x3FFF;
                base = (char *)arg0 + 4;
                probe = (s32)base;
                keys = (s16 *)(arg0 + 2);
                while (1) {
                    bo = (s32)(idx * 4);
                    if (*(s16 *)((char *)base + bo) == -1) break;
                    idx = (idx + 1) & 0x3FFF;
                }
                *(s16 *)((char *)probe + idx * 4) = arg2;
                *(s16 *)((char *)keys + idx * 4) = arg1;
            }
        }
    }
}
