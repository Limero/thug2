// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B6344-0x800B63C8 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
f32 fn_800B6404(void *);
extern f32 lbl_802988C0;
f32 fn_800B6344(Unk_C7387A53 *arg0) {
    volatile double _dummy;
    f32 sum;
    s32 i;
    s32 one;
    char *p;

    sum = lbl_802988C0;
    if ((s32) arg0->unk0x90 != 0) {
        arg0->unk0x90 = 0;
        p = (char *)arg0;
        one = 1;
        i = 6;
        do {
            if (*(s32 *)(p + 0x14) < 0) {
                arg0->unk0x90 = one;
                sum += fn_800B6404(p);
            }
            p += 0x18;
            i -= 1;
        } while (i != 0);
    }
    return sum;
}
