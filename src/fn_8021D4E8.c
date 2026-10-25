// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021D4E8-0x8021D578 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Os
#include "types.h"
#include "structs.h"
s32 fn_8021D4E8(s32, CStruct *, s32);
s32 fn_8022989C(CScript *);
s32 fn_8021D4E8(s32 arg0, CStruct *arg1, s32 arg2) {
    CStruct *r9;
    register CStruct *r11 __asm__("r11");
    s32 var_r31;

    r9 = (CStruct *)arg1->unk0x4;
    r11 = (CStruct *)r9->unk0xC;
    if (r11->unk0x4 == -1) {
        r11 = NULL;
    }
    arg1->unk0x4 = (s32)r11;
    var_r31 = (r11 != NULL) ? r11->unk0x4 : 0;
    if ((arg2 == 0) && (var_r31 != 0)
        && (fn_8022989C((CScript *)var_r31) != 0)) {
        var_r31 = fn_8021D4E8(arg0, arg1, 0);
    }
    return var_r31;
}
