// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024079C-0x80240810 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_803060A8;
extern char lbl_80306098[];
extern char lbl_803060A0[];
extern s32 fn_80011F94(Unk_78674569 *, s32, s32, s32);
void fn_8024079C(s32 arg0, s32 arg1) {
    s32 off = lbl_803060A8 * 4;
    s32 *dst = (s32 *)lbl_80306098;
    *(s32 *)((char *)(off + (s32)dst)) = fn_80011F94(Mem_Alloc2(0x5C), 0x10, arg0, arg1);
    ((s32 *)lbl_803060A0)[lbl_803060A8] = 1;
}
