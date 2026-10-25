// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007DEBC-0x8007DF14 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void fn_800577A0(s32);
extern s32 fn_800577B4(s32, s32);
extern s32 fn_80057CA0(void);
extern void fn_8007EC7C(s32);

s32 fn_8007DEBC(Unk_FFAD6788 *arg0) {
    s32 temp_r3;
    s32 temp_r3_2;

    fn_800577A0(arg0->unk0xD0);
    temp_r3 = fn_800577B4(arg0->unk0xD0, 0);
    while (temp_r3 != 0) {
        temp_r3_2 = fn_80057CA0();
        if (temp_r3_2 != 0) {
            fn_8007EC7C(temp_r3_2);
        }
        temp_r3 = fn_800577B4(arg0->unk0xD0, 0);
    }
    return temp_r3;
}
