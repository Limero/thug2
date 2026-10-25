// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009DFC0-0x8009E004 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
// CObject_RemoveRefLink @ 0x8009DFC0
void CObject_RemoveRefLink(CStruct *arg0, CStruct *arg1) {
    Unk_9994C3F5 *temp_r9;
    CStruct *temp_r9_2;

    temp_r9 = arg1->unk0x4;
    if (temp_r9 != NULL) {
        temp_r9->unk0x8 =  arg1->unk0x8;
    } else {
        arg0->unk0x4 =  arg1->unk0x8;
    }
    temp_r9_2 = arg1->unk0x8;
    if (temp_r9_2 != NULL) {
        temp_r9_2->unk0x4 =  arg1->unk0x4;
    }
    arg1->unk0x4 = NULL;
    arg1->unk0x8 = NULL;
}
