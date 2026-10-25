// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80172E64-0x80172ED4 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8009F9AC(s32, s32);
void fn_80172E64(s32 arg0, Unk_9994C3F5 *arg1, s32 arg2) {
    Unk_E71E4713 *temp_r9;
    Unk_E71E4713 *temp_r9_2;
    if (arg2 != 0) {
        temp_r9 = (Unk_E71E4713 *)arg1->unk0x8;
        ((s32 (*)(void *))temp_r9->unk0x64)((char *)arg1 + temp_r9->unk0x60);
    } else {
        temp_r9_2 = (Unk_E71E4713 *)arg1->unk0x8;
        ((s32 (*)(void *))temp_r9_2->unk0x6C)((char *)arg1 + temp_r9_2->unk0x68);
    }
    fn_8009F9AC(arg1, arg2);
}
