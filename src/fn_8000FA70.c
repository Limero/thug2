// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000FA70-0x8000FAB4 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8000FA70(Unk_1BA9BD24 *self, s32 key) {
    s32 i;
    s32 n;
    n = self->unk0xC4 - 1;
    for (i = 0; i < n; i++) {
        s32 *p = (s32 *)((char *)self + 8 + 4 * i);
        if (*(p - 1) == key) {
            return *p;
        }
    }
    return 0;
}
