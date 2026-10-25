// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024EA14-0x8024EA74 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
#include "types.h"

extern s32 lbl_803CA340;
extern s32 lbl_803CA344;
extern s32 lbl_803CA348;

s32 fn_8024EE00(s32, void *);
void fn_80252C00(void);

void fn_8024EA14(s32 (*arg0)(s32), s32 arg1, void *arg2) {
    s32 (*cb)(s32);

    cb = arg0;
    lbl_803CA344 = (s32)cb;
    lbl_803CA348 = arg1;
    lbl_803CA340 = fn_8024EE00(cb(8), arg2);
    ((void (*)(u32))lbl_803CA344)((u32)0xE0);
    fn_80252C00();
}
