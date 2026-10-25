// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010CAC-0x80010D04 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
void Mem_NewZero(s32);
void fn_80010CAC(Unk_C7387A53 *arg0) {
    s32 temp_r3;
    Unk_C7387A53 *temp_r10;
    CStruct *temp_r11;

    Mem_NewZero(0x20);
    temp_r3 = fn_80010A38();
    temp_r10 = (char *)arg0 + 0x48;
    temp_r11 = temp_r3 + 4;
    temp_r11->unk0x10 = temp_r10;
    temp_r11->unk0xC =  temp_r10->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r10) + 0xC) + 0x10) = temp_r11;
    temp_r10->unk0xC = temp_r11;
    arg0->unk0x40 = temp_r3;
}
