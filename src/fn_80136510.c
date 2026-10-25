// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80136510-0x801365B0 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8039D940[];
s32 fn_8024EA14(s32, s32, s32);
s32 fn_8024EA74(s32, s32, s32, s32);
s32 fn_8024EA94(s32);
bool fn_80136510(void) {
    s32 temp_r3;
    s32 temp_r4;
    s32 var_r0;
    Unk_FBC79ECB *p;

    temp_r3 = fn_8024EA14(*(s32 *)&lbl_8039D940, ((Unk_7B6F5FE5 *)lbl_8039D940)->unk0x4, ((Unk_7B6F5FE5 *)lbl_8039D940)->unk0x90);
    ((Unk_7B6F5FE5 *)lbl_8039D940)->unk0x190 = temp_r3;
    if (temp_r3 == 0) {
        return false;
    }
    if (((Unk_7B6F5FE5 *)lbl_8039D940)->unk0x8D != 0) {
        var_r0 = ((Unk_7B6F5FE5 *)lbl_8039D940)->unk0x8E + 0x10;
    } else {
        var_r0 = 0x24;
    }
    p = lbl_8039D940;
    temp_r4 = p->unk0xA8;
    if (fn_8024EA74(p->unk0x190, temp_r4 + var_r0, ((CStruct *)temp_r4)->unk0x4 - var_r0, p->unk0x94) == 0) {
        fn_8024EA94(p->unk0x190);
        return false;
    }
    return true;
}
