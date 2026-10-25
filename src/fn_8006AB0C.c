// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006AB0C-0x8006AC08 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"

extern char lbl_80294B08[];
extern f32 lbl_80294ACC[1];
extern f32 lbl_80294AD0[1];

// Sub-view at +0x78/+0x98/+0xB0: there fields 4/8/C are f32 (the
// sub-objects' own floats at 0x7C/0x80/0x84 ...), so the main struct's
// void*/s32 fields at 0x4..0xC cannot be reused for the sub-pointers.
typedef struct Wip6AB0CSub {
    f32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
} Wip6AB0CSub;

typedef struct Wip6AB0C {
    s32 unk0x0;
    void *unk0x4;
    s32 unk0x8;
    void *unk0xC;
    void *unk0x10;
    char *unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
    s32 unk0x24;
    f32 unk0x28;
    f32 unk0x2C;
    f32 unk0x30;
    f32 unk0x34;
    f32 unk0x38;
    f32 unk0x3C;
    f32 unk0x40;
    f32 unk0x44;
    f32 unk0x48;
    f32 unk0x4C;
    f32 unk0x50;
    f32 unk0x54;
    f32 unk0x58;
    f32 unk0x5C;
    f32 unk0x60;
    f32 unk0x64;
    f32 unk0x68;
    f32 unk0x6C;
    f32 unk0x70;
    s32 unk0x74;
    f32 unk0x78;
    f32 unk0x7C;
    f32 unk0x80;
    f32 unk0x84;
    s32 unk0x88;
    s32 unk0x8C;
    s32 unk0x90;
    s32 unk0x94;
    f32 unk0x98;
    f32 unk0x9C;
    f32 unk0xA0;
    f32 unk0xA4;
    f32 unk0xA8;
    s32 unk0xAC;
    f32 unk0xB0;
    f32 unk0xB4;
    f32 unk0xB8;
    f32 unk0xBC;
    f32 unk0xC0;
    f32 unk0xC4;
    f32 unk0xC8;
    s32 unk0xCC;
} Wip6AB0C;

Wip6AB0C *fn_8006AB0C(Wip6AB0C *arg0) {
    f32 temp_f0;
    f32 temp_f13;
    s32 var_ctr;
    register Wip6AB0CSub *temp_r10 __asm__("r10");
    register Wip6AB0CSub *temp_r11 __asm__("r11");
    register Wip6AB0CSub *temp_r9 __asm__("r9");
    register char *a1 __asm__("r8");   // page anchor for lbl_80294ACC
    register char *a2 __asm__("r7");   // page anchor for lbl_80294AD0
    register Wip6AB0C *p __asm__("r6");

    p = arg0;

    p->unk0x8 = 0;
    var_ctr = 4;
    p->unk0x14 = lbl_80294B08;
    p->unk0x4 = p;
    p->unk0xC = p;
    p->unk0x10 = p;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    p->unk0x18 = 0;
    p->unk0x1C = 0;
    temp_r9 = (Wip6AB0CSub *)((char *)p + 0x78);
    p->unk0x20 = 0;
    temp_r11 = (Wip6AB0CSub *)((char *)p + 0x98);
    p->unk0x74 = 0;
    temp_r10 = (Wip6AB0CSub *)((char *)p + 0xB0);
    a1 = (char *)lbl_80294ACC - 0x4ACC;
    temp_f13 = lbl_80294ACC[0];
    p->unk0x28 = temp_f13;
    a2 = (char *)lbl_80294AD0 - 0x4AD0;
    temp_f0 = lbl_80294AD0[0];
    p->unk0x3C = temp_f13;
    p->unk0x2C = temp_f0;
    p->unk0x30 = temp_f0;
    p->unk0x34 = temp_f0;
    p->unk0x38 = temp_f0;
    p->unk0x40 = temp_f0;
    p->unk0x44 = temp_f0;
    p->unk0x48 = temp_f0;
    p->unk0x4C = temp_f0;
    p->unk0x50 = temp_f13;
    p->unk0x54 = temp_f0;
    p->unk0x58 = temp_f0;
    p->unk0x5C = temp_f0;
    p->unk0x60 = temp_f0;
    p->unk0x64 = temp_f13;
    p->unk0x68 = temp_f0;
    p->unk0x6C = temp_f0;
    p->unk0x70 = temp_f0;
    p->unk0x78 = temp_f0;
    temp_r9->unk0xC = temp_f13;
    temp_r9->unk0x4 = temp_f0;
    temp_r9->unk0x8 = temp_f0;
    p->unk0x98 = temp_f0;
    temp_r11->unk0xC = temp_f13;
    temp_r11->unk0x4 = temp_f0;
    temp_r11->unk0x8 = temp_f0;
    p->unk0xA8 = temp_f0;
    p->unk0xAC = 0;
    p->unk0xB0 = temp_f0;
    temp_r10->unk0xC = temp_f13;
    temp_r10->unk0x4 = temp_f0;
    temp_r10->unk0x8 = temp_f0;
    p->unk0xC8 = temp_f0;
    p->unk0xCC = 0;
    p->unk0xC0 = temp_f0;
    p->unk0xC4 = temp_f0;
    return p;
}
