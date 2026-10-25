// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80055658-0x800556B0 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_80364C28[];

s32 fn_80055658(void) {
    Unk_FFAD6788 *temp_r3;
    register CStruct *var_r11 __asm__("r11");
    CStruct *var_r9;
    void *var_r10;

    var_r11 = *(CStruct **)&lbl_80364C28;
    if ((s32) var_r11->unk0x4 == -1) {
        var_r11 = NULL;
    }
    while (var_r11 != NULL) {
        var_r9 = var_r11->unk0xC;
        if ((s32) var_r9->unk0x4 == -1) {
            var_r10 = NULL;
        } else {
            var_r10 = var_r9;
        }
        temp_r3 = var_r11->unk0x4;
        if (temp_r3->unk0xD4 != 0) {
            return temp_r3->unk0xD4;
        }
        var_r11 = var_r10;
    }
    return 0;
}
