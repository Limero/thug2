// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016A8D0-0x8016A944 (116B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_803003D4[];
extern char lbl_803003DC[];
extern s32 lbl_803003E4;
void *fn_80011F94(Unk_78674569 *, s32, s32, s32);
void fn_8016A8D0(s32 arg0, s32 arg1) {
    s32 temp_r29 = lbl_803003E4 * 4;
    s32 *dst = (s32 *)((char *)lbl_803003D4 + temp_r29);

    *dst = (s32)fn_80011F94(Mem_Alloc2(0x5C), 0x2C, arg0, arg1);
    *(s32 *)((char *)lbl_803003DC + lbl_803003E4 * 4) = 1;
}
