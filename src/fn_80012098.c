// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012098-0x800120EC (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern bool lbl_80305E78;
extern void Mem_Free(void *arg0);

void fn_80012098(s32 *arg0, s32 arg1) {
    if (lbl_80305E78 == 0) {
        Mem_Free((void *)*arg0);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
