// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C4D0-0x8009C4EC (28B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// GetVec3Y: returns element [i*3+1] (Y) of the vec3 array whose pointer
// lives at o+0x28. Index written as ((i<<1)+i)+1 so ngccc emits the
// slwi/add/slwi dance instead of mulli.
// Suggested rename: GetVec3Y_0x28
#include "types.h"
float fn_8009C4D0(void *o, s32 i) {
    float *a = *(float **)((char *)o + 0x28);
    return a[((i << 1) + i) + 1];
}