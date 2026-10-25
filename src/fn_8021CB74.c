// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021CB74-0x8021CD38 (452B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80301A38;
extern s32 lbl_80305F9C;
s32 fn_800A398C(s32 arg0, s32 arg1);
void *GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
void fn_801BF2AC(Unk_5B483C70 * obj, Unk_6A70655D * val);
void fn_801C0B34(Unk_FFAD6788 * obj, Unk_6A70655D * val);
void fn_801C0AE4(CScript * obj);
void *NextItem(s32 mgr);

void fn_8021CB74(CScript *arg0, CScript *arg1) {
    CScript *temp_r29;
    void *temp_r30;
    CScript *temp_r31;
    Unk_C7387A53 *temp_r30_2;
    Unk_E06AC104 *sub;
    s32 var_r11;

    temp_r30 = (void *)fn_800A398C(lbl_80301A38, QB_SKATERCAM0);
    temp_r29 = GetChecksum_3((s32)temp_r30, QB_SKATERCAMERA);
    temp_r31 = GetChecksum_3((s32)temp_r30, QB_WALKCAMERA);
    if ((arg1 == NULL) || (arg1->unk0x18 == 0)) {
        fn_801BF2AC(temp_r29, 0);
        fn_801C0B34(temp_r31, 0);
        temp_r31->unk0x1C = 3;
        arg0->unk0x1F8 = 0;
        return;
    }
    if (arg1 != NextItem(lbl_80305F9C)) {
        fn_801BF2AC(temp_r29, arg1->unk0x18);
        fn_801C0B34(temp_r31, 0);
        temp_r31->unk0x1C = 3;
        ((s32 (*)(void *, s32))*(s32 *)((char *)(temp_r29->unk0x18) + 0x44))(
            (char *)temp_r29 + *(s16 *)((char *)(temp_r29->unk0x18) + 0x40), 0);
        ((s32 (*)(void *, s32))*(s32 *)((char *)(temp_r31->unk0x18) + 0x44))(
            (char *)temp_r31 + *(s16 *)((char *)(temp_r31->unk0x18) + 0x40), 1);
    } else {
        temp_r30_2 = GetChecksum_3(arg1->unk0x18, QB_SKATERPHYSICSCONTROL);
        fn_801BF2AC(temp_r29, arg1->unk0x18);
        fn_801C0B34(temp_r31, arg1->unk0x18);
        temp_r31->unk0x1C = 3;
        var_r11 = 0;
        sub = *((void * *)&temp_r30_2->unk0x38);
        if (sub->unk0x188 == 0) {
            var_r11 = (sub->unk0x20 == 0);
        }
        if (var_r11 != 0) {
            ((s32 (*)(void *, s32))*(s32 *)((char *)(temp_r29->unk0x18) + 0x44))(
                (char *)temp_r29 + *(s16 *)((char *)(temp_r29->unk0x18) + 0x40), 0);
            ((s32 (*)(void *, s32))*(s32 *)((char *)(temp_r31->unk0x18) + 0x44))(
                (char *)temp_r31 + *(s16 *)((char *)(temp_r31->unk0x18) + 0x40), 1);
        } else {
            ((s32 (*)(void *, s32))*(s32 *)((char *)(temp_r29->unk0x18) + 0x44))(
                (char *)temp_r29 + *(s16 *)((char *)(temp_r29->unk0x18) + 0x40), 1);
            ((s32 (*)(void *, s32))*(s32 *)((char *)(temp_r31->unk0x18) + 0x44))(
                (char *)temp_r31 + *(s16 *)((char *)(temp_r31->unk0x18) + 0x40), 0);
            fn_801C0AE4(temp_r31);
        }
    }
    arg0->unk0x1F8 = arg1;
}
