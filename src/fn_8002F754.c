// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002F754-0x8002F7A4 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8002DDE8(void *);
void fn_8002F754(Unk_C7387A53 *arg0) {
    void *var_r3;
    void *var_r9;

    var_r9 = arg0->unk0x24;
    if ((s32) ((CStruct *)var_r9)->unk0x4 == -1) {
        var_r9 = NULL;
    }
    var_r3 = (var_r9 != NULL) ? var_r9 - 4 : NULL;
    if (var_r3 != NULL) {
        fn_8002DDE8(var_r3 + 4);
    }
}
