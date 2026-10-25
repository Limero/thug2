// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80243FC8-0x8024402C (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80238964(void);
void fn_802371CC(Unk_673C6403 *, Unk_4A174A22 *, s32);
void fn_80236E10(s32 *, s32);
void fn_80243FC8(Unk_C8FEE62D *arg0) {
    Unk_9994C3F5 *temp_r9;

    temp_r9 = arg0->unk0x14;
    if (temp_r9 != NULL) {
        temp_r9->unk0x8 = (s32) (temp_r9->unk0x8 & QB_UNKNOWN_0xFFFFFDFF);
        fn_802371CC(fn_80238964(), arg0->unk0x14, 0);
        fn_80236E10(fn_80238964(), 0);
        arg0->unk0x14 = NULL;
    }
}
