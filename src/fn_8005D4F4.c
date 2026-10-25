// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005D4F4-0x8005D560 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8007B418(s32);
void fn_8005D844(void *, void *, void *);
extern char lbl_8036645C[];
void *fn_8005D4F4(s32 arg0) {
    s32 sp8;
    Unk_897A0ACF *var_r31;

    sp8 = fn_8000A778();
    var_r31 = fn_8005D7A0();
    if (var_r31 != NULL) {
        var_r31->unk0x4 = (u16) (var_r31->unk0x4 + 1);
    } else {
        var_r31 = fn_8007B418(sp8);
        fn_8005D844(lbl_8036645C, &sp8, var_r31);
    }
    return var_r31;
}
