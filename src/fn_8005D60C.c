// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005D60C-0x8005D6C8 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8036645C[];
void fn_8005D4A8(void *, void *);
unsigned int fn_8000A778(const char *str);
void fn_8001075C(void *);
void fn_80010760(void);
Unk_897A0ACF *fn_8005D7A0(s32);
void *fn_8007B38C(void *, s32, s32, s32, s32);
void fn_8005D844(void *, void *, void *);
Unk_897A0ACF *fn_8005D60C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp88;
    char sp8[0x80];
    Unk_897A0ACF *var_r30;
    s32 temp_r0;

    fn_8005D4A8(sp8, arg0);
    fn_8001075C(arg0);
    temp_r0 = fn_8000A778(arg0) + arg2;
    sp88 = temp_r0;
    var_r30 = fn_8005D7A0(temp_r0);
    if (var_r30 != NULL) {
        var_r30->unk0x4 = (u16) (var_r30->unk0x4 + 1);
    } else {
        var_r30 = fn_8007B38C(sp8, arg1, arg2, arg3, arg4);
        *((s32 *)var_r30) = sp88;
        fn_8005D844(lbl_8036645C, &sp88, var_r30);
    }
    fn_80010760();
    return var_r30;
}
