// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002DD70-0x8002DDAC (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char _p0[0x18];
    f32 unk0x18; f32 unk0x1C; f32 unk0x20; f32 unk0x24;
    s32 unk0x28; s32 unk0x2C; s32 unk0x30; s32 unk0x34;
} T2DD70;
extern f32 lbl_802918B4;
void fn_8002DD70(void *arg0) {
    T2DD70 *p = (T2DD70 *)arg0;
    p->unk0x18 = lbl_802918B4;
    p->unk0x1C = lbl_802918B4;
    p->unk0x20 = lbl_802918B4;
    p->unk0x24 = lbl_802918B4;
    p->unk0x28 = 0;
    p->unk0x2C = 1;
    p->unk0x30 = 0;
    p->unk0x34 = (s32)0xF60C9090;
}
