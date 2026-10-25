// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D2B0-0x8002D340 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8002CDE4(s32);
extern s32 fn_8002D008(Unk_C7387A53 *);
void fn_8002D2B0(Unk_FFAD6788 *arg0, s32 arg1) {
    s32 i;
    Unk_C7387A53 **p;
    p = (Unk_C7387A53 **)((char *)arg0 + 4);
    for (i = 0x32; i != 0; i--) {
        if (fn_8002D008(*p) != 0) {
            if (arg1 != 0) {
                if ((*p)->unk0x168 & QB_UNKNOWN_0xFFF80000) {
                    p++;
                    continue;
                }
                arg0->unk0xD0 -= fn_8002CDE4((s32)*p);
            } else {
                arg0->unk0xD0 -= fn_8002CDE4((s32)*p);
            }
        }
        p++;
    }
}
