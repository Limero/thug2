// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023EDE4-0x8023EE14 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8023EDE4(Unk_C7387A53 *arg0, s32 arg1) {
    if ((s32) arg0->unk0x74 != arg1) {
        arg0->unk0x74 = arg1;
        fn_8023EE14();
    }
}
