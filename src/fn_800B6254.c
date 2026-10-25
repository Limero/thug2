// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B6254-0x800B62A4 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800B6254(CScript *arg0, s32 arg1, s32 arg2) {
    Unk_0E2E8431 *rec;

    if ((s32) arg0->unk0x210 != 0) {
        rec = arg0->unk0x18;
        ((void (*)(void *, s32, s32, s32, s32))rec->unk0x74)((char *)arg0 + rec->unk0x70, arg1, 1, 0, arg2);
    }
}
