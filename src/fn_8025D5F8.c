// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025D5F8-0x8025D6D0 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern u8 lbl_803ACEE8[];
extern u8 lbl_803ADEE0[];
extern u8 lbl_80308BAC[];
extern u8 lbl_80308B5C[];
s32 lbl_8025C72C(void);
void lbl_8025C7B4(void *, s32);
void lbl_8025C970(void *, s32);
typedef void (*cb_t)(s32);
typedef struct { u8 pad[2]; u16 f2; u8 pad2[4]; s32 f8; } Dev;

void fn_8025D5F8(void) {
    Dev *dev = (Dev *)(lbl_803ACEE8 - 0x1C8);
    s32 *slot;
    s32 h;
    s32 zero;
    s32 zero2;
    s32 t;
    cb_t cb;

    if (*(s32 *)(lbl_803ADEE0 - 0x11CC) != 0) {
        do {
            h = lbl_8025C72C();
        } while (!h);
        slot = (s32 *)(lbl_803ADEE0 - 0x11C8);
        lbl_8025C7B4(dev, h);
        t = dev->f8;
        dev->f2 = 0;
        *slot = t;
        lbl_8025C970(dev, 8);
        zero = 0;
        *(s32 *)(lbl_80308BAC + 0xC4) = zero;
        cb = *(cb_t *)(lbl_80308B5C + 0x118);
        if (cb != 0) {
            cb(*slot);
            *(cb_t *)(lbl_80308B5C + 0x118) = zero;
        }
    }
    zero2 = 0;
    *(s32 *)(lbl_80308B5C + 0x118) = zero2;
    *(volatile u32 *)0xCC006828 = 8;
    *(volatile u32 *)0xCC003000 = 0x1000;
    *(s32 *)(lbl_80308BAC + 0xC4) = zero2;
}
