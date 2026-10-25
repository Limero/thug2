// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016AA2C-0x8016AAA0 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80301A64[];
extern char lbl_80301A6C[];
extern s32 lbl_80301A74;
void *fn_80011F94(Unk_78674569 *, s32, s32, s32);
void fn_8016AA2C(s32 arg0, s32 arg1) {
    s32 temp_r29 = lbl_80301A74 * 4;
    s32 *dst = (s32 *)((char *)lbl_80301A64 + temp_r29);

    *dst = (s32)fn_80011F94(Mem_Alloc2(0x5C), 0x1C, arg0, arg1);
    *(s32 *)((char *)lbl_80301A6C + lbl_80301A74 * 4) = 1;
}
