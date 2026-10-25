// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006DEE0-0x8006DF8C (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 lbl_8030142C;
void fn_8006F774(void *);
void fn_8006F6BC(s32, s32 *);
s32 fn_8006F600(s32, s32);
void fn_8006F5EC(s32);
void fn_8006DEE0(void) {
    s32 sp8;
    s32 handle;
    void *temp_r11;
    Unk_FFAD6788 *temp_r30;
    Unk_B1C93D59 *temp_r9;
    void *var_r31;

    fn_8006F5EC(lbl_8030142C);
    if ((var_r31 = (void *)fn_8006F600(lbl_8030142C, 0)) != NULL) {
        do {
            temp_r30 = (Unk_FFAD6788 *)var_r31;
            var_r31 = (void *)fn_8006F600(lbl_8030142C, 0);
            temp_r11 = (void *)temp_r30->unk0xB0;
            if (temp_r11 != NULL) {
                temp_r9 = (Unk_B1C93D59 *)((Unk_C7387A53 *)temp_r11)->unk0x20;
                temp_r9->unk0xC((char *)temp_r11 + temp_r9->unk0x8, 3);
            }
            handle = lbl_8030142C;
            temp_r30->unk0xB0 = 0;
            sp8 = (s32)temp_r30;
            fn_8006F6BC(handle, &sp8);
            fn_8006F774(temp_r30);
        } while (var_r31 != NULL);
    }
}
