// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005A060-0x8005A0A8 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char pad0[0x18];
    void *unk0x18;
    s32 unk0x1C;
} O8005A060;
typedef struct {
    char pad0[0x28];
    s32 unk0x28;
} R8005A060;
R8005A060 **fn_80059BB8(void *arg0, s32 *arg1);
void fn_8005A060(O8005A060 *arg0, s32 *arg1) {
    s32 temp_r31;
    R8005A060 **temp_r3;

    temp_r31 = *arg1;
    arg0->unk0x1C = temp_r31;
    temp_r3 = fn_80059BB8(arg0->unk0x18, arg1);
    if (temp_r3 != NULL) {
        (*temp_r3)->unk0x28 = temp_r31;
    }
}
