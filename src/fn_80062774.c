// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80062774-0x800627B4 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80062774(Unk_C7387A53 *arg0, s32 arg1) {
    s16 temp_r9;
    Unk_0E2E8431 *temp_r11;

    temp_r11 = arg0->unk0x50;
    arg0->unk0x48 = (s32) (arg0->unk0x48 & QB_UNKNOWN_0x7FFFFFFF);
    temp_r9 = temp_r11->unk0x70;
    ((s32 (*)(void *))temp_r11->unk0x74)((char *)arg0 + temp_r9);
}
