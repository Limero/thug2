// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017E340-0x8017E398 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -O1
#include "types.h"
#include "structs.h"
#include "mem.h"
s32 fn_80182F54(s32, s32);
void fn_80182E98(s32, s32);
void fn_80180390(Unk_F515CE8D *);
void fn_8017E340(s32 arg0, s32 arg1) {
    fn_80180390(arg0);
    fn_80182F54(arg0 + 0x54, 2);
    fn_80182E98(arg0 + 0x3C, 2);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}