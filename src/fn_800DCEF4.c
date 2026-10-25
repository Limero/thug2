// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DCEF4-0x800DCF68 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80299FA8[];
void fn_8009F558(Unk_C8FEE62D *, s32);

void fn_800DCEF4(CScript *arg0, s32 arg1) {
    Unk_9994C3F5 *temp_r11;
    Unk_F5317C5D *temp_r9;

    temp_r11 = arg0->unk0x1C;
    arg0->unk0x18 = (s32)lbl_80299FA8;
    if (temp_r11 != NULL) {
        temp_r9 = temp_r11->unk0x8;
        ((s32 (*)(void *, s32))temp_r9->unk0xC)(
            (char *)temp_r11 + temp_r9->unk0x8, 3);
        arg0->unk0x1C = NULL;
    }
    fn_8009F558(arg0, arg1);
}