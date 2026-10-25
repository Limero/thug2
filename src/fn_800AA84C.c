// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AA84C-0x800AA95C (272B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x00[0x1C];
    s32 unk0x1C;
} Unk_800AA84C_E;

void *fn_800AA84C(void *arg0, s32 arg1) {
    Unk_800AA84C_E *temp_r3;
    register Unk_800AA84C_E *var_r9 __asm__("r9");

    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x04);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x28);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x4C);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x70);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x190);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x16C);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x1B4);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x1D8);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x94);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0xB8);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0xDC);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x100);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x124);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x148);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    var_r9 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x1FC);
    if (var_r9->unk0x1C == arg1) {
        return var_r9;
    }
    temp_r3 = (Unk_800AA84C_E *)((u8 *)arg0 + 0x220);
    if (temp_r3->unk0x1C == arg1) {
        return (void *)((u8 *)arg0 + 0x220);
    }
    return NULL;
}
