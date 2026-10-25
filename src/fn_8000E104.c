// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000E104-0x8000E178 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *lbl_802FFE84;
extern s32 lbl_802FFE88;
s32 fn_8000D3DC(Unk_C8FEE62D *, s32);
s32 fn_8000E104(s32 arg0) {
    s32 temp_r3;
    register void *temp_r9 asm("r9");
    s32 var_r3;

    temp_r3 = fn_8000D3DC(lbl_802FFE84, arg0);
    if (temp_r3 != 0) {
        register void *temp_r11 asm("r11") = lbl_802FFE84;
        temp_r9 = ((CStruct *)temp_r11)->unk0x4;
        var_r3 = 0;
        lbl_802FFE88 = 1;
        temp_r9 = ((CStruct *)temp_r9)->unk0x10;
        if (temp_r9 != NULL) {
            var_r3 = ((CStruct *)temp_r9)->unk0x10;
        }
        return var_r3;
    }
    lbl_802FFE88 = temp_r3;
    return 0;
}
