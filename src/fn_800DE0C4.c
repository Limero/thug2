// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DE0C4-0x800DE11C (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_800A7938(CStruct *, s32);
extern char lbl_8029A110[];
void fn_800DE0C4(CScript *arg0, s32 arg1) {
    s32 v;
    arg0->unk0x18 = (s32)lbl_8029A110;
    v = arg0->unk0x1C;
    if (v != 0) {
        fn_800A7938(v, 3);
    }
    fn_8009F558(arg0, arg1);
}
