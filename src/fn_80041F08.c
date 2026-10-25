// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80041F08-0x80041F5C (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009E274(Unk_31DE137E *, s32);
extern char lbl_802923A0[];
void *fn_80041F08(Unk_4313CFEA *arg0) {
    fn_8003F360();
    arg0->unk0x8 = (s32)lbl_802923A0;
    arg0->unk0x190 = 0;
    fn_8009E274(arg0, QB_CONTAINERELEMENT);
    return arg0;
}
