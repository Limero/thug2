// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005B4F0-0x8005B558 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8005B4F0(CScript *arg0) {
    s32 temp_r29;
    Unk_89391A04 *temp_r9;

    temp_r9 = (Unk_89391A04 *)arg0->unk0x18;
    temp_r29 = temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20);
    temp_r9 = (Unk_89391A04 *)arg0->unk0x18;
    ((void (*)(void *, s32, s32))temp_r9->unk0x4C)((char *)arg0 + temp_r9->unk0x48, 0, 1);
    return temp_r29;
}
