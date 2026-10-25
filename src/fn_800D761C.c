// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D761C-0x800D76C0 (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800F0598(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_800F0670(void *, s32);
void fn_800F078C(CStruct *, Unk_9994C3F5 *);
void fn_800D69A0(Unk_C8FEE62D *, CStruct *, s32);
void fn_800D761C(CScript *arg0, CStruct *arg1) {
    f32 sp8[4];
    s32 sp18;
    s32 temp_r30;
    temp_r30 = fn_800F0598(arg0->unk0x200);
    if (temp_r30 != 0) {
        sp18 = 1;
        GetInteger(arg1, QB_LINKNUM, &sp18, 0);
        sp18 -= 1;
        if (sp18 < 0 || sp18 >= temp_r30) {
            sp18 = 0;
        }
        fn_800F078C(fn_800F0670(arg0->unk0x200, sp18), &sp8);
        fn_800D69A0(arg0, arg1, &sp8);
    }
}
