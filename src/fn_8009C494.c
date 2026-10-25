// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C494-0x8009C4A4 (16B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// SetVec2X: stores v into the first component [i*2] of the vec2 array whose
// pointer lives at o+0x34 (stride 8 = 2 floats).
// Suggested rename: SetVec2X_0x34
#include "types.h"
void fn_8009C494(void *o, s32 i, float v) {
    float *a = *(float **)((char *)o + 0x34);
    a[i * 2] = v;
}