// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80102350-0x80102444 (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern u8 lbl_8029C868[];
extern u8 lbl_8029C600[];

Unk_6AC87105 *fn_80102350(Unk_6AC87105 *arg0, Unk_6AC87105 *arg1) {
    __ps_t *dB = (__ps_t *)((char *)arg0 + 0x20);
    __ps_t *sB = (__ps_t *)((char *)arg1 + 0x20);
    __ps_t *dC;
    __ps_t *sC;
    s32 tmp8;
    s32 c = 4;

    arg0->unk0xC = (s32)lbl_8029C868;
    arg0->unk0x0 = arg1->unk0x0;
    arg0->unk0x4 = arg1->unk0x4;
    arg0->unk0x6 = arg1->unk0x6;    tmp8 = arg1->unk0x8;
    arg0->unk0xC = (s32)lbl_8029C600;
    arg0->unk0x8 = tmp8;
    ((__ps_t *)arg0)[2] = ((__ps_t *)arg1)[2];
    ((__ps_t *)arg0)[3] = ((__ps_t *)arg1)[3];
    do {
        c -= 1;
    } while (c != 0);
    dB[0] = sB[0];
    sC = (__ps_t *)((char *)arg1 + 0x60);
    dC = (__ps_t *)((char *)arg0 + 0x60);
    dB[1] = sB[1];
    dB[2] = sB[2];
    dB[3] = sB[3];
    dB[4] = sB[4];
    dB[5] = sB[5];
    dB[6] = sB[6];
    dB[7] = sB[7];
    c = 4;
    do {
        c -= 1;
    } while (c != 0);
    dC[0] = sC[0];
    dC[1] = sC[1];
    dC[2] = sC[2];
    dC[3] = sC[3];
    dC[4] = sC[4];
    dC[5] = sC[5];
    dC[6] = sC[6];
    dC[7] = sC[7];
    return arg0;
}
