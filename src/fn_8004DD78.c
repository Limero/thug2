// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004DD78-0x8004DE48 (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void fn_8005DB64(void *, s32, s32);
void fn_8005DBA0(void *, s32, s32);

extern f32 lbl_80292A1C;
extern f32 lbl_80292A20;

void fn_8004DD78(void *arg0, s32 arg1) {
    f32 c1;
    f32 c2;
    char *p;

    if (*(s32 *)((char *)arg0 + 0xC) & 0x1800) {
        c1 = lbl_80292A1C;
        c2 = lbl_80292A20;
        p = (char *)arg0 + 0x128;
        fn_8005DB64(*(void **)((char *)arg0 + 0x190),
                    (s32)(*(f32 *)(p + 0x18) - (*(f32 *)((char *)arg0 + 0x170) + c1) * c2 * *(f32 *)((char *)arg0 + 0x178)),
                    (s32)(*(f32 *)(p + 0x1C) - (*(f32 *)((char *)arg0 + 0x174) + c1) * c2 * *(f32 *)((char *)arg0 + 0x17C)));
        fn_8005DBA0(*(void **)((char *)arg0 + 0x190), (s32)(*(f32 *)((char *)arg0 + 0x178)), (s32)(*(f32 *)((char *)arg0 + 0x17C)));
    }
}
