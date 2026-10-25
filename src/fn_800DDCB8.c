// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DDCB8-0x800DDD34 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80062594(CStruct *, s32);
void fn_800DDCB8(Unk_C8FEE62D *arg0) {
    void *temp_r11;
    CScript *temp_r9;
    Unk_F5317C5D *temp_r9_2;

    if ( arg0->unk0x1C != NULL) {
        temp_r9 = arg0->unk0x44;
        if (temp_r9 != NULL) {
            fn_80062594(temp_r9->unk0x210, 0);
        }
        temp_r11 = arg0->unk0x1C;
        if (temp_r11 != NULL) {
            temp_r9_2 = ((Unk_9994C3F5 *)temp_r11)->unk0x8;
            ((s32 (*)(void *, s32))temp_r9_2->unk0xC)(temp_r11 + temp_r9_2->unk0x8, 3);
        }
        arg0->unk0x1C = NULL;
    }
}
