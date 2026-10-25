// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801ED890-0x801ED9EC (348B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void *fn_801ED890(Unk_EA529D06 *arg0, Unk_EA529D06 *arg1) {
    Unk_64253088 *temp_r10;
    Unk_64253088 *temp_r11;
    CStruct *temp_r4;
    s32 temp_r3;

    temp_r10 = (char *)arg1 + 0x28;
    temp_r11 = (char *)arg0 + 0x28;
    temp_r4 = (char *)arg0 + 0xA8;
    arg0->unk0x0 = arg1->unk0x0;
    arg0->unk0x8 = arg1->unk0x8;
    arg0->unk0x10 = arg1->unk0x10;
    arg0->unk0x18 = arg1->unk0x18;
    arg0->unk0x20 = arg1->unk0x20;
    arg0->unk0x28 = arg1->unk0x28;
    arg0->unk0x30 = arg1->unk0x30;
    arg0->unk0x38 = arg1->unk0x38;
    arg0->unk0x40 = arg1->unk0x40;
    temp_r11->unk0x20 = temp_r10->unk0x20;
    *((f32 *)&temp_r11->unk0x28) = *((f32 *)&temp_r10->unk0x28);
    temp_r11->unk0x2C = temp_r10->unk0x2C;
    temp_r11->unk0x2E = temp_r10->unk0x2E;
    *((u16 *)&temp_r11->unk0x30) = *((u16 *)&temp_r10->unk0x30);
    temp_r11->unk0x32 = temp_r10->unk0x32;
    temp_r11->unk0x34 = temp_r10->unk0x34;
    temp_r11->unk0x38 = temp_r10->unk0x38;
    temp_r11->unk0x3C = temp_r10->unk0x3C;
    temp_r11->unk0x40 = temp_r10->unk0x40;
    temp_r11->unk0x44 = temp_r10->unk0x44;
    temp_r11->unk0x48 = temp_r10->unk0x48;
    temp_r11->unk0x4C = temp_r10->unk0x4C;
    temp_r11->unk0x4D = temp_r10->unk0x4D;
    temp_r11->unk0x50 = temp_r10->unk0x50;
    arg0->unk0x80 = arg1->unk0x80;
    arg0->unk0x88 = arg1->unk0x88;
    arg0->unk0x90 = arg1->unk0x90;
    arg0->unk0x98 = arg1->unk0x98;
    arg0->unk0xA0 = arg1->unk0xA0;
    temp_r4->unk0x4 = 0;
    temp_r4->unk0x8 = 0;
    temp_r3 = arg1->unk0xA8;
    arg0->unk0xA8 = temp_r3;
    if (temp_r3 != 0) {
        CObject_AddRefLink((void *)temp_r3, temp_r4);
    }
    arg0->unk0xB4 = arg1->unk0xB4;
    arg0->unk0xB8 = arg1->unk0xB8;
    arg0->unk0xBC = arg1->unk0xBC;
    return arg0;
}
