// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A8DF8-0x801A8E5C (100B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern char lbl_80305F9C[];
void *fn_8017471C(void *, s32);
void *fn_8021D358(void *, s32);
s32 fn_801A8DF8(s32 arg0) {
    s32 mgr = *(s32 *)&lbl_80305F9C;
    void *temp_r3 = fn_8017471C(*(s32 *)&lbl_80305EAC, arg0);
    if (temp_r3 != NULL) {
        temp_r3 = fn_8021D358(mgr, ((Unk_FB68EF80 *)temp_r3)->unk0x1A);
        if (temp_r3 != NULL) {
            return ((Unk_FB68EF80 *)temp_r3)->unk0x1C;
        }
    }
    return 0;
}
