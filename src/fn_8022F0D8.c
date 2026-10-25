// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022F0D8-0x8022F184 (172B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_802FFE98;
extern s32 lbl_80301B40;
s32 fn_801F1FCC(void);
s32 fn_800F6430(Unk_31DE137E *, u32, s32);
s32 fn_801F1CE8(void *, s32 *, s32);
s32 fn_800F1F2C(Unk_A231C4C2 *, u32);
void fn_800F1E1C(void *, u32);
void fn_800F1C34(Unk_A231C4C2 *, u32, s32);
void fn_800F1B24(Unk_06D4670B *, s32);
void fn_8022F0D8(s32 arg0) {
    s32 sp8;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_h;
    s32 temp_cb;

    temp_r30 = arg0 + 0x494;
    temp_cb = fn_801F1FCC();
    sp8 = 0;
    temp_h = fn_800F6430(temp_r30, QB_NODEARRAY, temp_cb);
    fn_801F1CE8(temp_h, &sp8, *(s32 *)((char *)*(s32 *)&lbl_802FFE98 + 0x118));
    temp_r31 = lbl_80301B40;
    if (fn_800F1F2C(temp_r31, QB_NODEARRAY) != 0) {
        fn_800F1E1C(temp_r31, QB_NODEARRAY);
    }
    fn_800F1C34(temp_r31, QB_NODEARRAY, 1);
    fn_800F1B24(temp_r31, temp_r30);
}
