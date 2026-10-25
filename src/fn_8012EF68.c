// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012EF68-0x8012EFA4 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80130F20(Unk_15EF4A35 *);
s32 fn_8012543C(void);
void fn_8012EF68(Unk_FFAD6788 *arg0, Unk_15EF4A35 *arg1) {
    fn_80130F20(arg1);
    arg0->unk0xD0 = *(s32 *)((char *)fn_8012543C() + 8);
}