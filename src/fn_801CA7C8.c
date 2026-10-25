// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CA7C8-0x801CA820 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_8017E340(s32, s32);
extern char lbl_802ACF40[];
void fn_801CA7C8(CScript *arg0, s32 arg1) {
    s32 v;
    arg0->unk0x18 = (s32)lbl_802ACF40;
    v = arg0->unk0x1C;
    if (v != 0) {
        fn_8017E340(v, 3);
    }
    fn_8009F558(arg0, arg1);
}
