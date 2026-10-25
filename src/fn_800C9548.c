// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C9548-0x800C9598 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern s32 lbl_80301B48;
extern s32 fn_800F2AD8(s32, s32, s32);
extern void *fn_800363BC(Unk_DB0E2BAB *, Unk_09D16053 *);
void fn_800C9548(Unk_31DE137E *arg0, s32 arg1) {
    s32 temp_r29;

    temp_r29 = fn_800F2AD8(lbl_80301B48, arg1, 0);
    arg0->unk0x1C = (s32) fn_800363BC((void *) Mem_Alloc2(0x1C), (void *) temp_r29);
}
