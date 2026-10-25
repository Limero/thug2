// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D824-0x8022D89C (120B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_80240C80(void *);
s32 fn_80240E74(CStruct *);
s32 fn_80238970(void);
s32 fn_8023B17C(s32, s32);
void fn_80241548(s32 *, s32);
void fn_8022D824(Unk_9994C3F5 *arg0, s32 arg1) {
    void *temp_r29;
    s32 temp_r30;
    Unk_9994C3F5 *var_r31;

    var_r31 = *((void * *)&arg0->unk0x8);
    if (var_r31 != NULL) {
        do {
            temp_r29 = *((void * *)&var_r31->unk0x8);
            temp_r30 = fn_80240E74((void *)*(s32 *)((char *)fn_80240C80(var_r31) + 0x14));
            if (fn_8023B17C(fn_80238970(), temp_r30) != 0) {
                fn_80241548(fn_80240C80(var_r31), arg1);
            }
            var_r31 = temp_r29;
        } while (var_r31 != NULL);
    }
}
