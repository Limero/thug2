// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CBB74-0x800CBBC4 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8002F7D0(s32);
void fn_800CBB74(Unk_C7387A53 *arg0) {
    register void *var_r9 __asm__("r9");
    Unk_C7387A53 *var_r31;

    var_r9 = *((void * *)&arg0->unk0x38);
    while (1) {
        if (((CStruct *)var_r9)->unk0x4 == -1) {
            var_r9 = NULL;
        }
        var_r31 = var_r9;
        if (var_r31 == NULL) {
            break;
        }
        __asm__("" : "+r"(var_r31));
        fn_8002F7D0(var_r31);
        var_r9 = *((void * *)&var_r31->unk0xC);
    }
}
