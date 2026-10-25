// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CD2F4-0x800CD39C (168B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_80299654;
f32 fn_800144C8(void);
f32 FRunFilter(f32, f32, f32);
void fn_800CD2F4(s32 arg0, Unk_DB0E2BAB *arg1) {
    volatile double _dummy;
    volatile double _dummy2;
    f32 temp_f30;
    f32 temp_f31;

    temp_f30 = *((f32 *)&arg1->unk0x18);
    temp_f31 = *((f32 *)&arg1->unk0x8);
    if (temp_f30 != temp_f31) {
        *((f32 *)&arg1->unk0x8) = FRunFilter(temp_f30, temp_f31, *((f32 *)&arg1->unk0x20) * (fn_800144C8() * lbl_80299654));
    }
    temp_f30 = *((f32 *)&arg1->unk0x1C);
    temp_f31 = *((f32 *)&arg1->unk0xC);
    if (temp_f30 != temp_f31) {
        *((f32 *)&arg1->unk0xC) = FRunFilter(temp_f30, temp_f31, *((f32 *)&arg1->unk0x24) * (fn_800144C8() * lbl_80299654));
    }
}
