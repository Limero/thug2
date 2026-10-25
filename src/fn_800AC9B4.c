// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AC9B4-0x800ACA28 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8005F984(s32, s32);
void fn_800AC93C(s32);
void fn_800AC9B4(Unk_A03F5E5B *arg0, s32 arg1) {
    s32 temp_r3;
    CStruct *temp_r31;
    register s32 temp_r9 __asm__("r9");
    register s32 temp_r28 __asm__("r28");

    temp_r9 = arg0->unk0x2C58 * 0xC;
    temp_r28 = temp_r9 + 0x2058;
    fn_800AC93C(arg0);
    temp_r31 = (char *)arg0 + temp_r28;
    temp_r3 = fn_8005F984(arg1, 1);
    temp_r31->unk0x4 = 0;
    if ((s32) temp_r31->unk0x8 == 0) {
        temp_r31->unk0x8 = temp_r3;
    }
    *(s32 *)((char *)arg0 + temp_r28) = arg1;
    arg0->unk0x2C58 = (s32) (arg0->unk0x2C58 + 1);
}
