// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016CA58-0x8016CAC0 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8019EF9C(void *);;
void fn_8016CA58(Unk_C7387A53 *arg0) {
    void *temp_r11;
    void *temp_r3;
    Unk_F5317C5D *temp_r9;

    temp_r3 = arg0->unk0x58;
    if (temp_r3 != NULL) {
        fn_8019EF9C(temp_r3);
        temp_r11 = arg0->unk0x58;
        if (temp_r11 != NULL) {
            temp_r9 = ((Unk_9994C3F5 *)temp_r11)->unk0x8;
            ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
        }
        arg0->unk0x58 = NULL;
    }
}
