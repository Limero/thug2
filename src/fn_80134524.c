// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80134524-0x80134584 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80134524(CScript *arg0, Unk_C8FEE62D *arg1) {
    CStruct *temp_r9;
    Unk_C8FEE62D *temp_r9_2;

    temp_r9 = arg1->unk0x14;
    if (temp_r9 != NULL) {
        temp_r9->unk0x10 =  arg1->unk0x10;
    }
    temp_r9_2 = arg1->unk0x10;
    if (temp_r9_2 != NULL) {
        temp_r9_2->unk0x14 =  arg1->unk0x14;
    }
    if (arg1 ==  arg0->unk0x1C) {
        arg0->unk0x1C =  arg1->unk0x10;
    }
    if (arg1 ==  arg0->unk0x20) {
        arg0->unk0x20 =  arg1->unk0x14;
    }
    arg1->unk0x10 = NULL;
    arg1->unk0x14 = NULL;
}
