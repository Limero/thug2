// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062528-0x80062584 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef struct S62528F { u32 a:3; u32 f:1; u32 b:28; } S62528F;

extern f32 lbl_80293F00;

bool fn_80062528(void *arg0, f32 *arg1) {
    f32 c;
    s32 flag = 0;
    __ps_t *dst = (__ps_t *)((char *)arg0 + 0x20);

    dst[0] = ((__ps_t *)arg1)[0];
    dst[1] = ((__ps_t *)arg1)[1];
    c = lbl_80293F00;
    if (arg1[0] != c || arg1[1] != c || arg1[2] != c) {
        flag = 1;
    }
    ((S62528F *)((char *)arg0 + 0x48))->f = flag;
    return true;
}
