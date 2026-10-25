// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C5F0-0x8009C62C (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0[0x28];
    u8 *list;               /* +0x28 */
    char pad1[0x40 - 0x2C];
    s32 count;              /* +0x40 */
} S9C5F0;

void fn_8009C5F0(S9C5F0 *arg0, f32 farg0) {
    s32 i;

    for (i = 0; i < arg0->count; i++) {
        ((f32 *)arg0->list)[i * 3] += farg0;
    }
}
