// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F37CC-0x800F3830 (100B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800133B4(Unk_DB0E2BAB *);
void fn_80013788(s32);
bool fn_800F37CC(Unk_C7387A53 *arg0) {
    Unk_911027B9 *temp_r9;

    if ((s32) arg0->unk0x20 != 0) {
        fn_800133B4(arg0->unk0x20);
        fn_80013788(arg0->unk0x20);
        arg0->unk0x20 = 0;
    }
    temp_r9 = arg0->unk0x50;
    temp_r9->unk0xB4((char *)arg0 + temp_r9->unk0xB0);
    return true;
}
