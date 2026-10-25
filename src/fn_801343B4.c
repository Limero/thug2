// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801343B4-0x8013442C (120B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029EFF8[];
extern void *lbl_802FFE98;
void fn_8009C838(Unk_C8FEE62D *);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void *fn_801349B4(Unk_C8FEE62D *, s32);
void fn_8000F320(Unk_F12C5E01 *);
void *fn_801343B4(Unk_DB0E2BAB *arg0) {
    Unk_C7387A53 *temp_r3;
    fn_8009C838(arg0);
    temp_r3 = lbl_802FFE98;
    arg0->unk0x14 = (s32)lbl_8029EFF8;
    fn_8000F2F8(temp_r3, temp_r3->unk0x12C);
    arg0->unk0x18 = (s32)fn_801349B4((void *)Mem_Alloc2(0x18), 8);
    fn_8000F320(lbl_802FFE98);
    arg0->unk0x1C = 0;
    arg0->unk0x20 = 0;
    arg0->unk0x24 = 0;
    return arg0;
}
