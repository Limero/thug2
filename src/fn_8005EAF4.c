// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005EAF4-0x8005EB38 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08;
    char _0C[4];
    s32 unk0x10;
    char _14[4];
    s8  unk0x18; s8 unk0x19; s8 unk0x1A; s8 unk0x1B;
    s32 unk0x1C;
} T5EAF4;
typedef struct {
    s8 f0; s8 f1; s8 f2; s8 f3;
} TQB5EAF4;
extern char lbl_80293B70[];
void *fn_8005EAF4(void *arg0, s32 arg1) {
    T5EAF4 *p = (T5EAF4 *)arg0;
    TQB5EAF4 *q;
    p->unk0x1C = (s32)lbl_80293B70;
    p->unk0x00 = arg1;
    p->unk0x04 = 0;
    q = (TQB5EAF4 *)((char *)arg0 + 0x18);
    p->unk0x18 = -0x80;
    q->f1 = -0x80;
    q->f2 = -0x80;
    q->f3 = -0x80;
    p->unk0x08 = 1;
    p->unk0x10 = 0;
    return arg0;
}
