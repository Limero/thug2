// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003F93C-0x8003F9C0 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8004195C(void *, void *);
typedef struct SE { char _00[0xC]; s32 f_0C; char _10[0xC0]; char _D0[0xA8]; f32 f_178; f32 f_17C; } SE;
void fn_8003F93C(SE *arg0, s32 arg1, f32 arg2, f32 arg3) {
    s32 t;
    if ((arg0->f_178 != arg2) || (arg0->f_17C != arg3)) {
        arg0->f_178 = arg2;
        arg0->f_17C = arg3;
        arg0->f_0C = arg0->f_0C | 0x400;
        fn_8004195C((void *)arg0, (void *)((char *)arg0 + 0xD0));
    }
    if (arg1) {
        t = arg0->f_0C | 0x2000;
    } else {
        t = arg0->f_0C & 0xFFFFDFFF;
    }
    arg0->f_0C = t;
}
