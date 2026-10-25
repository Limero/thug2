// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002DE6C-0x8002DEAC (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 fn_8002DE6C(void *arg0) {
    if (*(s32 *)((char *)arg0 + 0x2C) == 0) {
        if (*(s32 *)((char *)arg0 + 0x28) == 0) {
            return *(f32 *)((char *)arg0 + 0x1C) == *(f32 *)((char *)arg0 + 0x20);
        }
        return *(f32 *)((char *)arg0 + 0x1C) == *(f32 *)((char *)arg0 + 0x18);
    }
    return 0;
}
