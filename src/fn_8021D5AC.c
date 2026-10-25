// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021D5AC-0x8021D5DC (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -ffixed-r9
#include "types.h"
#include "structs.h"
s32 fn_8021D5AC(void *arg0, CStruct *arg1) {
    register void *p __asm__("r9");
    CStruct *var_r11;

    p = *(s32 *)((char *)arg1 + 0x4);
    var_r11 = *(CStruct **)((char *)p + 0xC);
    if ((s32) var_r11->unk0x4 == -1) {
        var_r11 = NULL;
    }
    arg1->unk0x4 = var_r11;
    if (var_r11 != NULL) {
        return var_r11->unk0x4;
    }
    return 0;
}
