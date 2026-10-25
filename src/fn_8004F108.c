// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004F108-0x8004F15C (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009E274(Unk_31DE137E *, s32);
extern char lbl_80292B58[];
void *fn_8004F108(Unk_C5BAE83F *arg0) {
    fn_8004DE48();
    arg0->unk0x8 = (s32)lbl_80292B58;
    arg0->unk0x1A8 = 1;
    fn_8009E274(arg0, QB_VMENU);
    return arg0;
}
