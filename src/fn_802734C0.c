// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802734C0-0x80273500 (64B). Byte-identical.
#include "types.h"

typedef union {
    struct {
        s32 high;
        s32 low;
    } s;
    s64 ll;
} DWunion_ashr;

s64 fn_802734C0(s64 u, s32 b) {
    DWunion_ashr w;
    s32 bm;
    DWunion_ashr uu;

    if (b == 0)
        return u;

    uu.ll = u;

    bm = 32 - b;

    if (bm <= 0) {
        w.s.high = uu.s.high >> 31;
        w.s.low = uu.s.high >> -bm;
    } else {
        const u32 carries = (u32)(uu.s.high << bm);

        w.s.high = uu.s.high >> b;
        w.s.low = ((u32)uu.s.low >> b) | carries;
    }

    return w.ll;
}
