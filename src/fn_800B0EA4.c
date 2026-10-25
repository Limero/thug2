// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B0EA4-0x800B0EEC (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80301B0C[];
s32 Mem_NewZero(s32);
void fn_800B0EA4(void) {
    void *temp_r31;
    CStruct *temp_r3;

    temp_r31 = *(void * *)&lbl_80301B0C;
    if (temp_r31 == NULL) {
        temp_r3 = Mem_NewZero(0x10);
        temp_r3->unk0xC = temp_r31;
        *(void * *)&lbl_80301B0C = temp_r3;
        temp_r3->unk0x4 = temp_r31;
    }
}
