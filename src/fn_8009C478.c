// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C478-0x8009C494 (28B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// SetVec2: writes v0/v1 into the vec2 slot [i*2] of the float array whose
// pointer lives at o+0x34 (pointer re-loaded per element — aliasing).
// Suggested rename: SetVec2_0x34
#include "types.h"
void fn_8009C478(void *o, s32 i, float v0, float v1) {
    ((float *)*(float **)((char *)o + 0x34))[i * 2] = v0;
    ((float *)*(float **)((char *)o + 0x34))[i * 2 + 1] = v1;
}