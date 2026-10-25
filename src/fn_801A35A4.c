// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A35A4-0x801A35F0 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_801A26E0(s32, s32);
typedef struct Vtbl_A35A4 {
    char pad0x0[0x68];
    s16 unk0x68;
    s32 (*unk0x6C)(void *, s32);
} Vtbl_A35A4;
void fn_801A35A4(Unk_31DE137E *arg0, s32 arg1) {
    void *temp_r3;
    Vtbl_A35A4 *temp_r9;

    temp_r3 = (void *)fn_801A26E0((s32)arg0, 0);
    temp_r9 = (Vtbl_A35A4 *)((Unk_C8FEE62D *)temp_r3)->unk0x14;
    temp_r9->unk0x6C((char *)temp_r3 + temp_r9->unk0x68, arg1);
}
