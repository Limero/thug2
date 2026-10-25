// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001BAEC-0x8001BC9C (432B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct ModeObj {
    s32 unk0x0;
    s32 unk0x4;
    u16 unk0x8;
    u16 unk0xA;
    u16 unk0xC;
    u16 unk0xE;
    u16 unk0x10;
    u16 unk0x12;
    s32 unk0x14;
} ModeObj;
extern char lbl_803001D8[];
extern char lbl_803613E8[];
extern s32 lbl_803613E4;
extern s8 lbl_80300124;
extern bool lbl_8037B790;
extern bool lbl_8037B794;
extern char lbl_80290F9C[];
extern s32 VIGetTvFormat(void);
void GX_AdjustForOverscan(s32, s32, s32, s32);
s32 OSVReport(s32, s32);

void fn_8001BAEC(void *arg0) {
    char sp8[0x80];
    s32 temp_r3;
    register s32 var_r0 __asm__("r0");
    register s32 hwA __asm__("r10");
    register ModeObj *temp_r11 __asm__("r11");
    register ModeObj *temp_r9 __asm__("r9");

    if (arg0 != NULL) {
        lbl_803613E4 = (s32)arg0;
        return;
    }
    lbl_80300124 = 4;
    lbl_803613E4 = (s32)lbl_803001D8;
    GX_AdjustForOverscan((s32)lbl_803001D8, (s32)lbl_803613E8, 0, 0);
    lbl_803613E4 = (s32)lbl_803613E8;
    temp_r3 = VIGetTvFormat();
    switch ((u32)temp_r3) {
    case 0:
        if (lbl_8037B790 != 0) {
            temp_r9 = (ModeObj *)lbl_803613E4;
            temp_r9->unk0x0 = 2;
            temp_r9->unk0x14 = (s32)temp_r3;
        }
        break;
    case 1:
    case 4:
    case 5:
        temp_r11 = (ModeObj *)lbl_803613E4;
        if (temp_r11->unk0x0 == 0) {
            var_r0 = lbl_8037B794;
            if (var_r0 == 0) {
                var_r0 = 4;
            } else {
                var_r0 = 0x14;
            }
        } else {
            var_r0 = lbl_8037B794;
            if (var_r0 != 0) {
                var_r0 = 0x15;
            } else {
                var_r0 = 5;
            }
        }
        temp_r11->unk0x0 = var_r0;
        var_r0 = lbl_8037B794;
        if (var_r0 != 0) {
            hwA = 0x1C0;
            temp_r9 = (ModeObj *)lbl_803613E4;
            temp_r9->unk0x8 = hwA;
            temp_r9->unk0x10 = hwA;
            temp_r9->unk0xC = 0x10;
        } else {
            hwA = 0x1F4;
            temp_r9 = (ModeObj *)lbl_803613E4;
            temp_r9->unk0x10 = hwA;
            temp_r9->unk0x8 = hwA;
            temp_r9->unk0xC = 0x25;
        }
        temp_r11 = (ModeObj *)lbl_803613E4;
        sprintf(sp8, lbl_80290F9C, temp_r11->unk0xA, temp_r11->unk0xC, temp_r11->unk0xE, temp_r11->unk0x10);
        OSVReport((s32)sp8, 0);
        break;
    case 2:
        temp_r9 = (ModeObj *)lbl_803613E4;
        temp_r9->unk0x0 = 8;
        break;
    }
}
