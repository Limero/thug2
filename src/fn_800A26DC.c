// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A26DC-0x800A2740 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void CStruct_delete(CStruct *, s32);
extern char lbl_80297DA0[];
void fn_800A26DC(CStruct *arg0, s32 arg1) {
    arg0->unk0x4 = (s32)lbl_80297DA0;
    if ((s32) arg0->unk0x0 != 0) {
        CStruct_delete(arg0->unk0x0, 3);
        arg0->unk0x0 = 0;
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
