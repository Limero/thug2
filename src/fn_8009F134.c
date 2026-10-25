// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F134-0x8009F190 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
void fn_8000F320(Unk_F12C5E01 *);
void CStruct_new(s32);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8009F134(Unk_C7387A53 *arg0) {
    Unk_89783F6B *temp_r3;

    if ((s32) arg0->unk0x24 == 0) {
        temp_r3 = *(void * *)&lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x124);
        CStruct_new(8);
        arg0->unk0x24 = CStruct_ctor();
        fn_8000F320(*(void * *)&lbl_802FFE98);
    }
}
