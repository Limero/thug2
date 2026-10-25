// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80273480-0x802734C0 (64B). Byte-identical.
#include "types.h"

typedef union {
    struct {
        s32 high;
        s32 low;
    } s;
    s64 ll;
} DWunion_ashl;

s64 fn_80273480(s64 u, s32 b) {
    DWunion_ashl w;
    s32 bm;
    DWunion_ashl uu;

    if (b == 0)
        return u;

    uu.ll = u;

    bm = 32 - b;

    if (bm <= 0) {
        w.s.low = 0;
        w.s.high = uu.s.low << -bm;
    } else {
        const u32 carries = (u32)uu.s.low >> bm;

        w.s.low = uu.s.low << b;
        w.s.high = ((u32)(uu.s.high << b)) | carries;
    }

    return w.ll;
}
