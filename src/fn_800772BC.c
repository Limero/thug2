// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800772BC-0x80077328 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8007DF14(Unk_9D99273B *);
bool fn_800772BC(Unk_FFAD6788 *arg0, s32 arg1) {
    CStruct *temp_r3;
    Unk_F5317C5D *temp_r9;

    if (arg1 == 0) {
        temp_r3 = fn_8007DF14(arg0->unk0xC8);
        temp_r3->unk0x4 = (s32) (temp_r3->unk0x4 | 0x800);
    }
    if (arg0 != NULL) {
        temp_r9 = arg0->unk0xBC;
        ((s32 (*)(void *, s32))temp_r9->unk0xC)((char *)arg0 + temp_r9->unk0x8, 3);
    }
    return true;
}
