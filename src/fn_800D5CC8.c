// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D5CC8-0x800D5D88 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800D9DB0(s32);
s32 ContainsFlag(CStruct *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
extern f32 lbl_80299B6C;

typedef struct DCC {
    char pad0x0[0x20];
    s32 unk0x20;
    char pad0x24[0x18];
    f32 unk0x3C;
    f32 unk0x40;
} DCC;

s32 fn_800D5CC8(DCC *arg0, CStruct *arg1) {
    f32 temp_f13;
    s32 var_r3;

    GetFloat(arg1, QB_DISTABOVE, &arg0->unk0x3C, 0);
    GetFloat(arg1, QB_DISTBELOW, &arg0->unk0x40, 0);
    if (ContainsFlag(arg1, QB_OFF) != 0) {
        arg0->unk0x20 = (s32) (arg0->unk0x20 & QB_UNKNOWN_0xFFFFFFFB);
        goto block_5;
    }
    temp_f13 = lbl_80299B6C;
    arg0->unk0x20 = (s32) (arg0->unk0x20 | 4);
    if ((arg0->unk0x3C != temp_f13) || (var_r3 = 0, ((arg0->unk0x40 == temp_f13) == 0))) {
        fn_800D9DB0((s32) arg0);
block_5:
        var_r3 = 1;
    }
    return var_r3;
}
