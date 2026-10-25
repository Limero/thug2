// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800070E4-0x8000714C (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

/* self: fn_80006AB0 reads four PS pairs at +0x00..+0x18; the square test
 * reads the f32 at +0x20. */
typedef struct {
    __ps_t pair[4];
    f32 unk0x20;
} Obj0;

/* 16-byte callee out-param / caller out-vector: two PS pairs. */
typedef struct {
    __ps_t lo;
    __ps_t hi;
} P2;

/* fn_80006AB0(self, vec, out) -> f32 (f1 only; see header). */
f32 fn_80006AB0(void *self, __ps_t *vec, P2 *out);

s32 fn_800070E4(Obj0 *arg0, __ps_t *arg1, P2 *arg2) {
    P2 out;
    f32 d;
    f32 res;
    s32 cond;

    res = fn_80006AB0(arg0, arg1, &out);
    d = arg0->unk0x20;
    d = d * d;
    cond = (res <= d);
    if (cond != 0) {
        if (arg2 != NULL) {
            arg2->lo = out.lo;
            arg2->hi = out.hi;
        }
    }
    return cond;
}
