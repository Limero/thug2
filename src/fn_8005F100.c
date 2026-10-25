// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005F100-0x8005F148 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8005F100(s32 arg0, Unk_C8FEE62D *arg1) {
    Unk_DB0E2BAB *temp_r9;
    void (*temp_r9_2)();

    temp_r9 = (Unk_DB0E2BAB *)arg1->unk0x14;
    temp_r9_2 = (void (*)())temp_r9->unk0x44;
    temp_r9_2(arg0, (char *)arg1 + (s32)temp_r9->unk0x40);
    return arg0;
}
