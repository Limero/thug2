// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005B420-0x8005B488 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8005B420(CScript *arg0) {
    s32 temp_r29;
    Unk_07FDFB02 *temp_r9;
    Unk_89391A04 *temp_r9_2;

    temp_r9 = (Unk_07FDFB02 *)arg0->unk0x18;
    temp_r29 = temp_r9->unk0x14((char *)arg0 + temp_r9->unk0x10);
    temp_r9_2 = (Unk_89391A04 *)arg0->unk0x18;
    ((void (*)(void *, s32, s32))temp_r9_2->unk0x4C)((char *)arg0 + temp_r9_2->unk0x48, 1, 0);
    return temp_r29;
}
