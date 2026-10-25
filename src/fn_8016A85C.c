// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016A85C-0x8016A8D0 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_803003C0[];
extern char lbl_803003C8[];
extern s32 lbl_803003D0;
void *fn_80011F94(Unk_78674569 *, s32, s32, s32);
void fn_8016A85C(s32 arg0, s32 arg1) {
    s32 temp_r29 = lbl_803003D0 * 4;
    s32 *dst = (s32 *)((char *)lbl_803003C0 + temp_r29);

    *dst = (s32)fn_80011F94(Mem_Alloc2(0x5C), 0x78, arg0, arg1);
    *(s32 *)((char *)lbl_803003C8 + lbl_803003D0 * 4) = 1;
}
