// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FC760-0x801FC8CC (364B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_8030342C;
extern char lbl_80305F94[];
extern char lbl_80305F84[];
s32 fn_801FC56C(s32);
void fn_801FC5B8(void *);
s32 fn_801FC728(s32, s32 *, s32);
void *fn_8013465C(CScript *, s32);
void fn_801347CC(CScript *, s32);
void *fn_8012E168(u8 *);
void *fn_8012B2A0(void *);
bool fn_801FC760(s32 arg0) {
    s32 sp8;
    s32 spC;
    s32 temp_r29;
    s32 val;
    u8 *var_r3;
    u8 *var_r31;
    u8 temp_c;

    if (fn_801FC56C(arg0) != 0) {
        return false;
    }
    fn_801FC5B8((void *)arg0);
    if (fn_801FC728(arg0, (s32)lbl_80305F94, 1) != 0) {
        return false;
    }
    if (fn_801FC728(arg0, (s32)lbl_80305F84, 4) != 0) {
        return true;
    }
    temp_r29 = lbl_8030342C;
    var_r3 = (u8 *)fn_8013465C(temp_r29, arg0);
    if (var_r3 == NULL) {
        goto ret0;
    }
    goto getNext;

dispatch:
    __asm__("clrlwi %0,%0,0x18" : "+r"(temp_c));
    if (temp_c == 0x16) {
        goto case16;
    }
    if (temp_c != 0x47) {
        goto defaultlbl;
    }
    var_r31 = (u8 *)fn_8012B2A0(var_r31);
    if (*(u8 *)var_r31 == 0x39) {
        var_r31 += 1;
    }
    goto test;

case16:
    var_r31 += 1;
    fn_8012CB2C(&sp8, var_r31);
    var_r31 += 4;
    val = sp8;
    if (*(u8 *)var_r31 == 0x42) {
        var_r31 += 1;
        if (*(u8 *)var_r31 == 0x16) {
            var_r31 += 1;
            fn_8012CB2C(&spC, var_r31);
            var_r31 += 4;
            val = spC;
        } else {
            goto defaultlbl;
        }
    }
    if (fn_801FC760(val) != 0) {
        fn_801347CC(temp_r29, arg0);
        return true;
    }

defaultlbl:
    var_r3 = var_r31;
getNext:
    var_r31 = (u8 *)fn_8012E168(var_r3);
test:
    temp_c = *(u8 *)var_r31;
    if (temp_c == 0x24) {
        fn_801347CC(temp_r29, arg0);
        goto ret0;
    }
    goto dispatch;

ret0:
    return false;
}
