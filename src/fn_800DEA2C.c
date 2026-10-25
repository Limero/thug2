// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DEA2C-0x800DEA94 (104B). Byte-identical.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "structs.h"
void fn_8000C73C(Unk_FFAD6788 *);
void fn_800DEA2C(CScript *arg0) {
    Unk_DB0E2BAB *temp_r9;

    if ((s32) arg0->unk0x1C == 0) {
        temp_r9 = arg0->unk0x18;
        arg0->unk0x1C = 1;
        ((s32 (*)(void *, s32))temp_r9->unk0x44)((char *)arg0 + temp_r9->unk0x40, 0);
        if ((s32) arg0->unk0x38 != 0) {
            fn_8000C73C(arg0->unk0x38);
        }
    }
}
