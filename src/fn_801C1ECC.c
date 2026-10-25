// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C1ECC-0x801C1F6C (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
typedef struct {
    char pad0x0[0xC];
    s32 unk0xC;
    char pad0x10[0xC];
    s32 unk0x1C;
    char pad0x20[4];
    s32 unk0x24;
    char pad0x28[4];
    f32 unk0x2C;
} F801C1ECCObj;
extern f32 lbl_802AC8F8;
s32 fn_8010BB24(s32);
void fn_8010CC40(s32, s32, s32, s32, f32, f32, f32);
void fn_801C1ECC(F801C1ECCObj *arg0, void *arg1, f32 farg0) {
    volatile double _dummy;
    s32 var_r3;
    register f32 temp_f31 __asm__("fr31");
    register s32 temp_r30 __asm__("r30");

    temp_f31 = farg0;
    temp_r30 = (s32)arg1;
    if ((s32)arg0->unk0x1C == 4) {
        var_r3 = QB_TABLE_GRINDLAND;
        if ((s32)arg0->unk0x24 != 0) {
            var_r3 = QB_TABLE_SLIDELAND;
        }
    } else {
        var_r3 = QB_TABLE_LAND;
    }
    temp_f31 = temp_f31 * lbl_802AC8F8;
    fn_8010CC40(fn_8010BB24(var_r3), temp_r30, arg0->unk0xC + 0x58, 1,
        temp_f31 * arg0->unk0x2C, temp_f31, temp_f31);
}
