// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057BB4-0x80057BEC (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C;
    s32 unk0x10; s32 unk0x14; s32 unk0x18;
} T57BB4;
extern char lbl_80293350[];
void *fn_80057BB4(void *arg0) {
    T57BB4 *p = (T57BB4 *)arg0;
    p->unk0x18 = (s32)lbl_80293350;
    p->unk0x04 = 1;
    p->unk0x10 = 0;
    p->unk0x14 = 0;
    p->unk0x0C = 0;
    p->unk0x08 = (s32)0xE3714DC1;
    return arg0;
}
