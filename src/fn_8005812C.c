// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005812C-0x80058184 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_8010411C(s32);
void fn_8005812C(Unk_C8FEE62D *arg0) {
    s32 temp_r0;
    Unk_9994C3F5 *temp_r3;

    temp_r3 = arg0->unk0x14;
    if ((temp_r3 != NULL) && ((s32) temp_r3->unk0x8 != 0)) {
        fn_8010411C(temp_r3->unk0x8);
        temp_r0 = arg0->unk0x4;
        if (temp_r0 & 0x40) {
            arg0->unk0x4 = (s32) (temp_r0 | 0x20);
        }
    }
}
