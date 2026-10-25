// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007787C-0x80077A34 (440B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"

typedef struct Rec Rec;
typedef struct Child Child;
typedef struct Node Node;
typedef struct Ctx Ctx;
typedef struct Entry Entry;
typedef struct List List;
typedef struct Counts Counts;
typedef struct Owner Owner;

typedef union {
    f32 f;
    s32 i;
} Bits;

struct Rec {
    u16 unk0x0;
    u16 unk0x2;
    s32 unk0x4;
    s32 unk0x8;
    char pad0xC[0x2];
    u16 unk0xE;
    f32 unk0x10;
    f32 unk0x14;
    f32 unk0x18;
};

struct Child {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    f32 unk0x10;
    f32 unk0x14;
    f32 unk0x18;
    char pad0x1C[0x4];
    Rec *unk0x20;
    char pad0x24[0x10];
    Bits unk0x34;
    char pad0x38[0x4];
    u32 unk0x3C;
};

struct Node {
    s32 unk0x0;
    u16 unk0x4;
    u16 unk0x6;
    s32 unk0x8;
    f32 unk0xC;
    s32 unk0x10;
    Child *unk0x14;
};

struct Entry {
    s32 unk0x0;
    s32 unk0x4;
    char pad0x8[0x18];
};

struct Counts {
    char pad0x0[0x12];
    u16 unk0x12;
};

struct List {
    s32 unk0x0;
    s32 unk0x4;
    Counts *unk0x8;
    char pad0xC[0x24];
    Entry *unk0x30;
};

struct Ctx {
    char pad0x0[0x18];
    void *unk0x18;
    s32 unk0x1C;
    char pad0x20[0x4];
    u32 unk0x24;
};

struct Owner {
    s32 unk0x0;
    char pad0x4[0xC];
    Ctx *unk0x10;
    char pad0x14[0x8];
    s32 unk0x1C;
};

Node *fn_8009636C(void *);
void fn_8007EA5C(Ctx *, Node *);
List *fn_8007DF14(void *);
void fn_80057C98(void *, s32);

Child *fn_8007787C(Owner *arg0, Rec *arg1) {
    Ctx *ctx = arg0->unk0x10;
    Child *base = (Child *)((char *)arg1 + 0x40);
    Child *cur;
    Node *node;
    Entry *e;
    u32 i = 0;
    u32 j;
    s32 off;
    s32 found;

    ctx->unk0x24 = arg1->unk0x0;
    off = arg1->unk0x4;
    arg1->unk0x4 = (s32)base;
    cur = (Child *)((char *)base + off);
    arg0->unk0x1C = cur->unk0x8;
    fn_80057C98(arg0, cur->unk0xC);
    while (i < ctx->unk0x24) {
        node = fn_8009636C(Mem_Alloc2(0x1C));
        fn_8007EA5C(ctx, node);
        if (cur->unk0x3C & 0x500) {
            node->unk0x4 |= 0x80;
        }
        cur->unk0x3C = 0;
        node->unk0xC = cur->unk0x34.f;
        cur->unk0x34.i = 0;
        if (cur->unk0x0 != 0) {
            node->unk0x14 = cur;
            cur->unk0x20 = arg1;
            node->unk0x6 = node->unk0x14->unk0x20->unk0xE;
            switch (node->unk0x14->unk0x20->unk0x2) {
            case 1:
            case 2:
                node->unk0x14->unk0x10 = node->unk0x14->unk0x10 + node->unk0x14->unk0x20->unk0x10;
                node->unk0x14->unk0x14 = node->unk0x14->unk0x14 + node->unk0x14->unk0x20->unk0x14;
                node->unk0x14->unk0x18 = node->unk0x14->unk0x18 + node->unk0x14->unk0x20->unk0x18;
                break;
            }
            found = 0;
            cur = (Child *)((char *)cur + (cur->unk0x0 + 0x40));
            e = fn_8007DF14(ctx->unk0x18)->unk0x30;
            j = 0;
            while (j < fn_8007DF14(ctx->unk0x18)->unk0x8->unk0x12) {
                if (e->unk0x0 == node->unk0x14->unk0x4) {
                    node->unk0x14->unk0x4 = (s32)e;
                    found = 1;
                    break;
                }
                e++;
                j++;
            }
            if (found == 0) {
                node->unk0x14->unk0x4 = 0;
            }
        }
        i++;
    }
    return cur;
}
