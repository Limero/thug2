// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80096758-0x800967B8 (96B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_803018A8;
void fn_80098C70(CStruct *, s32 *);
s32 fn_80098C1C(s32, s32, s32);
void fn_80096758(s32 arg0) {
    s32 spC;
    s32 sp8;
    s32 temp_r3;

    sp8 = arg0;
    temp_r3 = fn_80098C1C(lbl_803018A8, &sp8, 1);
    if (temp_r3 != 0) {
        spC = arg0;
        fn_80098C70(lbl_803018A8, &spC);
        Mem_Free(temp_r3);
    }
}
