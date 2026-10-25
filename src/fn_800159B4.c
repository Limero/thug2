// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800159B4-0x80015A30 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern bool lbl_802FFF74;
void CARDInit(void);
void *fn_800159B4(void *arg0) {
    char *blk;
    char *p_i;
    char *p_j;
    s32 i;
    s32 j;
    s32 off;
    s32 k;

    if (lbl_802FFF74 == 0) {
        lbl_802FFF74 = 1;
        CARDInit();
    }
    i = 0;
    blk = (char *)arg0;
    p_i = blk + 0x18;
    p_j = blk + 0x1C;
    do {
        j = 0;
        k = i + 1;
        off = i * 0x20;
        do {
            *(s32 *)(off + (s32)p_i) = i;
            *(s32 *)(off + (s32)p_j) = j;
            off += 0x20;
        } while (++j <= 0);
        i = k;
    } while (i <= 0);
    return arg0;
}
