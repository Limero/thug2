// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80241E38-0x80241E68 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_80241E38(void *arg0, s32 arg1) {
    if (arg1 <= 1) {
        return (char *)arg0 + ((arg1 * 0xC) + 0x10);
    }
    return (char *)((Unk_C7387A53 *)arg0)->unk0x28 + ((arg1 * 0xC) - 0x18);
}
