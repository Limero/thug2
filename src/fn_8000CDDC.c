// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000CDDC-0x8000CE8C (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_8000E68C(void *, void *, u32);
void *Mem_Alloc_3(s32);
void fn_8000C9CC(u8 *, u8 *, u32);
void memcpy(s32, s32, s32);
void *fn_8000CDDC(s32 arg0, void *arg1, s32 *arg2, void *arg3) {
    s32 *p;

    p = fn_8000E68C(*(void **)((char *)arg0 + 0xC), arg1, 0);
    if (p == 0) {
        return 0;
    }
    *arg2 = p[4];
    if (arg3 == 0) {
        arg3 = Mem_Alloc_3(p[4]);
    }
    if (p[2] == 0) {
        if (p[0] != 0) {
            fn_8000C9CC((u8 *)p[1], (u8 *)arg3, p[0]);
        } else {
            memcpy((s32)arg3, p[1], p[4]);
        }
    } else {
        memcpy((s32)arg3, p[2], p[4]);
    }
    return arg3;
}
