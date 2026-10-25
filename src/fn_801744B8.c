// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801744B8-0x80174508 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
void *fn_801746A4(s32);
void *GetChecksum_3(void *, s32);
void *fn_801744B8(s32 arg0, s32 arg1, s32 arg2) {
    void *obj;
    register s32 idx __asm__("r0");
    char *base;

    idx = arg1 << 4;
    base = (char *)arg0 + 0x3AC;
    *(s32 *)(base + idx) = arg2;
    obj = fn_801746A4(arg0);
    if (obj) {
        obj = GetChecksum_3(obj, QB_SKATERCOREPHYSICS);
        *(s32 *)((char *)obj + 0x324) = arg2;
    }
    return obj;
}
