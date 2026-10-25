// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013A6FC-0x8013A744 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8013A6FC(Unk_DB0E2BAB *arg0) {
    u32 idx;
    s32 *base;
    arg0->unk0x8 = 2;
    if (arg0->unk0x14 & 1) {
        return 4;
    }
    idx = arg0->unk0x9C;
    base = (s32 *)((char *)arg0 + 0x1C);
    base[idx++] = **(u16 **)arg0;
    arg0->unk0x9C = idx;
    return 1;
}
