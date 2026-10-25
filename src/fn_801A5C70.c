// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A5C70-0x801A5CE0 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_801A56F4(s32);
extern char lbl_802FFE98[];
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_9F352E7C *);
s32 fn_801A44E8(s32 arg0, s32 arg1);
s32 fn_801A6734(Unk_C8FEE62D *arg0, s32 *arg1);
void fn_801A5C70(s32 arg0) {
    s32 sp8;
    s32 temp_r30;
    s32 var_r29;
    s32 off;
    Unk_B0F19D72 *temp_r3;

    temp_r3 = *(void * *)&lbl_802FFE98;
    off = 4;
    var_r29 = arg0 + 0x1C;
    fn_8000F2F8((Unk_9F352E7C *)temp_r3, temp_r3->unk0x5F8);
    sp8 = fn_801A56F4(*(s32 *)(var_r29 + off));
    temp_r30 = *(s32 *)(var_r29 + off);
    fn_801A44E8(temp_r30, fn_801A6734((Unk_C8FEE62D *)(arg0 + 4), &sp8));
    fn_8000F320(*(void * *)&lbl_802FFE98);
}
