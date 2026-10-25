// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001F91C-0x8001FA54 (312B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80300278[];
extern char lbl_8030028C[];
void fn_8001F91C(Unk_DB0E2BAB *arg0, u32 arg1, s32 arg2) {
    s32 var_r4;
    u16 var_r3;

    if (arg1 > 0x3FU) {
        var_r4 = 0xC;
        var_r3 = (arg1 * 4) + 0x400;
    } else {
        var_r3 = (arg1 * 4) & 0xFFFC;
        var_r4 = 0xC;
        if (arg2 == 1) {
            var_r4 = 8;
        }
    }
    ((void (*)(u16, s32))*(void (**)(u16, s32))lbl_8030028C)(var_r3, var_r4);
    ((void (*)(f32))*(void (**)(f32))lbl_80300278)(*((f32 *)&arg0->unk0x0));
    ((void (*)(f32))*(void (**)(f32))lbl_80300278)(*((f32 *)&arg0->unk0x4));
    ((void (*)(f32))*(void (**)(f32))lbl_80300278)(*((f32 *)&arg0->unk0x8));
    ((void (*)(f32))*(void (**)(f32))lbl_80300278)(*((f32 *)&arg0->unk0xC));
    ((void (*)(f32))*(void (**)(f32))lbl_80300278)(*((f32 *)&arg0->unk0x10));
    ((void (*)(f32))*(void (**)(f32))lbl_80300278)(*((f32 *)&arg0->unk0x14));
    ((void (*)(f32))*(void (**)(f32))lbl_80300278)(*((f32 *)&arg0->unk0x18));
    ((void (*)(f32))*(void (**)(f32))lbl_80300278)(*((f32 *)&arg0->unk0x1C));
    if (arg2 == 0) {
        ((void (*)(f32))*(void (**)(f32))lbl_80300278)(*((f32 *)&arg0->unk0x20));
        ((void (*)(f32))*(void (**)(f32))lbl_80300278)(*((f32 *)&arg0->unk0x24));
        ((void (*)(f32))*(void (**)(f32))lbl_80300278)(*((f32 *)&arg0->unk0x28));
        ((void (*)(f32))*(void (**)(f32))lbl_80300278)(*((f32 *)&arg0->unk0x2C));
    }
}