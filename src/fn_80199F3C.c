// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80199F3C-0x80199F9C (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern char lbl_80305F9C[];
void *fn_801746A4(s32);
void fn_8021D358(s32, u16);
s32 fn_8022A470(void);

s32 fn_80199F3C(void) {
    s32 temp_r31;
    Unk_EE36B018 *temp_r3_2;

    temp_r31 = *(s32 *)&lbl_80305F9C;
    temp_r3_2 = fn_801746A4(*(s32 *)&lbl_80305EAC);
    if (temp_r3_2 == NULL) {
        return 0;
    }
    fn_8021D358(temp_r31, temp_r3_2->unk0x1A);
    return fn_8022A470() == 0;
}
