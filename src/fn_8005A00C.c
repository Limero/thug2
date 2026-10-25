// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005A00C-0x8005A060 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void *fn_80059BB8(s32);
void fn_8005A00C(Unk_C8FEE62D *arg0, f32 farg0) {
    void **temp_r3;
    volatile f32 sp8;
    if (farg0 != *(f32 *)&arg0->unk0x10) {
        *(f32 *)&arg0->unk0x10 = farg0;
        temp_r3 = fn_80059BB8(arg0->unk0x18);
        if (temp_r3 != NULL) {
            *(f32 *)(*(s32 *)temp_r3 + 0x24) = farg0;
        }
    }
}
