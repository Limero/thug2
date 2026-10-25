// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E1A0-0x8009E1F0 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { char pad[8]; s16 unk0x8; char pad2[2]; s32 unk0xC; } Disp9E;
void fn_8009E1A0(void *arg0) {
    if (!(*(s32 *)((char *)arg0 + 0xC) & 2) && arg0 != NULL) {
        Disp9E *d = *(Disp9E **)((char *)arg0 + 8);
        ((void (*)(void *, s32))d->unk0xC)((char *)arg0 + d->unk0x8, 3);
    }
}
