// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009CA38-0x8009CAC4 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Node {
    char pad0x0[0x04];
    s32 unk0x4;
    s32 unk0x8;
    struct Node *unk0xC;
    struct Node *unk0x10;
    void *unk0x14;
} Node;

typedef struct Inner {
    char pad0x00[0x18];
    void *unk0x18;
    void *unk0x1C;
    void *unk0x20;
} Inner;

typedef struct Obj {
    char pad0x0[0x04];
    Inner *unk0x4;
    char pad0x8[0x18];
    s32 unk0x20;
} Obj;

extern char lbl_802978C0[];
extern char lbl_802978F0[];
extern char fn_8009CB5C[];
void *Mem_NewZero(s32);
void *fn_80009B04(void *, s32);

void *fn_8009CA38(Obj *arg0) {
    Node *n;
    Inner *child;
    void *h;

    n = (Node *)((char *)arg0 + 8);
    n->unk0x4 = -1;
    n->unk0x8 = 0;
    n->unk0xC = n;
    n->unk0x10 = n;
    n->unk0x14 = (void *)lbl_802978C0;
    child = Mem_NewZero(0x24);
    h = (void *)fn_8009CB5C;
    fn_80009B04(child, -0x3E8);
    child->unk0x1C = h;
    child->unk0x20 = arg0;
    child->unk0x18 = (void *)lbl_802978F0;
    arg0->unk0x4 = child;
    arg0->unk0x20 = 0;
    return arg0;
}
