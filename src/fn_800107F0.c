// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800107F0-0x80010808 (24B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { char _pad[0x10]; s32 arr[1]; } T107F0;
void fn_800107F0(T107F0 *arg0, Unk_C7387A53 *arg1) {
    arg0->arr[(arg1->unk0x38 & 2) >> 1] = 0;
}
