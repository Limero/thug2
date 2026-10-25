// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A64A8-0x801A6534 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8000F2F8(Unk_B0F19D72 *arg0, s32 arg1);
s32 fn_80128E34(CStruct *arg0, void *arg1, void *arg2, s32 arg3);
void *Mem_NewZero(s32 size);
s32 fn_801A44A0(void *arg0);
void fn_801A4540(s32 arg0, CStruct *arg1);
s32 fn_801A679C(s32 arg0, s32 *arg1, s32 arg2);
void fn_8000F320(Unk_B0F19D72 *arg0);
extern char lbl_802FFE98[];
bool fn_801A64A8(s32 arg0, CStruct *arg1) {
    s32 sp8;
    s32 temp_r30;
    Unk_B0F19D72 *temp_r3;
    void *temp_r5;

    temp_r3 = *(Unk_B0F19D72 **)&lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x5F8);
    fn_80128E34(arg1, QB_NAME, &sp8, 1);
    temp_r5 = Mem_NewZero(0x74);
    temp_r30 = fn_801A44A0(temp_r5);
    fn_801A4540(temp_r30, arg1);
    fn_801A679C(arg0 + 4, &sp8, temp_r30);
    fn_8000F320(*(Unk_B0F19D72 **)&lbl_802FFE98);
    return true;
}
