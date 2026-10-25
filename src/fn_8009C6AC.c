// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C6AC-0x8009C6FC (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8009C6AC(char *arg0, f32 f1, f32 f2) {
    s32 i;
    for (i = 0; i < *(s32 *)(arg0 + 0x40); i++) {
        ((f32 *)*(u32 *)(arg0 + 0x34))[i * 2] += f1;
        ((f32 *)*(u32 *)(arg0 + 0x34))[i * 2 + 1] += f2;
    }
}
