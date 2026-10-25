// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80054C6C-0x80054D54 (232B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80364C28[];
s32 fn_80077090(Unk_9D99273B *, s32);
void fn_80055CB0(Unk_CFB386B2 *);
bool fn_80054C6C(Unk_CFB386B2 * arg0, s32 arg1) {
    Unk_F5317C5D *temp_r9;
    Unk_F5317C5D *temp_r9_2;
    void *var_r11;
    CStruct *var_r9;

    fn_8005572C();
    fn_80055CB0(arg0);
    if (fn_80077090(arg0, arg1) != 0) {
        if (arg0 != NULL) {
            temp_r9 = arg0->unk0x284;
            ((s32 (*)(void *, s32))temp_r9->unk0xC)((char *)arg0 + temp_r9->unk0x8, 3);
        }
        var_r11 = *(void * *)&lbl_80364C28;
        if ((s32) ((Unk_C8FEE62D *)var_r11)->unk0x4 == -1) {
            var_r11 = NULL;
        }
        if (var_r11 != NULL) {
loop_6:
            var_r9 = ((Unk_C8FEE62D *)var_r11)->unk0xC;
            if ((s32) var_r9->unk0x4 == -1) {
                var_r9 = NULL;
            }
            if ((s32) ((Unk_C8FEE62D *)var_r11)->unk0x4 == arg0) {
                if (var_r11 != NULL) {
                    temp_r9_2 = ((Unk_C8FEE62D *)var_r11)->unk0x14;
                    ((s32 (*)(void *, s32))temp_r9_2->unk0xC)(var_r11 + temp_r9_2->unk0x8, 3);
                }
                return true;
            }
            var_r11 = var_r9;
            if (var_r11 == NULL) {
                goto block_13;
            }
            goto loop_6;
        }
        goto block_13;
    }
block_13:
    return false;
}
