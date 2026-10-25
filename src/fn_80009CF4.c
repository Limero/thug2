// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009CF4-0x80009D30 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C; s32 unk0x10;
    s32 unk0x14; s32 unk0x18; s32 unk0x1C; s32 unk0x20; s32 unk0x24;
} T9CF4;
typedef struct {
    s32 unk0x00; s32 unk0x04; s32 unk0x08; s32 unk0x0C; s32 unk0x10;
    s32 unk0x14;
} T9CF4P;
extern char lbl_8028FF58[];
void *fn_80009CF4(void *arg0) {
    T9CF4 *o = (T9CF4 *)arg0;
    T9CF4P *p;
    o->unk0x04 = 0;
    p = (T9CF4P *)((char *)arg0 + 8);
    p->unk0x14 = (s32)lbl_8028FF58;
    p->unk0x04 = -1;
    p->unk0x0C = (s32)p;
    p->unk0x10 = (s32)p;
    p->unk0x08 = 0;
    o->unk0x20 = 0;
    o->unk0x24 = 0;
    return arg0;
}
