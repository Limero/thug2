// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000C44C-0x8000C534 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    s32 u0;
    void *parent;
    s32 u8;
    void *next;
    void *prev;
    void *vt;
} CNode;
extern void *Mem_NewZero(int);
extern void *memset(void *, int, int);
extern char lbl_80290220[];
extern char lbl_80290290[];
void *fn_8000C44C(Unk_7C9BF17E *self, void *a, void *b, void *c) {
    CNode *node;
    self->unk0xC4 = 0;
    self->unk0xCC = 0;
    self->unk0xEC = (s32)lbl_80290290;
    node = Mem_NewZero(0x18);
    node->parent = self;
    node->vt = lbl_80290220;
    node->u8 = 0;
    node->next = node;
    node->prev = node;
    self->unk0xE4 = (s32)a;
    self->unk0x10 = (s32)b;
    self->unk0x14 = (s32)c;
    self->unk0xDC = 0;
    self->unk0xE0 = 0;
    self->unk0xCC = 0;
    self->unk0xD4 = 0;
    self->unk0x18 = 0;
    self->unk0x4 = node;
    memset((char *)self + 0x60, 0, 0x20);
    memset((char *)self + 0x40, 0xff, 0x20);
    self->unk0x40 = 0;
    self->unk0x41 = 1;
    memset((char *)self + 0x20, 0, 0x20);
    self->unk0x1C = (self->unk0xD8 + 0x3f) & ~0x3f;
    return self;
}
