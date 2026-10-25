// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007B738-0x8007B76C (52B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009A524(CStruct *, float);
void fn_8007B738(Unk_C7387A53 *arg0) {
    s32 temp_r0;

    temp_r0 = arg0->unk0x50;
    if (temp_r0 != 0) {
        fn_8009A524(temp_r0, *((float *)&arg0->unk0x24));
    }
}
