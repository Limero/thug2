// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070EC4-0x80070F08 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80070EC4(CStruct *arg0) {
    Unk_89391A04 *temp_r9;

    if ((s32) arg0->unk0x0 != 0) {
        temp_r9 = arg0->unk0x4;
        ((s32 (*)(void *))temp_r9->unk0x14)((char *)arg0 + temp_r9->unk0x10);
    }
}
