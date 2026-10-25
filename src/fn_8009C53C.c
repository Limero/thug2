// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C53C-0x8009C558 (28B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// GetVec3Z: returns element [i*3+2] (Z) of the vec3 array whose pointer
// lives at o+0x2C. Index written as ((i<<1)+i)+2 so ngccc emits the
// slwi/add/slwi dance instead of mulli.
// Suggested rename: GetVec3Z_0x2C
#include "types.h"
float fn_8009C53C(void *o, s32 i) {
    float *a = *(float **)((char *)o + 0x2c);
    return a[((i << 1) + i) + 2];
}