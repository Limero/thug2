// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005CC88-0x8005CCFC (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8005D2C8(s32, s32 *);
s32 fn_8005C5B4(CStruct *);
bool fn_8005CC88(CStruct *arg0, CStruct *arg1) {
    s32 sp8;
    Unk_C7387A53 *temp_r9;

    sp8 = fn_8005C5B4(arg1);
    fn_8005572C();
    temp_r9 = arg0->unk0x10;
    if (((s32 (*)(void *, void *))temp_r9->unk0x34)((char *)arg0 + *(s16 *)&temp_r9->unk0x30, arg1) != 0) {
        fn_8005D2C8(arg0->unk0x8, &sp8);
        return true;
    }
    return false;
}
