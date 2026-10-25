// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007B890-0x8007B8F0 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8007B890(void *arg0, s32 arg1, s32 arg2) {
    *(f32 *)(*(s32 *)((char *)arg0 + 8) + 0x144) = (f32)arg1;
    if (arg2 > 0) {
        *(f32 *)(*(s32 *)((char *)arg0 + 8) + 0x148) = (f32)arg2;
    }
}
