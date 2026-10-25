// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C6FC-0x8009C738 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0[0x34];
    u8 *list;               /* +0x34 */
    char pad1[0x40 - 0x38];
    s32 count;              /* +0x40 */
} S9C6FC;

void fn_8009C6FC(S9C6FC *arg0, f32 farg0) {
    s32 i;

    for (i = 0; i < arg0->count; i++) {
        ((f32 *)arg0->list)[i * 2] += farg0;
    }
}
