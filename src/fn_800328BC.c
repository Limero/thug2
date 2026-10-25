// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800328BC-0x80032934 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
bool fn_800328BC(Unk_C7387A53 *arg0, s32 arg1) {
    s32 var_r30;
    s32 *var_r31;
    void *temp_r11;
    Unk_89391A04 *temp_r9;

    var_r30 = 0;
    while (var_r30 < (s32) arg0->unk0x58) {
        s32 *arr = (s32 *)arg0 + 0x10;
        temp_r11 = (void *)arr[var_r30];
        var_r30 += 1;
        temp_r9 = ((Unk_C8FEE62D *)temp_r11)->unk0x14;
        ((s32 (*)(void *, void *))temp_r9->unk0x14)(temp_r11 + (s16)temp_r9->unk0x10, arg1);
    }
    return true;
}
