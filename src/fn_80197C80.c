// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80197C80-0x80197CF0 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80197DB8(void *, s32);

void fn_80197C80(Unk_D0C13A11 *arg0) {
    s32 var_r29;
    void *var_r31;

    var_r29 = 0;
    var_r31 = (char *)arg0 + 0x84;
    do {
        if (((s32)((CStruct *)var_r31)->unk0x4 == 0) && ((s32)*(s32 *)var_r31 == 1)) {
            arg0->unk0x548 += 1;
            fn_80197DB8(arg0, var_r29);
        }
        var_r29++;
        var_r31 += 0x28;
    } while (var_r29 <= 0x1D);
}
