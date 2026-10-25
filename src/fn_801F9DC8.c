// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F9DC8-0x801F9E38 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_801F95D4(Unk_C7387A53 * arg0);
void *fn_801F9820(Unk_C7387A53 * arg0);
void fn_801F9DC8(Unk_C7387A53 *arg0, Unk_C7387A53 *arg1) {
    Unk_C4654E77 *temp_r3;
    Unk_C4654E77 *var_r30;

    fn_801F95D4(arg0);
    var_r30 = *((void * *)&arg1->unk0xC);
    if (var_r30 != NULL) {
        do {
            temp_r3 = fn_801F9820(arg0);
            temp_r3->unk0x8 = var_r30->unk0x8;
            temp_r3->unk0x10 = var_r30->unk0x10;
            temp_r3->unk0x18 = var_r30->unk0x18;
            temp_r3->unk0x20 = var_r30->unk0x20;
            var_r30 = var_r30->unk0x24;
        } while (var_r30 != NULL);
    }
}
