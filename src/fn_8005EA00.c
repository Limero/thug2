// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005EA00-0x8005EA3C (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8005EA00(Unk_C7387A53 *arg0, s32 *arg1) {
    void (*fp)(void *);
    s16 off;
    Unk_C7387A53 *temp_r9;

    temp_r9 = arg0->unk0x4C;
    arg0->unk0x44 = *arg1;
    off = *(s16 *)((char *)temp_r9 + 0x20);
    fp = *(void (**)(void *))((char *)temp_r9 + 0x24);
    fp((char *)arg0 + off);
}
