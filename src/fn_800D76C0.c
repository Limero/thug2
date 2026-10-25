// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D76C0-0x800D7738 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800F0F84(s32, s32);
void fn_800F078C(CStruct *, Unk_9994C3F5 *);
void fn_800D69A0(Unk_C8FEE62D *, CStruct *, s32);
void fn_800D76C0(Unk_C8FEE62D *arg0, CStruct *arg1) {
    f32 sp8[4];
    s32 sp18;
    sp18 = 0;
    GetChecksum_2(arg1, QB_NAME, &sp18, 0);
    if (sp18 != 0) {
        fn_800F078C(fn_800F0F84(sp18, 1), &sp8);
        fn_800D69A0(arg0, arg1, &sp8);
    }
}
