// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000C79C-0x8000C868 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char pad0x0[0x4];
    s32 unk0x4;
} Sub_8000C79C;
typedef struct {
    char pad0x0[0x10];
    s32 unk0x10;
    char pad0x14[0x4C];
    u8 unk0x60[0x40];
    u8 unk0xA0[0x20];
    Sub_8000C79C unk0xC0;
    char pad0xC8[0x4];
    u32 unk0xCC;
    char pad0xD0[0x4];
    s32 unk0xD4;
    char pad0xD8[0x4];
    s32 unk0xDC;
} Rec_8000C79C;
void PADControlMotor(s32, s32);
void fn_8000C79C(Rec_8000C79C *arg0) {
    Sub_8000C79C *temp_r31;
    s32 var_r9;
    s32 var_r9_2;
    s32 i;

    temp_r31 = &arg0->unk0xC0;
    var_r9 = 1;
    if (temp_r31->unk0x4 == 0) {
        var_r9 = 0;
    }
    if (var_r9 == 0) {
        if (arg0->unk0xDC == 2) {
            var_r9_2 = 1;
            if (!(arg0->unk0xCC & 2)) {
                var_r9_2 = 0;
            }
            if (var_r9_2 != 0) {
                for (i = 0; i < arg0->unk0xD4; i++) {
                    arg0->unk0xA0[i] = arg0->unk0x60[i];
                    arg0->unk0x60[i] = 0;
                }
                PADControlMotor(arg0->unk0x10, 0);
            }
        }
    } else {
        PADControlMotor(arg0->unk0x10, 0);
    }
    temp_r31->unk0x4 = temp_r31->unk0x4 + 1;
}
