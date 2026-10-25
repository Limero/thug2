// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80273B68-0x80273BA8 (64B). Byte-identical.
#include "types.h"

typedef union {
    struct {
        s32 high;
        u32 low;
    } s;
    s64 ll;
} DWunion_lsr;

u64 fn_80273B68(u64 u, s32 b) {
    DWunion_lsr w;
    s32 bm;
    DWunion_lsr uu;

    if (b == 0)
        return u;

    uu.ll = u;

    bm = 32 - b;

    if (bm <= 0) {
        w.s.high = 0;
        w.s.low = (u32)uu.s.high >> -bm;
    } else {
        const u32 carries = (u32)uu.s.high << bm;

        w.s.high = (u32)uu.s.high >> b;
        w.s.low = ((u32)uu.s.low >> b) | carries;
    }

    return w.ll;
}
