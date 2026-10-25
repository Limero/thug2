// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D034C-0x800D03AC (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80299980[];
void *fn_800D034C(Unk_DB0E2BAB *arg0) {
    s32 var_ctr;

    fn_8009F53C();
    var_ctr = 4;
    arg0->unk0x18 = (s32)lbl_80299980;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0x4 = QB_LOCKOBJ;
    *((s32 *)&arg0->unk0x90) = (s32) (*((s32 *)&arg0->unk0x90) & QB_UNKNOWN_0xDFFFFFFF);
    return arg0;
}
