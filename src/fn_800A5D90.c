// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A5D90-0x800A5DBC (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C;
    s32 unk0x10; s32 unk0x14; s32 unk0x18;
} TA5D90;
extern char lbl_802980C8[];
void *fn_800A5D90(void *arg0) {
    TA5D90 *o = (TA5D90 *)arg0;
    TA5D90 *p;
    p = (TA5D90 *)(((char *)arg0) + 4);
    p->unk0x14 = (s32)lbl_802980C8;
    p->unk0x04 = -1;
    p->unk0x08 = 0;
    p->unk0x10 = (s32)p;
    p->unk0x0C = (s32)p;
    return arg0;
}
