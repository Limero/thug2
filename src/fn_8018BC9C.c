// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018BC9C-0x8018BD34 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 Mem_Alloc2(s32 arg0);
extern s32 fn_8018B6B8(CStruct *arg0);
void fn_8018BC9C(Unk_C7387A53 *arg0, s32 arg1) {
    CStruct *head;
    CStruct *node;
    s32 found;
    CStruct *temp_r3;

    head = (CStruct *)arg0->unk0x2C;
    if (head->unk0x0 == 0) {
        head->unk0x0 = arg1;
        return;
    }
    found = 0;
    for (node = head; node != NULL; node = (CStruct *)node->unk0x4) {
        if (node->unk0x0 == 0) {
            break;
        }
        if (node->unk0x0 == arg1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        temp_r3 = (s32 *)fn_8018B6B8(Mem_Alloc2(0xC));
        temp_r3->unk0x0 = arg1;
        temp_r3->unk0x4 = arg0->unk0x2C;
        arg0->unk0x2C = (s32)temp_r3;
    }
}
