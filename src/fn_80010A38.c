// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010A38-0x80010A68 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C;
    s32 unk0x10; s32 unk0x14; s32 unk0x18; s32 unk0x1C;
} T10A38;
extern char lbl_802906B8[];
void *fn_80010A38(void *arg0) {
    T10A38 *o = (T10A38 *)arg0;
    T10A38 *p = (T10A38 *)((char *)arg0 + 4);
    p->unk0x10 = (s32)p;
    p->unk0x04 = (s32)o;
    p->unk0x08 = 0;
    p->unk0x0C = (s32)p;
    p->unk0x14 = (s32)lbl_802906B8;
    o->unk0x1C = 0;
    return arg0;
}
