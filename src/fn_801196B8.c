// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801196B8-0x8011970C (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// IDENTIFIED (2026-09-01): audio-cluster (0x8011xxxx) max-|value| scan
// helper — best = arg0[0]; scans arg0[1..count) (count 2, or 5 when the
// flag at arg0+0x14 == 2) and returns the element with the largest
// absolute value. Match notes: loop counters must be u32 (WANT cmplw),
// fabs operands precomputed into temps (avoids GCC's fmr+in-place fabs).
#include "types.h"
#include "structs.h"
f32 fn_801196B8(Unk_C8FEE62D *arg0) {
    u32 i;
    u32 count;
    f32 best;
    f32 *p;
    f32 v;
    f32 av;
    f32 ab;
    best = *(f32 *)arg0;
    count = 2;
    if (arg0->unk0x14 == 2)
        count = 5;
    i = 1;
    if (i < count) {
        p = (f32 *)((char *)arg0 + 4);
        do {
            v = *p++;
            av = fabs(v);
            ab = fabs(best);
            if (av > ab)
                best = v;
            i++;
        } while (i < count);
    }
    return best;
}
