// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F576C-0x801F5808 (156B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_801F16E8(void);
extern s32 strcasecmp(const char *a, const char *b);
void *fn_801F576C(s32 arg0, void *arg1) {
    Unk_127FDB99 *var_r31;
    s32 temp_r28;
    s32 var_r29;
    s32 var_r9;
    char *var_r30;
    temp_r28 = fn_801F16E8();
    var_r29 = 0;
    var_r30 = (char *)(arg0 + 0x24);
    var_r31 = (void *)(arg0 + 0x20);
loop_1:
    var_r9 = 1;
    if (var_r31->unk0x2BE == 0) {
        var_r9 = 0;
    }
    if ((var_r9 != 0) && (*(s32 *)var_r31 == temp_r28) && (strcasecmp(var_r30, (char *)arg1) == 0)) {
        return var_r31;
    }
    var_r29 += 1;
    var_r30 += 0x370;
    var_r31 = (char *)var_r31 + 0x370;
    if (var_r29 > 0x31) {
        return 0;
    }
    goto loop_1;
}
