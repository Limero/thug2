// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80178214-0x80178284 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305F9C[];
s32 fn_8021FCF8(s32);
s32 fn_8021B554(Unk_9994C3F5 *);
s32 fn_8021FE18(Unk_7A675EAB *);
void fn_80177F38(Unk_C7387A53 *, s32);

void fn_80178214(Unk_C7387A53 *arg0) {
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r31;

    temp_r29 = arg0->unk0x20;
    temp_r31 = *(s32 *)&lbl_80305F9C;
    if (fn_8021FCF8(temp_r31) != 0) {
        temp_r30 = fn_8021B554(temp_r31);
        if ((u32)(*(s32 *)temp_r30 - fn_8021FE18(temp_r31)) > 0x7CFU) {
            fn_80177F38(temp_r29, 0);
        }
    }
}
