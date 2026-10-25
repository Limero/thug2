// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CA8A4-0x801CA970 (204B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305F04;
void fn_8017E6A4(Unk_667BA59C *);
s32 fn_801A6F44(s32, s32);
s32 Script_GetInteger(s32, s32);
void fn_801A6F8C(s32, s32);
void fn_801801CC(Unk_FFAD6788 *);
void fn_801CA8A4(Unk_C8FEE62D *arg0) {
    s32 temp_r30;
    Unk_DB0E2BAB *temp_r9;

    if (*(s32 *)(arg0->unk0xC + 0xC8) == 0) {
        temp_r9 = *((void * *)&arg0->unk0x18);
        ((s32 (*)(void *, s32))(*((void * *)&temp_r9->unk0x44)))(
            (char *)arg0 + temp_r9->unk0x40, 1);
        return;
    }
    fn_8017E6A4(arg0->unk0x1C);
    if ((*(s32 *)(arg0->unk0xC + 0x180) != 0) ||
        (fn_801A6F44(((Unk_C7387A53 *)lbl_80305EAC)->unk0x24, QB_CHEAT_ALWAYS_SPECIAL) != 0)) {
        temp_r30 = ((Unk_C7387A53 *)lbl_80305EAC)->unk0x24;
        fn_801A6F8C(temp_r30, Script_GetInteger(QB_CHEAT_ALWAYS_SPECIAL, 0));
        fn_801801CC(arg0->unk0x1C);
        lbl_80305F04 = 1;
    }
}
