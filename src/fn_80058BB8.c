// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058BB8-0x80058C38 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802FFE98[];
void strcpy(s32, s32);
void fn_8000F320(Unk_F12C5E01 *);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_80058BB8(CStruct *arg0, s32 arg1) {
    Unk_89783F6B *temp_r3;
    Unk_89391A04 *temp_r9;

    if ((s32) arg0->unk0x8 == 0) {
        temp_r3 = *(void * *)&lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x124);
        arg0->unk0x8 = Mem_Alloc(0x60);
        fn_8000F320(*(void * *)&lbl_802FFE98);
    }
    strcpy(arg0->unk0x8, arg1);
    temp_r9 = arg0->unk0x50;
    temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20);
}
