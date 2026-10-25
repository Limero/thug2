// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80150134-0x80150164 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_8009E1A0(void);
void fn_80150134(CScript *arg0, s32 *arg1) {
    s32 a = *arg1;
    s32 b = arg0->unk0x18;
    if (b == a) {
        fn_8009E1A0();
    }
}

