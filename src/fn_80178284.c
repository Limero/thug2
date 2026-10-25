// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80178284-0x80178324 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305F9C[];
s32 fn_8021D2C4(s32, s32);
s32 fn_801403CC(void *);
s32 fn_8021F6CC(Unk_2EC243AC *);
void fn_801815EC(Unk_667BA59C *, s32, s32, s32, s32 *, s32);

s32 fn_80178284(CStruct *arg0) {
    s32 temp_r28;
    s32 temp_r29;
    Unk_6A78CE27 *temp_r30;
    Unk_C71E6DE1 *temp_r31;
    s32 level;
    CScript *temp_r3;

    temp_r29 = *(s32 *)&lbl_80305F9C;
    temp_r3 = (void *)*(u8 *)&temp_r29;
    temp_r30 = arg0->unk0x0;
    temp_r3 = fn_8021D2C4(temp_r29, arg0->unk0x10);
    if (temp_r3 == NULL) {
        return 4;
    }
    temp_r28 = fn_801403CC(temp_r3->unk0x18);
    if ((s32)temp_r30->unk0x0 != 1) {
        return 1;
    }
    temp_r31 = arg0->unk0x0;
    level = fn_8021F6CC(temp_r29);
    if ((s32)temp_r31->unk0x1 == level) {
        fn_801815EC(temp_r28, temp_r31->unk0x4, temp_r31->unk0x8, temp_r31->unk0xC, (s32)temp_r31 + 0x10, 1);
    }
    return 1;
}
