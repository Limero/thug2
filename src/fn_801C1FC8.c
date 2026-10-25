// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C1FC8-0x801C2064 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct {
    char pad0x0[0xC];
    s32 unk0xC;
    char pad0x10[0x14];
    s32 unk0x24;
    char pad0x28[4];
    f32 unk0x2C;
} F801C1FC8Obj;

extern f32 lbl_802AC8FC;
s32 fn_8010BB24(s32);
void fn_8010CC40(s32, s32, s32, s32, f32, f32, f32);
void fn_801C1FC8(F801C1FC8Obj *arg0, Unk_C8FEE62D *arg1, s32 arg2, f32 farg0) {
    volatile double _dummy;
    s32 var_r3;
    register f32 temp_f31 __asm__("fr31");
    register s32 temp_r30 __asm__("r30");
    temp_f31 = farg0;
    temp_r30 = (s32)arg1;
    if (arg2 == 4) {
        var_r3 = QB_TABLE_GRINDJUMP;
        if ((s32) arg0->unk0x24 != 0) {
            var_r3 = QB_TABLE_SLIDEJUMP;
        }
    } else {
        var_r3 = QB_TABLE_JUMP;
    }
    temp_f31 = temp_f31 * lbl_802AC8FC;
    fn_8010CC40(fn_8010BB24(var_r3), temp_r30, arg0->unk0xC + 0x58, 1,
        temp_f31 * arg0->unk0x2C, temp_f31, temp_f31);
}
