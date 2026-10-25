// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80137BD8-0x80137C10 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C; s32 unk0x10;
    s32 unk0x14;
    u8  unk0x18;
    char _p19;
    u8  unk0x1A;
    char _p1B[0x0D];
    s32 unk0x28;
    s32 unk0x2C;
} T137BD8;
extern char lbl_8029F1C0[];
void *fn_80137BD8(void *arg0, s32 arg1) {
    T137BD8 *p = (T137BD8 *)arg0;
    p->unk0x04 = (s32)p;
    p->unk0x08 = 0;
    p->unk0x0C = (s32)p;
    p->unk0x10 = (s32)p;
    p->unk0x14 = (s32)lbl_8029F1C0;
    p->unk0x2C = arg1;
    p->unk0x1A = 0;
    p->unk0x28 = 0;
    p->unk0x18 = 0;
    return arg0;
}
