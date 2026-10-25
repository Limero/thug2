// range 0x8000D028-0x8000D0A4 (124B). Byte-identical.
// Identification: bounds-checked offset updater on a memory allocator's free
// cursor. Follows `obj = *(this+0x10)`; reads the current cursor `base =
// obj->cur` (offset 0xc), then per a 3-way operation code adjusts it:
//   0 -> set cur = value
//   1 -> cur = base + value   (advance)
//   2 -> cur = obj->end - value  (rewind)
// default -> fail. After the update it re-loads the object (this+0x10) and
// validates the new cursor is within [0, obj->end]; on overflow it restores
// `obj->cur = base` and returns -1, else returns 0. A real `switch` (not
// if/else) is required to reproduce want's comparison chain (beq case1/bgt/bne).
#include "types.h"
#include "structs.h"
s32 fn_8000D028(Unk_42076946 *p, s32 val, s32 op) {
    char *q = *((char * *)&p->unk0x10);
    s32 base = ((Unk_1D62F22E_2 *)q)->unk0xC;
    switch (op) {
    case 1:
        ((Unk_1D62F22E_2 *)q)->unk0xC = base + val;
        break;
    case 2:
        ((Unk_1D62F22E_2 *)q)->unk0xC = ((Unk_1D62F22E_2 *)q)->unk0x10 - val;
        break;
    case 0:
        ((Unk_1D62F22E_2 *)q)->unk0xC = val;
        break;
    default:
        return -1;
    }
    {
        char *t = *((char * *)&p->unk0x10);
        s32 c = ((Unk_1D62F22E_2 *)t)->unk0xC;
        if (c < 0 || c > ((Unk_1D62F22E_2 *)t)->unk0x10) {
            ((Unk_1D62F22E_2 *)t)->unk0xC = base;
            return -1;
        }
    }
    return 0;
}