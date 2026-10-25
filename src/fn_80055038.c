// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80055038-0x800550B4 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80364C28[];
void fn_80077498(void *, void *, void *);
void fn_80055038(Unk_C7387A53 *arg0, void *arg1, void *arg2) {
    Unk_FFAD6788 *temp_r11;
    CStruct *var_r11;
    void *var_r5;
    CStruct *var_r9;

    var_r5 = arg2;
    if (var_r5 == NULL) {
        var_r11 = *(void * *)&lbl_80364C28;
        if ((s32) var_r11->unk0x4 == -1) {
            var_r11 = NULL;
        }
        if (var_r11 != NULL) {
loop_4:
            var_r9 = var_r11->unk0xC;
            if ((s32) var_r9->unk0x4 == -1) {
                var_r9 = NULL;
            }
            temp_r11 = var_r11->unk0x4;
            if ((s32) temp_r11->unk0x8C == 0) {
                var_r5 = temp_r11;
            } else {
                var_r11 = var_r9;
                if (var_r11 != NULL) {
                    goto loop_4;
                }
            }
        }
    }
    fn_80077498(arg0, arg1, var_r5);
}
