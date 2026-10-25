// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023D184-0x8023D22C (168B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80238C40(Unk_673C6403 *, Unk_ECD1B899 *, void *);
void fn_802392F0(Unk_673C6403 *, void *);
s32 fn_802361E8(Unk_7BAE36EB *, void *, s32);
void fn_802394F8(Unk_673C6403 *, s32, Unk_C7387A53 *);
s32 fn_8023D184(Unk_E3D41763 *arg0) {
    s32 sp8;
    s32 var_r3;
    void *temp_r30;
    s32 temp_r3;

    if ((s32) arg0->unk0xC0 == 1) {
        fn_802392F0(*((void * *)&arg0->unk0x0), (char *)arg0 + 0x78);
        arg0->unk0xC0 = 0;
        fn_802361E8(*((void * *)&arg0->unk0x0), (char *)arg0 + 4, 0);
        goto block_4;
    }
    temp_r30 = (char *)arg0 + 4;
    temp_r3 = fn_80238C40(*((void * *)&arg0->unk0x0), temp_r30, &sp8);
    var_r3 = 0;
    if (temp_r3 != 0) {
        fn_802392F0(*((void * *)&arg0->unk0x0), temp_r3);
        fn_802361E8(*((void * *)&arg0->unk0x0), temp_r30, 0);
        fn_802394F8(*((void * *)&arg0->unk0x0), 1, NULL);
block_4:
        var_r3 = 1;
    }
    return var_r3;
}
