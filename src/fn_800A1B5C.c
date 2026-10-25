// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A1B5C-0x800A1BB4 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800A1B5C(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, void (*arg3)(void)) {
    char *a54 = (char *)arg0 + 0x54;
    char *a58 = (char *)arg0 + 0x58;

    *(s32 *)(a54 + (arg0->unk0x50 << 3)) = arg1;
    *(s32 *)(a58 + (arg0->unk0x50 << 3)) = arg2;
    arg0->unk0x50 = arg0->unk0x50 + 1;
    if (arg3 != NULL) {
        arg3();
    }
}
