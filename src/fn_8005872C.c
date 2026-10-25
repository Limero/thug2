// range 0x8005872C-0x80058750 (0x24). Byte-identical.
// Identification: halfword field initializer — sets five u16 fields
// (0x4000 active flags at +6/+4, zeros elsewhere), returning the object.
//
// Matching key (recipe 253): halfword stores also need permutation —
// want's order [8,6,0,2,4] is produced by source [0,2,8,4,6] + return
// arg0 (found by brute-forcing all 5! halfword-store orders).
#include "types.h"
#include "structs.h"
void *fn_8005872C(Unk_2BAD2BE8 *r) {
    r->unk0x0 = 0;
    r->unk0x2 = 0;
    r->unk0x8 = 0;
    r->unk0x4 = 0x4000;
    r->unk0x6 = 0x4000;
    return r;
}