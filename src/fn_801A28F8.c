// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A28F8-0x801A297C (132B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AB320[];
extern char lbl_802984C8[];
void fn_801A2A58(s32);
void fn_8002448C(void *, s32);
void fn_8009E0B0(Unk_DB0E2BAB *, s32);
void fn_801A28F8(Unk_9994C3F5 *arg0, s32 arg1) {
    Unk_C8FEE62D *temp_r9;

    arg0->unk0x8 = (s32)lbl_802AB320;
    fn_801A2A58(arg0);
    fn_8002448C(((char *)arg0 + 0x70), 2);
    temp_r9 = (char *)arg0 + 0x58;
    temp_r9->unk0x14 = (s32)lbl_802984C8;
    *(s32 *)(temp_r9->unk0x10 + 0xC) = temp_r9->unk0xC;
    *(s32 *)(temp_r9->unk0xC + 0x10) = temp_r9->unk0x10;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    fn_8009E0B0(arg0, arg1);
}
