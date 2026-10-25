// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023C7A4-0x8023C808 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_802371CC(Unk_673C6403 *, Unk_4A174A22 *, s32);
extern void fn_80236E10(s32 *, s32);

void fn_8023C7A4(CStruct *arg0) {
    Unk_9994C3F5 *temp_r9;

    temp_r9 = *((s32 * *)&arg0->unk0x48);
    if (temp_r9 != NULL) {
        *((u32 *)&temp_r9->unk0x8) &= QB_UNKNOWN_0xFFFFFDFF;
        fn_802371CC(arg0->unk0x0, arg0->unk0x48, 0);
        fn_80236E10(arg0->unk0x0, 0);
        arg0->unk0x48 = NULL;
    }
}
