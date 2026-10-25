// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001D478-0x8001D4A8 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void PSVECCrossProduct(void *, void *, void *);
// PSVEC_CrossProduct @ 0x8001D478
void PSVEC_CrossProduct(s32 arg0, s32 arg1, s32 arg2) {
    PSVECCrossProduct((void *)arg1, (void *)arg2, (void *)arg0);
}
