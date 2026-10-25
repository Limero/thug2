// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800109AC-0x80010A00 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8001076C(CScript *, void *);
extern char lbl_802905F8[];
void fn_800109AC(Unk_C8FEE62D *arg0, s32 arg1) {
    arg0->unk0x18 = (s32)lbl_802905F8;
    if ((s32) arg0->unk0x4 != 0) {
        Mem_Free2(arg0->unk0x4);
    }
    fn_8001076C(arg0, arg1);
}
