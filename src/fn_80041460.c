// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80041460-0x800414B0 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void *fn_80041460(CStruct *arg0, Unk_C7387A53 *arg1) {
    s32 temp_r3;

    arg0->unk0x4 = 0;
    arg0->unk0x8 = 0;
    temp_r3 = arg1->unk0x58;
    arg0->unk0x0 = temp_r3;
    if (temp_r3 != 0) {
        CObject_AddRefLink((void *)temp_r3, arg0);
    }
    return arg0;
}
