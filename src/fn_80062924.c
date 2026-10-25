// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062924-0x80062934 (16B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void fn_80062924(void *arg0, s32 arg1) {
    struct { u32 pad : 5; u32 b : 1; u32 rest : 26; } *p = (void *)((char *)arg0 + 0x48);
    p->b = arg1;
}
