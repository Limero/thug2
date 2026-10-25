// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801062AC-0x8010631C (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029C210[];
extern char lbl_80381098[];
extern void *Mem_NewZero(s32);
void fn_801062AC(s32 arg0) {
    s32 *head;
    Unk_C8FEE62D *temp_r3;
    s32 temp_r0;

    temp_r3 = Mem_NewZero(0x18);
    head = (s32 *)lbl_80381098;
    temp_r3->unk0xC = (s32)temp_r3;
    temp_r3->unk0x10 = (s32)temp_r3;
    temp_r3->unk0x14 = (s32)lbl_8029C210;
    temp_r3->unk0x4 = arg0;
    temp_r3->unk0x8 = 0;
    temp_r0 = head[4];
    temp_r3->unk0xC = (s32)head;
    temp_r3->unk0x10 = temp_r0;
    *(s32 *)(head[4] + 0xC) = (s32)temp_r3;
    head[4] = (s32)temp_r3;
}
