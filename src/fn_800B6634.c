// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B6634-0x800B6694 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: when the object's +0x240 active-flag is set, resolves its
// +0x210 target via fn_80061DE8 and dispatches a vtable call at +0x3C,
// passing the object base + the s16 offset at +0x38 and the caller's s32
// out-pointer. A generic object-notify / callback helper.
#include "types.h"
#include "structs.h"
s32 fn_80061DE8(CStruct *, void *);
void fn_800B6634(Unk_ADD6B5FC *arg0, s32 *arg1) {
    s32 sp8;
    s32 temp_r31;
    void *temp_r3;
    Unk_C6B642AC *temp_r9;

    temp_r31 = *arg1;
    if ((s32) arg0->unk0x240 != 0) {
        temp_r3 = fn_80061DE8(arg0->unk0x210, 0);
        sp8 = temp_r31;
        temp_r9 = ((Unk_C8FEE62D *)temp_r3)->unk0x14;
        ((s32 (*)(void *, void *))temp_r9->unk0x3C)(temp_r3 + temp_r9->unk0x38, &sp8);
    }
}
