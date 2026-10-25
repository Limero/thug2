// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012CB7C-0x8012CBA0 (36B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

u8 *fn_8012CB7C(u8 *p, u32 v) {
    *p++ = v;
    *p++ = v >> 8;
    *p++ = v >> 16;
    *p++ = v >> 24;
    return p;
}
