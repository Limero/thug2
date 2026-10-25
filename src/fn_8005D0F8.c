// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005D0F8-0x8005D194 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80012224(s32, void *);
void fn_8005D038(CStruct *);
void fn_8005D0F8(CStruct *arg0) {
    u32 temp_r27;
    u32 var_r11;
    void *temp_r30;
    void *temp_r3;
    Unk_9994C3F5 *var_r30;
    void *var_r31;

    temp_r3 = (void *)arg0->unk0x4;
    if (temp_r3 != NULL) {
        var_r11 = 0;
        var_r31 = temp_r3;
        temp_r27 = 1 << arg0->unk0x0;
        while (var_r11 < temp_r27) {
            var_r30 = (Unk_9994C3F5 *)((Unk_9994C3F5 *)var_r31)->unk0x8;
            if (var_r30 != NULL) {
                do {
                    temp_r30 = (void *)var_r30->unk0x8;
                    fn_80012224(0, var_r30);
                    var_r30 = temp_r30;
                } while (var_r30 != NULL);
            }
            fn_8005D038(var_r31);
            var_r31 = (void *)((char *)var_r31 + 0xC);
            var_r11 += 1;
        }
        arg0->unk0x8 = 0;
    }
}