// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800322C0-0x80032328 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8002DCCC(Unk_C8FEE62D *);
extern char lbl_80291B60[];
void *fn_800322C0(Unk_C8FEE62D *arg0, s32 arg1) {
    fn_8002DCCC((char *)arg0 + 4);
    arg0->unk0x18 = (s32)lbl_80291B60;
    arg0->unk0x74 = 1;
    arg0->unk0x58 = 0;
    arg0->unk0x6C = 0;
    arg0->unk0x70 = 0;
    arg0->unk0x3C = 2;
    arg0->unk0x68 = arg1;
    return arg0;
}
