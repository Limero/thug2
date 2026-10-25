// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80193770-0x801937EC (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8012720C(CStruct *, s32);
void fn_80193770(Unk_72E9CBBF *arg0) {
    s32 ctr;
    s32 *p10;
    char *p9;
    s32 z;
    s32 one;

    ctr = 0x1E;
    arg0->unk0x4AC = 0;
    arg0->unk0x4B0 = 0;
    z = 0;
    one = 1;
    p10 = (s32 *)((char *)arg0 + 0x4B4);
    p9 = (char *)arg0 + 0x88;
    do {
        *(s32 *)(p9 - 4) = z;
        *(s32 *)(p9 - 0x14) = z;
        *(s32 *)(p9 - 0x10) = z;
        *(s32 *)(p9 - 0xC) = z;
        *(s32 *)(p9 + 8) = z;
        *(s32 *)(p9 + 0xC) = one;
        *(s32 *)p9 = z;
        *(s32 *)p10 = z;
        p9 += 0x24;
        p10 += 1;
        ctr -= 1;
    } while (ctr != 0);
    fn_8012720C(arg0->unk0x20, QB_SINGLE_COMBO_ADDED);
}
