// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003A7A4-0x8003A80C (104B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8009E0B0(Unk_DB0E2BAB *, s32);
void CStruct_delete(CStruct *, s32);
extern char lbl_80291F88[];
void fn_8003A7A4(CStruct *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_80291F88;
    if ((s32) arg0->unk0x60 != 0) {
        Mem_Free(arg0->unk0x60);
        arg0->unk0x60 = 0;
    }
    CStruct_delete((char *)arg0 + 0x58, 2);
    fn_8009E0B0(arg0, arg1);
}
