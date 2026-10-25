// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80137BA4-0x80137BD8 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C; s32 unk0x10;
    s32 unk0x14; s32 unk0x18; s32 unk0x1C; s32 unk0x20;
    u8  unk0x24;
    char _p25[3];
    s32 unk0x28;
} T137BA4;
extern char lbl_8029F1D8[];
void *fn_80137BA4(void *arg0, s32 arg1) {
    T137BA4 *p = (T137BA4 *)arg0;
    p->unk0x04 = (s32)p;
    p->unk0x08 = 0;
    p->unk0x0C = (s32)p;
    p->unk0x10 = (s32)p;
    p->unk0x14 = (s32)lbl_8029F1D8;
    p->unk0x1C = arg1;
    p->unk0x28 = 0;
    p->unk0x24 = 0;
    return arg0;
}
