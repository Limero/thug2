// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019C1F4-0x8019C298 (164B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void CStruct_delete(CStruct *, s32);
void fn_80126A30(Unk_5AA7B5D7 *);
void fn_80128FB4(Unk_F8A5095F *, s32);
extern char lbl_802AAD08[];
void fn_8019C1F4(CStruct *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_802AAD08;
    if ((s32) arg0->unk0x0 != 0) {
        CStruct_delete(arg0->unk0x0, 3);
    }
    if ((s32) arg0->unk0x4 != 0) {
        fn_80126A30(arg0->unk0x4);
        if ((s32) arg0->unk0x4 != 0) {
            fn_80128FB4(arg0->unk0x4, 3);
        }
    }
    if ((s32) arg0->unk0x8 != 0) {
        fn_80126A30(arg0->unk0x8);
        if ((s32) arg0->unk0x8 != 0) {
            fn_80128FB4(arg0->unk0x8, 3);
        }
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
