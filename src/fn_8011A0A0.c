// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A0A0-0x8011A12C (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct E_11A0A0 {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    struct E_11A0A0 *unk0x10;
    struct E_11A0A0 *unk0x14;
} E_11A0A0;

extern E_11A0A0 lbl_80388C18[];
extern s32 lbl_80302C40;
extern s32 lbl_80302C4C;

void fn_8011A0A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    E_11A0A0 *e;
    s32 cnt;

    if (arg1 == 0) {
        return;
    }
    cnt = lbl_80302C4C;
    if (cnt == 0x80) {
        return;
    }
    lbl_80302C4C = cnt + 1;
    for (cnt = 0; cnt < 0x80; cnt++) {
        e = &lbl_80388C18[cnt];
        if ((e->unk0x8 ^ 1) & 1) {
            if (*(E_11A0A0 **)&lbl_80302C40 != 0) {
                (*(E_11A0A0 **)&lbl_80302C40)->unk0x14 = e;
            }
            e->unk0x10 = *(E_11A0A0 **)&lbl_80302C40;
            e->unk0x14 = 0;
            lbl_80302C40 = (s32)e;
            e->unk0x0 = arg1;
            e->unk0x4 = arg2;
            e->unk0x8 = 1;
            e->unk0xC = arg3;
            return;
        }
    }
}
