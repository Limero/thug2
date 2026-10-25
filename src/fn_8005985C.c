// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005985C-0x800598C8 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_8030089C;
extern char lbl_80364CC8[];
void fn_8005A0B0(Unk_C7387A53 *);
void fn_8005985C(void) {
    s32 var_r30;
    void *var_r31;
    for (var_r30 = 0; var_r30 < lbl_8030089C; var_r30++) {
        var_r31 = (void *)((s32)lbl_80364CC8 + var_r30 * 0x28);
        fn_8005A0B0((s32)var_r31);
    }
    lbl_8030089C = 0;
}
