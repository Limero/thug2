// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A3C24-0x800A3C50 (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C;
    s32 unk0x10; s32 unk0x14; s32 unk0x18;
} TA3C24;
extern char lbl_80298050[];
void *fn_800A3C24(void *arg0) {
    TA3C24 *p = (TA3C24 *)arg0;
    p->unk0x18 = (s32)lbl_80298050;
    p->unk0x04 = 0;
    p->unk0x08 = 0;
    p->unk0x00 = 0;
    p->unk0x10 = 0;
    p->unk0x14 = 0;
    return arg0;
}
