// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80240888-0x802408FC (116B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_803060D4;
extern char lbl_803060C4[];
extern char lbl_803060CC[];
extern s32 fn_80011F94(Unk_78674569 *, s32, s32, s32);
void fn_80240888(s32 arg0, s32 arg1) {
    s32 off = lbl_803060D4 * 4;
    s32 *dst = (s32 *)lbl_803060C4;
    *(s32 *)((char *)(off + (s32)dst)) = fn_80011F94(Mem_Alloc2(0x5C), 0x18, arg0, arg1);
    ((s32 *)lbl_803060CC)[lbl_803060D4] = 1;
}
