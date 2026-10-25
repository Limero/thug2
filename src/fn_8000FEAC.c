// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000FEAC-0x8000FF18 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000F9C4(Unk_FFAD6788 *, Unk_C7387A53 *);
void fn_8000FEAC(Unk_C7387A53 *arg0) {
    void *temp_r11;
    Unk_F5317C5D *temp_r9;

    if (arg0->unk0x138 != NULL) {
        fn_8000F9C4(arg0, arg0->unk0x13C);
        temp_r11 = arg0->unk0x138;
        if (temp_r11 != NULL) {
            temp_r9 = ((CScript *)temp_r11)->unk0x18;
            ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
        }
        arg0->unk0x138 = NULL;
    }
}
