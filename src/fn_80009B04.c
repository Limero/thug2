// range 0x80009B04-0x80009B80 (124B). Byte-identical.
// Identification: constructor that allocates a child node via Mem_NewZero and
// links it into a doubly-linked list rooted at self+8. Sets vtable pointers
// (lbl_8028FF00 on self, lbl_8028FF28 on child), stores arg1 into child+8, and
// chains child to itself. Returns self. ProgramData/Peer-like container node.
#include "types.h"
#include "structs.h"
extern char lbl_8028FF00[];
extern char lbl_8028FF28[];
extern void *Mem_NewZero(int);
void *fn_80009B04(Unk_5EF41E38 *self, void *arg1) {
    Unk_5EF41E38 *child;
    self->unk0x18 = (int)lbl_8028FF00;
    ((Unk_E266FB50_4 *)self)->unk0x4 = 0;
    self->unk0xC = 0;
    self->unk0x10 = 0;
    self->unk0x14 = 0;
    child = Mem_NewZero(0x18);
    child->unk0x14 = (int)lbl_8028FF28;
    ((Unk_E266FB50_2 *)child)->unk0x8 = (int)arg1;
    ((Unk_E266FB50_4 *)child)->unk0x4 = (int)self;
    child->unk0xC = (int)child;
    child->unk0x10 = (int)child;
    ((Unk_E266FB50_2 *)self)->unk0x8 = (int)child;
    return self;
}