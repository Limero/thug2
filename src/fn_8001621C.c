// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001621C-0x80016260 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C; s32 unk0x10;
    s32 unk0x14;
    char _p18[0x50];
    s32 unk0x68; s32 unk0x6C; s32 unk0x70; s32 unk0x74;
    s32 unk0x78; s32 unk0x7C; s32 unk0x80;
} T1621C;
extern char lbl_80290B68[];
void *fn_8001621C(void *arg0, s32 arg1, s32 arg2) {
    T1621C *p = (T1621C *)arg0;
    p->unk0x14 = (s32)lbl_80290B68;
    p->unk0x7C = arg1;
    p->unk0x04 = (s32)p;
    p->unk0x08 = 0;
    p->unk0x0C = (s32)p;
    p->unk0x80 = arg2;
    p->unk0x10 = (s32)p;
    p->unk0x68 = 0;
    p->unk0x6C = 0;
    p->unk0x70 = 0;
    p->unk0x74 = 0;
    p->unk0x78 = 0;
    return arg0;
}
