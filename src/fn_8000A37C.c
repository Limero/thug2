// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000A37C-0x8000A3DC (96B). Byte-identical.
#include "types.h"
#include "structs.h"
void Mem_NewZero(s32);
void fn_8000A37C(Unk_C7387A53 *arg0) {
    Unk_C7387A53 *temp_r10;
    CStruct *temp_r11;
    Unk_C7387A53 *temp_r3;

    Mem_NewZero(0x2C);
    temp_r3 = fn_8000A13C();
    arg0->unk0x3C = temp_r3;
    temp_r10 = (char *)arg0 + 0xC;
    temp_r11 = temp_r3->unk0x28;
    temp_r11->unk0x10 = temp_r10;
    temp_r11->unk0xC =  temp_r10->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r10) + 0xC) + 0x10) = temp_r11;
    temp_r10->unk0xC = temp_r11;
    arg0->unk0x44 = 1;
}
