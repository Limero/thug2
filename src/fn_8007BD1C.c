// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007BD1C-0x8007BD70 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8005DB30(Unk_C8FEE62D *, void *);
extern char lbl_80295CE0[];
void fn_8007BD1C(Unk_C8FEE62D *arg0, s32 arg1) {
    arg0->unk0x14 = (s32)lbl_80295CE0;
    if ((s32) arg0->unk0x18 != 0) {
        Mem_Free(arg0->unk0x18);
    }
    fn_8005DB30(arg0, arg1);
}
