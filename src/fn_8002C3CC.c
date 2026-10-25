// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002C3CC-0x8002C43C (112B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802917E0[];
extern char lbl_80291808[];
void CStruct_delete(CStruct *, s32);
void fn_8002C3CC(CStruct *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_802917E0;
    if ((s32) arg0->unk0x10 != 0) {
        CStruct_delete(arg0->unk0x10, 3);
        arg0->unk0x10 = 0;
    }
    arg0->unk0x8 = (s32)lbl_80291808;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
