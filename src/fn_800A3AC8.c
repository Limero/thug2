// range 0x800A3AC8-0x800A3AE8 (0x20). Byte-identical.
// Identification: 6-field scatter-set writing 5 incoming args (+ a zero)
// into the object's first 0x14 bytes — a fixed-layout packet/keyword
// initializer. Returns the object.
//
// Matching key: return-arg0 form (recipe 249) forces the mr r9,r3 base
// copy; the store order here is want's natural order [0,4,8,0xc,0x10].
#include "types.h"
#include "structs.h"
void *fn_800A3AC8(CStruct *r, s32 a, s32 b, s32 c, s32 d) {
    r->unk0x0 = a;
    r->unk0x4 = b;
    r->unk0x8 = c;
    r->unk0xC = 0;
    r->unk0x10 = d;
    return r;
}