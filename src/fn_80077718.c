// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077718-0x80077758 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct DispEntry { s16 unk0x0; char pad0x2[0x2]; s32 unk0x4; } DispEntry;
void fn_80077718(CScript *arg0) {
    DispEntry *temp_r9;

    if (arg0 != NULL) {
        temp_r9 = (DispEntry *)arg0->unk0x214;
        ((s32 (*)(void *, s32))temp_r9[1].unk0x4)((char *)arg0 + temp_r9[1].unk0x0, 3);
    }
}
