// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80209278-0x802092E0 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct { u8 _p[0xA70]; s32 f0; s32 f1; } T;
void fn_80209278(T *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 n; s32 off;
    s32 *b0; s32 *b1; s32 *b2;
    n = 0;
    if (arg0->f0 == -1 && arg0->f1 == -1) {
        arg0->f0 = 0;
        goto STORE;
    }
    n = arg0->f1 + 1;
    if (n > 0x63) n = 0;
    if (n == arg0->f0) return;
STORE:
    arg0->f1 = n;
    /* zero-code barrier: keeps the mulli below the store above (see header) */
    __asm__ __volatile__("" ::: "memory");
    off = n * 0x14;
    b1 = (s32 *)((char *)arg0 + 0xA7C);
    b0 = (s32 *)((char *)arg0 + 0xA78);
    b2 = (s32 *)((char *)arg0 + 0xA88);
    *(s32 *)((char *)b0 + (s32)off) = arg1;
    *(s32 *)((char *)b1 + (s32)off) = arg2;
    *(s32 *)((char *)b2 + (s32)off) = arg3;

}
