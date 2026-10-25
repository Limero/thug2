// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DEB40-0x800DEB80 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000C6A0(Unk_E93B8C39 *);
void fn_8000C73C(Unk_FFAD6788 *);
void fn_800DEB40(CScript *arg0,Unk_E93B8C39 * arg1) {
    arg0->unk0x38 = arg1;
    if ((s32) arg0->unk0x1C != 0) {
        fn_8000C73C(arg1);
        return;
    }
    fn_8000C6A0(arg1);
}
