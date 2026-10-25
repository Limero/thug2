// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011BD0C-0x8011BD7C (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8038A820[];
s32 fn_80121448(s32);
bool fn_8011BD0C(s32 arg0) {
    s32 var_r30;
    void *var_r31;
    char *base;

    base = lbl_8038A820;
    var_r30 = 0;
    var_r31 = base + 0x10;
loop_1:
    if (((s32) *(s32 *)((char *)var_r31 - 0xC) == arg0) && (fn_80121448(((CStruct *)var_r31)->unk0x0) != 1)) {
        return false;
    }
    var_r30 += 1;
    var_r31 += 0x74;
    if (var_r30 > 2) {
        return true;
    }
    goto loop_1;
}
