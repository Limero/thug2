// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054C00-0x80054C6C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80364C28[];
void fn_80055EEC(Unk_CFB386B2 *);
void fn_80054C00(void) {
    register void *r11 asm("r11");
    CStruct *temp_r9;
    void *var_r31;

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
            fn_80055EEC(((CStruct *)r11)->unk0x4);
            r11 = var_r31;
        } while (r11 != NULL);
    }
}
