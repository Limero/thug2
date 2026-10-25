// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019D17C-0x8019D230 (180B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AAE90[];
extern void fn_8009C8A8(Unk_C8FEE62D * arg0, s32 arg1);
void fn_8019D17C(Unk_C8FEE62D *arg0, s32 arg1) {
    CScript *temp_r11;
    Unk_4E705049 *temp_r9;
    s32 *var_arr;
    u32 var_idx;
    s32 var_cnt;
    s32 var_zero;

    temp_r11 = *((void * *)&arg0->unk0x18);
    arg0->unk0x14 = (s32)lbl_802AAE90;
    if (temp_r11 != NULL) {
        temp_r9 = *((void * *)&temp_r11->unk0x18);
        ((void (*)(void *, s32))temp_r9->unk0x1C)((char *)temp_r11 + temp_r9->unk0x18, 3);
    }
    var_arr = (s32 *)((char *)arg0 + 0x28);
    var_zero = 0;
    var_idx = 0;
    var_cnt = 4;
    do {
        temp_r11 = *(void **)(var_idx + (s32)var_arr);
        if (temp_r11 != NULL) {
            temp_r9 = *((void * *)&temp_r11->unk0x18);
            ((void (*)(void *, s32))temp_r9->unk0x1C)((char *)temp_r11 + temp_r9->unk0x18, 3);
        }
        *(s32 *)(var_idx + (s32)var_arr) = var_zero;
        var_idx += 4;
    } while (--var_cnt != 0);
    fn_8009C8A8(arg0, arg1);
}
