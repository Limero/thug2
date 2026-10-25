// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F214-0x8007F284 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

void fn_8007F214(void *arg0, __ps_t *arg1) {
    void *a = *(void **)((char *)arg0 + 0x30);
    void *b;
    void *c;
    void *d;
    void *e;
    void *g;
    __ps_t *dst;

    if (a == 0) {
        return;
    }
    b = *(void **)((char *)a + 0x54);
    if (b == 0) {
        return;
    }
    if (*(s32 *)((char *)a + 0x48) == 0) {
        goto L;
    }
    if (*(s32 *)((char *)b + 0x6c) == 0) {
        goto L;
    }
    dst = (__ps_t *)((char *)b + 0x48);
    dst[0] = arg1[0];
    dst[1] = arg1[1];
    return;
L:
    c = *(void **)((char *)b + 0x58);
    d = *(void **)c;
    if (d == 0) {
        return;
    }
    e = *(void **)((char *)d + 0x14);
    g = *(void **)((char *)e + 0x20);
    dst = (__ps_t *)((char *)g + 0x30);
    dst[0] = arg1[0];
    dst[1] = arg1[1];
}
