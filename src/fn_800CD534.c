// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CD534-0x800CD59C (104B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8011BEFC(void *);
void fn_8009F558(Unk_C8FEE62D *, void *);
extern char lbl_80299710[];
void fn_800CD534(CScript *arg0, s32 arg1) {
    s32 *var_r31;
    s32 temp_r3;
    s32 var_r30;

    arg0->unk0x18 = (s32)lbl_80299710;
    var_r31 = (char *)arg0 + 0x1C;
    var_r30 = 3;
    do {
        temp_r3 = *((s32 *)var_r31);
        var_r31 += 1;
        if (temp_r3 != 0) {
            fn_8011BEFC(temp_r3);
        }
        var_r30 -= 1;
    } while (var_r30 != 0);
    fn_8009F558(arg0, arg1);
}
