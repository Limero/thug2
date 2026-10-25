// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C4B8-0x8009C4D0 (24B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// GetVec3X: returns element [i*3] (X) of the vec3 array whose pointer lives
// at o+0x28. Index written as ((i<<1)+i) so ngccc emits the slwi/add/slwi
// dance instead of mulli (inlining the deref also fixes the regalloc).
// Suggested rename: GetVec3X_0x28
#include "types.h"
float fn_8009C4B8(void *o, s32 i) {
    return ((float *)*(float **)((char *)o + 0x28))[(i << 1) + i];
}