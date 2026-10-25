// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80174508-0x80174558 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 fn_801746A4(void *);
void *GetChecksum_3(void *, s32);
void *fn_80174508(char *arg0, s32 arg1, s32 arg2) {
    void *r;
    register s32 idx __asm__("r0");
    char *base = (char *)arg0 + 0x3A8;
    idx = arg1 << 4;
    *(s32 *)(base + idx) = arg2;
    r = (void *)fn_801746A4(arg0);
    if (r != 0) {
        r = GetChecksum_3(r, QB_SKATERCOREPHYSICS);
        *(s32 *)((char *)r + 0x320) = arg2;
    }
    return r;
}
