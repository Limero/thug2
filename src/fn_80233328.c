// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80233328-0x80233394 (108B). Byte-identical.
#include "types.h"
extern void fn_8014DB40(u32, s32, s32);
s32 fn_8023C598(s32);
void fn_80233328(void) {
    if ((fn_8023C598(0) != 0) && (*(s32 *)((char *)fn_8023C598(1) + 0x74) == 6)) {
        fn_8014DB40(0x5B509AD3u, 0, 0);
        return;
    }
    fn_8014DB40(0x64716BEEu, 0, 0);
}
