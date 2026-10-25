// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002DEAC-0x8002DF10 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_802918BC;
typedef struct {
    char pad0x0[0x18];
    f32 unk0x18;
    f32 unk0x1C;
    f32 unk0x20;
    f32 unk0x24;
    s32 unk0x28;
    s32 unk0x2C;
    s32 unk0x30;
    s32 unk0x34;
} F82DEAC;
void fn_8002DEAC(F82DEAC *arg0, s32 arg1, s32 arg2, f32 f1, f32 f2, f32 f3, f32 f4) {
    if (f1 < f2) {
        arg0->unk0x18 = f1;
    } else {
        arg0->unk0x18 = f2;
    }
    arg0->unk0x1C = f1;
    if (f1 < f2) {
        arg0->unk0x20 = f2;
    } else {
        arg0->unk0x20 = f1;
    }
    arg0->unk0x24 = f4 / lbl_802918BC;
    arg0->unk0x28 = (f1 < f2) ? 0 : -1;
    arg0->unk0x2C = arg2;
    arg0->unk0x30 = 0;
    arg0->unk0x34 = arg1;
}
