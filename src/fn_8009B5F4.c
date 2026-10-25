// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009B5F4-0x8009B6AC (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8009B5F4(Unk_F5317C5D *arg0, s32 arg1) {
    if (arg0->unk0x10 != 0) {
        Mem_Free(arg0->unk0x10);
        arg0->unk0x10 = 0;
        if ((u16)arg0->unk0xA & 0x100) {
            arg0->unk0x14 = 0;
        }
    }
    if ((arg0->unk0x14 != 0) && (((u16)arg0->unk0xA & 0x1C) == 4)) {
        Mem_Free(arg0->unk0x14);
    }
    if ((u16)arg0->unk0xA & 0x40) {
        if (arg0->unk0x18 != 0) {
            Mem_Free(arg0->unk0x18);
            arg0->unk0x18 = 0;
        }
    }
    if (arg0->unk0x18 != 0) {
        Mem_Free(arg0->unk0x18);
    }
    if (arg1 & 1) {
        Mem_Free((s32)arg0);
    }
}
