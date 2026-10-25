// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802296A0-0x80229718 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void *lbl_802FFE98;
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern void fn_8000F320(Unk_F12C5E01 * arg0);
void fn_802296A0(CScript *arg0, void *arg1, s32 arg2) {
    u8 *temp_r3;
    u8 temp_r29;

    fn_8000F2F8(lbl_802FFE98, ((Unk_C7387A53 *)lbl_802FFE98)->unk0x13C);
    temp_r29 = *(u8 *)(arg0->unk0x18 + (s32)0x1B);
    temp_r3 = (u8 *)Mem_Alloc(arg2 + 1);
    arg0->unk0x1F0 = (s32)temp_r3;
    *temp_r3 = temp_r29;
    memcpy(temp_r3 + 1, arg1, arg2);
    fn_8000F320(lbl_802FFE98);
}
