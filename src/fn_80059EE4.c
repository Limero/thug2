// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80059EE4-0x80059F2C (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 lbl_8030089C;
extern char lbl_80364CC8[];

typedef struct PoolRec {
    char pad0x00[0x10];
    f32 unk0x10;
    f32 unk0x14;
    s32 unk0x18;
    u8 unk0x1C;
    u8 unk0x1D;
    u8 unk0x1E;
    char pad0x1F;
    void *unk0x20;
} PoolRec;

void *fn_80059EE4(s32 arg0) {
    PoolRec *var_r3;
    s32 var_r11 = 0;
    if (var_r11 < lbl_8030089C) {
        var_r3 = (PoolRec *)lbl_80364CC8;
        do {
            if (var_r3->unk0x18 == arg0) {
                return var_r3;
            }
            var_r11 += 1;
            var_r3 = (PoolRec *)((char *)var_r3 + 0x28);
        } while (var_r11 < lbl_8030089C);
    }
    return 0;
}
