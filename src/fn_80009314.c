// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009314-0x80009370 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800093AC(CStruct *, s32, s32, s32);
u32 strlen(const char *);
s32 fn_80009314(CStruct *arg0, void *arg1) {
    s32 var_r6;

    var_r6 = 0;
    if (arg1 != 0) {
        var_r6 = strlen((const char *)arg1) - 1;
        if (var_r6 < 0) {
            var_r6 = 0;
        }
    }
    fn_800093AC(arg0, arg1, 0, var_r6);
    return arg0;
}
