// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EDE30-0x800EDEB4 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct {
    u8  _p0[4];
    s32 unk0x4;
    u8  _p8[0x10];
    char *unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
    s32 unk0x24;
    s32 unk0x28;
    u8  _p2C[0x70];
    f32 unk0x9C;
    s32 unk0xA0;
    u8  _pA4[4];
    s32 unk0xA8;
    s32 unk0xAC;
    f32 unk0xB0;
    s32 unk0xB4;
    s32 unk0xB8;
    s32 unk0xBC;
} T8029;

extern f32 lbl_8029AE94;
extern char lbl_8029AED8[];

void fn_8009F53C(void);

void *fn_800EDE30(T8029 *arg0) {
    f32 f0;

    fn_8009F53C();
    f0 = lbl_8029AE94;
    arg0->unk0x18 = lbl_8029AED8;
    arg0->unk0x4 = QB_UNKNOWN_0x28C97F3C;
    arg0->unk0xB8 = 0;
    arg0->unk0xBC = 0;
    arg0->unk0x1C = 0;
    arg0->unk0x20 = 0;
    arg0->unk0x9C = f0;
    arg0->unk0xB0 = f0;
    arg0->unk0xA0 = 0;
    arg0->unk0xA8 = 0;
    arg0->unk0xAC = 0;
    arg0->unk0xB4 = 0;
    arg0->unk0x24 = 0;
    arg0->unk0x28 = 0;
    return arg0;
}
