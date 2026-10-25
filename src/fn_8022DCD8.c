// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022DCD8-0x8022DD54 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
s32 fn_80056080(void * arg0, s32 arg1, void * arg2, Unk_C8FEE62D * arg3, s32 arg4, s32 arg5);
void fn_8000F320(Unk_F12C5E01 * arg0);
s32 fn_8022DCD8(Unk_DB0E2BAB *arg0, s32 arg1, Unk_C8FEE62D *arg2, s32 arg3, s32 arg4) {
    s32 temp_r30;
    Unk_9994C3F5 *temp_r3;

    temp_r3 = *(void * *)&lbl_802FFE98;
    arg0->unk0x0 = (s32) (arg0->unk0x0 | 0x40);
    fn_8000F2F8(temp_r3, temp_r3->unk0x11C);
    temp_r30 = fn_80056080(arg0->unk0x10, arg1, arg0->unk0x14, arg2, arg3, 0);
    fn_8000F320(*(void * *)&lbl_802FFE98);
    return temp_r30;
}
