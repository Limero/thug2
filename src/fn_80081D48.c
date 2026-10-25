// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80081D48-0x80081D9C (84B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8006BE8C(CStruct *, void *);
extern char lbl_80296610[];
void fn_80081D48(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0x28 = (s32)lbl_80296610;
    if ((s32) arg0->unk0x34 != 0) {
        Mem_Free2(arg0->unk0x34);
    }
    fn_8006BE8C(arg0, arg1);
}
