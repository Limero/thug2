// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800187BC-0x800187E8 (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
} Row187BC;

typedef struct {
    Row187BC rows[5];
    u16 unk0x3C;
    u16 unk0x3E;
} Table187BC;

// queue_front_2 @ 0x800187BC
Row187BC *queue_front_2(Row187BC *arg0, Table187BC *arg1) {
    Row187BC *out = arg0;
    s32 offset = arg1->unk0x3E * 0xC;
    Row187BC *row = (Row187BC *)(offset + (s32)arg1);
    *out = *row;
    return out;
}
