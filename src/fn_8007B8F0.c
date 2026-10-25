// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007B8F0-0x8007B918 (40B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x0[0x8];
    s32 *unk0x8;
} Unk_7B8F0;

void fn_8007B8F0(Unk_7B8F0 *arg0, s32 *arg1) {
    s32 i;

    for (i = 0; i < 16; i++) {
        char *dst = (char *)arg0->unk0x8 + 0x14C;

        *(s32 *)(dst + (i << 2)) = arg1[i];
    }
}
