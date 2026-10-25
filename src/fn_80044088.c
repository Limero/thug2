// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80044088-0x80044110 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char pad0[0xC];
    s32 unk0xC;
    char pad1[0x16C];
    f32 unk0x17C;
    char pad2[0x10];
    s32 unk0x190;
    char pad3[0x14];
    s32 unk0x1A8;
    char pad4[0x8];
    f32 unk0x1B4;
} Obj44088;
extern char lbl_80292508[];
s32 fn_80053790(s32);
void fn_800586CC(s32, char *, s32 *, f32 *);
void fn_80044088(Obj44088 *arg0, s32 arg1) {
    f32 spC;
    s32 sp8;
    arg0->unk0x190 = arg1;
    fn_800586CC(fn_80053790(arg1), lbl_80292508, &sp8, &spC);
    arg0->unk0xC |= 0x1000;
    arg0->unk0x1A8 = (s32)arg0->unk0x17C / (s32)(spC * arg0->unk0x1B4);
}
