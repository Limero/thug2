// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AB058-0x800AB0F0 (152B). Byte-identical.
#include "types.h"
extern char lbl_80301A38[];
extern char lbl_802983C4[];
extern char lbl_802983D0[];
extern char lbl_802983F4[];
void fn_800A1AE8(s32, s32, s32, s32);
s32 fn_80125A08(s32, s32);
s32 fn_801289A8(void *, void *);
void fn_800AB058(void *arg0) {
    s32 temp_r30;
    s32 temp_r30_2;

    if (fn_801289A8(arg0, (s32)lbl_802983C4) != 0) {
        temp_r30 = *(s32 *)&lbl_80301A38;
        fn_800A1AE8(temp_r30, fn_80125A08((s32)lbl_802983D0, 0), arg0, 1);
        return;
    }
    temp_r30_2 = *(s32 *)&lbl_80301A38;
    fn_800A1AE8(temp_r30_2, fn_80125A08((s32)lbl_802983F4, 0), arg0, 1);
}
