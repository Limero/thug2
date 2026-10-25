// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014510C-0x80145168 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305F9C[];
s32 fn_8009CF2C(CStruct *);
void *fn_800093A4(Unk_9994C3F5 *);
s32 fn_8021D358(s32, u16);
s32 fn_8014510C(Unk_EE36B018 *arg0) {
    s32 temp_r31;
    s32 r;

    temp_r31 = *(s32 *)&lbl_80305F9C;
    if (fn_8009CF2C(temp_r31) == 0) {
        r = (s32)fn_800093A4((char *)arg0 + 0x170);
    } else {
        r = fn_8021D358(temp_r31, arg0->unk0x1A) + 0x3C;
    }
    return r;
}
