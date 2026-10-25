// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F5808-0x801F5898 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_801F16E8(void);
extern s32 fn_801F2184(void *arg0);
void *fn_801F5808(s32 arg0, s32 arg1) {
    Unk_127FDB99 *var_r30;
    s32 temp_r29;
    s32 var_r31;
    s32 var_r9;
    temp_r29 = fn_801F16E8();
    var_r30 = (void *)(arg0 + 0x20);
    var_r31 = 0;
loop_1:
    var_r9 = 1;
    if (var_r30->unk0x2BE == 0) {
        var_r9 = 0;
    }
    if ((var_r9 != 0) && (*(s32 *)var_r30 == temp_r29) && (fn_801F2184(var_r30) == arg1)) {
        return var_r30;
    }
    var_r31 += 1;
    var_r30 = (char *)var_r30 + 0x370;
    if (var_r31 > 0x31) {
        return 0;
    }
    goto loop_1;
}
