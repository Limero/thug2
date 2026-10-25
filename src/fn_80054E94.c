// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054E94-0x80054EE8 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -ffixed-r11
#include "types.h"
#include "structs.h"
extern char lbl_80364C28[];
void *fn_80054E94(void) {
    Unk_FFAD6788 *temp_r3;
    register CStruct *var_r11 __asm__("r11");
    CStruct *var_r9;

    var_r11 = *(CStruct **)&lbl_80364C28;
    if ((s32) var_r11->unk0x4 == -1) {
        var_r11 = NULL;
    }
    while (var_r11 != NULL) {
        var_r9 = var_r11->unk0xC;
        if ((s32) var_r9->unk0x4 == -1) {
            var_r9 = NULL;
        }
        temp_r3 = var_r11->unk0x4;
        if ((s32) temp_r3->unk0x8C != 0) {
            return temp_r3;
        }
        var_r11 = var_r9;
    }
    return NULL;
}
