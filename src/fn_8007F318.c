// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F318-0x8007F3A0 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

typedef struct O_7F318 {
    char pad0x0[0x30];
    void *f30;         /* +0x30, null short-circuits to the trailing return */
} O_7F318;

void memcpy();

// fn_8007F318: copy 64 bytes of paired singles from arg1 to arg0+0x30+8, then
// memcpy arg3*64 bytes into the 9th pair slot. Always returns 1.
bool fn_8007F318(O_7F318 *arg0, void *arg1, void *arg2, s32 arg3) {
    void *n;
    void *a1;
    void *a2;
    __ps_t *d;
    __ps_t *s;

    n = arg0->f30;
    a1 = arg1;
    a2 = arg2;
    if (n == NULL) {
        return true;
    }
    d = (__ps_t *)((char *)n + 8);
    s = (__ps_t *)a1;
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = s[3];
    d[4] = s[4];
    d[5] = s[5];
    d[6] = s[6];
    d[7] = s[7];
    memcpy(*(void **)((char *)arg0->f30 + 0x48), a2, arg3 << 6);
    return true;
}
