// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801783B4-0x801784C8 (276B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305F9C[];
extern void* lbl_80305EC0;
s32 fn_8021D2C4(s32, s32);
s32 fn_801403CC(void *);
s32 fn_8021F6CC(Unk_2EC243AC *);
s32 IsTrue(s32, void *);
s32 fn_80198A80(s32);
s32 fn_8019880C(s32);
s32 fn_80198854(CStruct *);
s32 fn_801813F0(CStruct *);
void fn_80181300(Unk_F515CE8D *, s32);

s32 fn_801783B4(CStruct *arg0) {
    s32 temp_r30;
    Unk_252476BB *temp_r31;
    CScript *temp_r29;

    temp_r30 = *(s32 *)&lbl_80305F9C;
    temp_r29 = (void *)fn_8021D2C4(temp_r30, arg0->unk0x10);
    if ((temp_r29 == NULL) || (temp_r29->unk0x18 == 0)) {
        return 4;
    }
    temp_r31 = arg0->unk0x0;
    if (fn_8021F6CC(temp_r30) != (s32)temp_r31->unk0x0) {
        return 4;
    }
    temp_r30 = temp_r31->unk0x4;
    temp_r31 = fn_801403CC(temp_r29->unk0x18);
    if (temp_r30 > temp_r31->unk0x34) {
        temp_r31->unk0x34 = temp_r30;
    }
    if ((IsTrue(lbl_80305EC0, QB_SHOULD_MODULATE_COLOR) == 0) && (fn_80198A80(lbl_80305EC0) != 0)) {
        if (fn_8019880C(lbl_80305EC0) != 0) {
            fn_80181300(temp_r31, fn_801813F0(temp_r31) + temp_r30);
        } else if ((fn_80198854(lbl_80305EC0) != 0) && (fn_801813F0(temp_r31) < temp_r30)) {
            fn_80181300(temp_r31, temp_r30);
        }
    }
    return 1;
}
