// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F38C0-0x800F3930 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029B560[];
extern void *Mem_NewZero(s32);
void fn_800F38C0(s32 arg0, s32 arg1) {
    CStruct *temp_r30;
    Unk_C8FEE62D *temp_r3;

    temp_r3 = Mem_NewZero(0x18);
    temp_r3->unk0xC = temp_r3;
    temp_r3->unk0x10 = temp_r3;
    temp_r30 = arg0 + 0x38;
    temp_r3->unk0x14 = (s32)lbl_8029B560;
    temp_r3->unk0x4 = arg1;
    temp_r3->unk0x8 = 0;
    temp_r3->unk0x10 =  temp_r30->unk0x10;
    temp_r3->unk0xC = temp_r30;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r30) + 0x10) + 0xC) = temp_r3;
    temp_r30->unk0x10 = temp_r3;
}
