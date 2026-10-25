// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80007090-0x800070E4 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
f32 fn_800063E0(void *);
s32 fn_80007090(void *arg0, s32 a, s32 b, s32 c, f32 *out) {
    f32 v;
    f32 sq;

    v = fn_800063E0(arg0);
    if (out != NULL) {
        *out = v;
    }
    sq = *(f32 *)((char *)arg0 + 0x20);
    return v <= sq * sq;
}
