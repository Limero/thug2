// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80011E34-0x80011EA4 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80010808(s32, s32, s32, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
extern char lbl_80290628[];
typedef struct Unk_11E34 {
    s32 unk0x0;
    char pad0x4[0x4];
    u32 sz:24;
    u32 lo:8;
} Unk_11E34;
void *fn_80011E34(Unk_C7387A53 *arg0, s32 arg1, s32 arg2) {
    s32 temp_r29;
    s32 temp_r30;
    Unk_11E34 *temp_r3;

    temp_r29 = *(s32 *)&lbl_80290628;
    temp_r30 = (arg1 + 0x1F) & QB_UNKNOWN_0xFFFFFFE0;
    temp_r3 = (Unk_11E34 *)fn_80010808(arg0->unk0x34, arg0, temp_r30 + temp_r29, arg2);
    if (temp_r3 != NULL) {
        temp_r3->unk0x0 = (s32)arg0;
        temp_r3->sz = (u32)temp_r30;
        temp_r3->lo = 0;
    }
    return (char *)temp_r3 + temp_r29;
}
