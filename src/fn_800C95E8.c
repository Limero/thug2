// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C95E8-0x800C9640 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800367B4(Unk_C8FEE62D *, s32);
void fn_8009F558(Unk_C8FEE62D *, s32);
extern char lbl_80299388[];
void fn_800C95E8(CScript *arg0, s32 arg1) {
    s32 v;
    arg0->unk0x18 = (s32)lbl_80299388;
    v = arg0->unk0x1C;
    if (v != 0) {
        fn_800367B4(v, 3);
    }
    fn_8009F558(arg0, arg1);
}
