// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801394E0-0x80139510 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C; s32 unk0x10;
    s32 unk0x14; s32 unk0x18; s32 unk0x1C; s32 unk0x20;
} T1394E0;
extern char lbl_8029F368[];
void *fn_801394E0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    T1394E0 *p = (T1394E0 *)arg0;
    p->unk0x08 = arg4;
    p->unk0x14 = (s32)lbl_8029F368;
    p->unk0x18 = arg1;
    p->unk0x1C = arg3;
    p->unk0x20 = arg2;
    p->unk0x04 = (s32)p;
    p->unk0x0C = (s32)p;
    p->unk0x10 = (s32)p;
    return arg0;
}
