// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80091CF8-0x80091D98 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
typedef struct rec_s {
    s32 object;
    char pad[0x54];
    s32 values[2];
} rec_t;

s32 fn_80091CF8(rec_t *arg0, rec_t *arg1) {
    s32 sum_a = 0;
    s32 sum_b = 0;
    u32 i = 0;
    s32 *obj_a;
    s32 *obj_b;
    do {
        obj_a = *(s32 **)arg0;
        if (obj_a[1] == 0) {
            arg0->values[i] = 0;
        }
        obj_b = *(s32 **)arg1;
        if (obj_b[1] == 0) {
            arg1->values[i] = 0;
        }
        sum_a += arg0->values[i];
        sum_b += arg1->values[i];
        i += 1;
    } while (i < 2U);
    if (sum_a < sum_b) return 1;
    if (sum_a <= sum_b) return 0;
    return -1;
}
