// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80037B7C-0x80037BF0 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
typedef struct { s32 pad0; s32 pad4; s32 flags; s32 padC; f32 v0; f32 v1; f32 v2; f32 v3; } E37B7C;
typedef struct { f32 a; f32 b; f32 c; f32 d; } V4;
extern f32 lbl_80291EEC;
void fn_80037B7C(void *arg0) {
    V4 tmp;
    s32 i;
    s32 off;
    s32 n;
    f32 f0;
    E37B7C *e;
    V4 *tb;
    __ps_t *dst;

    n = *(s32 *)((char *)arg0 + 0x14);
    i = 0;
    if (i < n) {
        tb = &tmp;
        f0 = lbl_80291EEC;
        off = 0;
        do {
            e = (E37B7C *)((char *)(*(s32 *)((char *)arg0 + 0x18)) + off);
            i = i + 1;
            e->flags = e->flags & 0xCFFFFFFF;
            off = off + 0x20;
            tmp.a = f0;
            tb->c = f0;
            tb->d = f0;
            tb->b = f0;
            dst = (__ps_t *)&e->v0;
            dst[0] = ((__ps_t *)&tmp)[0];
            dst[1] = ((__ps_t *)tb)[1];
        } while (i < *(s32 *)((char *)arg0 + 0x14));
    }
}
