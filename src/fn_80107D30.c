// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80107D30-0x80107D7C (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80107D30(Unk_2DB370CA *arg0) {
    s32 var_r3;
    Unk_C7387A53 *temp_r3;
    Unk_89391A04 *temp_r9;

    if (arg0->unk0x74 == 0) {
        var_r3 = 1;
    } else {
        temp_r3 = arg0->unk0x5C;
        temp_r9 = *((void * *)&temp_r3->unk0xC);
        var_r3 = ((s32 (*)(void *))*((void * *)&temp_r9->unk0x14))(
            (char *)temp_r3 + temp_r9->unk0x10);
    }
    return var_r3;
}
