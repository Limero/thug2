// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070AE8-0x80070B40 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802950B0[];
extern void fn_80070D40(CStruct *);
void fn_80070AE8(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0x20 = (s32)lbl_802950B0;
    if ((s32) arg0->unk0xC == 1) {
        fn_80070D40(arg0);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
