// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80055134-0x800551B4 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80364C28[];
void fn_800145AC(void);
void fn_80056A6C(Unk_FFAD6788 *);
void fn_80055134(void) {
    register void *r11 asm("r11");
    CStruct *temp_r9;
    void *var_r31;

    fn_800145AC();
    r11 = *(void **)&lbl_80364C28;
    if ((s32) ((CStruct *)r11)->unk0x4 == -1) {
        r11 = NULL;
    }
    if (r11 != NULL) {
        do {
            temp_r9 = ((CStruct *)r11)->unk0xC;
            if ((s32) temp_r9->unk0x4 == -1) {
                var_r31 = NULL;
            } else {
                var_r31 = temp_r9;
            }
            if ((s32) *(s32 *)(((CStruct *)r11)->unk0x4 + 0x8C) == 0) {
                fn_80056A6C(((CStruct *)r11)->unk0x4);
            }
            r11 = var_r31;
        } while (r11 != NULL);
    }
    fn_800145AC();
}
