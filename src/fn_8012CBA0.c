// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012CBA0-0x8012CBD4 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

u8 *fn_8012CBA0(u8 *p, f32 f) {
    u32 v = *(u32 *)&f;

    *p++ = v;
    *p++ = v >> 8;
    *p++ = v >> 16;
    *p++ = v >> 24;
    return p;
}
