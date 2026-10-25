// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80206F7C-0x80207030 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern s32 fn_800145AC(void);

void *fn_80206F7C(Unk_90685748 *arg0, s32 arg1) {
    s32 temp_r9;
    u16 temp_r9_2;
    char *b1;
    char *b2;
    char *b3;
    char *b4;
    s32 ts;
    s32 *p;

    temp_r9 = arg0->unk0x99E + 1;
    arg0->unk0x99E = temp_r9;
    if ((u16)temp_r9 > 0x63U) {
        arg0->unk0x99E = 0;
    }
    temp_r9_2 = arg0->unk0x99C;
    if (temp_r9_2 <= 0x63U) {
        arg0->unk0x99C = temp_r9_2 + 1;
    }
    b1 = (char *)arg0 + 0x40;
    *(s32 *)(b1 + (arg0->unk0x99E) * 0x18) = arg1;
    ts = fn_800145AC();
    b2 = (char *)arg0 + 0x3C;
    b3 = (char *)arg0 + 0x4C;
    b4 = (char *)arg0 + 0x50;
    p = (s32 *)(b2 + (arg0->unk0x99E) * 0x18);
    *p = ts;
    p = (s32 *)(b3 + (arg0->unk0x99E) * 0x18);
    *p = 0;
    p = (s32 *)(b4 + (arg0->unk0x99E) * 0x18);
    *p = 0;
    return (void *)((char *)arg0 + ((arg0->unk0x99E) * 0x18 + 0x3C));
}
