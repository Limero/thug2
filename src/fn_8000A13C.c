// range 0x8000A13C-0x8000A19C (96B). Byte-identical.
// Identification: constructor. Calls sibling fn_80009CF4(self) to init the
// parent/node, allocates a child node via Mem_NewZero(0x18), wires the child's
// vtable (lbl_8028FFB8) and doubly-linked self-chain, and stores the child at
// self+0x28. Returns self. Same family as fn_80009B04 (which targets self+0x8).
#include "types.h"
#include "structs.h"
extern void fn_80009CF4(s32 *);
extern char lbl_8028FFB8[];
extern void *Mem_NewZero(int);
void *fn_8000A13C(void *self) {
    Unk_5EF41E38 *child;
    fn_80009CF4(self);
    child = Mem_NewZero(0x18);
    child->unk0x14 = (int)lbl_8028FFB8;
    ((Unk_E266FB50_2 *)child)->unk0x8 = 0;
    ((Unk_E266FB50_4 *)child)->unk0x4 = (int)self;
    child->unk0xC = (int)child;
    child->unk0x10 = (int)child;
    ((Unk_EB8F5E74_2 *)self)->unk0x28 = (int)child;
    return self;
}