// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009DFA0-0x8009DFC0 (32B). Byte-identical.
#include "types.h"
#include "structs.h"
// CObject_AddRefLink @ 0x8009DFA0
void CObject_AddRefLink(CStruct *arg0, Unk_9994C3F5 *arg1) {
    CStruct *temp_r9;

    arg1->unk0x8 = (void *) arg0->unk0x4;
    temp_r9 = arg0->unk0x4;
    if (temp_r9 != NULL) {
        temp_r9->unk0x4 = arg1;
    }
    arg0->unk0x4 = arg1;
}
