// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005EBA4-0x8005EBE4 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8005EBA4(Unk_C8FEE62D *arg0, f32 farg0) {
    void (*fn)(char *);
    Unk_C7387A53 *temp_r9;

    *((f32 *)&arg0->unk0xC) = farg0;
    arg0->unk0x10 = 0;
    temp_r9 = (Unk_C7387A53 *)arg0->unk0x1C;
    fn = (void (*)(char *))temp_r9->unk0x3C;
    fn((char *)arg0 + *(s16 *)((char *)temp_r9 + 0x38));
}