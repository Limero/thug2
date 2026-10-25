// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025D550-0x8025D5F8 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// EXI poll + callback dispatcher: spin on C72C, C7B4, dev f8->D18 slot,
// C970, BAC+C4 zero, B5C+0x118 callback (+clear), CC003000 tail.
// `zero` is assigned late (sched hoists the li early; keeps the sth zero
// a fresh li instead of CSE-merging into r30).
#include "types.h"

extern u8 lbl_803ACEE8[];
extern u8 lbl_803ADEE0[];
extern u8 lbl_80308BAC[];
extern u8 lbl_80308B5C[];
/* Gap EXI helpers, not yet decompiled: the lbl_ names are the linkable
   globals (cf. src/vt_803089D0.c). C72C returns the poll handle. */
s32 lbl_8025C72C(void);
void lbl_8025C7B4(void *, s32);
void lbl_8025C970(void *, s32);
typedef void (*cb_t)(s32);
typedef struct { u8 pad[2]; u16 f2; u8 pad2[4]; s32 f8; } Dev;

void fn_8025D550(void) {
    Dev *dev = (Dev *)(lbl_803ACEE8 - 0x1C8);
    s32 h;
    s32 zero;
    s32 t;
    cb_t cb;

    do {
        h = lbl_8025C72C();
    } while (!h);
    lbl_8025C7B4(dev, h);
    t = dev->f8;
    dev->f2 = 0;
    *(s32 *)(lbl_803ADEE0 - 0x11C8) = t;
    lbl_8025C970(dev, 8);
    zero = 0;
    *(s32 *)(lbl_80308BAC + 0xC4) = zero;
    cb = *(cb_t *)(lbl_80308B5C + 0x118);
    if (cb != 0) {
        cb(*(s32 *)(lbl_803ADEE0 - 0x11C8));
        *(cb_t *)(lbl_80308B5C + 0x118) = 0;
    }
    *(volatile u32 *)0xCC003000 = 0x1000;
}
