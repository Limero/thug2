// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80006FA8-0x8000702C (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_800063B4(void *);
typedef struct {
    __ps_t lo;
    volatile __ps_t hi;
} SumPair;
void *fn_80006FA8(Unk_C7387A53 *arg0, __ps_t *arg1, __ps_t *arg2, f32 f) {
    __ps_t *d = (__ps_t *)arg0;
    __ps_t *s = arg1;
    __ps_t *t = arg2;
    SumPair sum;

    fn_800063B4(arg0);
    d[0] = s[0];
    d[1] = s[1];
    sum.hi = s[1] + t[1];
    sum.lo = s[0] + t[0];
    d[2] = sum.lo;
    d[3] = sum.hi;
    *(f32 *)&d[4] = f;
    return arg0;
}
