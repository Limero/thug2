// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802043AC-0x802043F8 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern void fn_80204404(void *arg0);

void fn_802043AC(char *arg0) {
    char *src;
    s32 off;

    src = *(char **)(arg0 + 0xc);
    off = *(s32 *)(arg0 + 0x20) * 0x18 + *(s32 *)(arg0 + 0x1c);
    off = off + 0x1F0;
    ((__ps_t *)(off))[0] = ((__ps_t *)(src + 0x58))[0];
    ((__ps_t *)(off))[1] = ((__ps_t *)(src + 0x58))[1];
    fn_80204404(arg0);
}
