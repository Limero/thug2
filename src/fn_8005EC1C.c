// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005EC1C-0x8005EC58 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8005EC1C(Unk_C7387A53 *arg0, s32 *arg1) {
    void (*fp)(void *);
    s16 off;
    Unk_C7387A53 *temp_r9;

    temp_r9 = *(Unk_C7387A53 **)((char *)arg0 + 0x1C);
    *(s32 *)((char *)arg0 + 0x18) = *arg1;
    off = *(s16 *)((char *)temp_r9 + 0x30);
    fp = *(void (**)(void *))((char *)temp_r9 + 0x34);
    fp((char *)arg0 + off);
}
