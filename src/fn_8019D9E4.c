// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019D9E4-0x8019DA3C (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_802FFE98;
extern void* lbl_80300434;
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
void fn_8004B15C(Unk_9E4B1D7B *);
void fn_8019DB68(void *, s32);
void fn_8019D9E4(Unk_C7387A53 *arg0) {
    Unk_89783F6B *temp_r3;
    Unk_C7387A53 *temp_r3_2;

    temp_r3 = lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x124);
    temp_r3_2 = *((void * *)&arg0->unk0x20);
    fn_8019DB68(temp_r3_2, temp_r3_2->unk0x48);
    fn_8004B15C(lbl_80300434);
    fn_8000F320(lbl_802FFE98);
}
