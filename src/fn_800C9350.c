// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C9350-0x800C94C0 (368B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void *fn_800C9350(Unk_EA529D06 *arg0, Unk_EA529D06 *arg1) {
    Unk_64253088 *temp_r10;
    Unk_64253088 *temp_r11;
    void *temp_r29;
    s32 temp_r3;
    __ps_t t0;

    t0 = arg1->unk0x0;
    temp_r10 = (char *)arg1 + 0x28;
    temp_r11 = (char *)arg0 + 0x28;
    temp_r29 = (char *)arg0 + 0xA8;
    arg0->unk0x0 = t0;
    arg0->unk0x8 = arg1->unk0x8;
    arg0->unk0x10 = arg1->unk0x10;
    arg0->unk0x18 = arg1->unk0x18;
    arg0->unk0x20 = (s32)arg1->unk0x20;
    arg0->unk0x28 = arg1->unk0x28;
    arg0->unk0x30 = arg1->unk0x30;
    arg0->unk0x38 = arg1->unk0x38;
    arg0->unk0x40 = arg1->unk0x40;
    temp_r11->unk0x20 = (s32)temp_r10->unk0x20;
    *((f32 *)&temp_r11->unk0x28) = (f32)*((f32 *)&temp_r10->unk0x28);
    temp_r11->unk0x2C = (u16)temp_r10->unk0x2C;
    temp_r11->unk0x2E = (u16)temp_r10->unk0x2E;
    *((u16 *)&temp_r11->unk0x30) = (u16)*((u16 *)&temp_r10->unk0x30);
    temp_r11->unk0x32 = (u8)temp_r10->unk0x32;
    temp_r11->unk0x34 = (s32)temp_r10->unk0x34;
    temp_r11->unk0x38 = (s32)temp_r10->unk0x38;
    temp_r11->unk0x3C = (s32)temp_r10->unk0x3C;
    temp_r11->unk0x40 = (s32)temp_r10->unk0x40;
    temp_r11->unk0x44 = (s32)temp_r10->unk0x44;
    temp_r11->unk0x48 = (s32)temp_r10->unk0x48;
    temp_r11->unk0x4C = (u8)temp_r10->unk0x4C;
    temp_r11->unk0x4D = (u8)temp_r10->unk0x4D;
    temp_r11->unk0x50 = (s32)temp_r10->unk0x50;
    arg0->unk0x80 = (f32)arg1->unk0x80;
    temp_r3 = arg0->unk0xA8;
    arg0->unk0x88 = arg1->unk0x88;
    arg0->unk0x90 = arg1->unk0x90;
    arg0->unk0x98 = arg1->unk0x98;
    arg0->unk0xA0 = arg1->unk0xA0;
    if ((s32)temp_r3 != 0) {
        CObject_RemoveRefLink(temp_r3, temp_r29);
        arg0->unk0xA8 = 0;
    }
    temp_r3 = arg1->unk0xA8;
    arg0->unk0xA8 = temp_r3;
    if ((s32)temp_r3 != 0) {
        CObject_AddRefLink(temp_r3, temp_r29);
    }
    arg0->unk0xB4 = (s32)arg1->unk0xB4;
    arg0->unk0xB8 = (s32)arg1->unk0xB8;
    arg0->unk0xBC = (s32)arg1->unk0xBC;
    return arg0;
}
