// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EF13C-0x800EF194 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_801AAF54(Unk_C7387A53 *, s32);
extern char lbl_8029B0E0[];
void fn_800EF13C(CScript *arg0, s32 arg1) {
    s32 v;
    arg0->unk0x18 = (s32)lbl_8029B0E0;
    v = arg0->unk0x1C;
    if (v != 0) {
        fn_801AAF54(v, 3);
    }
    fn_8009F558(arg0, arg1);
}
