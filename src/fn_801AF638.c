// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AF638-0x801AF688 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801AED54(Unk_C7387A53 *);
void fn_801AF638(CStruct *arg0) {
    register void *var_r9 __asm__("r9");
    Unk_C7387A53 *var_r31;

    var_r9 = *((void * *)&arg0->unk0x10);
    while (1) {
        if (((CStruct *)var_r9)->unk0x4 == -1) {
            var_r9 = NULL;
        }
        var_r31 = var_r9;
        if (var_r31 == NULL) {
            break;
        }
        __asm__("" : "+r"(var_r31));
        fn_801AED54(var_r31);
        var_r9 = *((void * *)&var_r31->unk0xC);
    }
}
