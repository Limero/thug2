// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FC678-0x800FC6E8 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *Mem_NewZero(s32);
extern char lbl_8029C210[];
void fn_800FC678(CStruct *arg0, s32 arg1) {
    Unk_C8FEE62D *temp_r3;
    CStruct *temp_r11;
    void *temp_r0;
    temp_r3 = Mem_NewZero(0x18);
    temp_r3->unk0xC = (s32)temp_r3;
    temp_r3->unk0x10 = (s32)temp_r3;
    temp_r3->unk0x14 = (s32)lbl_8029C210;
    temp_r3->unk0x4 = arg1;
    temp_r3->unk0x8 = 0;
    temp_r11 = arg0->unk0x10;
    temp_r0 = temp_r11->unk0x10;
    temp_r3->unk0xC = (s32)temp_r11;
    temp_r3->unk0x10 = (s32)temp_r0;
    ((Unk_C7387A53 *)temp_r11->unk0x10)->unk0xC = (s32)temp_r3;
    temp_r11->unk0x10 = (s32)temp_r3;
}