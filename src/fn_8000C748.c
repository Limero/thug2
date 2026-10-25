// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000C748-0x8000C79C (84B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000C6A0(Unk_E93B8C39 *);
void fn_8000C73C(Unk_FFAD6788 *);
void fn_8000C748(Unk_E93B8C39 * arg0) {
    if ((s32) arg0->unk0xC8 != 0) {
        fn_8000C73C(arg0);
        fn_8000C6A0(arg0);
        return;
    }
    fn_8000C6A0(arg0);
    fn_8000C73C(arg0);
}
