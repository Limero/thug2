// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007B76C-0x8007B7B0 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009A464(Unk_C7387A53 *, s32);
void fn_8007B76C(Unk_C7387A53 *arg0) {
    CScript *temp_r9;

    temp_r9 = arg0->unk0x48;
    if (temp_r9 != NULL) {
        fn_8009A464(arg0->unk0x50, temp_r9->unk0x18);
        return;
    }
    fn_8009A464(arg0->unk0x50, 0);
}
