// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001CECC-0x8001CF80 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern char lbl_80312434[];
extern s32 lbl_80300198[];
extern bool lbl_803627D8;

void PADRead(void *st);
void PADClamp(void *st);
void PADReset(s32 mask);

// hwPadRead @ 0x8001CECC
void hwPadRead(void) {
    u8 *st;
    s32 *bits;
    s32 mask = 0;
    s32 ctr;
    s8 err;

    PADRead(lbl_80312434);
    PADClamp(lbl_80312434);
    ctr = 4;
    st = lbl_80312434;
    st += 0xA;
    bits = lbl_80300198;
    lbl_803627D8 = 0;
    do {
        ctr -= 1;
        err = *(s8 *)st;
        st += 0xC;
        if ((err == 0) || (err == -3)) {
            lbl_803627D8++;
        } else if (err == -1) {
            mask |= *bits;
        }
        bits++;
    } while (ctr != 0);
    if (mask != 0) {
        PADReset(mask);
    }
}
