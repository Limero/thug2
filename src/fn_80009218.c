// range 0x80009218-0x80009264 (0x4C). Byte-identical.
// Identification: node/object ID allocator. Reads the global counter
// lbl_802FFA34[0], stores it as this node's ID at self+4, zeroes a sibling
// field at self+8, bumps the global counter, then invokes the init callback
// fn_80009314(self) and returns self. The store order mattered: self->4 = c
// must precede the global counter increment in source to match ngccc's
// emission (the reversed order swapped the two stw words).
#include "types.h"
#include "structs.h"
extern void fn_80009314(void *);
extern int lbl_802FFA34[];
void *fn_80009218(CStruct *self, s32 arg1) {
    int c = lbl_802FFA34[0];
    *((int *)&self->unk0x8) = 0;
    *((int *)&self->unk0x4) = c;
    lbl_802FFA34[0] = c + 1;
    fn_80009314(self);
    return self;
}