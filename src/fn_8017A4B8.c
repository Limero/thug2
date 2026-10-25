// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017A4B8-0x8017A564 (172B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern s32 fn_8021D358(s32, s32);
extern void fn_8021DAD4(Unk_9994C3F5 *, CScript *, s32);
extern void fn_80173910(void *, Unk_9D99273B *);
extern s32 fn_8021D5DC(void *, s32);
extern void fn_8021D66C(void *, s32);
extern void fn_802204B8(Unk_C7387A53 *);
bool fn_8017A4B8(Unk_DB0E2BAB *arg0) {
    Unk_12004030 *temp_r30;
    s32 temp_r31;
    s32 temp_r29;
    CScript *temp_r3;
    s32 temp_r30_2;

    temp_r30 = arg0->unk0x0;
    temp_r31 = lbl_80305F9C;
    temp_r29 = arg0->unk0x18;
    temp_r3 = fn_8021D358(temp_r31, (u16) (s8) *((u8 *)&temp_r30->unk0x0));
    if (temp_r3 != 0) {
        temp_r30_2 = temp_r3->unk0x18;
        fn_8021DAD4(temp_r31, temp_r3, (s8) temp_r30->unk0x1);
        fn_80173910(temp_r29, temp_r30_2);
    } else {
        temp_r3 = fn_8021D5DC(temp_r31, (u16) (s8) *((u8 *)&temp_r30->unk0x0));
        if (temp_r3 != 0) {
            fn_8021D66C(temp_r31, temp_r3);
        }
    }
    fn_802204B8(temp_r31);
    return true;
}
