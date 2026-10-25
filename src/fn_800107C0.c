// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800107C0-0x800107F0 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct { char _pad[0x10]; s32 arr[1]; } T107C0;

void fn_800107C0(T107C0 *arg0, Unk_C7387A53 *arg1) {
    s32 var_r3;

    arg0->arr[(arg1->unk0x38 & 2) >> 1] = (s32)arg1;
    if ((s32) arg1->unk0x38 == 1) {
        var_r3 = ((CStruct *)arg0)->unk0x4;
    } else {
        var_r3 = ((CStruct *)arg0)->unk0xC;
    }
    arg1->unk0x3C = var_r3;
}
