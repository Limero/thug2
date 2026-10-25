// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A3294-0x801A33BC (296B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80300460;
extern char lbl_80305E98[];
u64 fn_8001448C(void);
s32 fn_801A269C(Unk_31DE137E * arg0);
void *fn_801A26E0(Unk_31DE137E * arg0, s32 arg1);
void fn_801A2C10(Unk_31DE137E * arg0, s32 arg1);
s32 fn_801A3294(Unk_C7387A53 *arg0) {
    s32 var_r3;
    s32 temp_r3;
    u64 temp_ret;
    union { u64 d; u32 w[2]; } uu;
    void *temp_r3_2;
    Unk_4E705049 *temp_r9;
    Unk_4E705049 *temp_r9_2;
    Unk_64253088 *temp_r9_3;

    if ((s32) arg0->unk0x144 != 0) {
        uu.w[1] = *((u32 *)&arg0->unk0x140);
        temp_ret = fn_8001448C();
        uu.w[0] = 0;
        if (uu.d <= temp_ret) {
            arg0->unk0x144 = 0;
            fn_801A269C(arg0);
        }
    }
    temp_r3_2 = fn_801A26E0(arg0, 0);
    if (temp_r3_2 == NULL) {
        return 0;
    }
    if ((lbl_80300460 != 0) && ((s32) *(s32 *)&lbl_80305E98 == 0)) {
        if ((s32) ((Unk_C8FEE62D *)temp_r3_2)->unk0x28 == 0) {
            temp_r9 = ((Unk_C8FEE62D *)temp_r3_2)->unk0x14;
            ((s32 (*)(void *))temp_r9->unk0x1C)(temp_r3_2 + temp_r9->unk0x18);
        }
    } else {
        temp_r9_2 = ((Unk_C8FEE62D *)temp_r3_2)->unk0x14;
        ((s32 (*)(void *))temp_r9_2->unk0x1C)(temp_r3_2 + temp_r9_2->unk0x18);
    }
    temp_r9_3 = ((Unk_C8FEE62D *)temp_r3_2)->unk0x14;
    if (((s32 (*)(void *))temp_r9_3->unk0x34)(temp_r3_2 + temp_r9_3->unk0x30) != 0) {
        fn_801A2C10(arg0, 0);
    }
    temp_r3 = fn_801A269C(arg0);
    var_r3 = 1;
    if (temp_r3 == 0) {
        var_r3 = 0;
    }
    return var_r3;
}
