// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003AEA0-0x8003AEEC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80292070[];
void *fn_8003AEA0(CStruct *arg0, s32 arg1, s32 arg2) {
    fn_8009E004();
    arg0->unk0x58 = arg1;
    arg0->unk0x5C = arg2;
    arg0->unk0x8 = (s32)lbl_80292070;
    return arg0;
}
