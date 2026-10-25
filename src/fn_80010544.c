// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010544-0x800105CC (136B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000F9C4(Unk_FFAD6788 *, Unk_C7387A53 *);
bool fn_80010544(Unk_FFAD6788 *arg0, s32 arg1, s32 arg2) {
    void *temp_r11;
    CStruct *temp_r3;
    Unk_F5317C5D *temp_r9;

    temp_r3 = fn_800103C4();
    if (temp_r3 != NULL) {
        fn_8000F9C4(arg0, temp_r3->unk0x4);
        temp_r11 = temp_r3->unk0x0;
        if (temp_r11 != NULL) {
            temp_r9 = ((CScript *)temp_r11)->unk0x18;
            ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
        }
        temp_r3->unk0x0 = NULL;
        temp_r3->unk0x4 = 0;
        temp_r3->unk0x8 = 0;
        temp_r3->unk0x8C = 0;
        return true;
    }
    return false;
}
