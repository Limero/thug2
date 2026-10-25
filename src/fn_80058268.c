// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058268-0x800582B8 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005F408(Unk_9994C3F5 *, void *);
bool fn_80058268(Unk_C8FEE62D *arg0, Unk_9994C3F5 *arg1) {
    s32 temp_r0;

    if ( arg0->unk0x14 == NULL) {
        temp_r0 = arg0->unk0x10;
        arg0->unk0x14 = arg1;
        if (temp_r0 != 0) {
            fn_8005F408(temp_r0, arg1->unk0x8);
        }
        return true;
    }
    return false;
}
