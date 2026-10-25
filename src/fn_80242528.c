// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80242528-0x80242590 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void *fn_80240C80(void * arg0);
#include "structs.h"
s32 fn_80241E38(s32, s32);
void fn_80241548(void *, void *);
void fn_80242528(Unk_C7387A53 *arg0, void *arg1) {
    u32 var_r31;
    Unk_9994C3F5 *temp_r3;

    var_r31 = 0U;
    while (var_r31 < (u32) *((u32 *)&arg0->unk0x30)) {
        temp_r3 = fn_80241E38((s32) arg0, var_r31);
        var_r31 += 1;
        fn_80241548(fn_80240C80(temp_r3->unk0x8), arg1);
    }
}
