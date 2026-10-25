// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80126E28-0x80126E9C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80126A30(s32);
void fn_80126BF0(void *, void *, void *, void *);
void * fn_801291FC(void *arg0);
#include "structs.h"
s32 fn_80129068(s32, s32, s32);
void fn_80126E28(Unk_5AA7B5D7 *arg0, Unk_5AA7B5D7 *arg1) {
    s32 temp_r30;
    s32 temp_r31;
    u8 temp_r28;

    fn_80126A30(arg0);
    temp_r31 = arg1->unk0x4;
    temp_r28 = *((u8 *)arg1 + 2);
    fn_80129068(arg0, temp_r31, temp_r28);
    if (temp_r31 != 0) {
        temp_r30 = fn_801291FC(arg1);
        fn_80126BF0(fn_801291FC(arg0), temp_r30, temp_r31, temp_r28);
    }
}
