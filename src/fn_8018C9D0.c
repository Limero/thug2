// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018C9D0-0x8018CA50 (128B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_801907E0(s32 arg0, s32 arg1);
bool fn_8018C9D0(Unk_C8FEE62D *arg0) {
    Unk_89391A04 *temp_r9;
    Unk_0E2E8431 *temp_r9_2;

    temp_r9 = *((void * *)&arg0->unk0x14);
    if (temp_r9->unk0x24((char *)arg0 + (s32)temp_r9->unk0x20) != 0) {
        fn_801907E0(arg0, QB_FAIL);
        temp_r9_2 = *((void * *)&arg0->unk0x14);
        ((s32 (*)(void *, s32, s32))(void *(*))temp_r9_2->unk0x74)((char *)arg0 + (s32)temp_r9_2->unk0x70, 1, 1);
        return true;
    }
    return false;
}
