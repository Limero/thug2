// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005C944-0x8005C9A8 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8005D194(void *, s32);
#include "structs.h"
#include "mem.h"
s32 fn_8005C9A8(void *, s32);
extern char lbl_802936E8[];
void fn_8005C944(CStruct *arg0, s32 arg1) {
    arg0->unk0x10 = (s32)lbl_802936E8;
    fn_8005C9A8(arg0, 1);
    if ((s32) arg0->unk0x8 != 0) {
        fn_8005D194(arg0->unk0x8, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
