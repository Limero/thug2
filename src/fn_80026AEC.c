// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80026AEC-0x80026B4C (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
typedef struct {
    f32 unk0x00;
    s32 unk0x04;
    s32 unk0x08;
    s32 unk0x0C;
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
    s32 unk0x24;
    s32 unk0x28;
    s32 unk0x2C;
    s32 unk0x30;
    s32 unk0x34;
    u32 f0 : 16;
    u32 f1 : 1;
    u32 f2 : 8;
    u32 f3 : 7;
} T26AEC;
extern f32 lbl_802915E4;
void *fn_80026AEC(void *arg0) {
    T26AEC *p = (T26AEC *)arg0;
    p->unk0x08 = 0;
    p->f1 = 0;
    p->f0 = 0;
    p->unk0x00 = lbl_802915E4;
    p->f2 = 0;
    p->unk0x0C = 0;
    p->unk0x10 = 0;
    p->unk0x14 = 0;
    p->unk0x18 = 0;
    p->unk0x1C = 0;
    p->unk0x2C = 0;
    p->unk0x30 = 0;
    p->unk0x28 = 0;
    p->unk0x24 = 0;
    p->unk0x20 = 0;
    return arg0;
}
