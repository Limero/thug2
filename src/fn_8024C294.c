// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024C294-0x8024C3AC (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
#include "types.h"
#include "structs.h"
extern s32 lbl_803CA240[];
extern s32 lbl_803CA320;
extern s32 lbl_803CA330;
extern s32 lbl_803CA334;
extern s32 lbl_803CA338;
void memset(void *, s32, s32);
void fn_8024C294(void) {
    char *walk;
    Unk_5B449B03 *ent;
    s32 base;
    s32 w;
    s32 h;
    s32 stride;
    s32 wh;
    s32 p24;
    s32 p28;
    u32 i;
    if (lbl_803CA330 != 0) {
        i = 0;
        lbl_803CA338 = ((s32 (*)(s32)) *(s32 *)&lbl_803CA320)(lbl_803CA330);
        base = lbl_803CA338;
        if ((u32)i < (u32)lbl_803CA334) {
            walk = (char *)lbl_803CA240;
            do {
                ent = *(char **)walk;
            w = ent->unk0x4;
            h = ent->unk0x6;
            stride = (w * 8) & 0x7FFF0;
            wh = w * h;
            ent->unk0x20 = base;
            *((s32 *)&ent->unk0x8) = base + (w << 5) + 0x80;
            p24 = base + wh + 0x60;
            p28 = p24 + (wh >> 2) + 0x60;
            ent->unk0xC = p24 + stride + 0x40;
            ent->unk0x24 = p24;
            ent->unk0x10 = p28 + stride + 0x40;
            ent->unk0x28 = p28;
            memset(base, 0x10, wh);
            memset(ent->unk0x24, 0x80,
                   (ent->unk0x4 * ent->unk0x6) >> 2);
            memset(ent->unk0x28, 0x80,
                   (ent->unk0x4 * ent->unk0x6) >> 2);
            base = base + ((Unk_4C649A8C *)walk)->unk0x4;
            walk = walk + 8;
            i = i + 1;
            } while ((u32)i < (u32)lbl_803CA334);
        }
    }
}
