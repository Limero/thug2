// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80136F1C-0x80136FA0 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80303148;
extern void fn_8000A578(void *arg0, s32 arg1);
extern s32 fn_8013BE10(Unk_298A0A9D * arg0);
extern s32 fn_8013BE08(Unk_9C44AE00 * arg0);
extern s32 fn_8013BE18(Unk_9C44AE00 * arg0);
extern s32 fn_8013BE20(Unk_CA1C78B1 * arg0);

void fn_80136F1C(s32 arg0, Unk_9C44AE00 *arg1) {
    void *temp_r30;
    s32 temp_r3;

    temp_r30 = (void *)lbl_80303148;
    temp_r3 = fn_8013BE10(arg1);
    fn_8000A578(temp_r30 + 8, temp_r3);
    fn_8000A578(temp_r30 + 8, fn_8013BE08(arg1));
    fn_8000A578(temp_r30 + 8, fn_8013BE18(arg1));
    fn_8000A578(temp_r30 + 8, fn_8013BE20(arg1));
}
