// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009FB20-0x8009FB7C (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void* lbl_80301A38;
void fn_800A205C(Unk_C7387A53 *, Unk_C8FEE62D *);
void fn_8009FB20(Unk_6A70655D *arg0, Unk_C7387A53 *arg1) {
    CStruct *node;

    if (arg0->unk0x110 == NULL) {
        arg0->unk0x110 = arg1;
    } else {
        node = *((void * *)&arg0->unk0x110);
        while (node->unk0x10 != NULL) {
            node = *((void * *)&node->unk0x10);
        }
        node->unk0x10 = arg1;
    }
    arg1->unk0xC = arg0;
    fn_800A205C(lbl_80301A38, (s32)arg1);
}
